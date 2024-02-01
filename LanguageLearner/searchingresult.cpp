#include "searchingresult.h"
#include "ui_searchingresult.h"

SearchingResult::SearchingResult(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SearchingResult)
{
	ui->setupUi(this);
}

SearchingResult::~SearchingResult()
{
	delete ui;
}
