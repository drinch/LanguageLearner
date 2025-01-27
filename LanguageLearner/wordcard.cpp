#include "wordcard.h"
#include "ui_wordcard.h"

WordCard::WordCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordCard)
{
    ui->setupUi(this);

    connect(ui->DeleteButton_,&QPushButton::clicked,[=](){
        emit deleted();
    });
}

WordCard::~WordCard()
{
    delete ui;
}

void WordCard::setWord(const Word &_word_){
    word_=_word_;
}
void WordCard::showWord(){
    ui->Word_->setText(word_.word());
}

void WordCard::mouseReleaseEvent(QMouseEvent *event){
    emit clicked();
}
