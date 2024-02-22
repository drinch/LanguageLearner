#include "displaywidget.h"
#include "ui_displaywidget.h"

#include<QLabel>
#include<QLineEdit>
#include<QDebug>

DisplayWidget::DisplayWidget(QWidget *parent) :
	QWidget(parent),
    ui(new Ui::DisplayWidget),
    running_(0),editmode_(0),
    height_(70)
{
    ui->setupUi(this);

    title_=new QLineEdit(ui->MainWidget_);
    additionalproperty_=new QLineEdit(ui->MainWidget_);
    addbutton_=new QPushButton("添加属性",ui->MainWidget_);

    setMH(height_);
    title_->resize(width()-10,60);
    qDebug()<<title_->width();
    title_->move(5,5);
    title_->setReadOnly(1);
    title_->show();
    additionalproperty_->resize(62,60);
    additionalproperty_->move(5,70+5);
    addbutton_->resize(width()-78,60);
    addbutton_->move(73,70+5);
    connect(addbutton_,&QPushButton::clicked,[=](){
        addProperty(additionalproperty_->text(),"");
        additionalproperty_->setText("");
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
            word_.setWord(title_->text());
            qDebug()<<"set title";
            for(int i=0;i<properties_.size();i++){
                if(word_.countProperty(properties_[i])){
                    word_.deleteProperty(properties_[i]);
                }
            }
            qDebug()<<"deleted properties";
            for(int i=0;i<numberOfP();i++){
                if(!word_.countProperty(keyofproperties_[i]->text()))
                    word_.addProperty(keyofproperties_[i]->text(),valueofproperties_[i]->text());
                else word_.editProperty(keyofproperties_[i]->text(),valueofproperties_[i]->text());
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
    if(!running_) return Word();
    return word_;
}

void DisplayWidget::setWord(const Word _word_){
    if(running_) return;
    running_=1;
    word_=_word_;
    setInterfaceWord();
    if(editmode_) changeMode();
}
void DisplayWidget::setMode(int _mode_){
    editmode_=_mode_;
    if(!running_) return;
    changeMode();
}

void DisplayWidget::setInterfaceWord(){
    title_->setText(word_.word());
    for(auto pro:word_.properties()){
        addProperty(pro,word_.property(pro));
    }
}
void DisplayWidget::changeMode(){
    if(editmode_){
        title_->setReadOnly(0);
        setMH(numberOfP()*70+70);
        additionalproperty_->show();
        addbutton_->show();
        for(int i=0;i<numberOfP();i++){
            valueofproperties_[i]->resize(width()-146,60);
            valueofproperties_[i]->setReadOnly(0);
            button_[i]->show();
        }
    }else{
        title_->setReadOnly(1);
        setMH(numberOfP()*70+70);
        additionalproperty_->hide();
        addbutton_->hide();
        for(int i=0;i<numberOfP();i++){
            valueofproperties_[i]->resize(width()-78,60);
            valueofproperties_[i]->setReadOnly(1);
            button_[i]->hide();
        }
    }
}
void DisplayWidget::deleteInterface(){
    running_=0;
    for(int i=0;i<numberOfP();i++){
        delete keyofproperties_[i];
        delete valueofproperties_[i];
        delete button_[i];
    }
    keyofproperties_.clear();
    valueofproperties_.clear();
    button_.clear();
    title_->setText("");
    additionalproperty_->setText("");
    additionalproperty_->move(5,70+5);
    addbutton_->move(73,70+5);
    setMH(height_);
}

void DisplayWidget::addProperty(QString _key_,QString _value_){
    int i=numberOfP(),y=height_*(i+1);

    keyofproperties_.append(new QLineEdit(_key_,ui->MainWidget_));
    keyofproperties_[i]->resize(62,60);
    keyofproperties_[i]->move(5,y+5);
    keyofproperties_[i]->setReadOnly(1);
    keyofproperties_[i]->show();

    valueofproperties_.append(new QLineEdit(_value_,ui->MainWidget_));
    valueofproperties_[i]->resize(width()-(editmode_?146:78),60);
    valueofproperties_[i]->move(73,y+5);
    if(!editmode_) valueofproperties_[i]->setReadOnly(1);
    valueofproperties_[i]->show();

    button_.append(new QPushButton("x",ui->MainWidget_));
    button_[i]->resize(62,60);
    button_[i]->move(width()-67,y+5);
    connect(button_[i],&QPushButton::clicked,[=](){
        deleteProperty(i);
    });
    if(editmode_) button_[i]->show();

    additionalproperty_->move(additionalproperty_->x(),additionalproperty_->y()+70);
    addbutton_->move(addbutton_->x(),addbutton_->y()+70);
    setMH((numberOfP()+(editmode_?2:1))*70);
}
void DisplayWidget::deleteProperty(int _index_){
    properties_.append(keyofproperties_[_index_]->text());
    delete keyofproperties_[_index_];
    delete valueofproperties_[_index_];
    delete button_[_index_];
    for(int i=_index_+1;i<numberOfP();i++){
        keyofproperties_[i]->move(keyofproperties_[i]->x(),keyofproperties_[i]->y()-70);
        valueofproperties_[i]->move(valueofproperties_[i]->x(),valueofproperties_[i]->y()-70);
        button_[i]->move(button_[i]->x(),button_[i]->y()-70);
        button_[i]->disconnect();
        connect(button_[i],&QPushButton::clicked,[=](){
            deleteProperty(i-1);
        });
        keyofproperties_[i-1]=keyofproperties_[i];
        valueofproperties_[i-1]=valueofproperties_[i];
        button_[i-1]=button_[i];
    }
    keyofproperties_.pop_back();
    valueofproperties_.pop_back();
    button_.pop_back();
    additionalproperty_->move(additionalproperty_->x(),additionalproperty_->y()-70);
    addbutton_->move(addbutton_->x(),addbutton_->y()-70);
    setMH(numberOfP()*70+70);
}

int DisplayWidget::numberOfP(){
    return keyofproperties_.size();
}
void DisplayWidget::setMH(int _height_){
    ui->MainWidget_->setMinimumHeight(_height_);
}

void DisplayWidget::resizeW(){
    title_->resize(width()-10,title_->height());
    for(auto vop:valueofproperties_){
        vop->resize(width()-(editmode_?146:78),vop->height());
    }
    for(auto btn:button_){
        btn->move(width()-67,btn->y());
    }
    addbutton_->resize(width()-78,addbutton_->height());
}

void DisplayWidget::resizeEvent(QResizeEvent *event){
    qDebug()<<"resizeEvent";
    resizeW();
}
