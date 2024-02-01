#ifndef WORD_H
#define WORD_H

#include<QString>
#include<QMap>

class Word
{
public:
	Word();
	bool countProperty(QString key);
	bool addProperty(QString key,QString value);
	bool editProperty(QString key,QString value);
	bool deleteProperty(QString key);
	QString viewProperty(QString key);

	QString save();
	void load(QString str);

	bool operator < (Word &word_) const {return word<word_.word;}

private:
	QString word;
	QMap<QString,QString> properties;
};

#endif // WORD_H
