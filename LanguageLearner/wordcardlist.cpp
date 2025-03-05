#include "wordcardlist.h"
#include "ui_wordcardlist.h"

WordCardList::WordCardList(QWidget *parent,
                           int _TopMargin_,
                           int _WordCardHeight_,
                           int _VerticalSpacing_,
                           int _HorizontalMargin_) :
    QWidget(parent),
    ui(new Ui::WordCardList),
    TopMargin_(_TopMargin_),
    WordCardHeight_(_WordCardHeight_),
    VerticalSpacing_(_VerticalSpacing_),
    HorizontalMargin_(_HorizontalMargin_),
    WordList_(),
    WordCardList_()
{
    ui->setupUi(this);
}

WordCardList::~WordCardList()
{
    for(int i=0;i<WordCardList_.size();i++){
        delete WordCardList_[i];
    }
    delete ui;
}

void WordCardList::setWordList(QVector<Word> _WordList_){
    WordList_=_WordList_;//保存单词列表
    for(int i=0;i<WordList_.size();i++){
        WordCardList_.append(new WordCard(ui->Contents_));
        //连接信号
        connect(WordCardList_[i],&WordCard::deleteWord,[=](){
            emit deleteWord(WordList_[i]);
        });
        //设置单词卡片位置及尺寸
        WordCardList_[i]->resize(ui->Contents_->width()-2*HorizontalMargin_,WordCardHeight_);
        WordCardList_[i]->move(HorizontalMargin_,TopMargin_+i*(WordCardHeight_+VerticalSpacing_));
        //设置单词卡片内容
        WordCardList_[i]->setWord(WordList_[i]);
        WordCardList_[i]->show();
    }
}
void WordCardList::clear(){
    for(int i=0;i<WordCardList_.size();i++){
        delete WordCardList_[i];
    }
    WordCardList_.clear();
    WordList_.clear();
}

//===================事件重载==========================
void WordCardList::resizeEvent(QResizeEvent *event){
    for(int i=0;i<WordCardList_.size();i++){
        auto _Card=WordCardList_[i];
        _Card->resize(ui->Contents_->width()-2*HorizontalMargin_,WordCardHeight_);
    }
    return QWidget::resizeEvent(event);
}
