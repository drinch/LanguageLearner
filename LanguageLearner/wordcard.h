#ifndef WORDBOX_H
#define WORDBOX_H

#include <QWidget>

#include"word.h"

namespace Ui {
class WordBox;
}

class WordCard : public QWidget
{
    Q_OBJECT

public:
    explicit WordCard(QWidget *parent = nullptr);
    ~WordCard();

    void setWord(const Word &_word_);
    void showWord();

    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::WordBox *ui;
    Word word_;

signals:
    void clicked();
    void deleted();
};

#endif // WORDBOX_H
