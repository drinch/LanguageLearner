#ifndef WORDBOX_H
#define WORDBOX_H

#include <QWidget>

#include"word.h"

namespace Ui {
class WordBox;
}

class WordBox : public QWidget
{
    Q_OBJECT

public:
    explicit WordBox(QWidget *parent = nullptr,int _height_=0);
    ~WordBox();

    void setWord(QString _word_);
    void setPlace(int _i_);
    void showWord();

private:
    Ui::WordBox *ui;
    QString word_;
    int place_;
};

#endif // WORDBOX_H
