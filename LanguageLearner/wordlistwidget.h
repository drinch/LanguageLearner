#ifndef WORDLISTWIDGET_H
#define WORDLISTWIDGET_H

#include<QWidget>
#include<QVector>

#include"word.h"
#include"wordcard.h"

namespace Ui {
class WordListWidget;
}

class WordListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WordListWidget(
            QWidget *parent = nullptr,
            int _TopMargin_=5,
            int _WordCardHeight_=70,
            int _VerticalSpacing_=2,
            int _HorizontalMargin_=5);
    ~WordListWidget();

    //===================公有成员函数==================
    void setWordList(QVector<Word> _WordList_);//设置单词列表，并配置单词卡片展示

    //====================事件重载==================
    void resizeEvent(QResizeEvent *event);//重载窗口改变事件，控制单词卡片尺寸

private:
    Ui::WordListWidget *ui;

    int TopMargin_,WordCardHeight_,VerticalSpacing_,HorizontalMargin_;//单词卡片的上边距，高度，垂直间距，侧边距
    QVector<Word> WordList_;//单词列表
    QVector<WordCard*> WordCardList_;//单词卡片列表
};

#endif // WORDLISTWIDGET_H
