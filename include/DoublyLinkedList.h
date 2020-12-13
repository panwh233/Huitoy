#include "illegalParameterValue.h"
#include "Abs_DoublyLinkedList.h"
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
namespace Huitoy{
template <class T>
class DoublyLinkedList:public Abs_DoublyLinkedList<T>
{
    public:
        //构造函数
        DoublyLinkedList();
        DoublyLinkedList(const T* Tarray,unsigned n);
        DoublyLinkedList(const T& element,unsigned n);
        DoublyLinkedList(const initializer_list<T>& init_list);
        DoublyLinkedList(const DoublyLinkedList& theDoublyLinkedList);
        DoublyLinkedList(DoublyLinkedList&& theDoublyLinkedList)noexcept;
        DoublyLinkedList(const LinearlistView<T>& view);
        DoublyLinkedList(const ConstLinearlistView<T>& view);
        DoublyLinkedList(const Linearlist<T>& theLinearlist);
        //析构函数
        ~DoublyLinkedList();
        void clear();
        //检测双向链表是否为空
        bool empty() const;
        //检测双向链表的长度
        unsigned size() const;
        //复制
        DoublyLinkedList& copy(const T* Tarray,unsigned n);
        DoublyLinkedList& operator=(const DoublyLinkedList& theDoublyLinkedList);
        DoublyLinkedList& operator=(const initializer_list<T>& init_list);
        DoublyLinkedList& operator=(DoublyLinkedList&& theDoublyLinkedList)noexcept;
        DoublyLinkedList& operator=(const LinearlistView<T>& view);
        DoublyLinkedList& operator=(const ConstLinearlistView<T>& view);
        DoublyLinkedList& operator=(const Linearlist<T>& theLinearlist);
        //合并
        void merge(const T* Tarray,unsigned n);
        void merge(const initializer_list<T>& init_list);
        void merge(const DoublyLinkedList& theDoublyLinkedList);
        void merge(const LinearlistView<T>& view);
        void merge(const ConstLinearlistView<T>& view);
        void merge(const Linearlist<T>& theLinearlist);
        //查，改
        T& operator[](unsigned index);
        const T& operator[](unsigned index)const;
        unsigned search(const T& element_) const;
        //增
        void insert(const T& element_,bool front_=true);
        void insert(unsigned index,const T& element_);
        void insertfront(const T& element);
        void insertback(const T& element);
        //删
        void erase();
        void erase(unsigned index);
        void erasefront();
        void eraseback();
        //移动
        bool nullPointer() const;
        void switch_to_begin() const;
        void switch_to_end() const;
        void next() const;
        void last() const;
        T& thisElement();
        const T& thisElement() const;
        /*创建线性表视图*/
        LinearlistView<T> createView();
        ConstLinearlistView<T> createConstView() const;
        ConstLinearlistView<T> createView() const;
        /*取子串*/
        LinearlistView<T> sublist(unsigned start_,unsigned end_);
        ConstLinearlistView<T> sublist(unsigned start_,unsigned end_) const;
        //迭代器
        DoublyLinkedListIterator<T> begin();
        DoublyLinkedListIterator<T> end();
        ConstDoublyLinkedListIterator<T> begin() const;
        ConstDoublyLinkedListIterator<T> end() const;

    protected:
        unsigned listSize;
        DoublyLinkedListNode<T>* firstnode;
        DoublyLinkedListNode<T>* endnode;
        mutable DoublyLinkedListNode<T>* thisnode;
    private:
};
//构造函数
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(){//如果调用默认构造函数，直接构造一个空的链表
    listSize = 0;
    firstnode = nullptr;
    endnode = nullptr;
    thisnode = nullptr;
}
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const T& element,unsigned n){
    listSize = n;
    if(n==0){
        firstnode = nullptr;
        endnode = nullptr;
        thisnode = nullptr;
    }else{
        firstnode = new DoublyLinkedListNode<T>(element);
        thisnode = firstnode;
        DoublyLinkedListNode<T>* LastNode_ = firstnode;
        for(unsigned i=1;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element);
            LastNode_->setNextnode(newnode);
            newnode->setLastnode(LastNode_);
            LastNode_ = newnode;
        }
        endnode = LastNode_;
    }
}
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const T* Tarray,unsigned n){
    if(n==0){//如果n==0，生成一个空的双向链表
        listSize=0;
        firstnode=nullptr;
        endnode = nullptr;
        thisnode = nullptr;
    }else{
        listSize = n;
        DoublyLinkedListNode<T>* thisNode_ = new DoublyLinkedListNode<T>(Tarray[0]);
        firstnode=thisNode_;
        thisnode=thisNode_;
        for(unsigned i=1;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(Tarray[i]);
            newnode->setLastnode(thisNode_);
            thisNode_->setNextnode(newnode);
            thisNode_=newnode;
        }
        endnode=thisNode_;
    }
}
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& theDoublyLinkedList){
    if(theDoublyLinkedList.listSize==0){
        listSize=0;
        firstnode = nullptr;
        endnode =nullptr;
        thisnode = nullptr;
    }else{
        listSize=theDoublyLinkedList.listSize;
        DoublyLinkedListNode<T>* theDoublyLinkedList_thisnode = theDoublyLinkedList.firstnode;
        DoublyLinkedListNode<T>* thisNode_ = new DoublyLinkedListNode<T>(theDoublyLinkedList_thisnode->get());
        firstnode = thisNode_;
        thisnode = thisNode_;
        theDoublyLinkedList_thisnode = theDoublyLinkedList_thisnode->getNextnode();
        for(unsigned i=1;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(theDoublyLinkedList_thisnode->get());
            newnode->setLastnode(thisNode_);
            thisNode_->setNextnode(newnode);
            theDoublyLinkedList_thisnode = theDoublyLinkedList_thisnode->getNextnode();
            thisNode_ = thisNode_->getNextnode();
        }
        endnode = thisNode_;
    }
}
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList&& chain) noexcept{
    firstnode = chain.firstnode;
    chain.firstnode = nullptr;
    endnode = chain.endnode;
    chain.endnode = nullptr;
    thisnode = firstnode;
    listSize = chain.listSize;
    chain.listSize=0;
}
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const LinearlistView<T>& view){
    listSize = view.size();
    if(listSize==0){
        firstnode = nullptr;
        endnode = nullptr;
        thisnode =nullptr;
    }else{
        firstnode = new DoublyLinkedListNode<T>(view[0]);
        DoublyLinkedListNode<T>* lastNode_ = firstnode;
        thisnode = firstnode;
        for(unsigned i=1;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
    }
}
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const ConstLinearlistView<T>& view){
    listSize = view.size();
    if(listSize==0){
        firstnode = nullptr;
        endnode = nullptr;
        thisnode =nullptr;
    }else{
        firstnode = new DoublyLinkedListNode<T>(view[0]);
        DoublyLinkedListNode<T>* lastNode_ = firstnode;
        thisnode = firstnode;
        for(unsigned i=1;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
    }
}
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const Linearlist<T>& theLinearlist){
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    listSize = view.size();
    if(listSize==0){
        firstnode = nullptr;
        endnode = nullptr;
        thisnode =nullptr;
    }else{
        firstnode = new DoublyLinkedListNode<T>(view[0]);
        DoublyLinkedListNode<T>* lastNode_ = firstnode;
        thisnode = firstnode;
        for(unsigned i=1;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
    }
}
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const initializer_list<T>& init_list){
    listSize = init_list.size();
    if(listSize==0){
        firstnode = nullptr;
        endnode = nullptr;
        thisnode = nullptr;
    }else{
        unsigned index = 0;
        DoublyLinkedListNode<T>* lastNode_;
        for(const T& element_:init_list){
            if(index==0){
                firstnode = new DoublyLinkedListNode<T>(element_);
                thisnode = firstnode;
                lastNode_ = firstnode;
            }else{
                DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element_);
                lastNode_->setNextnode(newnode);
                newnode->setLastnode(lastNode_);
                lastNode_ = newnode;
            }
            index++;
        }
        endnode = lastNode_;
    }
}
//析构函数
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList(){
    if(listSize==0) return;
    thisnode = firstnode;
    for(unsigned i=0;i<listSize;i++){
        DoublyLinkedListNode<T>* nextnode = thisnode->getNextnode();
        delete thisnode;
        thisnode = nextnode;
    }
}
template <class T>
void DoublyLinkedList<T>::clear(){
    if(listSize==0) return;
    thisnode = firstnode;
    for(unsigned i=0;i<listSize;i++){
        DoublyLinkedListNode<T>* nextnode = thisnode->getNextnode();
        delete thisnode;
        thisnode = nextnode;
    }
    thisnode=nullptr;
    firstnode=nullptr;
    endnode=nullptr;
    listSize=0;
}
//空和长度
template <class T>
bool DoublyLinkedList<T>::empty() const{
    return listSize==0;
}
template <class T>
unsigned DoublyLinkedList<T>::size() const{
    return listSize;
}
//复制
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator = (const DoublyLinkedList& theDoublyLinkedList){
   clear();//首先清空链表
   listSize = theDoublyLinkedList.listSize;
   if(listSize==0) {}
   else{
        DoublyLinkedListNode<T>* theDoublyLinkedList_thisnode = theDoublyLinkedList.firstnode;
        DoublyLinkedListNode<T>* thisNode_ = new DoublyLinkedListNode<T>(theDoublyLinkedList_thisnode->get());
        firstnode = thisNode_;
        thisnode = thisNode_;
        theDoublyLinkedList_thisnode = theDoublyLinkedList_thisnode->getNextnode();
        for(unsigned i=1;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(theDoublyLinkedList_thisnode->get());
            newnode->setLastnode(thisNode_);
            thisNode_->setNextnode(newnode);
            theDoublyLinkedList_thisnode = theDoublyLinkedList_thisnode->getNextnode();
            thisNode_ = thisNode_->getNextnode();
        }
        endnode = thisNode_;
   }
   return *this;
}
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator = (DoublyLinkedList&& theDoublyLinkedList)noexcept{
    clear();
    firstnode = theDoublyLinkedList.firstnode;
    theDoublyLinkedList.firstnode = nullptr;
    endnode = theDoublyLinkedList.endnode;
    theDoublyLinkedList.endnode = nullptr;
    listSize = theDoublyLinkedList.listSize;
    theDoublyLinkedList.listSize = 0;
    thisnode = firstnode;
    return *this;
}
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator = (const LinearlistView<T>& view){
    clear();
    listSize = view.size();
    if(listSize==0){
        firstnode = nullptr;
        endnode = nullptr;
        thisnode =nullptr;
    }else{
        firstnode = new DoublyLinkedListNode<T>(view[0]);
        DoublyLinkedListNode<T>* lastNode_ = firstnode;
        thisnode = firstnode;
        for(unsigned i=1;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
    }
    return *this;
}
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator = (const ConstLinearlistView<T>& view){
    clear();
    listSize = view.size();
    if(listSize==0){
        firstnode = nullptr;
        endnode = nullptr;
        thisnode =nullptr;
    }else{
        firstnode = new DoublyLinkedListNode<T>(view[0]);
        DoublyLinkedListNode<T>* lastNode_ = firstnode;
        thisnode = firstnode;
        for(unsigned i=1;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
    }
    return *this;
}
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator = (const Linearlist<T>& theLinearlist){
    clear();
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    listSize = view.size();
    if(listSize==0){
        firstnode = nullptr;
        endnode = nullptr;
        thisnode =nullptr;
    }else{
        firstnode = new DoublyLinkedListNode<T>(view[0]);
        DoublyLinkedListNode<T>* lastNode_ = firstnode;
        thisnode = firstnode;
        for(unsigned i=1;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
    }
    return *this;
}
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator = (const initializer_list<T>& init_list){
    clear();
    listSize = init_list.size();
    if(listSize==0){
        firstnode = nullptr;
        endnode = nullptr;
        thisnode = nullptr;
    }else{
        unsigned index = 0;
        DoublyLinkedListNode<T>* lastNode_;
        for(const T& element_:init_list){
            if(index==0){
                firstnode = new DoublyLinkedListNode<T>(element_);
                thisnode = firstnode;
                lastNode_ = firstnode;
            }else{
                DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element_);
                lastNode_->setNextnode(newnode);
                newnode->setLastnode(lastNode_);
                lastNode_ = newnode;
            }
            index++;
        }
        endnode = lastNode_;
    }
    return *this;
}
template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::copy(const T* Tarray,unsigned n){
    clear();//先清空双向链表
    //再复制Tarray，时间复杂度n
    if(n==0){}
    else{
        listSize = n;
        DoublyLinkedListNode<T>* thisNode_ = new DoublyLinkedListNode<T>(Tarray[0]);
        firstnode=thisNode_;
        thisnode=thisNode_;
        for(unsigned i=1;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(Tarray[i]);
            newnode->setLastnode(thisNode_);
            thisNode_->setNextnode(newnode);
            thisNode_=newnode;
        }
        endnode=thisNode_;
    }
    return *this;
}
//合并
template <class T>
void DoublyLinkedList<T>::merge(const DoublyLinkedList& theDoublyLinkedList){
    if(theDoublyLinkedList.listSize==0){}
    else if(listSize==0) {
        (*this)=theDoublyLinkedList;
    }else{
        DoublyLinkedListNode<T>* theDoublyLinkedList_thisnode = theDoublyLinkedList.firstnode;
        DoublyLinkedListNode<T>* thisNode_ = endnode;
        unsigned n = theDoublyLinkedList.listSize;
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(theDoublyLinkedList_thisnode->get());
            newnode->setLastnode(thisNode_);
            thisNode_->setNextnode(newnode);
            thisNode_=newnode;
            theDoublyLinkedList_thisnode = theDoublyLinkedList_thisnode->getNextnode();
        }
        endnode = thisNode_;
        listSize += n;
    }
}
template <class T>
void DoublyLinkedList<T>::merge(const initializer_list<T>& init_list){
    unsigned n = init_list.size();
    if(n==0) return;
    else if(listSize==0) *this = init_list;
    else{
        DoublyLinkedListNode<T>* lastNode_ = endnode;
        for(const T& element_ : init_list){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element_);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
    }
}
template <class T>
void DoublyLinkedList<T>::merge(const T* Tarray,unsigned n){
    if(n==0) {}
    else if(listSize==0){
        this->copy(Tarray,n);
    }else{
        DoublyLinkedListNode<T>* thisNode_ =endnode;
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(Tarray[i]);
            newnode->setLastnode(thisNode_);
            thisNode_->setNextnode(newnode);
            thisNode_=newnode;
        }
        endnode=thisNode_;
        listSize+=n;
    }
}
template <class T>
void DoublyLinkedList<T>::merge(const LinearlistView<T>& view){
    unsigned n = view.size();
    if(n==0) {}
    else if(listSize==0) *this = view;
    else{
        DoublyLinkedListNode<T>* lastNode_ = endnode;
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
        listSize+=n;
    }
}
template <class T>
void DoublyLinkedList<T>::merge(const ConstLinearlistView<T>& view){
    unsigned n = view.size();
    if(n==0) {}
    else if(listSize==0) *this = view;
    else{
        DoublyLinkedListNode<T>* lastNode_ = endnode;
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
        listSize+=n;
    }
}
template <class T>
void DoublyLinkedList<T>::merge(const Linearlist<T>& theLinearlist){
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    unsigned n = view.size();
    if(n==0) {}
    else if(listSize==0) *this = view;
    else{
        DoublyLinkedListNode<T>* lastNode_ = endnode;
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            lastNode_ = newnode;
        }
        endnode = lastNode_;
        listSize+=n;
    }
}
//查
template <class T>
T& DoublyLinkedList<T>::operator[](unsigned index){
    if(index>=listSize) throw illegalParameterValue("index out of range.");
    if(index<listSize/2){
        DoublyLinkedListNode<T>* this_thisnode = firstnode;
        for(unsigned i=1;i<=index;i++){
            this_thisnode = this_thisnode->getNextnode();
        }
        return this_thisnode->get();
    }else{
        DoublyLinkedListNode<T>* this_thisnode = endnode;
        for(unsigned i=listSize-2;i>=index;i--){
            this_thisnode=this_thisnode->getLastnode();
        }
        return this_thisnode->get();
    }
}
template <class T>
const T& DoublyLinkedList<T>::operator[](unsigned index) const{
    if(index>=listSize) throw illegalParameterValue("index out of range.");
    if(index<listSize/2){
        const DoublyLinkedListNode<T>* this_thisnode = firstnode;
        for(unsigned i=1;i<=index;i++){
            this_thisnode = this_thisnode->getNextnode();
        }
        return this_thisnode->get();
    }else{
        const DoublyLinkedListNode<T>* this_thisnode = endnode;
        for(unsigned i=listSize-2;i>=index;i--){
            this_thisnode=this_thisnode->getLastnode();
        }
        return this_thisnode->get();
    }
}
template <class T>
unsigned DoublyLinkedList<T>::search(const T& element_) const{
    if(listSize==0) return 0;
    else{
        const DoublyLinkedListNode<T>* this_thisnode = firstnode;
        for(unsigned i=0;i<listSize;i++){
            if(this_thisnode->get()==element_) return i;
            this_thisnode = this_thisnode->getNextnode();
        }
        return listSize;
    }
}
//增
template <class T>
void DoublyLinkedList<T>::insert(unsigned index,const T& element_){
    if(index>listSize) throw illegalParameterValue("Index out of range!");
    else if(listSize==0){
        firstnode = new DoublyLinkedListNode<T>(element_);
        endnode = firstnode;
        listSize=1;
        thisnode=firstnode;
    }else if(index==0){
        DoublyLinkedListNode<T>* newfirstnode = new DoublyLinkedListNode<T>(element_);
        newfirstnode->setNextnode(firstnode);
        firstnode->setLastnode(newfirstnode);
        firstnode = newfirstnode;
        listSize++;
    }else if(index==listSize){
        DoublyLinkedListNode<T>* newendnode = new DoublyLinkedListNode<T>(element_);
        endnode->setNextnode(newendnode);
        newendnode->setLastnode(endnode);
        endnode=newendnode;
        listSize++;
    }else{
        DoublyLinkedListNode<T>* lastNode_ = nullptr;
        if(index<= listSize/2){
            lastNode_ = firstnode;
            for(unsigned i=0;i<index;i++){
                lastNode_ = lastNode_->getNextnode();
            }
        }else{
            lastNode_ = endnode;
            for(unsigned i=listSize-1;i>=index;i--){
                lastNode_ = lastNode_->getLastnode();
            }
            lastNode_ = lastNode_->getLastnode();
        }
        DoublyLinkedListNode<T>* thisNode_ = lastNode_->getNextnode();
        DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element_);
        lastNode_->setNextnode(newnode);
        newnode->setLastnode(lastNode_);
        newnode->setNextnode(thisNode_);
        thisNode_->setLastnode(newnode);
        listSize++;
    }
}
template <class T>
void DoublyLinkedList<T>::insert(const T& element,bool front_){
    if(listSize==0){
        listSize=1;
        DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element);
        firstnode = newnode;
        endnode = newnode;
        thisnode = newnode;
    }else if(nullPointer()){
        if(front_) {
            insertfront(element);
            thisnode = firstnode;
        }else{
            insertback(element);
            thisnode=endnode;
        }
        listSize++;
    }else if(front_){
        if(thisnode==firstnode) insertfront(element);
        else{
            DoublyLinkedListNode<T>* lastNode_ = thisnode->getLastnode();
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element);
            lastNode_->setNextnode(newnode);
            newnode->setLastnode(lastNode_);
            newnode->setNextnode(thisnode);
            thisnode->setLastnode(newnode);
            listSize++;
        }
    }else{
        if(thisnode==endnode) insertback(element);
        else{
            DoublyLinkedListNode<T>* nextNode_ = thisnode->getNextnode();
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element);
            thisnode->setNextnode(newnode);
            newnode->setLastnode(thisnode);
            newnode->setNextnode(nextNode_);
            nextNode_->setLastnode(newnode);
            thisnode=newnode;
            listSize++;
        }
    }
}
template <class T>
void DoublyLinkedList<T>::insertfront(const T& element){
    if(listSize==0){
        listSize=1;
        firstnode=new DoublyLinkedListNode<T>(element);
        endnode = firstnode;
        thisnode = firstnode;
    }else{
        DoublyLinkedListNode<T>* newfirstnode = new DoublyLinkedListNode<T>(element);
        newfirstnode->setNextnode(firstnode);
        firstnode->setLastnode(newfirstnode);
        firstnode=newfirstnode;
        listSize++;
    }
}
template <class T>
void DoublyLinkedList<T>::insertback(const T& element){
    if(listSize==0){
        listSize=1;
        firstnode=new DoublyLinkedListNode<T>(element);
        endnode = firstnode;
        thisnode = firstnode;
    }else{
        DoublyLinkedListNode<T>* newendnode = new DoublyLinkedListNode<T>(element);
        newendnode->setLastnode(endnode);
        endnode->setNextnode(newendnode);
        endnode=newendnode;
        listSize++;
    }
}
//删
template <class T>
void DoublyLinkedList<T>::erase(){
    if(listSize==0||nullPointer()){}
    else if(listSize==1){
        DoublyLinkedListNode<T>* deletenode = firstnode;
        firstnode=nullptr;
        endnode=nullptr;
        thisnode=nullptr;
        listSize=0;
        delete deletenode;
    }else if(thisnode==firstnode){
        DoublyLinkedListNode<T>* deletenode = thisnode;
        DoublyLinkedListNode<T>* nextNode_ = thisnode->getNextnode();
        firstnode = nextNode_;
        thisnode = nextNode_;
        listSize--;
        nextNode_->setLastnode(nullptr);
        delete deletenode;
    }else if(thisnode==endnode){
        DoublyLinkedListNode<T>* deletenode = thisnode;
        DoublyLinkedListNode<T>* lastNode_ = thisnode->getLastnode();
        endnode = lastNode_;
        thisnode = nullptr;
        listSize--;
        lastNode_->setNextnode(nullptr);
        delete deletenode;
    }else{
        DoublyLinkedListNode<T>* lastNode_ = thisnode->getLastnode();
        DoublyLinkedListNode<T>* nextNode_ = thisnode->getNextnode();
        DoublyLinkedListNode<T>* deletenode = thisnode;
        thisnode = nextNode_;
        lastNode_->setNextnode(nextNode_);
        nextNode_->setLastnode(lastNode_);
        listSize--;
        delete deletenode;
    }
}
template <class T>
void DoublyLinkedList<T>::erase(unsigned index){
    if(index>=listSize) return;
    else if(listSize==1){
        delete firstnode;
        firstnode=nullptr;
        thisnode=nullptr;
        endnode=nullptr;
        listSize=0;
    }else if(index==0){
        DoublyLinkedListNode<T>* deletenode = firstnode;
        DoublyLinkedListNode<T>* nextnode_ = firstnode->getNextnode();
        if(thisnode==deletenode) thisnode = nextnode_;
        firstnode=nextnode_;
        nextnode_->setLastnode(nullptr);
        delete deletenode;
        listSize--;
    }else if(index==listSize-1){
        DoublyLinkedListNode<T>* deletenode = endnode;
        DoublyLinkedListNode<T>* lastnode_ = endnode->getLastnode();
        lastnode_->setNextnode(nullptr);
        if(thisnode==endnode) thisnode=nullptr;
        endnode = lastnode_;
        delete deletenode;
        listSize--;
    }else{
        DoublyLinkedListNode<T>* thisnode_ = firstnode;
        for(unsigned i=1;i<=index;i++){
            thisnode_ = thisnode_->getNextnode();
        }
        DoublyLinkedListNode<T>* lastnode_ = thisnode_->getLastnode();
        DoublyLinkedListNode<T>* nextnode_ = thisnode_->getNextnode();
        lastnode_->setNextnode(nextnode_);
        nextnode_->setLastnode(lastnode_);
        if(thisnode==thisnode_) thisnode = nextnode_;
        delete thisnode_;
        listSize--;
    }
}
template <class T>
void DoublyLinkedList<T>::erasefront(){
    if(listSize==0) return;
    else if(listSize==1){
        delete firstnode;
        thisnode=nullptr;
        firstnode=nullptr;
        endnode=nullptr;
        listSize=0;
    }else if(thisnode==firstnode){
        DoublyLinkedListNode<T>* nextnode_ = firstnode->getNextnode();
        DoublyLinkedListNode<T>* Oldfirstnode = firstnode;
        thisnode = nextnode_;
        firstnode = nextnode_;
        nextnode_->setLastnode(nullptr);
        listSize--;
        delete Oldfirstnode;
    }else{
        DoublyLinkedListNode<T>* nextnode_ = firstnode->getNextnode();
        DoublyLinkedListNode<T>* Oldfirstnode = firstnode;
        delete Oldfirstnode;
        firstnode = nextnode_;
        nextnode_->setLastnode(nullptr);
        listSize--;
    }
}
template <class T>
void DoublyLinkedList<T>::eraseback(){
    if(listSize==0) return;
    else if(listSize==1){
        delete firstnode;
        firstnode=nullptr;
        endnode=nullptr;
        thisnode=nullptr;
        listSize=0;
    }else if(thisnode==endnode){
        DoublyLinkedListNode<T>* oldEndnode = endnode;
        DoublyLinkedListNode<T>* lastnode_ = oldEndnode->getLastnode();
        delete oldEndnode;
        endnode = lastnode_;
        thisnode = nullptr;
        lastnode_->setNextnode(nullptr);
        listSize--;
    }else{
        DoublyLinkedListNode<T>* oldEndnode = endnode;
        DoublyLinkedListNode<T>* lastnode_ = oldEndnode->getLastnode();
        delete oldEndnode;
        endnode = lastnode_;
        lastnode_->setNextnode(nullptr);
        listSize--;
    }
}
//移动
template <class T>
bool DoublyLinkedList<T>::nullPointer() const{
    if(thisnode) return false;
    else return true;
}
template <class T>
void DoublyLinkedList<T>::switch_to_begin() const{
    thisnode = firstnode;
}
template <class T>
void DoublyLinkedList<T>::switch_to_end() const{
    thisnode = endnode;
}
template <class T>
void DoublyLinkedList<T>::next() const{
    if(thisnode) thisnode=thisnode->getNextnode();
}
template <class T>
void DoublyLinkedList<T>::last() const{
    if(thisnode) thisnode=thisnode->getLastnode();
}
template <class T>
T& DoublyLinkedList<T>::thisElement(){
    if(thisnode) return thisnode->get();
    else throw illegalParameterValue("thisnode is null.");
}
template <class T>
const T& DoublyLinkedList<T>::thisElement()const{
    if(thisnode) return thisnode->get();
    else throw illegalParameterValue("thisnode is null.");
}
//迭代器
template <class T>
DoublyLinkedListIterator<T> DoublyLinkedList<T>::begin(){
    return DoublyLinkedListIterator<T>(firstnode);
}
template <class T>
DoublyLinkedListIterator<T> DoublyLinkedList<T>::end(){
    return DoublyLinkedListIterator<T>(nullptr);
}
template <class T>
ConstDoublyLinkedListIterator<T> DoublyLinkedList<T>::begin() const{
    return ConstDoublyLinkedListIterator<T>(firstnode);
}
template<class T>
ConstDoublyLinkedListIterator<T> DoublyLinkedList<T>::end() const{
    return ConstDoublyLinkedListIterator<T>(nullptr);
}
/*创建线性表视图*/
template <class T>
LinearlistView<T> DoublyLinkedList<T>::createView(){
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
ConstLinearlistView<T> DoublyLinkedList<T>::createView() const{
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
ConstLinearlistView<T> DoublyLinkedList<T>::createConstView() const{
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
LinearlistView<T> DoublyLinkedList<T>::sublist(unsigned begin_,unsigned end_){
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
ConstLinearlistView<T> DoublyLinkedList<T>::sublist(unsigned begin_,unsigned end_) const{
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
#endif // DOUBLYLINKEDLIST_H
