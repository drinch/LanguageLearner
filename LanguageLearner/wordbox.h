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
    explicit WordBox(QWidget *parent = nullptr);
    ~WordBox();
    void setWord(QString* _word_);

private:
    Ui::WordBox *ui;
    Word* word_;
};

#endif // WORDBOX_H
