#include "Abs_Chainlist.h"
#include "illegalParameterValue.h"
#ifndef CHAINLIST_H
#define CHAINLIST_H
namespace Huitoy{
template <class T>
class Chainlist:public Abs_Chainlist<T>
{
    public:
        /*���캯��*/
        Chainlist();
        Chainlist(const Chainlist& theChainlist);
        Chainlist(const initializer_list<T>& init_list);
        Chainlist(Chainlist&& theChainlist)noexcept;
        Chainlist(const LinearlistView<T>& view);
        Chainlist(const ConstLinearlistView<T>& view) ;
        Chainlist(const Linearlist<T>& theLinearlist);
        Chainlist(const T& element,unsigned n);
        Chainlist(const T* Tarray,unsigned n);
        /*�������ز���*/
        bool empty() const;
        unsigned size() const;
        /*�����ָ���ƶ�*/
        void next() const;
        void switch_to_begin() const;
        bool null_ptr() const;
        T& thisElement();
        const T& thisElement() const;
        /*�����������Ա���ȡ��һ����Ӧ��Ԫ��*/
        T& operator[] (unsigned index);
        const T& operator[](unsigned index) const;
        /*����ĳһԪ�������Ա����״γ��ֵ�����*/
        unsigned search(const T& element)const;
        /*��������ɾȥһ��Ԫ��*/
        void erase(unsigned index);
        void erase();
        void eraseback();
        void erasefront();
        /*�������в���һ��Ԫ��*/
        void insert(unsigned index,const T& element_);
        void insert(const T& theElement,bool front_ = true);
        void insertback(const T& element);
        void insertfront(const T& element);
        /*����ĸ���*/
        Chainlist& operator=(const Chainlist& theChainlist);
        Chainlist& operator=(Chainlist&& theChainlist) noexcept;
        Chainlist& operator=(const LinearlistView<T>& view);
        Chainlist& operator=(const ConstLinearlistView<T>& view);
        Chainlist& operator=(const Linearlist<T>& theLinearlist);
        Chainlist& operator=(const initializer_list<T>& init_list);
        Chainlist& copy(const T* Tarray,unsigned n);
        /*�������*/
        void clear();
        /*����ĺϲ�*/
        void merge(const T* Tarray,unsigned n);
        void merge(const initializer_list<T>& init_list);
        void merge(const Chainlist& theChainlist);
        void merge(const LinearlistView<T>& view);
        void merge(const ConstLinearlistView<T>& view);
        void merge(const Linearlist<T>& theLinearlist);
        /*�������Ա���ͼ*/
        LinearlistView<T> createView();
        ConstLinearlistView<T> createConstView() const;
        ConstLinearlistView<T> createView() const;
        /*ȡ�Ӵ�*/
        LinearlistView<T> sublist(unsigned start_,unsigned end_);
        ConstLinearlistView<T> sublist(unsigned start_,unsigned end_) const;
        /*����ĵ�����*/
        ChainlistIterator<T> begin();
        ChainlistIterator<T> end();
        ConstChainlistIterator<T> begin() const;
        ConstChainlistIterator<T> end() const;
        /*��������*/
        ~Chainlist();

    protected:
        ChainNode<T>* firstNode;
        ChainNode<T>* endNode;
        mutable ChainNode<T>* thisNode;
        mutable ChainNode<T>* lastNode;
        unsigned listSize;
    private:
};
/*���캯����ʵ�֣�1. Ĭ�Ϲ��캯��*/
template <class T>
Chainlist<T>::Chainlist(){
    firstNode = nullptr;
    endNode = nullptr;
    thisNode = nullptr;
    lastNode = nullptr;
    listSize = 0;
}
/*2. ���ƹ��캯��*/
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
/*3. ����һ��T��������г�ʼ��*/
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
/*���캯��4���ƶ����캯��*/
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
/*���캯��5��6��������ͼ����*/
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
/*���캯��7�����������Ա���г�ʼ��*/
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
/*���캯��8�����ó�ʼ���б���г�ʼ��*/
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
/*���캯��9����һ��Ԫ�س�ʼ������*/
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
/*��������*/
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
/*������ز���*/
template <class T>
bool Chainlist<T>::empty() const{
    return listSize==0;
}
template <class T>
unsigned Chainlist<T>::size() const{
    return listSize;
}
/*�����ָ���ƶ�*/
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
/*����������ȡԪ��*/
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
/*����Ԫ����������*/
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
/*��������ɾȥһ��Ԫ��*/
template <class T>
void Chainlist<T>::erase(unsigned index){
    if(index>=listSize){
        /*���index���ڻ����listSize��˵������Խ�磬�׳�����Խ���쳣*/
        throw illegalParameterValue("index out of range.");
    }else if(listSize==1){
        /*���listSizeΪ1����ô����ֻ��һ��Ԫ�أ�ֻҪ����ɾ������*/
        delete firstNode;
        thisNode = nullptr;
        lastNode = nullptr;
        firstNode = nullptr;
        endNode = nullptr;
        listSize = 0;
    }else if(index==0){
        /*����������������������㣬˵����������������Ԫ�أ����index==0��˵��Ҫɾ�����������ͷ��Ԫ��*/
        ChainNode<T>* OldfirstNode = firstNode;
        firstNode = OldfirstNode->getNextPointer();
        listSize--;
        if(thisNode==OldfirstNode){
            /*��������ۣ����thisNode��firstNode����firstNode�Ǽ���Ҫɾ���Ľ�㣬��thisNodeָ����Ƽ���*/
            thisNode = OldfirstNode->getNextPointer();
        }else if(lastNode == OldfirstNode){
            /*���lastNode��firstNode��˵��thisNode��firstNode����һ��Ԫ�أ�����ֻ��Ҫ��lastNode��Ϊ��ָ�뼴��*/
            lastNode = nullptr;
        }else{}
        delete OldfirstNode;
    }else if(index==listSize-1){
        /*���index==listSize-1����ô˵��Ҫɾ����Ԫ��������ı�βԪ�أ�����������Ҫ�ҵ������ڶ���Ԫ��
        ע�⣺���ǰ��������������㣬һ����listSize>=2*/
        ChainNode<T>* OldendNode = endNode;
        if(thisNode==endNode){
            /*���thisNode����endNode��˵��lastNodeָ��ľ��ǵ����ڶ���Ԫ�أ���ʱֻ��Ҫ��endNode��ΪlastNode��thisNode��Ϊnullptr����*/
            endNode=lastNode;
            thisNode=nullptr;
            listSize--;
        }else{
            /*����������Ҫ��ͷ��ʼ�ҵ����ڶ���Ԫ��*/
            ChainNode<T>* thisNode_ = firstNode;
            for(unsigned i=1;i<=listSize-2;i++){
             /*
                ��ʼ��thisNode_����ΪfirstNode��Ȼ��ͨ�����ϵ�����Ų�����ҵ������ڶ���Ԫ�أ����listSize==2����ô�������ڶ���������firstNode������Ҫ�����κβ�������ʱҲ������i<=listSize-2(0)�����listSize==3������Ҫ����Ų��һ�Σ�forѭ���м������Ҳ����ֻ����1�Σ��������ơ�
               */
                thisNode_ = thisNode_->getNextPointer();
            }
            /*��ʱ�õ���thisNode_���ǵ����ڶ�����㣬ֻ��Ҫ��������Ϊĩβ��㣬���ҽ���ָ��Ľ����Ϊ�ս�㼴��*/
            endNode = thisNode_;
            endNode->changeNextPointer(nullptr);
            listSize--;
            /*�����ʱlastNodeǡ��Ϊ�ɵ�endNode����lastNodeӦ����Ϊ�µ�endNode����delete���ɵ�endNode*/
            if(lastNode==OldendNode) lastNode = endNode;
            delete OldendNode;
        }
    }else{
        /*
        ���������������������˵�����㣺
        1. listSize>=2
        2. Ҫɾ����Ԫ�ؼȲ��ڱ�ͷ���ֲ��ڱ�β
        �������Ҫ���ĵ�һ�������ҵ�����Ϊindex-1��Ԫ�أ���ΪlastNode_����Ӧ�ؾ��ҵ���thisNode_��nextNode_
        */
        ChainNode<T>* lastNode_ = firstNode;//��ʼ��lastNode_����ΪfirstNode
        for(unsigned i=1;i<=index-1;i++){//index-1���ܳ���ĵ���index==0����������Ҫɾ����Ԫ�ؼȲ��ڱ�ͷ��Ҳ���ٱ�β�����index>=1������ѭ�������ǺϷ���
//���index==1����ô��ǰһ��Ԫ�ؾ���firstNode���������κ��ƶ��������index==2������ǰһ��Ԫ���ǵڶ���Ԫ�أ���ҪŲ��һ�Σ��Դ����ƣ����forѭ��������
            lastNode_ = lastNode_->getNextPointer();
        }
        //�����forִ��֮��lastNode_������Ϊindex-1��Ԫ�أ�����������ξ�������Ϊindex��index+1��Ԫ��
        ChainNode<T>* thisNode_ = lastNode_->getNextPointer();
        //thisNode_���ܻ��ǿ�ָ�룬������ǰ��������������㣬���thisNode_���ڱ�β���������Ͻ��ǿգ�����getNextPointer()�����ǺϷ���
        ChainNode<T>* nextNode_ = thisNode_->getNextPointer();
        //��lastNode_��ָ��Ų��nextNode_�ϣ�Ȼ�������ģ-1
        lastNode_->changeNextPointer(nextNode_);
        listSize--;
        if(thisNode==thisNode_){//���thisNodeǡ��ΪthisNode_��˵��thisNodeǡ��ΪҪɾ����Ԫ�أ���ʱֻҪ��thisNode���Ƽ���
            thisNode = nextNode_;
        }else if(lastNode==thisNode_){//���lastNodeǡ��ΪthisNode_��ֻҪ��lastNodeǰ�Ƽ���
            lastNode = lastNode_;
        }else{}
        delete thisNode_;//���ɾ��thisNode_
    }
}
template <class T>
void Chainlist<T>::erase(){
    if(null_ptr()) return;//���thisNodeָ����ǿս�㣬��ôʲô������
    ChainNode<T>* nextnode_ = thisNode->getNextPointer();//���򣬻�ȡthisNode����һ�����nextnode_
    if(listSize==1){//���listSize==1��˵��thisNodeָ��ľ����׽���β��㣬ֱ��ɾ������
        delete thisNode;
        listSize=0;
        firstNode = nullptr;
        lastNode = nullptr;
        thisNode = nullptr;
        endNode = nullptr;
    }else if(thisNode==firstNode){//�����Ǿ���listSize>=2�����thisNode==firstNode��˵��Ҫɾ�������׽��
        delete thisNode;
        firstNode = nextnode_;
        thisNode = nextnode_;//ֻҪ����һ�������ΪfirstNode��thisNode����
        listSize--;
    }else if(thisNode==endNode){//���thisNode==endNode��˵��Ҫɾ������β��㣬lastNode���ǵ����ڶ������
        delete thisNode;
        thisNode = nullptr;//��ʱthisNode���ƣ�������Ϊ�ս��
        endNode = lastNode;//����lastNode���ǵ����ڶ�����㣬ֻ��Ҫ��endNode������Ϊ��lastNode����
        listSize--;
    }else{
        //���򣬾���˵Ҫɾ���Ľ��Ȳ��ڱ�ͷ��Ҳ���ڱ�β����ֱ�ӽ�lastNode��β������nextnode_��Ȼ��thisNode����Ϊnextnode_����
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
/*�������в���һ��Ԫ��*/
template <class T>
void Chainlist<T>::insert(unsigned index,const T& element_){
    if(index>listSize){//���index>listSize��˵��indexԽ�磬�׳��쳣
        throw illegalParameterValue("Index out of range!");
    }else if(listSize==0){//���listSize==0��˵��ԭ���ǿ�����������Ҫ��������������в���һ����Ԫ��
        firstNode = new ChainNode<T>(element_,nullptr);
        endNode = firstNode;
        thisNode = firstNode;
        lastNode = nullptr;
        listSize = 1;
    }else if(index==0){//����listSize>=1�����index==0��˵������Ҫ�ڱ�ͷ�������Ԫ�أ�ֻҪ����һ���µĽ��ָ��ԭ���ı�ͷ
        ChainNode<T>* OldfirstNode = firstNode;
        ChainNode<T>* NewfirstNode =new ChainNode<T>(element_,OldfirstNode);
        firstNode = NewfirstNode;
        if(thisNode==OldfirstNode)//���ԭ����thisNodeָ�����OldfirstNode����ôlastNode��nullptr��������thisNode֮ǰ������һ���µĽ�㣬��ʱ��Ҫ��lastNode=firstNode
        {
            lastNode = firstNode;
        }
        listSize++;
    }else if(index==listSize){//���index==listSize��˵������Ҫ�ڱ�β����һ���µ�Ԫ��
        ChainNode<T>* NewEndNode = new ChainNode<T>(element_,nullptr);
        ChainNode<T>* OldEndNode = endNode;
        endNode->changeNextPointer(NewEndNode);
        endNode = NewEndNode;
        if(lastNode==OldEndNode){
            lastNode = endNode;
        }
        listSize++;
    }else{//������������������㣬˵���Ȳ��ڱ�ͷ���룬Ҳ���ٱ�β���룬ͬʱ�̺���listSize>=2��index>0����index<listSize
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
/*����һ������*/
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
/*�������Ա���ͼ*/
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
/*ȡ�Ӵ�*/
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
