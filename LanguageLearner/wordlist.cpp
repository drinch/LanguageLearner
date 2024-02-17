#include"wordlist.h"

#include<QDebug>

WordList::WordList(){}
WordList::~WordList(){
    for(auto word:map_){
        delete word.first;
    }
}

QList<QString> WordList::getWords(){
    return map_.keys();
}
QList<Word> WordList::searchWords(QString _str_){
    QList<Word> words;
    for(auto it=map_.lowerBound(_str_);it!=map_.end();it++){
        if(it.key().left(_str_.size())!=_str_) break;
        words.push_back(*it.value().first);
    }
    return words;
}

Word WordList::getWord(QString _str_){
    if(!map_.count(_str_)) return Word();
    return *map_[_str_].first;
}
int WordList::getWeight(QString _str_){
    if(!map_.count(_str_)) return -1;
    return map_[_str_].second;
}

void WordList::addWord(QString _word_,Word* _wordinfo_){
    if(_word_!=_wordinfo_->word()) return;
    map_.insert(_word_,QPair<Word*,int>(_wordinfo_,0));
}
void WordList::editWord(QString _word_,Word* _wordinfo_){
    if(_word_!=_wordinfo_->word()){
        QString word=_wordinfo_->word();
        map_.insert(word,QPair<Word*,int>(_wordinfo_,map_[_word_].second));
        map_.remove(_word_);
    }else map_[_word_].first=_wordinfo_;
}
int WordList::deleteWord(QString _word_){
	delete map_[_word_].first;
    return map_.remove(_word_);
}
int WordList::countWord(QString _word_){
	return map_.count(_word_);
}

QVector<Word> WordList::getTestWords(int _n_){
    QVector<QString> vector=map_.keys().toVector();
    std::sort(vector.begin(),vector.end(),[this](const QString &_wordA_,const QString &_wordB_){
        return this->map_[_wordA_].second<this->map_[_wordB_].second;
    });
    QVector<Word> wordlist;
    for(int i=vector.size()-_n_;i<vector.size();i++){
        wordlist.append(*map_[vector[i]].first);
    }
    return wordlist;
}

void WordList::debug_ShowWord(){
    for(auto word:map_){
        qDebug()<<word.first->word();
    }
}
