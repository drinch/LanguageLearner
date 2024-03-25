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

    connect(this,&ExamineWidget::check,[=](bool result){
        if(!result) examinescore_[currentindex_]++;
        currentindex_++;
        readExamineList(currentindex_);
    });
}

ExamineWidget::~ExamineWidget()
{
	delete ui;
}

void ExamineWidget::setExamineType(int _type_){
    examinetype_=_type_;
}
void ExamineWidget::setNumber(int _number_){
    number_=_number_;
}
void ExamineWidget::setWords(QVector<Word> &_wordlist_){
    wordlist_=_wordlist_;
    std::random_shuffle(wordlist_.begin(),wordlist_.end());
}
void ExamineWidget::generateProblem(){
    examinelist_.resize(wordlist_.size());
    for(int i=0;i<wordlist_.size();i++){
        examinelist_[i]=wordlist_[i].property("释义");
        examinelist_[i]+=wordlist_[i].word();
        qsrand(time(0));
        int index[3];
        for(int j=0;j<3;j++){
            index[j]=qrand()%number_;
            bool r=(index[j]==i);
            for(int k=0;k<j;k++){
                if(index[j]==index[k]) r=1;
            }
            if(r){
                j--;
                continue;
            }
            examinelist_[i]+=","+wordlist_[index[j]].word();
        }
    }
    currentindex_=0;
}
void ExamineWidget::readExamineList(int _index_){
    if(_index_>=number_){
        ui->StackedWidget->setCurrentIndex(2);
    }else{
        auto strlist=examinelist_[_index_].split(",");
        QString choise[4]={strlist[1],strlist[2],strlist[3],strlist[4]};
        createChoiceQuestion(strlist[0],choise);
    }
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
        else emit check(0);
    });
}
