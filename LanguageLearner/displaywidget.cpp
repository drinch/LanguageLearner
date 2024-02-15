#include "displaywidget.h"
#include "ui_displaywidget.h"

#include<QLabel>
#include<QLineEdit>

DisplayWidget::DisplayWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DisplayWidget)
{
	ui->setupUi(this);

    editmode_=0;
    word_=wordcopy_=nullptr;

    connect(ui->ReturnButton_,&QPushButton::clicked,[=](){
        if(wordcopy_!=nullptr) delete wordcopy_;
        word_=wordcopy_=nullptr;
        deleteInterface();
        back();
    });
    connect(ui->EditButton_,&QPushButton::clicked,[=](){
        if(!editmode_){
            wordcopy_=new Word(*word_);
        }else{
            QString wordstr=wordcopy_->word();
            wordcopy_->setWord(interface_[0]->text());
            for(int i=0;i<properties_.size();i++){
                if(wordcopy_->countProperty(properties_[i])){
                    wordcopy_->deleteProperty(properties_[i]);
                }
            }
            for(int i=1;i<interface_.size()/2;i++){
                if(!wordcopy_->countProperty(interface_[i*2]->text()))
                    wordcopy_->addProperty(interface_[i*2]->text(),interface_[i*2+1]->text());
                else wordcopy_->editProperty(interface_[i*2]->text(),interface_[i*2+1]->text());
            }
            save(wordstr,wordcopy_);
            word_=wordcopy_;
            wordcopy_=nullptr;
        }
        setMode(!editmode_);
    });
}

DisplayWidget::~DisplayWidget()
{
	delete ui;
}

void DisplayWidget::setWord(Word* _word_){
    word_=_word_;
    if(editmode_) wordcopy_=new Word(*_word_);
    createInterface();
    QList<QString> propertieslist=word_->properties();
    for(int i=0;i<propertieslist.size();i++){
        addProperty(propertieslist[i],word_->property(propertieslist[i]));
    }
}
void DisplayWidget::setMode(int _mode_){
    if(_mode_!=0) {
        editmode_=1;
        wordcopy_=new Word(*word_);
    }
    else editmode_=0;
    if(word_==nullptr) return;
    setInterface();
}

void DisplayWidget::createInterface(){
    ui->MainWidget_->setMinimumHeight(70*2);
    interface_.append(new QLineEdit(word_->word(),ui->MainWidget_));
    interface_.append(new QLineEdit(ui->MainWidget_));
    interface_[0]->resize(width()-10,60);
    interface_[0]->move(5,5);
    interface_[0]->setReadOnly(!editmode_);
    interface_[0]->show();
    interface_[1]->resize(62,60);
    interface_[1]->move(5,70+5);
    button_.append(new QPushButton("添加",ui->MainWidget_));
    button_[0]->resize(width()-78,60);
    button_[0]->move(73,70+5);
    connect(button_[0],&QPushButton::clicked,[=](){
        addProperty(interface_[1]->text(),"");
        interface_[1]->setText("");
    });
    if(editmode_){
        interface_[1]->show();
        button_[0]->show();
    }
}
void DisplayWidget::setInterface(){
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
    for(int i=0;i<interface_.size();i++){
        delete interface_[i];
    }
    for(int i=0;i<button_.size();i++){
        delete button_[i];
    }
    interface_.clear();
    button_.clear();
    ui->MainWidget_->setMinimumHeight(0);
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
