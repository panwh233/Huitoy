#include "Abs_Chainlist.h"
#include "illegalParameterValue.h"
#ifndef CHAINLIST_H
#define CHAINLIST_H
namespace Huitoy{
template <class T>
class Chainlist:public Abs_Chainlist<T>
{
    public:
        /*构造函数*/
        Chainlist();
        Chainlist(const Chainlist& theChainlist);
        Chainlist(const initializer_list<T>& init_list);
        Chainlist(Chainlist&& theChainlist)noexcept;
        Chainlist(const LinearlistView<T>& view);
        Chainlist(const ConstLinearlistView<T>& view) ;
        Chainlist(const Linearlist<T>& theLinearlist);
        Chainlist(const T& element,unsigned n);
        Chainlist(const T* Tarray,unsigned n);
        /*链表的相关参数*/
        bool empty() const;
        unsigned size() const;
        /*链表的指针移动*/
        void next() const;
        void switch_to_begin() const;
        bool null_ptr() const;
        T& thisElement();
        const T& thisElement() const;
        /*按索引从线性表中取出一个相应的元素*/
        T& operator[] (unsigned index);
        const T& operator[](unsigned index) const;
        /*查找某一元素在线性表中首次出现的索引*/
        unsigned search(const T& element)const;
        /*从链表中删去一个元素*/
        void erase(unsigned index);
        void erase();
        void eraseback();
        void erasefront();
        /*从链表中插入一个元素*/
        void insert(unsigned index,const T& element_);
        void insert(const T& theElement,bool front_ = true);
        void insertback(const T& element);
        void insertfront(const T& element);
        /*链表的复制*/
        Chainlist& operator=(const Chainlist& theChainlist);
        Chainlist& operator=(Chainlist&& theChainlist) noexcept;
        Chainlist& operator=(const LinearlistView<T>& view);
        Chainlist& operator=(const ConstLinearlistView<T>& view);
        Chainlist& operator=(const Linearlist<T>& theLinearlist);
        Chainlist& operator=(const initializer_list<T>& init_list);
        Chainlist& copy(const T* Tarray,unsigned n);
        /*清空链表*/
        void clear();
        /*链表的合并*/
        void merge(const T* Tarray,unsigned n);
        void merge(const initializer_list<T>& init_list);
        void merge(const Chainlist& theChainlist);
        void merge(const LinearlistView<T>& view);
        void merge(const ConstLinearlistView<T>& view);
        void merge(const Linearlist<T>& theLinearlist);
        /*创建线性表视图*/
        LinearlistView<T> createView();
        ConstLinearlistView<T> createConstView() const;
        ConstLinearlistView<T> createView() const;
        /*取子串*/
        LinearlistView<T> sublist(unsigned start_,unsigned end_);
        ConstLinearlistView<T> sublist(unsigned start_,unsigned end_) const;
        /*链表的迭代器*/
        ChainlistIterator<T> begin();
        ChainlistIterator<T> end();
        ConstChainlistIterator<T> begin() const;
        ConstChainlistIterator<T> end() const;
        /*析构函数*/
        ~Chainlist();

    protected:
        ChainNode<T>* firstNode;
        ChainNode<T>* endNode;
        mutable ChainNode<T>* thisNode;
        mutable ChainNode<T>* lastNode;
        unsigned listSize;
    private:
};
/*构造函数的实现：1. 默认构造函数*/
template <class T>
Chainlist<T>::Chainlist(){
    firstNode = nullptr;
    endNode = nullptr;
    thisNode = nullptr;
    lastNode = nullptr;
    listSize = 0;
}
/*2. 复制构造函数*/
template <class T>
Chainlist<T>::Chainlist(const Chainlist& cl){
    listSize=cl.listSize;
    if(listSize==0){
        firstNode = nullptr;
        endNode = nullptr;
        lastNode = nullptr;
        thisNode = nullptr;
    }else{
        ChainNode<T>* cl_thisnode = cl.firstNode;
        firstNode = new ChainNode<T>(cl_thisnode->get());
        thisNode = firstNode;
        lastNode = nullptr;
        cl_thisnode = cl_thisnode->getNextPointer();
        ChainNode<T>* lastNode_ = firstNode;
        for(unsigned i=1;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(cl_thisnode->get());
            lastNode_->changeNextPointer(newnode);
            lastNode_ =newnode;
            cl_thisnode = cl_thisnode->getNextPointer();
        }
        endNode = lastNode_;
    }
}
/*3. 利用一个T的数组进行初始化*/
template <class T>
Chainlist<T>::Chainlist(const T* Tarray,unsigned n){
    listSize = n;
    if(n==0){
        firstNode = nullptr;
        endNode = nullptr;
        lastNode = nullptr;
        thisNode = nullptr;
    }else{
        firstNode = new ChainNode<T>(Tarray[0]);
        lastNode = nullptr;
        thisNode = firstNode;
        ChainNode<T>* lastNode_ = firstNode;
        for(unsigned i=1;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(Tarray[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
        }
        endNode = lastNode_;
    }
}
/*构造函数4：移动构造函数*/
template <class T>
Chainlist<T>::Chainlist(Chainlist&& theChainlist) noexcept{
    firstNode = theChainlist.firstNode;
    theChainlist.firstNode = nullptr;
    endNode = theChainlist.endNode;
    theChainlist.endNode = nullptr;
    listSize = theChainlist.listSize;
    theChainlist.listSize = 0;
    theChainlist.thisNode = nullptr;
    theChainlist.lastNode = nullptr;
    lastNode = nullptr;
    thisNode = firstNode;
}
/*构造函数5、6：利用视图构造*/
template <class T>
Chainlist<T>::Chainlist(const LinearlistView<T>& view){
    listSize = view.size();
    if(listSize==0){
        firstNode = nullptr;
        endNode = nullptr;
        thisNode = nullptr;
        lastNode = nullptr;
    }else{
        firstNode = new ChainNode<T>(view[0]);
        lastNode = nullptr;
        thisNode = firstNode;
        ChainNode<T>* lastNode_ = firstNode;
        for(unsigned i=1;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_=newnode;
        }
        endNode = lastNode_;
    }
}
template <class T>
Chainlist<T>::Chainlist(const ConstLinearlistView<T>& view){
    listSize = view.size();
    if(listSize==0){
        firstNode = nullptr;
        endNode = nullptr;
        thisNode = nullptr;
        lastNode = nullptr;
    }else{
        firstNode = new ChainNode<T>(view[0]);
        lastNode = nullptr;
        thisNode = firstNode;
        ChainNode<T>* lastNode_ = firstNode;
        for(unsigned i=1;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_=newnode;
        }
        endNode = lastNode_;
    }
}
/*构造函数7：用其他线性表进行初始化*/
template <class T>
Chainlist<T>::Chainlist(const Linearlist<T>& theLinearList){
    ConstLinearlistView<T> view = theLinearList.createConstView();
    listSize = view.size();
    if(listSize==0){
        firstNode = nullptr;
        endNode = nullptr;
        thisNode = nullptr;
        lastNode = nullptr;
    }else{
        firstNode = new ChainNode<T>(view[0]);
        lastNode = nullptr;
        thisNode = firstNode;
        ChainNode<T>* lastNode_ = firstNode;
        for(unsigned i=1;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_=newnode;
        }
        endNode = lastNode_;
    }
}
/*构造函数8：利用初始化列表进行初始化*/
template <class T>
Chainlist<T>::Chainlist(const initializer_list<T>& init_list){
    listSize = init_list.size();
    if(listSize==0){
        firstNode = nullptr;
        endNode = nullptr;
        thisNode = nullptr;
        lastNode = nullptr;
    }else{
        unsigned index = 0;
        ChainNode<T>* newnode;
        ChainNode<T>* lastNode_;
        for(const T& element_:init_list){
            if(index!=0){
                newnode = new ChainNode<T>(element_);
                lastNode_->changeNextPointer(newnode);
                lastNode_=newnode;
            }else{
                firstNode = new ChainNode<T>(element_);
                thisNode = firstNode;
                lastNode = nullptr;
                lastNode_ = firstNode;
            }
            index++;
        }
        endNode = lastNode_;
    }
}
/*构造函数9：用一个元素初始化链表*/
template <class T>
Chainlist<T>::Chainlist(const T& element,unsigned n){
    listSize=n;
    if(n==0){
        firstNode = nullptr;
        endNode = nullptr;
        lastNode = nullptr;
        thisNode = nullptr;
    }else{
        firstNode = new ChainNode<T>(element);
        lastNode = nullptr;
        thisNode = firstNode;
        ChainNode<T>* LastNode_ = firstNode;
        for(unsigned i=1;i<n;i++){
            ChainNode<T>* newnode = ChainNode<T>(element);
            LastNode_->changeNextPointer(newnode);
            LastNode_ = newnode;
        }
        endNode = LastNode_;
    }
}
/*析构函数*/
template <class T>
Chainlist<T>::~Chainlist(){
    if(listSize==0){
        return;
    }
    else{
        ChainNode<T>* thisNode_ = firstNode;
        for(unsigned i=0;i<listSize;i++){
            ChainNode<T>* nextnode = thisNode_->getNextPointer();
            delete thisNode_;
            thisNode_ = nextnode;
        }
    }
}
template <class T>
void Chainlist<T>::clear(){
    if(listSize==0){
        return;
    }
    else{
        ChainNode<T>* thisNode_ = firstNode;
        for(unsigned i=0;i<listSize;i++){
            ChainNode<T>* nextnode = thisNode_->getNextPointer();
            delete thisNode_;
            thisNode_ = nextnode;
        }
    }
    firstNode = nullptr;
    endNode = nullptr;
    thisNode = nullptr;
    lastNode = nullptr;
    listSize = 0;
}
/*链表相关参数*/
template <class T>
bool Chainlist<T>::empty() const{
    return listSize==0;
}
template <class T>
unsigned Chainlist<T>::size() const{
    return listSize;
}
/*链表的指针移动*/
template <class T>
void Chainlist<T>::next() const{
    if(listSize==0) return;
    if(thisNode==lastNode||thisNode==nullptr) {
        thisNode=nullptr;
        return;
    }
    lastNode = thisNode;
    thisNode = thisNode->getNextPointer();
}
template <class T>
bool Chainlist<T>::null_ptr() const{
    return thisNode==nullptr;
}
template <class T>
void Chainlist<T>::switch_to_begin() const{
    lastNode = nullptr;
    thisNode = firstNode;
}
template <class T>
T& Chainlist<T>::thisElement(){
    if(null_ptr()) throw "Pointer is a null pointer!";
    return thisNode->get();
}
template <class T>
const T& Chainlist<T>::thisElement() const{
    if(null_ptr()) throw "Pointer is a null pointer!";
    return thisNode->get();
}
/*按照索引获取元素*/
template <class T>
T& Chainlist<T>::operator[](unsigned index){
    if(index>=listSize){
        throw illegalParameterValue("index out of range.");
    }
    if(index==listSize-1) return endNode->get();
    ChainNode<T>* thisnode = firstNode;
    for(unsigned i=1;i<=index;i++){
        thisnode = thisnode->getNextPointer();
    }
    return thisnode->get();
}
template <class T>
const T& Chainlist<T>::operator[](unsigned index) const{
    if(index>=listSize){
        throw illegalParameterValue("index out of range.");
    }
    if(index==listSize-1) return endNode->get();
    const ChainNode<T>* thisnode = firstNode;
    for(unsigned i=1;i<=index;i++){
        thisnode = thisnode->getNextPointer();
    }
    return thisnode->get();
}
/*按照元素搜索索引*/
template <class T>
unsigned Chainlist<T>::search(const T& element_) const{
    unsigned i = 0;
    const ChainNode<T>* thisnode = firstNode;
    while(i<listSize){
        if((thisnode->get())==element_){
            return i;
        }
        thisnode = thisnode->getNextPointer();
        i++;
    }
    return listSize;
}
/*从链表中删去一个元素*/
template <class T>
void Chainlist<T>::erase(unsigned index){
    if(index>=listSize){
        /*如果index大于或等于listSize，说明索引越界，抛出索引越界异常*/
        throw illegalParameterValue("index out of range.");
    }else if(listSize==1){
        /*如果listSize为1，那么链表只有一个元素，只要把它删掉即可*/
        delete firstNode;
        thisNode = nullptr;
        lastNode = nullptr;
        firstNode = nullptr;
        endNode = nullptr;
        listSize = 0;
    }else if(index==0){
        /*如果以上两个条件都不满足，说明链表至少有两个元素，如果index==0，说明要删除的是链表表头的元素*/
        ChainNode<T>* OldfirstNode = firstNode;
        firstNode = OldfirstNode->getNextPointer();
        listSize--;
        if(thisNode==OldfirstNode){
            /*分情况讨论：如果thisNode是firstNode，而firstNode是即将要删除的结点，则将thisNode指针后移即可*/
            thisNode = OldfirstNode->getNextPointer();
        }else if(lastNode == OldfirstNode){
            /*如果lastNode是firstNode，说明thisNode是firstNode的下一个元素，这是只需要将lastNode设为空指针即可*/
            lastNode = nullptr;
        }else{}
        delete OldfirstNode;
    }else if(index==listSize-1){
        /*如果index==listSize-1，那么说明要删除的元素是链表的表尾元素，我们首先需要找到倒数第二个元素
        注意：如果前面的条件都不满足，一定有listSize>=2*/
        ChainNode<T>* OldendNode = endNode;
        if(thisNode==endNode){
            /*如果thisNode就是endNode，说明lastNode指向的就是倒数第二个元素，此时只需要将endNode设为lastNode，thisNode设为nullptr即可*/
            endNode=lastNode;
            thisNode=nullptr;
            listSize--;
        }else{
            /*否则，我们需要从头开始找倒数第二个元素*/
            ChainNode<T>* thisNode_ = firstNode;
            for(unsigned i=1;i<=listSize-2;i++){
             /*
                初始的thisNode_设置为firstNode，然后通过不断的往后挪动来找到倒数第二的元素，如果listSize==2，那么，倒数第二个结点就是firstNode，不需要进行任何操作，此时也不满足i<=listSize-2(0)。如果listSize==3，则需要往后挪动一次，for循环中间的条件也正好只满足1次，依次类推。
               */
                thisNode_ = thisNode_->getNextPointer();
            }
            /*此时得到的thisNode_就是倒数第二个结点，只需要将其设置为末尾结点，并且将其指向的结点设为空结点即可*/
            endNode = thisNode_;
            endNode->changeNextPointer(nullptr);
            listSize--;
            /*如果此时lastNode恰好为旧的endNode，则lastNode应设置为新的endNode，并delete掉旧的endNode*/
            if(lastNode==OldendNode) lastNode = endNode;
            delete OldendNode;
        }
    }else{
        /*
        如果以上条件都不成立，说明两点：
        1. listSize>=2
        2. 要删除的元素既不在表头，又不在表尾
        因此下面要做的第一步就是找到索引为index-1的元素，作为lastNode_，相应地就找到了thisNode_和nextNode_
        */
        ChainNode<T>* lastNode_ = firstNode;//初始的lastNode_设置为firstNode
        for(unsigned i=1;i<=index-1;i++){//index-1可能出错的点是index==0，但是由于要删除的元素既不在表头，也不再表尾，因此index>=1，以上循环条件是合法的
//如果index==1，那么它前一个元素就是firstNode，不用作任何移动处理，如果index==2，它的前一个元素是第二个元素，需要挪动一次，以此类推，因此for循环如此设计
            lastNode_ = lastNode_->getNextPointer();
        }
        //上面的for执行之后，lastNode_是索引为index-1的元素，向后推移两次就是索引为index和index+1的元素
        ChainNode<T>* thisNode_ = lastNode_->getNextPointer();
        //thisNode_可能会是空指针，但由于前面的条件都不满足，因此thisNode_不在表尾，从理论上讲非空，进行getNextPointer()操作是合法的
        ChainNode<T>* nextNode_ = thisNode_->getNextPointer();
        //将lastNode_的指针挪到nextNode_上，然后数组规模-1
        lastNode_->changeNextPointer(nextNode_);
        listSize--;
        if(thisNode==thisNode_){//如果thisNode恰好为thisNode_，说明thisNode恰好为要删除的元素，此时只要将thisNode后移即可
            thisNode = nextNode_;
        }else if(lastNode==thisNode_){//如果lastNode恰好为thisNode_，只要将lastNode前移即可
            lastNode = lastNode_;
        }else{}
        delete thisNode_;//最后，删掉thisNode_
    }
}
template <class T>
void Chainlist<T>::erase(){
    if(null_ptr()) return;//如果thisNode指向的是空结点，那么什么都不做
    ChainNode<T>* nextnode_ = thisNode->getNextPointer();//否则，获取thisNode的下一个结点nextnode_
    if(listSize==1){//如果listSize==1，说明thisNode指向的就是首结点兼尾结点，直接删除即可
        delete thisNode;
        listSize=0;
        firstNode = nullptr;
        lastNode = nullptr;
        thisNode = nullptr;
        endNode = nullptr;
    }else if(thisNode==firstNode){//否则，那就是listSize>=2，如果thisNode==firstNode，说明要删除的是首结点
        delete thisNode;
        firstNode = nextnode_;
        thisNode = nextnode_;//只要把下一个结点设为firstNode和thisNode即可
        listSize--;
    }else if(thisNode==endNode){//如果thisNode==endNode，说明要删除的是尾结点，lastNode就是倒数第二个结点
        delete thisNode;
        thisNode = nullptr;//此时thisNode后移，就是设为空结点
        endNode = lastNode;//由于lastNode就是倒数第二个结点，只需要把endNode就设置为是lastNode即可
        listSize--;
    }else{
        //否则，就是说要删除的结点既不在表头，也不在表尾，则直接将lastNode的尾结点调到nextnode_，然后thisNode设置为nextnode_即可
        delete thisNode;
        thisNode = nextnode_;
        lastNode->changeNextPointer(nextnode_);
        listSize--;
    }
}
template <class T>
void Chainlist<T>::eraseback(){
    if(listSize==0) throw "Chainlist is empty!";
    erase(listSize-1);
}
template <class T>
void Chainlist<T>::erasefront(){
    if(listSize==0) throw "Chainlist is empty!";
    erase(0);
}
/*往链表中插入一个元素*/
template <class T>
void Chainlist<T>::insert(unsigned index,const T& element_){
    if(index>listSize){//如果index>listSize，说明index越界，抛出异常
        throw illegalParameterValue("Index out of range!");
    }else if(listSize==0){//如果listSize==0，说明原来是空链表，我们需要做的是向空链表中插入一个新元素
        firstNode = new ChainNode<T>(element_,nullptr);
        endNode = firstNode;
        thisNode = firstNode;
        lastNode = nullptr;
        listSize = 1;
    }else if(index==0){//否则，listSize>=1，如果index==0，说明我们要在表头插入这个元素，只要申请一个新的结点指向原来的表头
        ChainNode<T>* OldfirstNode = firstNode;
        ChainNode<T>* NewfirstNode =new ChainNode<T>(element_,OldfirstNode);
        firstNode = NewfirstNode;
        if(thisNode==OldfirstNode)//如果原来的thisNode指针就是OldfirstNode，那么lastNode是nullptr，我们在thisNode之前插入了一点新的结点，此时需要让lastNode=firstNode
        {
            lastNode = firstNode;
        }
        listSize++;
    }else if(index==listSize){//如果index==listSize，说明我们要在表尾插入一个新的元素
        ChainNode<T>* NewEndNode = new ChainNode<T>(element_,nullptr);
        ChainNode<T>* OldEndNode = endNode;
        endNode->changeNextPointer(NewEndNode);
        endNode = NewEndNode;
        if(lastNode==OldEndNode){
            lastNode = endNode;
        }
        listSize++;
    }else{//如果以上条件都不满足，说明既不在表头插入，也不再表尾插入，同时蕴含了listSize>=2，index>0，且index<listSize
        ChainNode<T>* lastnode_ = firstNode;
        for(unsigned i=1;i<=index-1;i++){
            lastnode_ = lastnode_->getNextPointer();
        }
        ChainNode<T>* nextnode_ = lastnode_->getNextPointer();
        ChainNode<T>* newnode_ = new ChainNode<T>(element_,nextnode_);
        lastnode_->changeNextPointer(newnode_);
        if(lastNode==lastnode_) lastNode=newnode_;
        listSize++;
    }
}
template<class T>
void Chainlist<T>::insert(const T& element,bool front_){
    if(listSize==0){
        firstNode = new ChainNode<T>(element);
        endNode = firstNode;
        thisNode = firstNode;
        lastNode = nullptr;
        listSize = 1;
        return;
    }else if(thisNode==nullptr){
        ChainNode<T>* newEndNode = new ChainNode<T>(element);
        endNode->changeNextPointer(newEndNode);
        endNode = newEndNode;
        listSize++;
    }else if(listSize==1){
        if(front_){
            ChainNode<T>* OldfirstNode = firstNode;
            firstNode = new ChainNode<T>(element,OldfirstNode);
            lastNode = firstNode;
            thisNode = OldfirstNode;
            listSize=2;
        }else{
            ChainNode<T>* newEndNode = new ChainNode<T>(element);
            firstNode->changeNextPointer(newEndNode);
            endNode=newEndNode;
            lastNode=firstNode;
            thisNode=endNode;
            listSize=2;
        }
    }else if(thisNode==firstNode){
        if(front_){
            ChainNode<T>* OldFirstNode = firstNode;
            firstNode = new ChainNode<T>(element,OldFirstNode);
            lastNode = firstNode;
            listSize++;
        }else{
            ChainNode<T>* nextnode_ = firstNode->getNextPointer();
            ChainNode<T>* newnode_ = new ChainNode<T>(element,nextnode_);
            firstNode->changeNextPointer(newnode_);
            lastNode = firstNode;
            thisNode = nextnode_;
            listSize++;
        }
    }else{
        if(front_){
            ChainNode<T>* newLastnode_ = new ChainNode<T>(element,thisNode);
            lastNode->changeNextPointer(newLastnode_);
            lastNode = newLastnode_;
            listSize++;
        }else{
            ChainNode<T>* oldNextNode_ = thisNode->getNextPointer();
            ChainNode<T>* newNextNode_ = new ChainNode<T>(element,oldNextNode_);
            thisNode->changeNextPointer(newNextNode_);
            lastNode=thisNode;
            thisNode=newNextNode_;
            listSize++;
        }
    }
}
template <class T>
void Chainlist<T>::insertfront(const T& element){
    if(listSize==0){
        firstNode = new ChainNode<T>(element);
        endNode = firstNode;
        thisNode = firstNode;
        lastNode = nullptr;
        listSize=1;
        return;
    }
    ChainNode<T>* Oldfirstnode = firstNode;
    firstNode = new ChainNode<T>(element,Oldfirstnode);
    if(thisNode==Oldfirstnode) lastNode = firstNode;
    listSize++;
}
template <class T>
void Chainlist<T>::insertback(const T& element){
    if(listSize==0){
        firstNode = new ChainNode<T>(element);
        endNode = firstNode;
        thisNode = firstNode;
        lastNode = nullptr;
        listSize=1;
        return;
    }
    ChainNode<T>* OldEndNode = endNode;
    endNode = new ChainNode<T>(element);
    OldEndNode->changeNextPointer(endNode);
    listSize++;
    if(lastNode==OldEndNode) lastNode = endNode;
}
/*复制一个链表*/
template <class T>
Chainlist<T>& Chainlist<T>::operator=(const Chainlist& cl){
    clear();
    listSize=cl.listSize;
    if(listSize==0){
        firstNode = nullptr;
        endNode = nullptr;
        lastNode = nullptr;
        thisNode = nullptr;
    }else{
        ChainNode<T>* cl_thisnode = cl.firstNode;
        firstNode = new ChainNode<T>(cl_thisnode->get());
        thisNode = firstNode;
        lastNode = nullptr;
        cl_thisnode = cl_thisnode->getNextPointer();
        ChainNode<T>* lastNode_ = firstNode;
        for(unsigned i=1;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(cl_thisnode->get());
            lastNode_->changeNextPointer(newnode);
            lastNode_ =newnode;
            cl_thisnode = cl_thisnode->getNextPointer();
        }
        endNode = lastNode_;
    }
    return *this;
}
template <class T>
Chainlist<T>& Chainlist<T>::operator=(Chainlist&& theChainlist)noexcept{
    clear();
    firstNode = theChainlist.firstNode;
    theChainlist.firstNode = nullptr;
    endNode = theChainlist.endNode;
    theChainlist.endNode = nullptr;
    listSize = theChainlist.listSize;
    theChainlist.listSize = 0;
    theChainlist.thisNode = nullptr;
    theChainlist.lastNode = nullptr;
    thisNode = firstNode;
    lastNode = nullptr;
    return *this;
}
template <class T>
Chainlist<T>& Chainlist<T>::operator=(const LinearlistView<T>& view){
    clear();
    listSize = view.size();
    if(listSize==0){
        firstNode = nullptr;
        endNode = nullptr;
        thisNode = nullptr;
        lastNode = nullptr;
    }else{
        firstNode = new ChainNode<T>(view[0]);
        lastNode = nullptr;
        thisNode = firstNode;
        ChainNode<T>* lastNode_ = firstNode;
        for(unsigned i=1;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_=newnode;
        }
        endNode = lastNode_;
    }
    return *this;
}
template <class T>
Chainlist<T>& Chainlist<T>::operator=(const ConstLinearlistView<T>& view){
    clear();
    listSize = view.size();
    if(listSize==0){
        firstNode = nullptr;
        endNode = nullptr;
        thisNode = nullptr;
        lastNode = nullptr;
    }else{
        firstNode = new ChainNode<T>(view[0]);
        lastNode = nullptr;
        thisNode = firstNode;
        ChainNode<T>* lastNode_ = firstNode;
        for(unsigned i=1;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_=newnode;
        }
        endNode = lastNode_;
    }
    return *this;
}
template <class T>
Chainlist<T>& Chainlist<T>::operator=(const Linearlist<T>& theLinearlist){
    clear();
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    listSize = view.size();
    if(listSize==0){
        firstNode = nullptr;
        endNode = nullptr;
        thisNode = nullptr;
        lastNode = nullptr;
    }else{
        firstNode = new ChainNode<T>(view[0]);
        lastNode = nullptr;
        thisNode = firstNode;
        ChainNode<T>* lastNode_ = firstNode;
        for(unsigned i=1;i<listSize;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_=newnode;
        }
        endNode = lastNode_;
    }
    return *this;
}
template <class T>
Chainlist<T>& Chainlist<T>::operator = (const initializer_list<T>& init_list){
    clear();
    listSize = init_list.size();
    if(listSize==0){
        firstNode = nullptr;
        endNode = nullptr;
        thisNode = nullptr;
        lastNode = nullptr;
    }else{
        unsigned index = 0;
        ChainNode<T>* newnode;
        ChainNode<T>* lastNode_;
        for(const T& element_:init_list){
            if(index!=0){
                newnode = new ChainNode<T>(element_);
                lastNode_->changeNextPointer(newnode);
                lastNode_=newnode;
            }else{
                firstNode = new ChainNode<T>(element_);
                thisNode = firstNode;
                lastNode = nullptr;
                lastNode_ = firstNode;
            }
            index++;
        }
        endNode = lastNode_;
    }
    return *this;
}
template <class T>
Chainlist<T>& Chainlist<T>::copy(const T* Tarray,unsigned n){
    clear();
    listSize = n;
    if(n==0){
        firstNode = nullptr;
        endNode = nullptr;
        lastNode = nullptr;
        thisNode = nullptr;
    }else{
        firstNode = new ChainNode<T>(Tarray[0]);
        lastNode = nullptr;
        thisNode = firstNode;
        ChainNode<T>* lastNode_ = firstNode;
        for(unsigned i=1;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(Tarray[i]);
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
        }
        endNode = lastNode_;
    }
    return *this;
}
template <class T>
void Chainlist<T>::merge(const Chainlist& cl){
    unsigned n_cl = cl.size();
    if(n_cl) return;
    else if(listSize==0){
        *this = cl;
    }else{
        ChainNode<T>* cl_thisNode = cl.firstNode;
        ChainNode<T>* lastNode_ = endNode;
        ChainNode<T>* oldEndNode = endNode;
        for(unsigned i=1;i<n_cl;i++){
            ChainNode<T>* newnode = new ChainNode<T>(cl_thisNode->get());
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
            cl_thisNode = cl_thisNode->getNextPointer();
        }
        endNode = lastNode_;
        if(lastNode_==oldEndNode) thisNode=oldEndNode->getNextPointer();
        listSize+=n_cl;
    }
}
template <class T>
void Chainlist<T>::merge(const initializer_list<T>& init_list){
    unsigned n = init_list.size();
    if(n==0) return;
    else if(listSize==0) *this = init_list;
    else{
        ChainNode<T>* lastNode_ = endNode;
        ChainNode<T>* oldEndnode = endNode;
        for(const T& element_:init_list){
            ChainNode<T>* newnode = new ChainNode<T>(element_);
            lastNode_->changeNextPointer(newnode);
            lastNode_ = newnode;
        }
        endNode = lastNode_;
        if(thisNode == nullptr) thisNode = oldEndnode->getNextPointer();
        listSize+=n;
    }
}
template <class T>
void Chainlist<T>::merge(const T* Tarray,unsigned n){
    if(n==0) return;
    else if(listSize==0){
        copy(Tarray,n);
    }
    else{
        ChainNode<T>* thisnode = endNode;
        ChainNode<T>* oldEndNode = endNode;
        listSize+=n;
        for(unsigned i=0;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(Tarray[i]);
            thisnode->changeNextPointer(newnode);
            thisnode = newnode;
        }
        if(thisNode==nullptr) thisNode=oldEndNode->getNextPointer();
        endNode = thisnode;
    }
}
template <class T>
void Chainlist<T>::merge(const LinearlistView<T>& view){
    unsigned n = view.size();
    if(n==0) return;
    else if(listSize==0){
        *this = view;
    }
    else{
        ChainNode<T>* thisnode = endNode;
        ChainNode<T>* oldEndNode = endNode;
        listSize+=n;
        for(unsigned i=0;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            thisnode->changeNextPointer(newnode);
            thisnode = newnode;
        }
        if(thisNode==nullptr) thisNode=oldEndNode->getNextPointer();
        endNode = thisnode;
    }
}
template <class T>
void Chainlist<T>::merge(const ConstLinearlistView<T>& view){
    unsigned n = view.size();
    if(n==0) return;
    else if(listSize==0){
        *this = view;
    }
    else{
        ChainNode<T>* thisnode = endNode;
        ChainNode<T>* oldEndNode = endNode;
        listSize+=n;
        for(unsigned i=0;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            thisnode->changeNextPointer(newnode);
            thisnode = newnode;
        }
        if(thisNode==nullptr) thisNode=oldEndNode->getNextPointer();
        endNode = thisnode;
    }
}
template <class T>
void Chainlist<T>::merge(const Linearlist<T>& theLinearlist){
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    unsigned n = view.size();
    if(n==0) return;
    else if(listSize==0){
        *this = view;
    }
    else{
        ChainNode<T>* thisnode = endNode;
        ChainNode<T>* oldEndNode = endNode;
        listSize+=n;
        for(unsigned i=0;i<n;i++){
            ChainNode<T>* newnode = new ChainNode<T>(view[i]);
            thisnode->changeNextPointer(newnode);
            thisnode = newnode;
        }
        if(thisNode==nullptr) thisNode=oldEndNode->getNextPointer();
        endNode = thisnode;
    }
}
template <class T>
ChainlistIterator<T> Chainlist<T>::begin(){
    return ChainlistIterator<T>(firstNode);
}
template <class T>
ChainlistIterator<T> Chainlist<T>::end(){
    return ChainlistIterator<T>(nullptr);
}
template <class T>
ConstChainlistIterator<T> Chainlist<T>::begin() const{
    return ConstChainlistIterator<T>(firstNode);
}
template <class T>
ConstChainlistIterator<T> Chainlist<T>::end() const{
    return ConstChainlistIterator<T>(nullptr);
}
/*创建线性表视图*/
template <class T>
LinearlistView<T> Chainlist<T>::createView(){
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
ConstLinearlistView<T> Chainlist<T>::createView() const{
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
ConstLinearlistView<T> Chainlist<T>::createConstView() const{
    if(listSize==0) {}
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
    return ConstLinearlistView<T>();
}
/*取子串*/
template <class T>
LinearlistView<T> Chainlist<T>::sublist(unsigned begin_,unsigned end_){
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
ConstLinearlistView<T> Chainlist<T>::sublist(unsigned begin_,unsigned end_) const{
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
#endif // CHAINLIST_H
