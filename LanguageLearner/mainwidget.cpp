#include "mainwidget.h"
#include "ui_mainwidget.h"

#include<QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    resize(600,400);
    mainSwitch(0);
    interfaceSwitch(0);

    connect(ui->Interface_,&Interface::examine,[=](){mainSwitch(2);});
    connect(ui->ExamineWidget_,&ExamineWidget::end,[=](){mainSwitch(0);});
    connect(ui->SearchingWidget_,&SearchingWidget::search,[=](QString _str_){interfaceSwitch(_str_==""?0:1);});
    connect(ui->SearchingResult_,&SearchingResult::check,[=](){mainSwitch(1);});
    connect(ui->DisplayWidget_,&DisplayWidget::back,[=](){mainSwitch(0);});
    connect(ui->SearchingWidget_,&SearchingWidget::addWord,[=](){mainSwitch(1);});
    connect(ui->SearchingWidget_,&SearchingWidget::addWord,
            [=](){
        ui->DisplayWidget_->setWord(Word());
        ui->DisplayWidget_->setMode(1);
    });
    connect(ui->DisplayWidget_,&DisplayWidget::save,[=](QString _str_){
        Word word=ui->DisplayWidget_->getWord();
        if(!wordlist_.countWord(_str_))
            wordlist_.addWord(word.word(),new Word(word));
        else wordlist_.editWord(_str_,new Word(word));
        qDebug()<<"====wordlist====";
        wordlist_.debug_ShowWord();
    });

    connect(ui->SearchingWidget_,&SearchingWidget::search,[=](QString _str_){
        ui->SearchingResult_->setWordList(wordlist_.searchWords(_str_));
    });
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::mainSwitch(int _index_){
    if(_index_<0||_index_>=3) return;
	ui->MainStackedWidget_->setCurrentIndex(_index_);
}
void MainWidget::interfaceSwitch(int _index_){
    if(_index_<0||_index_>=2) return;
	ui->StackedWidget_->setCurrentIndex(_index_);
}
