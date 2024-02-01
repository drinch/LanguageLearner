#ifndef WORDPRIORITYQUEUE_H
#define WORDPRIORITYQUEUE_H

#include<QVector>

#include"word.h"

class WordPriorityQueue
{
public:
	WordPriorityQueue(bool (*cmp_)(Word*,Word*));
	~WordPriorityQueue();
	bool empty();
	Word* top();
	void push(Word* item);
	void pop();

private:
	QVector<Word*> queue;
	bool (*cmp)(Word*,Word*);

	void down(int idx);
	void up(int idx);
};

int lson(int idx);
int rson(int idx);
int fa(int idx);

#endif // WORDPRIORITYQUEUE_H
