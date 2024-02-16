#include "displaywidget.h"
#include "ui_displaywidget.h"

#include<QLabel>
#include<QLineEdit>
#include<QDebug>

DisplayWidget::DisplayWidget(QWidget *parent) :
	QWidget(parent),
    ui(new Ui::DisplayWidget),
    running(0),editmode_(0)
{
    ui->setupUi(this);

    ui->MainWidget_->setMinimumHeight(70*2);
    interface_.append(new QLineEdit(word_.word(),ui->MainWidget_));
    interface_.append(new QLineEdit(ui->MainWidget_));
    interface_[0]->resize(width()-10,60);
    interface_[0]->move(5,5);
    interface_[0]->setReadOnly(1);
    interface_[0]->show();
    interface_[1]->resize(62,60);
    interface_[1]->move(5,70+5);
    button_.append(new QPushButton("添加属性",ui->MainWidget_));
    button_[0]->resize(width()-78,60);
    button_[0]->move(73,70+5);
    connect(button_[0],&QPushButton::clicked,[=](){
        addProperty(interface_[1]->text(),"");
        interface_[1]->setText("");
    });

    connect(ui->ReturnButton_,&QPushButton::clicked,[=](){
        word_=Word();
        deleteInterface();
        back();
    });
    connect(ui->EditButton_,&QPushButton::clicked,[=](){
        qDebug()<<"clicked";
        if(editmode_){
            QString wordstr=word_.word();
            word_.setWord(interface_[0]->text());
            qDebug()<<"set title";
            for(int i=0;i<properties_.size();i++){
                if(word_.countProperty(properties_[i])){
                    word_.deleteProperty(properties_[i]);
                }
            }
            qDebug()<<"deleted properties";
            for(int i=1;i<interface_.size()/2;i++){
                if(!word_.countProperty(interface_[i*2]->text()))
                    word_.addProperty(interface_[i*2]->text(),interface_[i*2+1]->text());
                else word_.editProperty(interface_[i*2]->text(),interface_[i*2+1]->text());
            }
            qDebug()<<"add properties";
            save(wordstr);
            qDebug()<<"saved";
        }
        setMode(!editmode_);
    });
}

DisplayWidget::~DisplayWidget()
{
	delete ui;
}

Word DisplayWidget::getWord()const{
    if(!running) return Word();
    return word_;
}

void DisplayWidget::setWord(const Word _word_){
    if(running) return;
    running=1;
    word_=_word_;
    setInterfaceWord();
}
void DisplayWidget::setMode(int _mode_){
    if(!running) return;
    editmode_=_mode_;
    setInterfaceMode();
}

void DisplayWidget::setInterfaceWord(){
    interface_[0]->setText(word_.word());
    for(auto pro:word_.properties()){
        addProperty(pro,word_.property(pro));
    }
}
void DisplayWidget::setInterfaceMode(){
    if(editmode_){
        interface_[0]->setReadOnly(0);
        ui->MainWidget_->setMinimumHeight(interface_.size()/2*70+70);
        interface_[1]->show();
        button_[0]->show();
        for(int i=1;i<interface_.size()/2;i++){
            interface_[2*i+1]->resize(width()-146,60);
            interface_[2*i+1]->setReadOnly(0);
            button_[i]->show();
        }
    }else{
        interface_[0]->setReadOnly(1);
        ui->MainWidget_->setMinimumHeight((interface_.size()/2-1)*70+70);
        interface_[1]->hide();
        button_[0]->hide();
        for(int i=1;i<interface_.size()/2;i++){
            interface_[2*i+1]->resize(width()-78,60);
            interface_[2*i+1]->setReadOnly(1);
            button_[i]->hide();
        }
    }
}
void DisplayWidget::deleteInterface(){
    running=0;
    for(int i=2;i<interface_.size();i++){
        delete interface_[i];
    }
    for(int i=1;i<button_.size();i++){
        delete button_[i];
    }
    interface_.resize(2);
    button_.resize(1);
    interface_[0]->setText("");
    interface_[1]->setText("");
    ui->MainWidget_->setMinimumHeight(70*2);
}

void DisplayWidget::addProperty(QString _key_,QString _value_){
    int i=interface_.size()/2,x=interface_[1]->x(),y=interface_[1]->y();
    interface_.append(new QLineEdit(_key_,ui->MainWidget_));
    interface_.append(new QLineEdit(_value_,ui->MainWidget_));
    interface_[i*2]->resize(62,60);
    interface_[i*2]->move(x,y);
    interface_[i*2]->setReadOnly(1);
    interface_[i*2]->show();
    interface_[i*2+1]->resize(width()-(editmode_?146:78),60);
    interface_[i*2+1]->move(x+68,y);
    if(!editmode_) interface_[i*2+1]->setReadOnly(1);
    interface_[i*2+1]->show();
    button_.append(new QPushButton("x",ui->MainWidget_));
    button_[i]->resize(62,60);
    button_[i]->move(width()-67,y);
    connect(button_[i],&QPushButton::clicked,[=](){
        deleteProperty(i);
    });
    if(editmode_) button_[i]->show();
    interface_[1]->move(interface_[1]->x(),interface_[1]->y()+70);
    button_[0]->move(button_[0]->x(),button_[0]->y()+70);
    ui->MainWidget_->setMinimumHeight(button_.size()*70+70);
}
void DisplayWidget::deleteProperty(int _index_){
    properties_.append(interface_[_index_*2]->text());
    delete interface_[_index_*2];
    delete interface_[_index_*2+1];
    delete button_[_index_];
    for(int i=_index_+1;i<interface_.size()/2;i++){
        interface_[i*2]->move(interface_[i*2]->x(),interface_[i*2]->y()-70);
        interface_[i*2+1]->move(interface_[i*2+1]->x(),interface_[i*2+1]->y()-70);
        button_[i]->move(button_[i]->x(),button_[i]->y()-70);
        button_[i]->disconnect();
        connect(button_[i],&QPushButton::clicked,[=](){
            deleteProperty(i-1);
        });
        interface_[i*2-2]=interface_[i*2];
        interface_[i*2-1]=interface_[i*2+1];
        button_[i-1]=button_[i];
    }
    interface_.pop_back();
    interface_.pop_back();
    button_.pop_back();
    interface_[1]->move(interface_[1]->x(),interface_[1]->y()-70);
    button_[0]->move(button_[0]->x(),button_[0]->y()-70);
    ui->MainWidget_->setMinimumHeight(button_.size()*70+70);
}
