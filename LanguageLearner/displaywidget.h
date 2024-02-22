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

    Word getWord()const;

    void setWord(const Word _word_);
    void setMode(int _mode_);

    void resizeEvent(QResizeEvent *event);

private:
	Ui::DisplayWidget *ui;

    bool running_,editmode_;
    int height_;
    Word word_;
    QLineEdit *title_,*additionalproperty_;
    QPushButton* addbutton_;
    QVector<QLineEdit*> keyofproperties_,valueofproperties_;
    QVector<QPushButton*> button_;
    QVector<QString> properties_;

    void setInterfaceWord();
    void changeMode();
    void deleteInterface();

    void addProperty(QString _key_,QString _value_);
    void deleteProperty(int _index_);

    int numberOfP();
    void setMH(int _height_);
    void resizeW();

signals:
    void back();
    void save(QString _str_);
};

#endif // DISPLAYWIDGET_H
