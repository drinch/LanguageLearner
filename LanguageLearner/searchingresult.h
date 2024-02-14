#ifndef SEARCHINGRESULT_H
#define SEARCHINGRESULT_H

#include<QWidget>
#include<QVector>

namespace Ui {
class SearchingResult;
}

class SearchingResult : public QWidget
{
	Q_OBJECT

public:
	explicit SearchingResult(QWidget *parent = nullptr);
    ~SearchingResult();

    void setWordList(QList<QString> _list_);

private:
	Ui::SearchingResult *ui;
    QList<QString> wordlist_;

signals:
    void check(QString _word_);
};

#endif // SEARCHINGRESULT_H
