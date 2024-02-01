#ifndef SEARCHINGRESULT_H
#define SEARCHINGRESULT_H

#include <QWidget>

namespace Ui {
class SearchingResult;
}

class SearchingResult : public QWidget
{
	Q_OBJECT

public:
	explicit SearchingResult(QWidget *parent = nullptr);
	~SearchingResult();

private:
	Ui::SearchingResult *ui;
};

#endif // SEARCHINGRESULT_H
