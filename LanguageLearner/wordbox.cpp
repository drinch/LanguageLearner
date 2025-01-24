#include"wordbox.h"
#include"ui_wordbox.h"

#include<QDebug>

WordBox::WordBox(QWidget *parent,int _height_) :
    QWidget(parent),
    ui(new Ui::WordBox),
    place_(0)
{
    ui->setupUi(this);

    //调整窗口大小，水平边距为5，
    resize(parent->width()-10,_height_-4);

    //设置并调整位置
    setPlace(0);
    qDebug()<<"addNewBox";

    connect(ui->DeleteButton_,&QPushButton::clicked,[=](){
        emit deleted();
    });
}

WordBox::~WordBox(){
    delete ui;
}

void WordBox::setWord(const Word &_word_){//设置单词
    word_=_word_;
}
void WordBox::setPlace(int _i_){//设置并调整位置
    place_=_i_;
    move(5,_i_*height()+5);
}
void WordBox::showWord(){//显示单词
    qDebug()<<"showwordofthebox";
    ui->WordLabel_->setText(word_.word());
}

void WordBox::mouseReleaseEvent(QMouseEvent *event){
    emit clicked();
}
