#ifndef EXAMINEWIDGET_H
#define EXAMINEWIDGET_H

#include<QWidget>
#include<QVector>

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
    void readExamineList();
    void startExamine();
    void endExamine();

private:
	Ui::ExamineWidget *ui;
    int examinetype_;
    int number_;
    QVector<QString> examinelist_;
    QVector<int> examinescore_;

signals:
    void end();
};

#endif // EXAMINEWIDGET_H
