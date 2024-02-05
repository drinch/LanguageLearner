#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    connect(ui->Interface_,&Interface::examine,
            [=](){
        mainSwitch(3);
    });
    connect(ui->ExamineWidget_,&ExamineWidget::end,
            [=](){
        mainSwitch(1);
    });
    connect(ui->SearchingWidget_,&SearchingWidget::search,
            [=](QString _str_){
        interfaceSwitch(_str_==""?1:2);
    });
    connect(ui->SearchingResult_,&SearchingResult::check,
            [=](){
        mainSwitch(2);
    });
    connect(ui->DisplayWidget_,&DisplayWidget::back,
            [=](){
        mainSwitch(1);
    });
    connect(ui->SearchingWidget_,&SearchingWidget::addWord,
            [=](){
        mainSwitch(2);
    });
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::mainSwitch(int _index_){
	if(_index_<1||_index_>3) return;
	ui->MainStackedWidget_->setCurrentIndex(_index_);
}
void MainWidget::interfaceSwitch(int _index_){
	if(_index_<1||_index_>2) return;
	ui->StackedWidget_->setCurrentIndex(_index_);
}
