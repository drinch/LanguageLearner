#ifndef WORD_H
#define WORD_H

#include<QString>
#include<QDataStream>
#include<QMap>

class Word
{
public:
    Word();
    ~Word();

    QString word()const;
    void setWord(QString _str_);

    int propertyNumber();
    QString property(QString _key_);
    QList<QString> properties();
    void addProperty(QString _key_,QString _value_);
    void editProperty(QString _key_,QString value_);
    int deleteProperty(QString _key_);
    int countProperty(QString _key_);

    void serialize(QDataStream &out)const;
    static Word deserialize(QDataStream &in);

	bool operator < (Word &_word_) const {return word_<_word_.word_;}

private:
    QString word_;
    QMap<QString,QString> properties_;
};

#endif // WORD_H
