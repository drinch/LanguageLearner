#ifndef WORDLIST_H
#define WORDLIST_H

#include<QMap>
#include<QString>
#include<QPair>
#include<QVector>

#include"word.h"

class WordList
{
public:
	WordList();
    ~WordList();

    //单词列表查询
    int countWord(QString _word_);//根据单词名检查单词是否存在
    Word getWord(QString _word_);//根据单词名获取单词信息
    int getWeight(QString _word_);//根据单词名获取单词权重
    QVector<Word> searchWords(QString _str_);//根据字符串搜索单词
    QList<QString> getAllWords();//获取所有单词

    //单词列表操作
    void addWord(QString _word_,Word _wordInfo_,int _weight_=0);//添加单词
    void addWord(Word _wordInfo_,int _weight_=0);
    void editWord(QString _word_,Word _wordInfo_);//修改单词
    int deleteWord(QString _word_);//删除单词

private:
    QMap<QString,QPair<Word,int> > map_;
};

#endif // WORDLIST_H
