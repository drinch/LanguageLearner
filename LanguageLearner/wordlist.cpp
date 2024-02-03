#include "wordlist.h"

WordList::WordList(){}

void WordList::addWord(QString _word_,Word* _wordInfo_){
	map_.insert(_word_,QPair<Word*,int>(_wordInfo_,0));
}
void WordList::editWord(QString _word_,Word* _wordInfo_){
	map_[_word_].first=_wordInfo_;
}
void WordList::deleteWord(QString _word_){
	delete map_[_word_].first;
	map_.remove(_word_);
}
bool WordList::count(QString _word_){
	return map_.count(_word_);
}

QString WordList::getWord(){
	QString word=top();
	pop();
	return word;
}
void WordList::pushWord(QString _word_){
	push(_word_);
}

bool WordList::cmp(QString _wordA_,QString _wordB_){
	return map_[_wordA_].second<map_[_wordB_].second;
}
QString WordList::top(){
	if(empty()) return "";
	else return queue_[0];
}
void WordList::push(QString _word_){
	queue_.append(_word_);
	up(queue_.size()-1);
}
void WordList::pop(){
	if(empty()) return;
	int last=queue_.size()-1;
	queue_[0]=queue_[last];
	queue_.resize(last);
	if(empty()) return;
	down(0);
}
bool WordList::empty(){
	return queue_.empty();
}

bool WordList::isValid(int _index_){
	return _index_<queue_.size()&&_index_>=0;
}
void WordList::down(int _index_){
	int son=lson(_index_);
	while(isValid(son)){
		if(isValid(rson(_index_))&&cmp(queue_[son],queue_[rson(_index_)]))
			son=rson(_index_);
		if(cmp(queue_[son],queue_[_index_])) break;
		qSwap<QString>(queue_[son],queue_[_index_]);
		_index_=son;
		son=lson(_index_);
	}
}
void WordList::up(int _index_){
	int father=fa(_index_);
	while(isValid(father)){
		if(cmp(queue_[_index_],queue_[father])) break;
		qSwap(queue_[_index_],queue_[father]);
		_index_=father;
		father=fa(_index_);
	}
}

int WordList::lson(int i){
	return i*2+1;
}
int WordList::rson(int i){
	return i*2+2;
}
int WordList::fa(int i){
	return (i-1)/2;
}
