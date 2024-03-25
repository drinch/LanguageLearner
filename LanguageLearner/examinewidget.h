#ifndef EXAMINEWIDGET_H
#define EXAMINEWIDGET_H

#include<QWidget>
#include<QVector>
#include"word.h"

namespace Ui {
class ExamineWidget;
}

class ExamineWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ExamineWidget(QWidget *parent = nullptr);
	~ExamineWidget();

    void setExamineType(int _type_);
    void setNumber(int _number_);
    void setWords(QVector<Word> &_wordlist_);
    void generateProblem();
    void readExamineList(int _index_);

private:
	Ui::ExamineWidget *ui;
    int examinetype_,number_,currentindex_;
    QVector<Word> wordlist_;
    QVector<QString> examinelist_;
    QVector<int> examinescore_;

    int rightchoiceindex_;

    void createChoiceQuestion(QString _question_,QString _choice_[4]);
    void createBlankFillingQuestion(QString _question_,QString _answer_);

signals:
    void end();
    void check(bool _result_);
};

#endif // EXAMINEWIDGET_H
