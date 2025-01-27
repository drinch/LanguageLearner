#include "searchingresult.h"
#include "ui_searchingresult.h"

#include<wordcard.h>
#include<QDebug>

SearchingResult::SearchingResult(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SearchingResult)
{
	ui->setupUi(this);
}

SearchingResult::~SearchingResult()
{
	delete ui;
}

void SearchingResult::setWordList(QList<Word> _list_){

    WordList_=_list_;
    ui->scrollAreaWidget_->setMinimumHeight(70*WordList_.size()+6);//设置窗口高度

    //清空已有窗口
    for(auto _Card:CardList_){
        delete _Card;
    }
    CardList_.clear();

    QList<Word>::iterator it=WordList_.begin();
    for(int i=0;i<WordList_.size();i++){
        CardList_.append(new WordCard(ui->scrollAreaWidget_));

        //设置窗口大小和位置
        CardList_[i]->resize(ui->scrollAreaWidget_->width()-10,66);
        CardList_[i]->move(5,70*i+5);

        CardList_[i]->setWord(*it);
        CardList_[i]->showWord();

        connect(CardList_[i],&WordCard::clicked,[=](){
            emit check(*it);
        });
        connect(CardList_[i],&WordCard::deleted,[=](){
            emit deleted(*it);
        });
        CardList_[i]->show();
        it++;
    }
}
