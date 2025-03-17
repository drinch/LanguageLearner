# WordCardList类

[toc]

2025/03/06

## 简介

这是基于WordCard类，将单词卡片以一列的形式展示出来的窗口。计划用于查看单词本功能，以及替换原先的搜索显示功能。

## 具体功能

设置需要展示的单词列表，并将其以一列卡片形式展示出来，目前尚未提供操作。

窗口布局，整个窗口为Widget套ScrollArea。内部单词卡片一列排列，手动控制内部布局。

成员函数：

`void setWordList(QVector<Word> _wordList_)`设置单词列表，并自动生成单词卡片排列好展示出来

`void clear()`清空单词列表，为设置新的单词列表作准备

`void resizeEvent(QResizeEvent *_event_)`窗口大小变化事件重载，用于手动控制内部单词卡片布局

成员变量：

`int topMargin_`单词卡片顶部边距

`int wordCardHeight_`单词卡片高度

`int verticalSpacing_`单词卡片垂直间距

`int horizontalMargin_`单词卡片侧边距

`QVector<Word> wordList_`单词列表

`QVector<WordCard*> wordCardList_`单词卡片列表

信号：

`void deleteWord(Word _Word_)`当该页面的某个单词卡进行删除操作，发送删除信号`deleteWord()`时，该删除信号发送，并指明哪个单词


## 具体实现

暂无复杂功能