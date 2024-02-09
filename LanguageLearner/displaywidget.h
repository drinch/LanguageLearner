#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include<QWidget>
#include<QLineEdit>
#include<QPushButton>

#include"word.h"

namespace Ui {
class DisplayWidget;
}

class DisplayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DisplayWidget(QWidget *parent = nullptr);
	~DisplayWidget();

    void setWord(Word* _word_);
    void setMode(int _mode_);

private:
	Ui::DisplayWidget *ui;
    bool editmode_;
    Word *word_,*wordcopy_;
    QVector<QLineEdit*> interface_;
    QVector<QPushButton*> button_;
    QVector<QString> properties_;

    void createInterface();
    void setInterface();
    void deleteInterface();
    void addProperty(QString _key_,QString _value_);
    void deleteProperty(int _index_);

signals:
    void back();
    void save();
};

#endif // DISPLAYWIDGET_H
