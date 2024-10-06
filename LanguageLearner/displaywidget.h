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

    bool Running_,EditMode_;
    int Height_;
    Word Word_;
    QLineEdit *Title_,*NewProperty_;
    QPushButton* AddButton_;
    QVector<QLineEdit*> KeyOfProperties_,ValueOfProperties_;
    QVector<QPushButton*> PropertyButton_;
    QVector<QString> Properties_;

    void setInterfaceWord();
    void changeMode();
    void deleteInterface();

    void addProperty(QString _key_,QString _value_);
    void deleteProperty(int _index_);

    int numberOfP();
    void setMH(int _height_);
    void resizeW();

    int NEWcountProperty(QString _key_);//查找属性编号，不存在返回-1
    void NEWaddProperty(QString _key_,QString _value_);
    void NEWsetProperty(QString _key_,QString _value_);
    void NEWsetProperty(int _index_,QString _value_);
    void NEWremoveProperty(QString _key_,QString _value_);
    void NEWremoveProperty(int _index_,QString _value_);

    void NEWsetPropertyPosition(int _index_);//调整编号index的属性的窗口
    void NEWsetNewPropertyWidgetPosition();

signals:
    void back();
    void save(QString _str_);
};

#endif // DISPLAYWIDGET_H
