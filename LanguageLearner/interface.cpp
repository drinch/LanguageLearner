#include "interface.h"
#include "ui_interface.h"

Interface::Interface(QWidget *parent):
	QWidget(parent),
	ui(new Ui::Interface)
{
	ui->setupUi(this);

    connect(ui->TestA_,&QPushButton::click,[=](){
        examine(1,ui->spinBox->value());
    });
}

Interface::~Interface()
{
	delete ui;
}
