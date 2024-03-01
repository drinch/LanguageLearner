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

    QList<QString> getWords();
    QList<Word> searchWords(QString _str_);

    Word getWord(QString _str_);
    int getWeight(QString _str_);

    void addWord(QString _word_,Word* _wordInfo_,int _weight_=0);
	void editWord(QString _word_,Word* _wordInfo_);
    int deleteWord(QString _word_);
    int countWord(QString _word_);

    QVector<Word> getTestWords(int _n_);

    void debug_ShowWord();

private:
    QMap<QString,QPair<Word*,int> > map_;
};

#endif // WORDLIST_H
