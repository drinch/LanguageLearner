#include"wordlist.h"

#include<QFile>
#include<QDataStream>

#include<QDebug>

//================构造和析构函数===============
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

//=======================单词列表查询=====================
int WordList::countWord(QString _word_){//根据单词名检查单词是否存在
    return map_.count(_word_);
}
Word WordList::getWord(QString _word_){//根据单词名获取单词信息
    if(!map_.count(_word_)) return Word();
    return map_[_word_].first;
}
int WordList::getWeight(QString _word_){//根据单词名获取单词权重
    if(!map_.count(_word_)) return -1;
    return map_[_word_].second;
}
QVector<Word> WordList::searchWords(QString _str_){//根据字符串搜索单词
    QVector<Word> _words;
    for(auto _it=map_.begin();_it!=map_.end();_it++){//遍历词库
        if(_it.key().indexOf(_str_)!=-1){//匹配片段
            _words.push_back(_it.value().first);
        }
    }
    return _words;
}
QList<QString> WordList::getAllWords(){//获取所有单词
    return map_.keys();
}

//=============================单词列表操作====================================
void WordList::addWord(QString _word_,Word _wordInfo_,int _weight_){//添加单词
    if(_word_!=_wordInfo_.word()||countWord(_word_)) return;
    map_.insert(_word_,QPair<Word,int>(_wordInfo_,_weight_));
}
void WordList::addWord(Word _wordInfo_,int _weight_){
    map_.insert(_wordInfo_.word(),QPair<Word,int>(_wordInfo_,_weight_));
}
void WordList::editWord(QString _word_,Word _wordInfo_){//修改单词
    if(!countWord(_word_)||countWord(_wordInfo_.word())) return;
    if(_word_!=_wordInfo_.word()){
        map_.insert(_wordInfo_.word(),QPair<Word,int>(_wordInfo_,map_[_word_].second));
        map_.remove(_word_);
    }else map_[_word_].first=_wordInfo_;
}
int WordList::deleteWord(QString _word_){//删除单词
    return map_.remove(_word_);
}
