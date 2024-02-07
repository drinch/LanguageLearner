#include "wordbox.h"
#include "ui_wordbox.h"

WordBox::WordBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordBox)
{
    ui->setupUi(this);
}

WordBox::~WordBox()
{
    delete ui;
}
