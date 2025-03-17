#ifndef WORDCARD_H
#define WORDCARD_H

#include <QWidget>

#include"word.h"

namespace Ui {
class WordCard;
}

class WordCard : public QWidget
{
    Q_OBJECT

public:
    explicit WordCard(QWidget *_parent_=nullptr);
    ~WordCard();

    void setWord(const Word &_word_);
    void showWord();

    void mouseReleaseEvent(QMouseEvent *_event_);

private:
    Ui::WordCard *ui;
    Word word_;
    int place_;

signals:
    void clicked();
    void deleted();
    void deleteWord();
};

#endif // WORDCARD_H
