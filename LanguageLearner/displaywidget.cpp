#include "displaywidget.h"
#include "ui_displaywidget.h"

#include<QLabel>
#include<QLineEdit>

DisplayWidget::DisplayWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DisplayWidget)
{
	ui->setupUi(this);

    connect(ui->ReturnButton_,&QPushButton::clicked,[=](){back();});
}

DisplayWidget::~DisplayWidget()
{
	delete ui;
}

void DisplayWidget::setMode(int _mode_){
    if(_mode_) editmode_=1;
    else editmode_=0;
}
void DisplayWidget::setWord(Word* _word_){
    word_=_word_;
    showWord();
}

void DisplayWidget::showWord(){
    int num=word_->propertyNumber();
    ui->MainWidget_->setMinimumHeight(num*70+70);
    if(editmode_){
        title_=new QLineEdit(ui->MainWidget_);
        properties_.resize(num*2+1);
        for(int i=0;i<num;i++){
            properties_[i]=new QLineEdit(ui->MainWidget_);
            properties_[i+num]=new QLineEdit(ui->MainWidget_);
        }
        properties_[2*num]=new QPushButton("添加",ui->MainWidget_);
        properties_[2*num]->resize(width()-10,60);
        properties_[2*num]->move(5,70*num+75);
        properties_[2*num]->show();
    }else{
        title_=new QLabel(ui->MainWidget_);
        properties_.resize(num*2);
        for(int i=0;i<num;i++){
            properties_[i]=new QLabel(ui->MainWidget_);
            properties_[i+num]=new QLabel(ui->MainWidget_);
        }
    }
    title_->resize(width()-10,60);
    title_->move(5,5);
    title_->show();
    for(int i=0;i>num;i++){
        properties_[i]->resize(60,60);
        properties_[i+num]->resize(width()-80,60);
        properties_[i]->move(5,70*i+75);
        properties_[i+num]->move(75,70*i+75);
        properties_[i]->show();
        properties_[i+num]->show();
    }
}
