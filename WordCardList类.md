# WordCardList类

[toc]

2025/02/07

## 简介

这是基于WordCard类，将单词卡片以一列的形式展示出来的窗口。计划用于查看单词本功能，以及替换原先的搜索显示功能。

## 具体功能

设置需要展示的单词列表，并将其以一列卡片形式展示出来，目前尚未提供操作。

窗口布局，整个窗口为Widget套ScrollArea。内部单词卡片一列排列，手动控制内部布局。

成员函数：

`void setWordList(QVector<Word> _WordList_);`设置单词列表，并自动生成单词卡片排列好展示出来

`void resizeEvent(QResizeEvent *event);`窗口大小变化事件重载，用于手动控制内部单词卡片布局

## 具体实现

暂无复杂功能