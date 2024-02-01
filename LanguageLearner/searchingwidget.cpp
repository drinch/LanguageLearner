#include "searchingwidget.h"
#include "ui_searchingwidget.h"

SearchingWidget::SearchingWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SearchingWidget)
{
	ui->setupUi(this);
}

SearchingWidget::~SearchingWidget()
{
	delete ui;
}
