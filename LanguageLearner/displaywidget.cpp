#include "displaywidget.h"
#include "ui_displaywidget.h"

#include<QLabel>
#include<QLineEdit>
#include<QDebug>

DisplayWidget::DisplayWidget(QWidget *parent) :
	QWidget(parent),
    ui(new Ui::DisplayWidget),
    Running_(0),EditMode_(0),
    Height_(70)
{
    ui->setupUi(this);

    Title_=new QLineEdit(ui->MainWidget_);
    NewProperty_=new QLineEdit(ui->MainWidget_);
    AddButton_=new QPushButton("添加属性",ui->MainWidget_);

    setMH(Height_);
    Title_->resize(width()-10,60);
    qDebug()<<Title_->width();
    Title_->move(5,5);
    Title_->setReadOnly(1);
    Title_->show();
    NewProperty_->resize(62,60);
    NewProperty_->move(5,70+5);
    AddButton_->resize(width()-78,60);
    AddButton_->move(73,70+5);
    connect(AddButton_,&QPushButton::clicked,[=](){
        addProperty(NewProperty_->text(),"");
        NewProperty_->setText("");
    });

    connect(ui->ReturnButton_,&QPushButton::clicked,[=](){
        Word_=Word();
        deleteInterface();
        back();
    });
    connect(ui->EditButton_,&QPushButton::clicked,[=](){
        qDebug()<<"clicked";
        if(EditMode_){
            QString wordstr=Word_.word();
            Word_.setWord(Title_->text());
            qDebug()<<"set title";
            for(int i=0;i<Properties_.size();i++){
                if(Word_.countProperty(Properties_[i])){
                    Word_.deleteProperty(Properties_[i]);
                }
            }
            qDebug()<<"deleted properties";
            for(int i=0;i<numberOfP();i++){
                if(!Word_.countProperty(KeyOfProperties_[i]->text()))
                    Word_.addProperty(KeyOfProperties_[i]->text(),ValueOfProperties_[i]->text());
                else Word_.editProperty(KeyOfProperties_[i]->text(),ValueOfProperties_[i]->text());
            }
            qDebug()<<"add properties";
            save(wordstr);
            qDebug()<<"saved";
        }
        setMode(!EditMode_);
    });
}

DisplayWidget::~DisplayWidget()
{
	delete ui;
}

Word DisplayWidget::getWord()const{
    if(!Running_) return Word();
    return Word_;
}

void DisplayWidget::setWord(const Word _word_){
    if(Running_) return;
    Running_=1;
    Word_=_word_;
    setInterfaceWord();
    if(EditMode_) changeMode();
}
void DisplayWidget::setMode(int _mode_){
    EditMode_=_mode_;
    if(!Running_) return;
    changeMode();
}

void DisplayWidget::setInterfaceWord(){
    Title_->setText(Word_.word());
    for(auto pro:Word_.properties()){
        addProperty(pro,Word_.property(pro));
    }
}
void DisplayWidget::changeMode(){
    if(EditMode_){
        Title_->setReadOnly(0);
        setMH(numberOfP()*70+70);
        NewProperty_->show();
        AddButton_->show();
        for(int i=0;i<numberOfP();i++){
            ValueOfProperties_[i]->resize(width()-146,60);
            ValueOfProperties_[i]->setReadOnly(0);
            PropertyButton_[i]->show();
        }
    }else{
        Title_->setReadOnly(1);
        setMH(numberOfP()*70+70);
        NewProperty_->hide();
        AddButton_->hide();
        for(int i=0;i<numberOfP();i++){
            ValueOfProperties_[i]->resize(width()-78,60);
            ValueOfProperties_[i]->setReadOnly(1);
            PropertyButton_[i]->hide();
        }
    }
}
void DisplayWidget::deleteInterface(){
    Running_=0;
    for(int i=0;i<numberOfP();i++){
        delete KeyOfProperties_[i];
        delete ValueOfProperties_[i];
        delete PropertyButton_[i];
    }
    KeyOfProperties_.clear();
    ValueOfProperties_.clear();
    PropertyButton_.clear();
    Title_->setText("");
    NewProperty_->setText("");
    NewProperty_->move(5,70+5);
    AddButton_->move(73,70+5);
    setMH(Height_);
}

void DisplayWidget::addProperty(QString _key_,QString _value_){
    int i=numberOfP(),y=Height_*(i+1);

    KeyOfProperties_.append(new QLineEdit(_key_,ui->MainWidget_));
    KeyOfProperties_[i]->resize(62,60);
    KeyOfProperties_[i]->move(5,y+5);
    KeyOfProperties_[i]->setReadOnly(1);
    KeyOfProperties_[i]->show();

    ValueOfProperties_.append(new QLineEdit(_value_,ui->MainWidget_));
    ValueOfProperties_[i]->resize(width()-(EditMode_?146:78),60);
    ValueOfProperties_[i]->move(73,y+5);
    if(!EditMode_) ValueOfProperties_[i]->setReadOnly(1);
    ValueOfProperties_[i]->show();

    PropertyButton_.append(new QPushButton("x",ui->MainWidget_));
    PropertyButton_[i]->resize(62,60);
    PropertyButton_[i]->move(width()-67,y+5);
    connect(PropertyButton_[i],&QPushButton::clicked,[=](){
        deleteProperty(i);
    });
    if(EditMode_) PropertyButton_[i]->show();

    NewProperty_->move(NewProperty_->x(),NewProperty_->y()+70);
    AddButton_->move(AddButton_->x(),AddButton_->y()+70);
    setMH((numberOfP()+(EditMode_?2:1))*70);
}
void DisplayWidget::deleteProperty(int _index_){
    Properties_.append(KeyOfProperties_[_index_]->text());
    delete KeyOfProperties_[_index_];
    delete ValueOfProperties_[_index_];
    delete PropertyButton_[_index_];
    for(int i=_index_+1;i<numberOfP();i++){
        KeyOfProperties_[i]->move(KeyOfProperties_[i]->x(),KeyOfProperties_[i]->y()-70);
        ValueOfProperties_[i]->move(ValueOfProperties_[i]->x(),ValueOfProperties_[i]->y()-70);
        PropertyButton_[i]->move(PropertyButton_[i]->x(),PropertyButton_[i]->y()-70);
        PropertyButton_[i]->disconnect();
        connect(PropertyButton_[i],&QPushButton::clicked,[=](){
            deleteProperty(i-1);
        });
        KeyOfProperties_[i-1]=KeyOfProperties_[i];
        ValueOfProperties_[i-1]=ValueOfProperties_[i];
        PropertyButton_[i-1]=PropertyButton_[i];
    }
    KeyOfProperties_.pop_back();
    ValueOfProperties_.pop_back();
    PropertyButton_.pop_back();
    NewProperty_->move(NewProperty_->x(),NewProperty_->y()-70);
    AddButton_->move(AddButton_->x(),AddButton_->y()-70);
    setMH(numberOfP()*70+70);
}

int DisplayWidget::numberOfP(){
    return KeyOfProperties_.size();
}
void DisplayWidget::setMH(int _height_){
    ui->MainWidget_->setMinimumHeight(_height_);
}

void DisplayWidget::resizeW(){
    Title_->resize(width()-10,Title_->height());
    for(auto vop:ValueOfProperties_){
        vop->resize(width()-(EditMode_?146:78),vop->height());
    }
    for(auto btn:PropertyButton_){
        btn->move(width()-67,btn->y());
    }
    AddButton_->resize(width()-78,AddButton_->height());
}

void DisplayWidget::resizeEvent(QResizeEvent *event){
    qDebug()<<"resizeEvent";
    resizeW();
}


int DisplayWidget::NEWcountProperty(QString _key_){
    for(int i=0;i<KeyOfProperties_.size();i++){
        if(KeyOfProperties_[i]->text()==_key_) return i;
    }
    return -1;
}
void DisplayWidget::NEWaddProperty(QString _key_,QString _value_){
    if(NEWcountProperty(_key_)!=-1) return;
    KeyOfProperties_.append(new QLineEdit(_key_));
    ValueOfProperties_.append(new QLineEdit(_value_));
    Word_.addProperty(_key_,_value_);

    int i=KeyOfProperties_.size()-1;
    NEWsetPropertyPosition(i);
    NEWsetNewPropertyWidgetPosition();
}
void DisplayWidget::NEWsetProperty(QString _key_,QString _value_){
    int i=NEWcountProperty(_key_);
    if(i==-1)return;
    ValueOfProperties_[i]->setText(_value_);
    Word_.editProperty(_key_,_value_);
}
void DisplayWidget::NEWsetProperty(int _index_,QString _value_){}
void DisplayWidget::NEWremoveProperty(QString _key_,QString _value_){}
void DisplayWidget::NEWremoveProperty(int _index_,QString _value_){}

void DisplayWidget::NEWsetPropertyPosition(int _index_){}
