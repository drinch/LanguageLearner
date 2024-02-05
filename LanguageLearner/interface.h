#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>

namespace Ui {
class Interface;
}

class Interface : public QWidget
{
	Q_OBJECT

public:
	explicit Interface(QWidget *parent = nullptr);
	~Interface();

private:
	Ui::Interface *ui;

signals:
    void examine(int _type_,int _number_);
};

#endif // INTERFACE_H
