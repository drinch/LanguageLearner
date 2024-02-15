#include"word.h"

Word::Word(){}
Word::~Word(){}

QString Word::word()const{
    return word_;
}
void Word::setWord(QString _str_){
    word_=_str_;
}

int Word::propertyNumber(){
    return properties_.size();
}
QString Word::property(QString _key_){
    if(!properties_.count(_key_)) return "";
    else return properties_[_key_];
}
QList<QString> Word::properties(){
    return properties_.keys();
}
void Word::addProperty(QString _key_,QString _value_){
    properties_.insert(_key_,_value_);
}
void Word::editProperty(QString _key_,QString _value_){
    properties_[_key_]=_value_;
}
int Word::deleteProperty(QString _key_){
    return properties_.remove(_key_);
}
int Word::countProperty(QString _key_){
    return properties_.count(_key_);
}



QString Word::save(){return "";}
void Word::load(QString _str_){_str_="";}
