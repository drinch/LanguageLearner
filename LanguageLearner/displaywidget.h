#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DisplayWidget(QWidget *parent = nullptr);
	~DisplayWidget();

private:
	Ui::DisplayWidget *ui;
};

#endif // DISPLAYWIDGET_H
