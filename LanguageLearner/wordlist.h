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
	void addWord(QString _word_,Word* _wordInfo_);
	void editWord(QString _word_,Word* _wordInfo_);
	void deleteWord(QString _word_);
	bool count(QString _word_);

	QString getWord();
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
