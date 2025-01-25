#ifndef SEARCHINGRESULT_H
#define SEARCHINGRESULT_H

#include<QWidget>
#include<QVector>

#include"word.h"
#include"wordcard.h"

namespace Ui {
class SearchingResult;
}

class SearchingResult : public QWidget
{
	Q_OBJECT

public:
	explicit SearchingResult(QWidget *parent = nullptr);
    ~SearchingResult();

    void setWordList(QList<Word> _list_);

    void resizeEvent(QResizeEvent *event);

private:
	Ui::SearchingResult *ui;
    QList<Word> wordlist_;
    QList<WordCard*> boxlist_;

signals:
    void check(Word _word_);
    void deleted(Word _word_);
};

#endif // SEARCHINGRESULT_H
