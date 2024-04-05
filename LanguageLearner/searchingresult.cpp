#include "searchingresult.h"
#include "ui_searchingresult.h"

#include<wordbox.h>
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
        boxlist_.append(new WordBox(ui->scrollAreaWidget_,70));
        boxlist_[i]->setWord(*it);
        boxlist_[i]->setPlace(i);
        boxlist_[i]->showWord();
        connect(boxlist_[i],&WordBox::clicked,[=](){
            emit check(*it);
        });
        connect(boxlist_[i],&WordBox::deleted,[=](){
            emit deleted(*it);
        });
        boxlist_[i]->show();
        it++;
    }
}
