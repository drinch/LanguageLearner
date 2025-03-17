#include "wordcard.h"
#include "ui_wordcard.h"

WordCard::WordCard(QWidget *_parent_) :
    QWidget(_parent_),
    ui(new Ui::WordCard)
{
    ui->setupUi(this);

    connect(ui->deleteButton_,&QPushButton::clicked,[=](){
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
    ui->word_->setText(word_.word());
    if(word_.countProperty("释义")){
        ui->property_->setText("释义");
        ui->meaning_->setText(word_.property("释义"));
    }else{
        ui->property_->setText("");
        ui->meaning_->setText("");
    }
}
void WordCard::showWord(){
    ui->word_->setText(word_.word());
    if(word_.countProperty("释义")){
        ui->property_->setText("释义");
        ui->meaning_->setText(word_.property("释义"));
    }else{
        ui->property_->setText("");
        ui->meaning_->setText("");
    }
}

void WordCard::mouseReleaseEvent(QMouseEvent *_event_){
    emit clicked();
    return QWidget::mouseReleaseEvent(_event_);
}
