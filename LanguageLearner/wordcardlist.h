#ifndef WORDCARDLIST_H
#define WORDCARDLIST_H

#include <QWidget>
#include <QVector>

#include "word.h"
#include "wordcard.h"

namespace Ui {
class WordCardList;
}

class WordCardList : public QWidget
{
    Q_OBJECT

public:
    explicit WordCardList(
            QWidget *_parent_=nullptr,
            int _topMargin_=5,
            int _wordCardHeight_=70,
            int _verticalSpacing_=2,
            int _horizontalMargin_=5);
    ~WordCardList();

    //===================公有成员函数==================
    void setWordList(QVector<Word> _wordList_);//设置单词列表，并配置单词卡片展示
    void clear();//清空单词列表和窗口列表

    //====================事件重载==================
    void resizeEvent(QResizeEvent *_event_);//重载窗口改变事件，控制单词卡片尺寸

private:
    Ui::WordCardList *ui;

    int topMargin_,wordCardHeight_,verticalSpacing_,horizontalMargin_;//单词卡片的上边距，高度，垂直间距，侧边距
    QVector<Word> wordList_;//单词列表
    QVector<WordCard*> wordCardList_;//单词卡片列表

signals:
    void deleteWord(Word _word_);
};

#endif // WORDCARDLIST_H
