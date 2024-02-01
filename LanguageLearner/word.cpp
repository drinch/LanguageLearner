#include "word.h"

Word::Word(){
}
bool Word::countProperty(QString key){
	return properties.count(key);
}
bool Word::addProperty(QString key,QString value){
	if(properties.count(key)) return 0;
	else{
		properties.insert(key,value);
		return 1;
	}
}
bool Word::editProperty(QString key,QString value){
	if(!properties.count(key)) return 0;
	else{
		properties[key]=value;
		return 1;
	}
}
bool Word::deleteProperty(QString key){
	if(!properties.count(key)) return 0;
	else return properties.remove(key);
}
QString Word::viewProperty(QString key){
	if(!properties.count(key)) return "";
	else return properties[key];
}

QString Word::save(){}
void Word::load(QString str){}
