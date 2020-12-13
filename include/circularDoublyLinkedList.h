#include "Abs_DoublyLinkedList.h"
#include "illegalParameterValue.h"
#ifndef CIRCULARDOUBLYLINKEDLIST_H
#define CIRCULARDOUBLYLINKEDLIST_H
namespace Huitoy{
template <class T>
class circularDoublyLinkedList:public Abs_DoublyLinkedList<T>
{
    public:
        //构造函数，析构函数
        circularDoublyLinkedList();
        circularDoublyLinkedList(circularDoublyLinkedList&& thecircularDoublyLinkedList)noexcept;
        circularDoublyLinkedList(const circularDoublyLinkedList& thecircularDoublyLinkedList);
        circularDoublyLinkedList(const LinearlistView<T>& view);
        circularDoublyLinkedList(const ConstLinearlistView<T>& view);
        circularDoublyLinkedList(const Linearlist<T>& theLinearlist);
        circularDoublyLinkedList(const initializer_list<T>& init_list);
        circularDoublyLinkedList(const T& element,unsigned n);
        circularDoublyLinkedList(const T* Tarray,unsigned n);
        ~circularDoublyLinkedList();
        void clear();
        //复制
        circularDoublyLinkedList& operator=(const circularDoublyLinkedList& thecircularDoublyLinkedList);
        circularDoublyLinkedList& operator=(circularDoublyLinkedList&& thecircularDoublyLinkedList)noexcept;
        circularDoublyLinkedList& operator=(const LinearlistView<T>& view);
        circularDoublyLinkedList& operator=(const ConstLinearlistView<T>& view);
        circularDoublyLinkedList& operator=(const Linearlist<T>& theLinearlist);
        circularDoublyLinkedList& operator=(const initializer_list<T>&  init_list);
        circularDoublyLinkedList& copy(const T* Tarray,unsigned n);
        //合并
        void merge(const circularDoublyLinkedList& thecircularDoublyLinkedList);
        void merge(const initializer_list<T>& init_list);
        void merge(const T* Tarray,unsigned);
        void merge(const LinearlistView<T>& view);
        void merge(const ConstLinearlistView<T>& view);
        void merge(const Linearlist<T>& theLinearlist);
        //空、线性表长度
        bool empty() const;
        unsigned size() const;
        //查、改
        T& operator[](unsigned index);
        const T& operator[](unsigned index) const;
        unsigned search(const T& element_) const;
        //删
        void erase(unsigned index);
        void erase();
        void erasefront();
        void eraseback();
        //增
        void insert(const T& element,bool front_=true);
        void insert(unsigned index,const T& element_);
        void insertfront(const T& element);
        void insertback(const T& element);
        //移动
        bool head() const;
        void next() const;
        void last() const;
        T& thisElement();
        const T& thisElement() const;
        void switch_to_begin() const;
        void switch_to_end() const;
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
        DoublyLinkedListNode<T>* headnode;
        unsigned listSize;
        mutable DoublyLinkedListNode<T>* thisnode;
    private:
};
template <class T>
circularDoublyLinkedList<T>::circularDoublyLinkedList(){
    headnode = new DoublyLinkedListNode<T>;
    headnode->setLastnode(headnode);
    headnode->setNextnode(headnode);
    thisnode = headnode;
    listSize=0;
}
template <class T>
circularDoublyLinkedList<T>::circularDoublyLinkedList(const circularDoublyLinkedList& thecircularDoublyLinkedList){
    headnode = new DoublyLinkedListNode<T>;
    listSize = thecircularDoublyLinkedList.listSize;
    if(listSize==0){
        headnode->setLastnode(headnode);
        headnode->setNextnode(headnode);
        thisnode=headnode;
    }else{
        DoublyLinkedListNode<T>* thecircularDoublyLinkedList_thisnode = thecircularDoublyLinkedList.headnode->getNextnode();
        DoublyLinkedListNode<T>* thisNode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(thecircularDoublyLinkedList_thisnode->get());
            newnode->setLastnode(thisNode_);
            thisNode_->setNextnode(newnode);
            thisNode_ = newnode;
            thecircularDoublyLinkedList_thisnode=thecircularDoublyLinkedList_thisnode->getNextnode();
        }
        thisNode_->setNextnode(headnode);
        headnode->setLastnode(thisNode_);
        thisnode = headnode->getNextnode();
    }
}
template <class T>
circularDoublyLinkedList<T>::circularDoublyLinkedList(circularDoublyLinkedList&& thecircularDoublyLinkedList) noexcept{
    headnode = thecircularDoublyLinkedList.headnode;
    thecircularDoublyLinkedList.headnode = new DoublyLinkedListNode<T>;
    listSize = thecircularDoublyLinkedList.listSize;
    thecircularDoublyLinkedList.listSize = 0;
    thisnode = headnode->getNextnode();
}
template <class T>
circularDoublyLinkedList<T>::circularDoublyLinkedList(const LinearlistView<T>& view){
    headnode = new DoublyLinkedListNode<T>;
    listSize = view.size();
    if(listSize==0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* Lastnode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            Lastnode_->setNextnode(newnode);
            newnode->setLastnode(Lastnode_);
            Lastnode_ = newnode;
        }
        Lastnode_->setNextnode(headnode);
        headnode->setLastnode(Lastnode_);
    }
}
template <class T>
circularDoublyLinkedList<T>::circularDoublyLinkedList(const ConstLinearlistView<T>& view){
    headnode = new DoublyLinkedListNode<T>;
    listSize = view.size();
    if(listSize==0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* Lastnode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            Lastnode_->setNextnode(newnode);
            newnode->setLastnode(Lastnode_);
            Lastnode_ = newnode;
        }
        Lastnode_->setNextnode(headnode);
        headnode->setLastnode(Lastnode_);
    }
}
template <class T>
circularDoublyLinkedList<T>::circularDoublyLinkedList(const Linearlist<T>& theLinearlist){
    headnode = new DoublyLinkedListNode<T>;
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    listSize = view.size();
    if(listSize==0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* Lastnode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            Lastnode_->setNextnode(newnode);
            newnode->setLastnode(Lastnode_);
            Lastnode_ = newnode;
        }
        Lastnode_->setNextnode(headnode);
        headnode->setLastnode(Lastnode_);
    }
}
template <class T>
circularDoublyLinkedList<T>::circularDoublyLinkedList(const initializer_list<T>& init_list){
    headnode = new DoublyLinkedListNode<T>;
    listSize = init_list.size();
    if(listSize == 0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* Lastnode_ = headnode;
        for(const T& element:init_list){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element);
            Lastnode_->setNextnode(newnode);
            newnode->setLastnode(Lastnode_);
            Lastnode_=newnode;
        }
        Lastnode_->setNextnode(headnode);
        headnode->setLastnode(Lastnode_);
    }
}
template <class T>
circularDoublyLinkedList<T>::circularDoublyLinkedList(const T& element,unsigned n){
    headnode = new DoublyLinkedListNode<T>;
    listSize = n;
    if(n==0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* LastNode_ = headnode;
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element);
            LastNode_->setNextnode(newnode);
            newnode->setLastnode(LastNode_);
            LastNode_ = newnode;
        }
        LastNode_->setNextnode(headnode);
        headnode->setLastnode(LastNode_);
        thisnode = headnode->getNextnode();
    }
}
template <class T>
circularDoublyLinkedList<T>::circularDoublyLinkedList(const T* Tarray,unsigned n){
    headnode = new DoublyLinkedListNode<T>;
    listSize=n;
    if(n==0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* thisNode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(Tarray[i]);
            newnode->setLastnode(thisNode_);
            thisNode_->setNextnode(newnode);
            thisNode_=newnode;
        }
        thisNode_->setNextnode(headnode);
        headnode->setLastnode(thisNode_);
        thisnode = headnode->getNextnode();
    }
}
template <class T>
circularDoublyLinkedList<T>::~circularDoublyLinkedList(){
    thisnode = headnode->getNextnode();
    for(unsigned i=0;i<listSize;i++){
        DoublyLinkedListNode<T>* nextnode = thisnode->getNextnode();
        delete thisnode;
        thisnode = nextnode;
    }
    delete headnode;
}
template <class T>
void circularDoublyLinkedList<T>::clear(){
    thisnode = headnode->getNextnode();
    for(unsigned i=0;i<listSize;i++){
        DoublyLinkedListNode<T>* nextnode = thisnode->getNextnode();
        delete thisnode;
        thisnode=nextnode;
    }
    headnode->setLastnode(headnode);
    headnode->setNextnode(headnode);
    listSize=0;
}
//复制
template <class T>
circularDoublyLinkedList<T>& circularDoublyLinkedList<T>::operator=(const circularDoublyLinkedList& thecircularDoublyLinkedList){
    clear();//首先清空链表
    listSize = thecircularDoublyLinkedList.listSize;
    if(listSize==0){
        headnode->setLastnode(headnode);
        headnode->setNextnode(headnode);
        thisnode=headnode;
    }else{
        DoublyLinkedListNode<T>* thecircularDoublyLinkedList_thisnode = thecircularDoublyLinkedList.headnode->getNextnode();
        DoublyLinkedListNode<T>* thisNode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(thecircularDoublyLinkedList_thisnode->get());
            newnode->setLastnode(thisNode_);
            thisNode_->setNextnode(newnode);
            thisNode_ = newnode;
            thecircularDoublyLinkedList_thisnode=thecircularDoublyLinkedList_thisnode->getNextnode();
        }
        thisNode_->setNextnode(headnode);
        headnode->setLastnode(thisNode_);
        thisnode = headnode->getNextnode();
    }
}
template <class T>
circularDoublyLinkedList<T>& circularDoublyLinkedList<T>::operator=(circularDoublyLinkedList&& thecircularDoublyLinkedList) noexcept{
    clear();
    headnode = thecircularDoublyLinkedList.headnode;
    thecircularDoublyLinkedList.headnode = new DoublyLinkedListNode<T>;
    listSize = thecircularDoublyLinkedList.listSize;
    thecircularDoublyLinkedList.listSize = 0;
    thisnode = headnode->getNextnode();
}
template <class T>
circularDoublyLinkedList<T>& circularDoublyLinkedList<T>::operator=(const LinearlistView<T>& view){
    clear();
    listSize = view.size();
    if(listSize==0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* Lastnode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            Lastnode_->setNextnode(newnode);
            newnode->setLastnode(Lastnode_);
            Lastnode_ = newnode;
        }
        Lastnode_->setNextnode(headnode);
        headnode->setLastnode(Lastnode_);
    }
    return *this;
}
template <class T>
circularDoublyLinkedList<T>& circularDoublyLinkedList<T>::operator=(const ConstLinearlistView<T>& view){
    clear();
    listSize = view.size();
    if(listSize==0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* Lastnode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            Lastnode_->setNextnode(newnode);
            newnode->setLastnode(Lastnode_);
            Lastnode_ = newnode;
        }
        Lastnode_->setNextnode(headnode);
        headnode->setLastnode(Lastnode_);
    }
    return *this;
}
template <class T>
circularDoublyLinkedList<T>& circularDoublyLinkedList<T>::operator=(const Linearlist<T>& theLinearlist){
    clear();
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    listSize = view.size();
    if(listSize==0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* Lastnode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            Lastnode_->setNextnode(newnode);
            newnode->setLastnode(Lastnode_);
            Lastnode_ = newnode;
        }
        Lastnode_->setNextnode(headnode);
        headnode->setLastnode(Lastnode_);
    }
    return *this;
}
template <class T>
circularDoublyLinkedList<T>& circularDoublyLinkedList<T>::operator = (const initializer_list<T>& init_list){
    clear();
    listSize = init_list.size();
    if(listSize==0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* Lastnode_ = headnode;
        for(const T& element:init_list){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element);
            Lastnode_->setNextnode(newnode);
            newnode->setLastnode(Lastnode_);
            Lastnode_=newnode;
        }
        Lastnode_->setNextnode(headnode);
        headnode->setLastnode(Lastnode_);
    }
    return *this;
}
template <class T>
circularDoublyLinkedList<T>& circularDoublyLinkedList<T>::copy(const T* Tarray,unsigned n){
    clear(); //先清空链表
    listSize=n;
    if(n==0){
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode = headnode;
    }else{
        DoublyLinkedListNode<T>* thisNode_ = headnode;
        for(unsigned i=0;i<listSize;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(Tarray[i]);
            newnode->setLastnode(thisNode_);
            thisNode_->setNextnode(newnode);
            thisNode_=newnode;
        }
        thisNode_->setNextnode(headnode);
        headnode->setLastnode(thisNode_);
        thisnode = headnode->getNextnode();
    }
    return *this;
}
//merge
template <class T>
void circularDoublyLinkedList<T>::merge(const circularDoublyLinkedList& thecircularDoublyLinkedList){
    unsigned n = thecircularDoublyLinkedList.listSize;
    if(n==0) return;
    else if(listSize==0) (*this)=thecircularDoublyLinkedList;
    else{
        listSize+=n;
        DoublyLinkedListNode<T>* thisNode_ = headnode->getLastnode();
        DoublyLinkedListNode<T>* thecircularDoublyLinkedList_thisnode = thecircularDoublyLinkedList.headnode->getNextnode();
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(thecircularDoublyLinkedList_thisnode->get());
            thisNode_->setNextnode(newnode);
            newnode->setLastnode(thisNode_);
            thisNode_ = newnode;
            thecircularDoublyLinkedList_thisnode = thecircularDoublyLinkedList_thisnode->getNextnode();
        }
        thisNode_->setNextnode(headnode);
        headnode->setLastnode(thisNode_);
    }
}
template <class T>
void circularDoublyLinkedList<T>::merge(const LinearlistView<T>& view){
    unsigned n = view.size();
    if(n==0) return;
    else if(listSize==0) *this = view;
    else{
        listSize+=n;
        DoublyLinkedListNode<T>* thisNode_ = headnode->getLastnode();
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            thisNode_->setNextnode(newnode);
            newnode->setLastnode(thisNode_);
            thisNode_=newnode;
        }
        thisNode_->setNextnode(headnode);
        headnode->setLastnode(thisNode_);
    }
}
template <class T>
void circularDoublyLinkedList<T>::merge(const ConstLinearlistView<T>& view){
    unsigned n = view.size();
    if(n==0) return;
    else if(listSize==0) *this = view;
    else{
        listSize+=n;
        DoublyLinkedListNode<T>* thisNode_ = headnode->getLastnode();
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            thisNode_->setNextnode(newnode);
            newnode->setLastnode(thisNode_);
            thisNode_=newnode;
        }
        thisNode_->setNextnode(headnode);
        headnode->setLastnode(thisNode_);
    }
}
template <class T>
void circularDoublyLinkedList<T>::merge(const Linearlist<T>& theLinearlist){
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    unsigned n = view.size();
    if(n==0) return;
    else if(listSize==0) *this = view;
    else{
        listSize+=n;
        DoublyLinkedListNode<T>* thisNode_ = headnode->getLastnode();
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(view[i]);
            thisNode_->setNextnode(newnode);
            newnode->setLastnode(thisNode_);
            thisNode_=newnode;
        }
        thisNode_->setNextnode(headnode);
        headnode->setLastnode(thisNode_);
    }
}
template <class T>
void circularDoublyLinkedList<T>::merge(const initializer_list<T>& init_list){
    unsigned n = init_list.size();
    if(n==0) return;
    else if(listSize==0) *this = init_list;
    else{
        listSize+=n;
        DoublyLinkedListNode<T>* lastNode = headnode->getLastnode();
        for(const T& element:init_list){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element);
            lastNode->setNextnode(newnode);
            newnode->setLastnode(lastNode);
            lastNode=newnode;
        }
        lastNode->setNextnode(headnode);
        headnode->setLastnode(lastNode);
    }
}
template <class T>
void circularDoublyLinkedList<T>::merge(const T* Tarray,unsigned n){
    if(n==0) return;
    else if(listSize==0) copy(Tarray,n);
    else{
        listSize+=n;
        DoublyLinkedListNode<T>* thisNode_ = headnode->getLastnode();
        for(unsigned i=0;i<n;i++){
            DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(Tarray[i]);
            thisNode_->setNextnode(newnode);
            newnode->setLastnode(thisNode_);
            thisNode_=newnode;
        }
        thisNode_->setNextnode(headnode);
        headnode->setLastnode(thisNode_);
    }
}
//空、线性表的长度
template<class T>
bool circularDoublyLinkedList<T>::empty() const{
    return listSize==0;
}
template <class T>
unsigned circularDoublyLinkedList<T>::size() const{
    return listSize;
}
//查
template <class T>
T& circularDoublyLinkedList<T>::operator[](unsigned index){
    if(index>=listSize) throw illegalParameterValue("index out of range.");
    DoublyLinkedListNode<T>* this_thisnode;
    if(index<listSize/2){
        this_thisnode = headnode->getNextnode();
        for(unsigned i=1;i<=index;i++){
            this_thisnode = this_thisnode->getNextnode();
        }
    }else{
        this_thisnode = headnode->getLastnode();
        for(unsigned i=listSize-2;i>=index;i--){
            this_thisnode = this_thisnode->getLastnode();
        }
    }
    return this_thisnode->get();
}
template <class T>
const T& circularDoublyLinkedList<T>::operator[](unsigned index) const{
    if(index>=listSize) throw illegalParameterValue("index out of range.");
    const DoublyLinkedListNode<T>* this_thisnode;
    if(index<listSize/2){
        this_thisnode = headnode->getNextnode();
        for(unsigned i=1;i<=index;i++){
            this_thisnode = this_thisnode->getNextnode();
        }
    }else{
        this_thisnode = headnode->getLastnode();
        for(unsigned i=listSize-2;i>=index;i--){
            this_thisnode = this_thisnode->getLastnode();
        }
    }
    return this_thisnode->get();
}
template <class T>
unsigned circularDoublyLinkedList<T>::search(const T& element_) const{
    if(listSize==0) return 0;
    const DoublyLinkedListNode<T>* this_thisnode = headnode->getNextnode();
    for(unsigned i=0;i<listSize;i++){
        if(this_thisnode->get()==element_) return i;
        this_thisnode = this_thisnode->getNextnode();
    }
    return listSize;
}
//删
template <class T>
void circularDoublyLinkedList<T>::erase(){
    if(listSize==0||head()) return;
    else if(listSize==1){
        delete headnode->getNextnode();
        headnode->setNextnode(headnode);
        headnode->setLastnode(headnode);
        thisnode=headnode;
        listSize=0;
    }else{
        DoublyLinkedListNode<T>* lastnode_ = thisnode->getLastnode();
        DoublyLinkedListNode<T>* nextnode_ = thisnode->getNextnode();
        lastnode_->setNextnode(nextnode_);
        nextnode_->setLastnode(lastnode_);
        listSize--;
        delete thisnode;
        thisnode = nextnode_;
    }
}
template <class T>
void circularDoublyLinkedList<T>::erase(unsigned index){
    DoublyLinkedListNode<T>* thisNode_ = headnode;
    if(index>=listSize) return;
    else if(index<=listSize/2){
        for(unsigned i=0;i<=index;i++){
            thisNode_ = thisNode_->getNextnode();
        }
    }else{
        for(unsigned i=listSize-1;i>=index;i--){
            thisNode_ = thisNode_->getLastnode();
        }
    }
    if(thisNode_==thisnode){
        thisnode = thisnode->getNextnode();
    }
    DoublyLinkedListNode<T>* lastnode_ = thisNode_->getLastnode();
    DoublyLinkedListNode<T>* nextnode_ =thisNode_->getNextnode();
    lastnode_->setNextnode(nextnode_);
    nextnode_->setLastnode(lastnode_);
    listSize--;
    delete thisNode_;
}
template <class T>
void circularDoublyLinkedList<T>::erasefront(){
    if(listSize==0) return;
    else{
        DoublyLinkedListNode<T>* firstnode_ = headnode->getNextnode();
        if(thisnode==firstnode_) thisnode = thisnode->getNextnode();
        DoublyLinkedListNode<T>* nextnode = firstnode_->getNextnode();
        headnode->setNextnode(nextnode);
        nextnode->setLastnode(headnode);
        delete firstnode_;
        listSize--;
    }
}
template <class T>
void circularDoublyLinkedList<T>::eraseback(){
    if(listSize==0) return;
    else{
        DoublyLinkedListNode<T>* endnode_ = headnode->getLastnode();
        if(thisnode==endnode_) thisnode = headnode;
        DoublyLinkedListNode<T>* lastnode_ = endnode_->getLastnode();
        lastnode_->setNextnode(headnode);
        headnode->setLastnode(lastnode_);
        delete endnode_;
        listSize--;
    }
}
//增
template <class T>
void circularDoublyLinkedList<T>::insert(unsigned index,const T& element_){
    if(index>listSize) throw illegalParameterValue("index out of range.");
    else if(listSize==0){
        DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element_,headnode,headnode);
        headnode->setNextnode(newnode);
        headnode->setLastnode(newnode);
        listSize=1;
        thisnode = newnode;
    }else if(index == 0){
        DoublyLinkedListNode<T>* newfirstnode = new DoublyLinkedListNode<T>(element_);
        DoublyLinkedListNode<T>* oldfirstnode = headnode->getNextnode();
        headnode->setNextnode(newfirstnode);
        newfirstnode->setLastnode(headnode);
        newfirstnode->setNextnode(oldfirstnode);
        oldfirstnode->setLastnode(newfirstnode);
        listSize++;
    }else if(index==listSize){
        DoublyLinkedListNode<T>* oldendnode = headnode->getLastnode();
        DoublyLinkedListNode<T>* newendnode = new DoublyLinkedListNode<T>(element_);
        oldendnode->setNextnode(newendnode);
        newendnode->setLastnode(oldendnode);
        newendnode->setNextnode(headnode);
        headnode->setLastnode(newendnode);
        listSize++;
    }else if(index<=listSize/2){
        DoublyLinkedListNode<T>* thisNode_ = headnode;
        for(unsigned i=0;i<=index;i++){
            thisNode_ = thisNode_->getNextnode();
        }
        DoublyLinkedListNode<T>* lastNode_ = thisNode_->getLastnode();
        DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element_);
        lastNode_->setNextnode(newnode);
        newnode->setLastnode(lastNode_);
        newnode->setNextnode(thisNode_);
        thisNode_->setLastnode(newnode);
        listSize++;
    }else{
        DoublyLinkedListNode<T>* thisNode_ = headnode;
        for(unsigned i=listSize-1;i>=index;i--){
            thisNode_ = thisNode_->getLastnode();
        }
        DoublyLinkedListNode<T>* lastNode_ = thisNode_->getLastnode();
        DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element_);
        lastNode_->setNextnode(newnode);
        newnode->setLastnode(lastNode_);
        newnode->setNextnode(thisNode_);
        thisNode_->setLastnode(newnode);
        listSize++;
    }
}
template <class T>
void circularDoublyLinkedList<T>::insert(const T& element,bool front_){
    if(listSize==0){
        DoublyLinkedListNode<T>* newfirstnode = new DoublyLinkedListNode<T>(element,headnode,headnode);
        headnode->setLastnode(newfirstnode);
        headnode->setNextnode(newfirstnode);
        thisnode = newfirstnode;
        listSize=1;
    }else if(front_){
        DoublyLinkedListNode<T>* lastNode_ = thisnode->getLastnode();
        DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element);
        lastNode_->setNextnode(newnode);
        newnode->setLastnode(lastNode_);
        newnode->setNextnode(thisnode);
        thisnode->setLastnode(newnode);
        listSize++;
    }else{
        DoublyLinkedListNode<T>* nextNode_ = thisnode->getNextnode();
        DoublyLinkedListNode<T>* newnode = new DoublyLinkedListNode<T>(element);
        thisnode->setNextnode(newnode);
        newnode->setLastnode(thisnode);
        newnode->setNextnode(nextNode_);
        nextNode_->setLastnode(newnode);
        listSize++;
    }
}
template <class T>
void circularDoublyLinkedList<T>::insertfront(const T& element){
    DoublyLinkedListNode<T>* oldfirstnode = headnode->getNextnode();
    DoublyLinkedListNode<T>* newfirstnode = new DoublyLinkedListNode<T>(element);
    headnode->setNextnode(newfirstnode);
    newfirstnode->setLastnode(headnode);
    newfirstnode->setNextnode(oldfirstnode);
    oldfirstnode->setLastnode(newfirstnode);
    listSize++;
    if(listSize==1) thisnode = newfirstnode;
}
template <class T>
void circularDoublyLinkedList<T>::insertback(const T& element){
    DoublyLinkedListNode<T>* oldendnode = headnode->getLastnode();
    DoublyLinkedListNode<T>* newendnode = new DoublyLinkedListNode<T>(element);
    oldendnode->setNextnode(newendnode);
    newendnode->setLastnode(oldendnode);
    newendnode->setNextnode(headnode);
    headnode->setLastnode(newendnode);
    listSize++;
    if(listSize==1) thisnode=newendnode;
}
//移动
template <class T>
bool circularDoublyLinkedList<T>::head() const{
    return thisnode==headnode;
}
template <class T>
void circularDoublyLinkedList<T>::next() const{
    thisnode = thisnode->getNextnode();
}
template <class T>
void circularDoublyLinkedList<T>::last() const{
    thisnode = thisnode->getLastnode();
}
template <class T>
void circularDoublyLinkedList<T>::switch_to_begin() const{
    thisnode = headnode->getNextnode();
}
template <class T>
void circularDoublyLinkedList<T>::switch_to_end() const{
    thisnode = headnode->getLastnode();
}
template <class T>
T& circularDoublyLinkedList<T>::thisElement(){
    return thisnode->get();
}
template <class T>
const T& circularDoublyLinkedList<T>::thisElement() const{
    return thisnode->get();
}
//迭代器
template <class T>
DoublyLinkedListIterator<T> circularDoublyLinkedList<T>::begin(){
    return DoublyLinkedListIterator<T>(headnode->getNextnode());
}
template <class T>
DoublyLinkedListIterator<T> circularDoublyLinkedList<T>::end(){
    return DoublyLinkedListIterator<T>(headnode);
}
template <class T>
ConstDoublyLinkedListIterator<T> circularDoublyLinkedList<T>::begin() const{
    return ConstDoublyLinkedListIterator<T>(headnode->getNextnode());
}
template <class T>
ConstDoublyLinkedListIterator<T> circularDoublyLinkedList<T>::end() const{
    return ConstDoublyLinkedListIterator<T>(headnode);
}
/*创建线性表视图*/
template <class T>
LinearlistView<T> circularDoublyLinkedList<T>::createView(){
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
ConstLinearlistView<T> circularDoublyLinkedList<T>::createView() const{
    if(listSize==0) return ConstLinearlistView<T>();
    else{
        unsigned index=0;
        ConstLinearlistView<T> view(listSize);
        view.changeSize(listSize);
        for(const T& element:*this){
            view(index) = &element;
            index++;
        }
        return view;
    }
}
template <class T>
ConstLinearlistView<T> circularDoublyLinkedList<T>::createConstView() const{
    if(listSize==0) return ConstLinearlistView<T>();
    else{
        unsigned index=0;
        ConstLinearlistView<T> view(listSize);
        view.changeSize(listSize);
        for(const T& element:*this){
            view(index) = &element;
            index++;
        }
        return view;
    }
}
/*取子串*/
template <class T>
LinearlistView<T> circularDoublyLinkedList<T>::sublist(unsigned begin_,unsigned end_){
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
ConstLinearlistView<T> circularDoublyLinkedList<T>::sublist(unsigned begin_,unsigned end_) const{
    if(begin_>end_||begin_>=listSize||end_>=listSize) throw illegalParameterValue("illegal parameter: begin>end Or Index out of range!");
    unsigned viewsize = end_-begin_+1;
    ConstLinearlistView<T> result(viewsize);
    result.changeSize(viewsize,false);
    unsigned index=0;
    for(const auto& element:*this){
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
#endif // CIRCULARDOUBLYLINKEDLIST_H
