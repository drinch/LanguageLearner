#include"wordbox.h"
#include"ui_wordbox.h"

#include<QDebug>

WordBox::WordBox(QWidget *parent,int _height_) :
    QWidget(parent),
    ui(new Ui::WordBox),
    place_(0)
{
    ui->setupUi(this);
    resize(parent->width()-10,_height_-4);
    qDebug()<<"addNewBox";
}

WordBox::~WordBox(){
    delete ui;
}

void WordBox::setWord(const Word &_word_){
    word_=_word_;
}
void WordBox::setPlace(int _i_){
    place_=_i_;
    move(5,_i_*height()+5);
}
void WordBox::showWord(){
    qDebug()<<"showwordofthebox";
    ui->WordLabel_->setText(word_.word());
}

void WordBox::mouseReleaseEvent(QMouseEvent *event){
    emit clicked();
}
