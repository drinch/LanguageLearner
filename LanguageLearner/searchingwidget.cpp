#include "searchingwidget.h"
#include "ui_searchingwidget.h"

SearchingWidget::SearchingWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SearchingWidget)
{
	ui->setupUi(this);

    connect(ui->lineEdit,&QLineEdit::textChanged,[=](QString _str_){search(_str_);});
    connect(ui->AddWord_,&QPushButton::clicked,[=](){addWord();});
}

SearchingWidget::~SearchingWidget()
{
	delete ui;
}

void SearchingWidget::clear(){
    ui->lineEdit->clear();
}
