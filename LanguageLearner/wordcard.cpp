#include"wordcard.h"
#include"ui_wordbox.h"

#include<QDebug>

WordCard::WordCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordBox)
{
    ui->setupUi(this);

    //添加删除信号，点击删除按钮触发
    connect(ui->DeleteButton_,&QPushButton::clicked,[=](){
        emit deleted();
    });
}

WordCard::~WordCard(){
    delete ui;
}

void WordCard::setWord(const Word &_word_){//设置单词
    word_=_word_;
}
void WordCard::showWord(){//显示单词
    ui->WordLabel_->setText(word_.word());
}

void WordCard::mouseReleaseEvent(QMouseEvent *event){
    emit clicked();
}
