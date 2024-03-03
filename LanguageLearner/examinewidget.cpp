#include "examinewidget.h"
#include "ui_examinewidget.h"

#include<algorithm>
#include<random>

#include<QDebug>

ExamineWidget::ExamineWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ExamineWidget)
{
	ui->setupUi(this);

    connect(ui->ButtonA,&QPushButton::clicked,[=](){
        emit check(rightchoiceindex_==0);
    });
    connect(ui->ButtonB,&QPushButton::clicked,[=](){
        emit check(rightchoiceindex_==1);
    });
    connect(ui->ButtonC,&QPushButton::clicked,[=](){
        emit check(rightchoiceindex_==2);
    });
    connect(ui->ButtonD,&QPushButton::clicked,[=](){
        emit check(rightchoiceindex_==3);
    });
}

ExamineWidget::~ExamineWidget()
{
	delete ui;
}



void ExamineWidget::createChoiceQuestion(QString _question_,QString _choice_[4]){
    ui->StackedWidget->setCurrentIndex(0);
    ui->QuestionBrowser->setText(_question_);
    int order[]={0,1,2,3};
    std::random_shuffle(order,order+4);
    rightchoiceindex_=order[0];
    QPushButton *btn_p[]={ui->ButtonA,ui->ButtonB,ui->ButtonC,ui->ButtonD};
    for(int i=0;i<4;i++){
        qDebug()<<order[i];
        btn_p[order[i]]->setText(_choice_[i]);
    }
}
void ExamineWidget::createBlankFillingQuestion(QString _question_,QString _answer_){
    ui->StackedWidget->setCurrentIndex(1);
    ui->QuestionBrowser2->setText(_question_);
    disconnect(ui->ConfirmButton,&QPushButton::clicked,nullptr,nullptr);
    connect(ui->ConfirmButton,&QPushButton::clicked,[=](){
        if(ui->LineEdit->text()==_answer_) emit check(1);
    });
}
