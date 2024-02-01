#ifndef WORDLIST_H
#define WORDLIST_H

#include<QMap>
#include<QString>
#include<QPair>

#include"word.h"
#include"wordpriorityqueue.h"

class WordList
{
public:
	WordList();
private:
	QMap<QString,QPair<Word,int> > wordlist;
	WordPriorityQueue wordqueue;
};

bool cmp(Word*,Word*);

#endif // WORDLIST_H
