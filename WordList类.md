# WordList类

[toc]

2025/03/20

## 简介

这是词库类，储存所有单词，并提供相关操作

## 具体功能

包括基本操作，添加单词，修改单词，删除单词，以及在词库中检索特定单词的存在性，信息，权重，或是根据字符串检索单词（目前仅支持按单个子串查找），以及获取所有单词名称列表

**成员函数**

- 查询

`int countWord(QString _word_);`
根据单词名\_word\_检查该单词是否存在，返回单词数量，即，存在为$1$，不存在为$0$
`Word getWord(QString _word_);`
根据单词名\_word\_获取单词的所有信息
`int getWeight(QString _word_);`
根据单词名\_word\_获取单词权重，单词权重在将来用于衡量单词记忆程度
`QVector<Word> searchWords(QString _str_);`
根据字符串\_str\_搜索单词，要求单词连续包含子串\_str\_
`QList<QString> getAllWords();`
获取所有单词

- 操作

`void addWord(QString _word_,Word _wordInfo_,int _weight_=0);`
根据单词名\_word\_，单词信息\_wordInfo\_，以及权重\_weight\_添加单词，若单词信息中的单词名与输入单词名不一致，或单词在词库中已存在，则忽略，不执行操作
`void addWord(Word _wordInfo_,int _weight_=0);`
根据单词信息\_wordInfo\_，以及权重\_weight\_添加单词，去掉了重复的单词名，若单词在词库中已存在，则忽略，不执行操作
`void editWord(QString _word_,Word _wordInfo_);`
修改单词，将单词名为\_word\_的单词的信息修改为\_wordInfo\_
`int deleteWord(QString _word_);`
删除单词名为\_word\_的单词

**成员变量**

`QMap<QString,QPair<Word,int> > map_;`
储存单词信息，以单词名为关键字排序并作为索引，储存单词信息和单词权重

## 具体实现

搜索功能目前只支持查找子串，不支持特殊的查找方式如多个条件，模糊查找等。该功能采用遍历词库的方式实现对每个单词采用`int QString::indexOf(const QString &str)`函数进行比较