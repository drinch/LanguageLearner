#ifndef SEARCHINGWIDGET_H
#define SEARCHINGWIDGET_H

#include <QWidget>

namespace Ui {
class SearchingWidget;
}

class SearchingWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SearchingWidget(QWidget *parent = nullptr);
	~SearchingWidget();

    void clear();
    void searchAgain();

private:
	Ui::SearchingWidget *ui;

signals:
	void addWord();
	void search(QString _str_);
};

#endif // SEARCHINGWIDGET_H
