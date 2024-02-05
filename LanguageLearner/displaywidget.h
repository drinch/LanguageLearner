#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include<QWidget>

#include"word.h"

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DisplayWidget(QWidget *parent = nullptr);
	~DisplayWidget();

    void setMode(int _mode_);
    void setWord(Word* _word_);
    void editWord();

private:
	Ui::DisplayWidget *ui;
    Word* word_;
    bool editmode_;

    void displayWord();

signals:
    void back();
};

#endif // DISPLAYWIDGET_H
