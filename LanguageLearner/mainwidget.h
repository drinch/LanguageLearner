#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include<QWidget>

#include"wordlist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

	void mainSwitch(int _index_);
	void interfaceSwitch(int _index_);

private:
    Ui::MainWidget *ui;
	WordList wordlist_;
};
#endif // MAINWIDGET_H
