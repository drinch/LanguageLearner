#include "wordcardlist.h"
#include "ui_wordcardlist.h"

WordCardList::WordCardList(QWidget *parent,
                           int _topMargin_,
                           int _wordCardHeight_,
                           int _verticalSpacing_,
                           int _horizontalMargin_) :
    QWidget(parent),
    ui(new Ui::WordCardList),
    topMargin_(_topMargin_),
    wordCardHeight_(_wordCardHeight_),
    verticalSpacing_(_verticalSpacing_),
    horizontalMargin_(_horizontalMargin_),
    wordList_(),
    wordCardList_()
{
    ui->setupUi(this);
}

WordCardList::~WordCardList()
{
    for(int i=0;i<wordCardList_.size();i++){
        delete wordCardList_[i];
    }
    delete ui;
}

void WordCardList::setWordList(QVector<Word> _wordList_){
    clear();
    wordList_=_wordList_;//保存单词列表
    for(int i=0;i<wordList_.size();i++){
        wordCardList_.append(new WordCard(ui->contents_));
        //连接信号
        connect(wordCardList_[i],&WordCard::deleteWord,[=](){
            emit deleteWord(wordList_[i]);
        });
        //设置单词卡片位置及尺寸
        wordCardList_[i]->resize(ui->contents_->width()-2*horizontalMargin_,wordCardHeight_);
        wordCardList_[i]->move(horizontalMargin_,topMargin_+i*(wordCardHeight_+verticalSpacing_));
        //设置单词卡片内容
        wordCardList_[i]->setWord(wordList_[i]);
        wordCardList_[i]->show();
    }
}
void WordCardList::clear(){
    for(int i=0;i<wordCardList_.size();i++){
        delete wordCardList_[i];
    }
    wordCardList_.clear();
    wordList_.clear();
}

//===================事件重载==========================
void WordCardList::resizeEvent(QResizeEvent *event){
    for(int i=0;i<wordCardList_.size();i++){
        auto _Card=wordCardList_[i];
        _Card->resize(ui->contents_->width()-2*horizontalMargin_,wordCardHeight_);
    }
    return QWidget::resizeEvent(event);
}
