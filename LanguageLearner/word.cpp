#include "word.h"

Word::Word(){
}
bool Word::countProperty(QString _key_){
	return properties_.count(_key_);
}
bool Word::addProperty(QString _key_,QString _value_){
	if(properties_.count(_key_)) return 0;
	else{
		properties_.insert(_key_,_value_);
		return 1;
	}
}
bool Word::editProperty(QString _key_,QString _value_){
	if(!properties_.count(_key_)) return 0;
	else{
		properties_[_key_]=_value_;
		return 1;
	}
}
bool Word::deleteProperty(QString _key_){
	if(!properties_.count(_key_)) return 0;
	else return properties_.remove(_key_);
}

QString Word::word(){
	return word_;
}
QString Word::property(QString _property_){
	if(!properties_.count(_property_)) return "";
	else return properties_[_property_];
}
int Word::propertyNumber(){
    return properties_.size();
}

QString Word::save(){}
void Word::load(QString _str_){}
