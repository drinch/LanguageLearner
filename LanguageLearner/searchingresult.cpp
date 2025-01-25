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
    wordlist_=_list_;
    ui->scrollAreaWidget_->setMinimumHeight(70*wordlist_.size()+6);
    for(auto box:boxlist_){
        delete box;
    }
    boxlist_.clear();
    QList<Word>::iterator it=wordlist_.begin();
    for(int i=0;i<wordlist_.size();i++){
        boxlist_.append(new WordCard(ui->scrollAreaWidget_));

        //设置单词卡片大小及位置
        int _totleHeight=66,_topMargin=5,_sideMargins=5,_verticalSpace=4;
        int _height=_totleHeight-_verticalSpace;
        boxlist_[i]->resize(ui->scrollAreaWidget_->width()-2*_sideMargins,_height);//水平边距5，竖直间距4
        boxlist_[i]->move(_sideMargins,_topMargin+i*70);//顶端边距5
        //重写resizeEvent保证改变窗口大小的时候单词卡片随之改变

        qDebug()<<boxlist_[i]->width()<<" : "<<ui->scrollAreaWidget_->width();

        boxlist_[i]->setWord(*it);
        //boxlist_[i]->setPlace(i);
        boxlist_[i]->showWord();
        connect(boxlist_[i],&WordCard::clicked,[=](){
            emit check(*it);
        });
        connect(boxlist_[i],&WordCard::deleted,[=](){
            emit deleted(*it);
        });
        boxlist_[i]->show();
        it++;
    }
}

void SearchingResult::resizeEvent(QResizeEvent *event){
    for(int i=0;i<wordlist_.size();i++){

        //设置单词卡片大小及位置
        int _totleHeight=66,_topMargin=5,_sideMargins=5,_verticalSpace=4;
        int _height=_totleHeight-_verticalSpace;
        boxlist_[i]->resize(ui->scrollAreaWidget_->width()-2*_sideMargins,_height);//水平边距5，竖直间距4
        boxlist_[i]->move(_sideMargins,_topMargin+i*70);//顶端边距5
    }
}
