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
    QList<QString> searchWords(QString _str_);

    Word getWord(QString _str_);
    int getWeight(QString _str_);

	void addWord(QString _word_,Word* _wordInfo_);
	void editWord(QString _word_,Word* _wordInfo_);
    int deleteWord(QString _word_);
    int countWord(QString _word_);

    QString topWord();
	void pushWord(QString _word_);

private:
	QMap<QString,QPair<Word*,int> > map_;
	QVector<QString> queue_;

	bool cmp(QString _wordA_,QString _wordB_);
	QString top();
	void push(QString _word_);
	void pop();
	bool empty();

	bool isValid(int _index_);
	void down(int _index_);
	void up(int _index_);

	static int lson(int i);
	static int rson(int i);
	static int fa(int i);
};

#endif // WORDLIST_H
