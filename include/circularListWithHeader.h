#include "Abs_Chainlist.h"
#include "illegalParameterValue.h"
#ifndef CIRCULARLISTWITHHEADER_H
#define CIRCULARLISTWITHHEADER_H
namespace Huitoy{
template <class T>
class circularListWithHeader:public Abs_Chainlist<T>
{
    public:
        /*循环链表的构造函数*/
        circularListWithHeader();
        circularListWithHeader(const circularListWithHeader& theCircularList);
        circularListWithHeader(circularListWithHeader&& theCircularList)noexcept;
        circularListWithHeader(const LinearlistView<T>& view);
        circularListWithHeader(const ConstLinearlistView<T>& view);
        circularListWithHeader(const Linearlist<T>& theLinearlist);
        circularListWithHeader(const initializer_list<T>& init_list);
        circularListWithHeader(const T& element,unsigned n);
        circularListWithHeader(const T* tarray,unsigned n);
        /*循环链表的析构函数*/
        ~circularListWithHeader();
        /*循环链表的参数*/
        bool empty() const;
        unsigned size() const;
        void clear();
        /*链表指针移动*/
        void next() const;//work
        bool head() const;//work
        void switch_to_begin() const;//work
        T& thisElement();//work
        const T& thisElement() const;//work
        /*按照索引取元素*/
        T& operator[](unsigned index);
        const T& operator[](unsigned index) const;
        /*按照元素取索引*/
        unsigned search(const T& element_) const;
        /*从链表中删去一个元素*/
        void erase(unsigned index);
        void erase();//work
        void erasefront();
        void eraseback();
        /*向循环链表中插入一个元素*/
        void insert(unsigned index,const T& theElement);
        void insert(const T& theElement,bool front_ = true);//work
        void insertfront(const T& theElement);
        void insertback(const T& theElement);
        /*循环链表的赋值与赋值*/
        circularListWithHeader& operator= (const circularListWithHeader& theCircularList);
        circularListWithHeader& operator = (circularListWithHeader&& theCircularList)noexcept;
        circularListWithHeader& operator = (const LinearlistView<T>& view);
        circularListWithHeader& operator = (const ConstLinearlistView<T>& view);
        circularListWithHeader& operator = (const Linearlist<T>& theLinearlist);
        circularListWithHeader& operator = (const initializer_list<T>& init_list);
        circularListWithHeader& copy(const T* Tarray,unsigned n);
        /*合并两个循环链表*/
        void merge(const circularListWithHeader& theCircularList);
        void merge(const LinearlistView<T>& view);
        void merge(const ConstLinearlistView<T>& view);
        void merge(const Linearlist<T>& theLinearlist);
        void merge(const initializer_list<T>& init_list);
        void merge(const T* Tarray,unsigned n);
        /*创建线性表视图*/
        LinearlistView<T> createView();
        ConstLinearlistView<T> createConstView() const;
        ConstLinearlistView<T> createView() const;
        /*取子串*/
        LinearlistView<T> sublist(unsigned start_,unsigned end_);
        ConstLinearlistView<T> sublist(unsigned start_,unsigned end_) const;
        /*循环链表的迭代器*/
        ChainlistIterator<T> begin();
        ChainlistIterator<T> end();
        ConstChainlistIterator<T> begin() const;
        ConstChainlistIterator<T> end() const;
    protected:
        ChainNode<T>* headnode;
        mutable ChainNode<T>* thisnode;
        mutable ChainNode<T>* lastnode;
        ChainNode<T>* endnode;
        unsigned listSize;
    private:
};
/*循环链表的构造函数*/
template <class T>
circularListWithHeader<T>::circularListWithHeader(){
    //默认构造函数，生成一个空循环链表，headnode连着headnode即可
    listSize = 0;
    headnode = new ChainNode<T>;
    headnode->changeNextPointer(headnode);
    thisnode = headnode;
    lastnode = headnode;
    endnode = headnode;
}
template <class T>
circularListWithHeader<T>::circularListWithHeader(const circularListWithHeader& theCircularList){
//如果选择复制一个链表，则先生成一个headnode
    headnode =new ChainNode<T>;
    if(theCircularList.listSize == 0){
        //如果theCircularList为空，那么不用执行复制操作
        listSize = 0;
        headnode->changeNextPointer(headnode);
        thisnode = headnode;
        lastnode = headnode;
        endnode = headnode;
    }
    else{
        //否则，listSize等于theCircularList的listSize
        listSize = theCircularList.listSize;
        //然后开始逐个复制
        ChainNode<T>* thisNode_ = headnode;
            //thisNode_先以headnode进行初始化
        ChainNode<T>* theCircularList_thisnode = theCircularList.headnode->getNextPointer();
            //先后取theCircularList的首结点来对theCircularList_thisnode进行初始化
        for(unsigned i=0;i<listSize;i++){
            /*
            比如，如果listSize==1，那么，首先定义一个newnode复制theCircularList_thisnode，，然后thisNode_也就是headnode指向newnode，只进行了一轮循环，循环结束后thisNode_恰好为最后一个结点同时也是首结点，以此类推，最后thisNode_指向最后一个结点
              */
            ChainNode<T>* newnode = new ChainNode<T>(theCircularList_thisnode->get());
            //先创建一个newnode复制theCircularList_thisnode的内容
            thisNode_->changeNextPointer(newnode);
            //然后thisNode_相当于这轮的lastNode_，让其指向newnode
            thisNode_=newnode;
            theCircularList_thisnode = theCircularList_thisnode->getNextPointer();
            //随后，thisNode和theCircularList_thisnode指针同时后移
        }
        endnode = thisNode_;
        //循环结束后，thisNode_就是endNode，因此endNode进行赋值
        endnode->changeNextPointer(headnode);
        //endnode再指向头结点
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
        //然后初始化lastnode和thisnode
    }
}
template <class T>
circularListWithHeader<T>::circularListWithHeader(circularListWithHeader&& chain)noexcept{
    headnode = chain.headnode;
    chain.headnode = new ChainNode<T>;
    endnode = chain.endnode;
    chain.endnode = nullptr;
    listSize = chain.listSize;
    chain.listSize = 0;
    thisnode = headnode->getNextPointer();
    lastnode = headnode;
}
template <class T>
circularListWithHeader<T>::circularListWithHeader(const LinearlistView<T>& view){
    listSize = view.size();
    headnode = new ChainNode<T>;
    if(listSize==0){
        headnode->changeNextPointer(headnode);
        endnode = headnode;
        lastnode = headnode;
        thisnode = headnode;
    }else{
        ChainNode<T>* lastNode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
        endnode->changeNextPointer(headnode);
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
    }
}
template <class T>
circularListWithHeader<T>::circularListWithHeader(const ConstLinearlistView<T>& view){
    listSize = view.size();
    headnode = new ChainNode<T>;
    if(listSize==0){
        headnode->changeNextPointer(headnode);
        endnode = headnode;
        lastnode = headnode;
        thisnode = headnode;
    }else{
        ChainNode<T>* lastNode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
        endnode->changeNextPointer(headnode);
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
    }
}
template <class T>
circularListWithHeader<T>::circularListWithHeader(const Linearlist<T>& theLinearList){
    ConstLinearlistView<T> view = theLinearList.createConstView();
    listSize = view.size();
    headnode = new ChainNode<T>;
    if(listSize==0){
        headnode->changeNextPointer(headnode);
        endnode = headnode;
        lastnode = headnode;
        thisnode = headnode;
    }else{
        ChainNode<T>* lastNode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
        endnode->changeNextPointer(headnode);
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
    }
}
template <class T>
circularListWithHeader<T>::circularListWithHeader(const initializer_list<T>& init_list){
    listSize = init_list.size();
    headnode = new ChainNode<T>;
    if(listSize==0){
        headnode->changeNextPointer(headnode);
        endnode = headnode;
        lastnode = headnode;
        thisnode = headnode;
    }else{
        ChainNode<T>* lastNode_ = headnode;
        for(const T& element_:init_list){
            ChainNode<T>* newnode = new ChainNode<T>(element_);
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
        endnode->changeNextPointer(headnode);
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
    }
}
template <class T>
circularListWithHeader<T>::circularListWithHeader(const T& element,unsigned n){
    headnode = new ChainNode<T>;
    listSize = n;
    if(n==0){
        headnode->changeNextPointer(headnode);
        lastnode = headnode;
        thisnode = headnode;
        endnode = headnode;
    }else{
        ChainNode<T>* LastNode_ = headnode;
        for(unsigned i=0;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(element);
            LastNode_->changeNextPointer(newnode);
            LastNode_ = newnode;
        }
        endnode = LastNode_;
        endnode->changeNextPointer(headnode);
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
    }
}
template <class T>
circularListWithHeader<T>::circularListWithHeader(const T* Tarray,unsigned n){
    headnode = new ChainNode<T>;//先创建头结点
    if(n==0){
        //如果n==0，说明要生成一个空链表
        listSize = 0;
        headnode->changeNextPointer(headnode);
        thisnode = headnode;
        lastnode = headnode;
        endnode = headnode;
    }else{
        listSize = n;//先令listSize=n
        ChainNode<T>* thisNode_ = headnode;
        //先用headnode进行初始化
        for(unsigned i=0;i<listSize;i++){
            //i的含义是创建索引为i的元素，在每轮循环之前，thisNode_是lastNode_
            ChainNode<T>* newnode = new ChainNode<T>(Tarray[i]);
            //因此，每轮先创建一个newnode赋值Tarray[i]
            thisNode_->changeNextPointer(newnode);
            //然后thisNode_指向newnode
            thisNode_ = newnode;
            //然后thisNode_后移
        }//循环之后，thisNode_就是最后一个元素
        endnode = thisNode_;
        //在初始化lastnode和thisnode
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
    }
}
/*循环链表的析构函数*/
template <class T>
circularListWithHeader<T>::~circularListWithHeader(){
    if(listSize == 0){
        delete headnode;
    }else{
        ChainNode<T>* this_thisnode = headnode->getNextPointer();
        for(unsigned i=0;i<listSize;i++){
            ChainNode<T>* nextnode = this_thisnode->getNextPointer();
            delete this_thisnode;
            this_thisnode = nextnode;
        }
        delete headnode;
    }
}
template <class T>
void circularListWithHeader<T>::clear(){
    if(listSize==0) return;
    else{
        ChainNode<T>* deletenode = headnode->getNextPointer();
        while(deletenode!=headnode){
            ChainNode<T>* nextnode = deletenode->getNextPointer();
            delete deletenode;
            deletenode = nextnode;
        }
        headnode->changeNextPointer(headnode);
        endnode=headnode;
        thisnode=headnode;
        lastnode=headnode;
        listSize=0;
    }
}
/*循环链表的相关参数*/
template <class T>
bool circularListWithHeader<T>::empty() const{
    return listSize == 0;
}
template <class T>
unsigned circularListWithHeader<T>::size() const{
    return listSize;
}
/*循环链表的指针移动*/
template <class T>
bool circularListWithHeader<T>::head() const{
    if(listSize==0) return true;
    return thisnode == headnode;
}
template <class T>
void circularListWithHeader<T>::next() const{
    if(listSize==0) return;
    lastnode = thisnode;
    thisnode = thisnode->getNextPointer();
}
template <class T>
T& circularListWithHeader<T>::thisElement(){
    if(listSize==0) return headnode->get();
    return thisnode->get();
}
template <class T>
const T& circularListWithHeader<T>::thisElement() const{
    if(listSize==0) return headnode->get();
    return thisnode->get();
}
/*按照索引取元素*/
template <class T>
T& circularListWithHeader<T>::operator[](unsigned index){
    if(index>=listSize){
        throw illegalParameterValue("Index out of range.");
    }
    if(index==listSize-1) return endnode->get();
    ChainNode<T>* this_thisnode = headnode;
    for(unsigned i=0;i<=index;i++){
        this_thisnode = this_thisnode->getNextPointer();
    }
    return this_thisnode->get();
}
template <class T>
const T& circularListWithHeader<T>::operator[](unsigned index) const{
    if(index>=listSize){
        throw illegalParameterValue("Index out of range.");
    }
    if(index==listSize-1) return endnode->get();
    const ChainNode<T>* this_thisnode = headnode;
    for(unsigned i=0;i<=index;i++){
        this_thisnode = this_thisnode->getNextPointer();
    }
    return this_thisnode->get();
}
/*搜索某个元素首次出现的索引*/
template <class T>
unsigned circularListWithHeader<T>::search(const T& element_) const{
    if(listSize==0){
        return 0;
    }
    else{
        const ChainNode<T>* this_thisnode = headnode;
        for(unsigned i=0;i<listSize;i++){
            this_thisnode = this_thisnode->getNextPointer();
            if(this_thisnode->get()==element_) return i;
        }
        return listSize;
    }
}
/*从循环链表中删去一个元素*/
template <class T>
void circularListWithHeader<T>::erase(){
    if(thisnode==headnode) return;
    else{
        ChainNode<T>* nextnode = thisnode->getNextPointer();
        lastnode->changeNextPointer(nextnode);
        delete thisnode;
        thisnode = nextnode;
        listSize--;
    }
}
template <class T>
void circularListWithHeader<T>::erase(unsigned index){
    if(index>=listSize) throw illegalParameterValue("index out of range.");
    else if(listSize==1){//如果listSize==1，则erase就是删除唯一的一个元素
        delete headnode->getNextPointer();
        headnode->changeNextPointer(headnode);
        thisnode=headnode;
        lastnode=headnode;
        endnode=headnode;
        listSize=0;
    }else if(index==0){
        ChainNode<T>* deletenode = headnode->getNextPointer();
        ChainNode<T>* nextnode = deletenode->getNextPointer();
        if(thisnode==deletenode){
            thisnode=nextnode;
        }else if(lastnode==deletenode){
            lastnode=headnode;
        }else{}
        headnode->changeNextPointer(nextnode);
        delete deletenode;
        listSize--;
    }else if(index==listSize-1){
        ChainNode<T>* lastNode_ = headnode;
        ChainNode<T>* deletenode = endnode;
        for(unsigned i=0;i<listSize-2;i++){
            lastNode_ = lastNode_->getNextPointer();
        }
        if(thisnode==endnode){
            thisnode = headnode;
        }else if(lastnode==endnode){
            lastnode = lastNode_;
        }else{}
        endnode=lastNode_;
        endnode->changeNextPointer(headnode);
        listSize--;
        delete deletenode;
    }else{
        ChainNode<T>* lastNode_ =headnode;
        for(unsigned i=0;i<index;i++){
            lastNode_ = lastNode_->getNextPointer();
        }
        ChainNode<T>* deletenode = lastNode_->getNextPointer();
        ChainNode<T>* nextnode = deletenode->getNextPointer();
        lastNode_->changeNextPointer(nextnode);
        if(thisnode==deletenode){
            thisnode=nextnode;
        }else if(lastnode==deletenode){
            lastnode=lastNode_;
        }else{}
        delete deletenode;
        listSize--;
    }
}
template <class T>
void circularListWithHeader<T>::erasefront(){
    if(listSize==0) return;
    else if(listSize==1){
        ChainNode<T>* deletenode = headnode->getNextPointer();
        headnode->changeNextPointer(headnode);
        listSize=0;
        delete deletenode;
        thisnode = headnode;
        lastnode = headnode;
        endnode = headnode;
    }else if(thisnode == headnode->getNextPointer()){
        ChainNode<T>* deletenode = headnode->getNextPointer();
        thisnode = deletenode->getNextPointer();
        headnode->changeNextPointer(thisnode);
        delete deletenode;
        listSize--;
    }else if(lastnode == headnode->getNextPointer()){
        ChainNode<T>* deletenode = headnode->getNextPointer();
        lastnode = headnode;
        headnode->changeNextPointer(deletenode->getNextPointer());
        delete deletenode;
        listSize--;
    }else{
        ChainNode<T>* deletenode = headnode->getNextPointer();
        headnode->changeNextPointer(deletenode->getNextPointer());
        delete deletenode;
        listSize--;
    }
}
template <class T>
void circularListWithHeader<T>::eraseback(){
    if(listSize==0) return;
    else if(listSize==1){
        ChainNode<T>* deletenode = headnode->getNextPointer();
        headnode->changeNextPointer(headnode);
        delete deletenode;
        listSize=0;
        thisnode=headnode;
        lastnode = headnode;
        endnode =headnode;
    }else if(thisnode==endnode){
        ChainNode<T>* deletenode = thisnode;
        endnode = lastnode;
        thisnode = headnode;
        listSize--;
        endnode->changeNextPointer(headnode);
        delete deletenode;
    }else if(lastnode==endnode){
        ChainNode<T>* deletenode = endnode;
        ChainNode<T>* thisnode_ = headnode;
        for(unsigned i=0;i<listSize-1;i++){
            thisnode_ = thisnode_->getNextPointer();
        }
        endnode = thisnode_;
        lastnode = thisnode_;
        listSize--;
        endnode->changeNextPointer(headnode);
        delete deletenode;
    }else{
        ChainNode<T>* deletenode = endnode;
        ChainNode<T>* thisnode_ = headnode;
        for(unsigned i=0;i<listSize-1;i++){
            thisnode_ = thisnode_->getNextPointer();
        }
        endnode = thisnode_;
        listSize--;
        endnode->changeNextPointer(headnode);
        delete deletenode;
    }
}
/*往循环链表中插入一个元素*/
template <class T>
void circularListWithHeader<T>::insert(const T& element_,bool front_){
    if(listSize==0){
        lastnode = headnode;
        endnode = new ChainNode<T>(element_,headnode);
        headnode->changeNextPointer(endnode);
        thisnode = endnode;
        listSize++;
    }else if(front_){
        ChainNode<T>* newnode = new ChainNode<T>(element_,thisnode);
        lastnode->changeNextPointer(newnode);
        lastnode=newnode;
        listSize++;
    }else if(thisnode==endnode){
        ChainNode<T>* newnode = new ChainNode<T>(element_,headnode);
        endnode->changeNextPointer(newnode);
        endnode=newnode;
        lastnode = thisnode;
        thisnode = newnode;
        listSize++;
    }else{
        ChainNode<T>* newnode = new ChainNode<T>(element_,thisnode->getNextPointer());
        thisnode->changeNextPointer(newnode);
        lastnode = thisnode;
        thisnode = newnode;
        listSize++;
    }
}
template <class T>
void circularListWithHeader<T>::insert(unsigned index,const T& element_){
    if(index>listSize) throw illegalParameterValue("index out of range.");
    else if(listSize==0){
        ChainNode<T>* newfirstnode = new ChainNode<T>(element_,headnode);
        headnode->changeNextPointer(newfirstnode);
        listSize=1;
        thisnode=newfirstnode;
    }else if(index==0){
        ChainNode<T>* oldfirstnode = headnode->getNextPointer();
        ChainNode<T>* newfirstnode = new ChainNode<T>(element_,oldfirstnode);
        headnode->changeNextPointer(newfirstnode);
        if(thisnode==oldfirstnode) lastnode=newfirstnode;
        listSize++;
    }else if(index==listSize){
        ChainNode<T>* newendnode = new ChainNode<T>(element_,headnode);
        ChainNode<T>* oldendnode = endnode;
        endnode->changeNextPointer(newendnode);
        endnode=newendnode;
        if(lastnode==oldendnode) lastnode = endnode;
        listSize++;
    }else{
        ChainNode<T>* LastNode_ = headnode;
        for(unsigned i=0;i<index;i++){
            LastNode_ = LastNode_->getNextPointer();
        }
        ChainNode<T>* nextnode = LastNode_->getNextPointer();
        ChainNode<T>* newnode = new ChainNode<T>(element_,nextnode);
        LastNode_->changeNextPointer(newnode);
        listSize++;
        if(thisnode==nextnode) lastnode=newnode;
    }
}
template <class T>
void circularListWithHeader<T>::insertfront(const T& element){
    if(listSize==0){
        lastnode = headnode;
        thisnode = new ChainNode<T>(element,headnode);
        endnode = thisnode;
        headnode->changeNextPointer(thisnode);
        listSize=1;
    }else if(thisnode==headnode->getNextPointer()){
        ChainNode<T>* newnode = new ChainNode<T>(element,headnode->getNextPointer());
        headnode->changeNextPointer(newnode);
        lastnode = newnode;
        listSize++;
    }else{
        ChainNode<T>* newnode = new ChainNode<T>(element,headnode->getNextPointer());
        headnode->changeNextPointer(newnode);
        listSize++;
    }
}
template <class T>
void circularListWithHeader<T>::insertback(const T& element){
    if(listSize==0){
        lastnode = headnode;
        thisnode = new ChainNode<T>(element,headnode);
        endnode = thisnode;
        headnode->changeNextPointer(thisnode);
        listSize=1;
    }else if(lastnode==endnode){
        ChainNode<T>* newnode = new ChainNode<T>(element,headnode);
        endnode->changeNextPointer(newnode);
        endnode = newnode;
        thisnode = newnode;
        listSize++;
    }else{
        ChainNode<T>* newnode = new ChainNode<T>(element,headnode);
        endnode->changeNextPointer(newnode);
        endnode = newnode;
        listSize++;
    }
}
/*循环链表的赋值和复制*/
template <class T>
circularListWithHeader<T>& circularListWithHeader<T>::operator=(const circularListWithHeader& theCircularList){
    clear();
    if(theCircularList.listSize == 0){
        //如果theCircularList为空，那么不用执行复制操作
        listSize = 0;
        headnode->changeNextPointer(headnode);
        thisnode = headnode;
        lastnode = headnode;
        endnode = headnode;
    }
    else{
        //否则，listSize等于theCircularList的listSize
        listSize = theCircularList.listSize;
        //然后开始逐个复制
        ChainNode<T>* thisNode_ = headnode;
            //thisNode_先以headnode进行初始化
        ChainNode<T>* theCircularList_thisnode = theCircularList.headnode->getNextPointer();
            //先后取theCircularList的首结点来对theCircularList_thisnode进行初始化
        for(unsigned i=0;i<listSize;i++){
            /*
            比如，如果listSize==1，那么，首先定义一个newnode复制theCircularList_thisnode，，然后thisNode_也就是headnode指向newnode，只进行了一轮循环，循环结束后thisNode_恰好为最后一个结点同时也是首结点，以此类推，最后thisNode_指向最后一个结点
              */
            ChainNode<T>* newnode = new ChainNode<T>(theCircularList_thisnode->get());
            //先创建一个newnode复制theCircularList_thisnode的内容
            thisNode_->changeNextPointer(newnode);
            //然后thisNode_相当于这轮的lastNode_，让其指向newnode
            thisNode_=newnode;
            theCircularList_thisnode = theCircularList_thisnode->getNextPointer();
            //随后，thisNode和theCircularList_thisnode指针同时后移
        }
        endnode = thisNode_;
        //循环结束后，thisNode_就是endNode，因此endNode进行赋值
        endnode->changeNextPointer(headnode);
        //endnode再指向头结点
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
        //然后初始化lastnode和thisnode
    }
    return *this;
}
template <class T>
circularListWithHeader<T>& circularListWithHeader<T>::operator = (circularListWithHeader&& chain)noexcept{
    clear();
    delete headnode;
    headnode = chain.headnode;
    chain.headnode = new ChainNode<T>;
    endnode = chain.endnode;
    chain.endnode = nullptr;
    listSize = chain.listSize;
    chain.listSize = 0;
    thisnode = headnode->getNextPointer();
    lastnode = headnode;
    return *this;
}
template <class T>
circularListWithHeader<T>& circularListWithHeader<T>::operator = (const LinearlistView<T>& view){
    clear();
    listSize = view.size();
    if(listSize==0){
        headnode->changeNextPointer(headnode);
        endnode = headnode;
        lastnode = headnode;
        thisnode = headnode;
    }else{
        ChainNode<T>* lastNode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
        endnode->changeNextPointer(headnode);
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
    }
    return *this;
}
template <class T>
circularListWithHeader<T>& circularListWithHeader<T>::operator = (const ConstLinearlistView<T>& view){
    clear();
    listSize = view.size();
    if(listSize==0){
        headnode->changeNextPointer(headnode);
        endnode = headnode;
        lastnode = headnode;
        thisnode = headnode;
    }else{
        ChainNode<T>* lastNode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
        endnode->changeNextPointer(headnode);
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
    }
    return *this;
}
template <class T>
circularListWithHeader<T>& circularListWithHeader<T>::operator = (const Linearlist<T>& theLinearList){
    clear();
    ConstLinearlistView<T> view = theLinearList.createConstView();
    listSize = view.size();
    if(listSize==0){
        headnode->changeNextPointer(headnode);
        endnode = headnode;
        lastnode = headnode;
        thisnode = headnode;
    }else{
        ChainNode<T>* lastNode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
        endnode->changeNextPointer(headnode);
        lastnode = headnode;
        thisnode = headnode->getNextPointer();
    }
    return *this;
}
template <class T>
circularListWithHeader<T>& circularListWithHeader<T>::operator = (const initializer_list<T>& init_list){
    clear();
    listSize = init_list.size();
    ChainNode<T>* lastNode_ = headnode;
    for(const T& element_:init_list){
        ChainNode<T>* newnode = new ChainNode<T>(element_);
        lastNode_->changeNextPointer(newnode);
        lastNode_ = newnode;
    }
    endnode = lastNode_;
    endnode->changeNextPointer(headnode);
    lastnode = headnode;
    thisnode = headnode->getNextPointer();
    return *this;
}
template <class T>
circularListWithHeader<T>& circularListWithHeader<T>::copy(const T* Tarray,unsigned n){
    ChainNode<T>* this_thisnode = headnode->getNextPointer();
    for(unsigned i=0;i<listSize;i++){
        delete this_thisnode;
        this_thisnode = this_thisnode->getNextPointer();
    }
    headnode->changeNextPointer(headnode);
    if(n==0) {
        listSize = 0;
        thisnode = headnode;
        lastnode = headnode;
        endnode = headnode;
    }
    listSize = n;
    ChainNode<T>* newnode = new ChainNode<T>;
    headnode->changeNextPointer(newnode);
    lastnode = headnode;
    thisnode = newnode;
    this_thisnode=newnode;
    for(unsigned i=0;i<listSize;i++){
        this_thisnode->get() = Tarray[i];
        if(i<listSize-1){
            newnode = new ChainNode<T>;
            this_thisnode->changeNextPointer(newnode);
            this_thisnode = newnode;
        }else{
            this_thisnode->changeNextPointer(headnode);
            endnode = this_thisnode;
        }
    }
    return *this;
}
/*两个链表的合并*/
template <class T>
void circularListWithHeader<T>::merge(const circularListWithHeader& theCircularList){
    unsigned n = theCircularList.listSize;
    if(n==0) return;
    else if(listSize==0) *this = theCircularList;
    else{
        ChainNode<T>* oldEndnode = endnode;
        ChainNode<T>* LastNode_ = endnode;
        ChainNode<T>* chain_thisnode = theCircularList.headnode->getNextPointer();
        for(unsigned i=0;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(chain_thisnode->get());
            LastNode_->changeNextPointer(newnode);
            LastNode_ = newnode;
            chain_thisnode = chain_thisnode->getNextPointer();
        }
        endnode = LastNode_;
        endnode->changeNextPointer(headnode);
        if(thisnode == headnode) thisnode = oldEndnode->getNextPointer();
        listSize += n;
    }
}
template <class T>
void circularListWithHeader<T>::merge(const LinearlistView<T>& view){
    unsigned n = view.size();
    if(n==0) return;
    else if(listSize==0) *this = view;
    else{
        ChainNode<T>* oldEndnode = endnode;
        ChainNode<T>* LastNode_ = endnode;
        for(unsigned i=0;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            LastNode_->changeNextPointer(newnode);
            LastNode_ = newnode;
        }
        endnode = LastNode_;
        endnode->changeNextPointer(headnode);
        if(thisnode == headnode) thisnode = oldEndnode->getNextPointer();
        listSize += n;
    }
}
template <class T>
void circularListWithHeader<T>::merge(const ConstLinearlistView<T>& view){
    unsigned n = view.size();
    if(n==0) return;
    else if(listSize==0) *this = view;
    else{
        ChainNode<T>* oldEndnode = endnode;
        ChainNode<T>* LastNode_ = endnode;
        for(unsigned i=0;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            LastNode_->changeNextPointer(newnode);
            LastNode_ = newnode;
        }
        endnode = LastNode_;
        endnode->changeNextPointer(headnode);
        if(thisnode == headnode) thisnode = oldEndnode->getNextPointer();
        listSize += n;
    }
}
template <class T>
void circularListWithHeader<T>::merge(const Linearlist<T>& theLinearList){
    ConstLinearlistView<T> view = theLinearList.createConstView();
    unsigned n = view.size();
    if(n==0) return;
    else if(listSize==0) *this = view;
    else{
        ChainNode<T>* oldEndnode = endnode;
        ChainNode<T>* LastNode_ = endnode;
        for(unsigned i=0;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            LastNode_->changeNextPointer(newnode);
            LastNode_ = newnode;
        }
        endnode = LastNode_;
        endnode->changeNextPointer(headnode);
        if(thisnode == headnode) thisnode = oldEndnode->getNextPointer();
        listSize += n;
    }
}
template <class T>
void circularListWithHeader<T>::merge(const initializer_list<T>& init_list){
    unsigned n = init_list.size();
    if(n==0) return;
    else if(listSize==0) *this = init_list;
    else{
        ChainNode<T>* oldEndnode = endnode;
        ChainNode<T>* LastNode_ = endnode;
        for(const T& element_:init_list){
            ChainNode<T>* newnode = new ChainNode<T>(element_);
            LastNode_->changeNextPointer(newnode);
            LastNode_ = newnode;
        }
        if(thisnode ==headnode)  thisnode = oldEndnode->getNextPointer();
        endnode = LastNode_;
        listSize+=n;
    }
}
template <class T>
void circularListWithHeader<T>::merge(const T* Tarray,unsigned n){
    if(n==0) return;
    else if(listSize==0) copy(Tarray,n);
    else{
        ChainNode<T>* oldEndnode = endnode;
        ChainNode<T>* LastNode_ = endnode;
        for(unsigned i=0;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(Tarray[i]);
            LastNode_->changeNextPointer(newnode);
            LastNode_ = newnode;
        }
        endnode = LastNode_;
        endnode->changeNextPointer(headnode);
        if(thisnode == headnode) thisnode = oldEndnode->getNextPointer();
        listSize += n;
    }
}
/*循环链表的迭代器*/
template <class T>
ChainlistIterator<T> circularListWithHeader<T>::begin(){
    return ChainlistIterator<T>(headnode->getNextPointer());
}
template <class T>
ChainlistIterator<T> circularListWithHeader<T>::end(){
    return ChainlistIterator<T>(headnode);
}
template <class T>
ConstChainlistIterator<T> circularListWithHeader<T>::begin() const{
    return ConstChainlistIterator<T>(headnode->getNextPointer());
}
template <class T>
ConstChainlistIterator<T> circularListWithHeader<T>::end() const{
    return ConstChainlistIterator<T>(headnode);
}
template <class T>
void circularListWithHeader<T>::switch_to_begin() const{
    thisnode = headnode->getNextPointer();
    lastnode = headnode;
}
/*创建线性表视图*/
template <class T>
LinearlistView<T> circularListWithHeader<T>::createView(){
    if(listSize==0) return LinearlistView<T>();
    else{
        unsigned index=0;
        LinearlistView<T> view(listSize);
        view.changeSize(listSize);
        for(auto& element:*this){
            view(index) = &element;
            index++;
        }
        return view;
    }
}
template <class T>
ConstLinearlistView<T> circularListWithHeader<T>::createView() const{
    if(listSize==0) return ConstLinearlistView<T>();
    else{
        unsigned index=0;
        ConstLinearlistView<T> view(listSize);
        view.changeSize(listSize);
        for(const auto& element:*this){
            view(index) = &element;
            index++;
        }
        return view;
    }
}
template <class T>
ConstLinearlistView<T> circularListWithHeader<T>::createConstView() const{
    if(listSize==0) return ConstLinearlistView<T>();
    else{
        unsigned index=0;
        ConstLinearlistView<T> view(listSize);
        view.changeSize(listSize);
        for(const auto& element:*this){
            view(index) = &element;
            index++;
        }
        return view;
    }
}
/*取子串*/
template <class T>
LinearlistView<T> circularListWithHeader<T>::sublist(unsigned begin_,unsigned end_){
    if(begin_>end_||begin_>=listSize||end_>=listSize) throw illegalParameterValue("illegal parameter: begin>end Or Index out of range!");
    unsigned viewsize = end_-begin_+1;
    LinearlistView<T> result(viewsize);
    result.changeSize(viewsize,false);
    unsigned index=0;
    for(auto& element:*this){
        if(index<begin_){
            index++;
        }else if(index>=end_){
            result(index-begin_) = &element;
            break;
        }else{
            result(index-begin_) = &element;
            index++;
        }
    }
    return result;
}
template <class T>
ConstLinearlistView<T> circularListWithHeader<T>::sublist(unsigned begin_,unsigned end_) const{
    if(begin_>end_||begin_>=listSize||end_>=listSize) throw illegalParameterValue("illegal parameter: begin>end Or Index out of range!");
    unsigned viewsize = end_-begin_+1;
    ConstLinearlistView<T> result(viewsize);
    result.changeSize(viewsize,false);
    unsigned index=0;
    for(auto& element:*this){
        if(index<begin_){
            index++;
        }else if(index>=end_){
            result(index-begin_) = &element;
            break;
        }else{
            result(index-begin_) = &element;
            index++;
        }
    }
    return result;
}
}
#endif // CIRCULARLISTWITHHEADER_H
