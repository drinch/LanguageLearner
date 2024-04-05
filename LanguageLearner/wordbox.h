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

    void setWord(const Word &_word_);
    void setPlace(int _i_);
    void showWord();

    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::WordBox *ui;
    Word word_;
    int place_;

signals:
    void clicked();
    void deleted();
};

#endif // WORDBOX_H
