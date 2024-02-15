#include "searchingresult.h"
#include "ui_searchingresult.h"

#include<wordbox.h>

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

void SearchingResult::setWordList(QList<QString> _list_){
    wordlist_=_list_;
    QList<QString>::iterator it=wordlist_.begin();
    for(int i=0;i<wordlist_.size();i++){
        WordBox* box=new WordBox(this,70);
        box->setWord(*it);
        box->setPlace(i);
        box->showWord();
        box->show();
        it++;
    }
}
