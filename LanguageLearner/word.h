#ifndef WORD_H
#define WORD_H

#include<QString>
#include<QMap>

class Word
{
public:
	Word();
	bool countProperty(QString _key_);
	bool addProperty(QString _key_,QString _value_);
	bool editProperty(QString _key_,QString value_);
	bool deleteProperty(QString _key_);

	QString word();
	QString property(QString _property_);
    int propertyNumber();

	QString save();
	void load(QString _str_);

	bool operator < (Word &_word_) const {return word_<_word_.word_;}

private:
	QString word_;
	QMap<QString,QString> properties_;
};

#endif // WORD_H
