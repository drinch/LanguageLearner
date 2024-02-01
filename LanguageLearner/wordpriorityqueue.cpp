#include "wordpriorityqueue.h"

WordPriorityQueue::WordPriorityQueue(bool (*cmp_)(Word*,Word*)):cmp(cmp_){}
WordPriorityQueue::~WordPriorityQueue(){
	for(int i=0;i<queue.size();i++){
		delete queue[i];
	}
}
bool WordPriorityQueue::empty(){
	return queue.empty();
}
Word* WordPriorityQueue::top(){
	if(empty()) return 0;
	else return queue[0];
}
void WordPriorityQueue::push(Word* item){
	queue.append(item);
	up(queue.size()-1);
}
void WordPriorityQueue::pop(){
	int endidx=queue.size()-1;
	queue[0]=queue[endidx];
	queue.resize(endidx);
	down(0);
}

void WordPriorityQueue::down(int idx){
	while(lson(idx)<queue.size()){
		int son=lson(idx);
		if(rson(idx)<queue.size()&&cmp(queue[son],queue[rson(idx)])) son=rson(idx);
		if(cmp(queue[son],queue[idx])) break;
		else{
			qSwap(queue[son],queue[idx]);
			idx=son;
		}
	}
}
void WordPriorityQueue::up(int idx){
	while(fa(idx)>=0){
		if(cmp(queue[idx],queue[fa(idx)])) break;
		else{
			qSwap(queue[fa(idx)],queue[idx]);
			idx=fa(idx);
		}
	}
}

int lson(int idx){
	return idx*2+1;
}
int rson(int idx){
	return idx*2+2;
}
int fa(int idx){
	return (idx+1)/2-1;
}
