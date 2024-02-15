#include "wordbox.h"
#include "ui_wordbox.h"

WordBox::WordBox(QWidget *parent,int _height_) :
    QWidget(parent),
    ui(new Ui::WordBox),
    place_(0)
{
    ui->setupUi(this);
    resize(parent->width(),_height_);
}

WordBox::~WordBox()
{
    delete ui;
}

void WordBox::setWord(QString _word_){
    word_=_word_;
}
void WordBox::setPlace(int _i_){
    place_=_i_;
    move(0,_i_*height());
}
void WordBox::showWord(){
    ui->WordLabel_->setText(word_);
}
