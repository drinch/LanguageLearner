#include"wordlist.h"

#include<QFile>
#include<QDataStream>

#include<QDebug>

WordList::WordList(){
    QFile _file("data.txt");
    _file.open(QIODevice::ReadOnly);
    QDataStream _in(&_file);
    Word _word;
    int _i;
    qDebug()<<"Loading...";
    while(!_in.atEnd()){
        _word=Word::deserialize(_in);
        _in>>_i;
        qDebug()<<_word.word()<<" "<<_i;
        addWord(_word.word(),_word,_i);
    }
    _file.close();
}
WordList::~WordList(){
    QFile _file("data.txt");
    _file.open(QIODevice::WriteOnly);
    QDataStream _out(&_file);
    qDebug()<<"Saving...";
    for(auto _word:map_){
        _word.first.serialize(_out);
        _out<<_word.second;
        qDebug()<<_word.first.word();
    }
    _file.close();
}

QList<QString> WordList::getWords(){
    return map_.keys();
}
QVector<Word> WordList::searchWords(QString _str_){
    QVector<Word> _words;
    for(auto _it=map_.begin();_it!=map_.end();_it++){//遍历词库
        qDebug()<<"Searching... "<<_it.key()<<" "<<_str_<<" "<<_it.key().indexOf(_str_);
        if(_it.key().indexOf(_str_)!=-1){//匹配片段
            _words.push_back(_it.value().first);
        }
    }
    return _words;
}

Word WordList::getWord(QString _str_){//根据单词名获取单词所有信息
    if(!map_.count(_str_)) return Word();
    return map_[_str_].first;
}
int WordList::getWeight(QString _str_){//根据单词名获取单词相关权重
    if(!map_.count(_str_)) return -1;
    return map_[_str_].second;
}

void WordList::addWord(QString _word_,Word _wordInfo_,int _weight_){//添加单词
    if(_word_!=_wordInfo_.word()) return;
    map_.insert(_word_,QPair<Word,int>(_wordInfo_,_weight_));
}
void WordList::editWord(QString _word_,Word _wordInfo_){//编辑单词
    if(_word_!=_wordInfo_.word()){
        QString _word=_wordInfo_.word();
        map_.insert(_word,QPair<Word,int>(_wordInfo_,map_[_word_].second));
        map_.remove(_word_);
    }else map_[_word_].first=_wordInfo_;
}
int WordList::deleteWord(QString _word_){//删除单词
    return map_.remove(_word_);
}
int WordList::countWord(QString _word_){//检查单词是否存在
    return map_.count(_word_);
}

QVector<Word> WordList::getTestWords(int _n_){
    QVector<QString> vector=map_.keys().toVector();
    std::sort(vector.begin(),vector.end(),[this](const QString &_wordA_,const QString &_wordB_){
        return this->map_[_wordA_].second<this->map_[_wordB_].second;
    });
    QVector<Word> wordlist;
    for(int i=vector.size()-_n_;i<vector.size();i++){
        wordlist.append(map_[vector[i]].first);
    }
    return wordlist;
}

void WordList::debug_ShowWord(){
    for(auto word:map_){
        qDebug()<<word.first.word();
    }
}
