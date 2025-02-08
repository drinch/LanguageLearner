#include "wordcard.h"
#include "ui_wordcard.h"

WordCard::WordCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordCard)
{
    ui->setupUi(this);

    connect(ui->DeleteButton_,&QPushButton::clicked,[=](){
        emit deleted();
        emit deleteWord();
    });
}

WordCard::~WordCard()
{
    delete ui;
}

void WordCard::setWord(const Word &_word_){
    word_=_word_;
    ui->Word_->setText(word_.word());
    if(word_.countProperty("释义")){
        ui->Property_->setText("释义");
        ui->Meaning_->setText(word_.property("释义"));
    }else{
        ui->Property_->setText("");
        ui->Meaning_->setText("");
    }
}
void WordCard::showWord(){
    ui->Word_->setText(word_.word());
    if(word_.countProperty("释义")){
        ui->Property_->setText("释义");
        ui->Meaning_->setText(word_.property("释义"));
    }else{
        ui->Property_->setText("");
        ui->Meaning_->setText("");
    }
}

void WordCard::mouseReleaseEvent(QMouseEvent *event){
    emit clicked();
    return QWidget::mouseReleaseEvent(event);
}
