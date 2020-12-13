#ifndef DOUBLYLINKEDLISTNODE_H
#define DOUBLYLINKEDLISTNODE_H
namespace Huitoy{
template <class T>
class DoublyLinkedListNode
{
    public:
        DoublyLinkedListNode();
        DoublyLinkedListNode(const T& element_,DoublyLinkedListNode* lastnode_=nullptr,DoublyLinkedListNode* nextnode_=nullptr);
        DoublyLinkedListNode(const DoublyLinkedListNode& dlln);
        T& get();
        const T& get() const;
        const DoublyLinkedListNode* getLastnode() const;
        const DoublyLinkedListNode* getNextnode() const;
        DoublyLinkedListNode* getLastnode();
        DoublyLinkedListNode* getNextnode();
        void setNextnode(DoublyLinkedListNode* nextnode_);
        void setLastnode(DoublyLinkedListNode* lastnode_);

    protected:
        T element;
        mutable DoublyLinkedListNode* lastnode;
        mutable DoublyLinkedListNode* nextnode;
    private:
};
template <class T>
DoublyLinkedListNode<T>::DoublyLinkedListNode(){
    lastnode = nullptr;
    nextnode = nullptr;
}
template <class T>
DoublyLinkedListNode<T>::DoublyLinkedListNode(const T& element_,DoublyLinkedListNode* lastnode_,DoublyLinkedListNode* nextnode_){
    element = element_;
    lastnode = lastnode_;
    nextnode = nextnode_;
}
template <class T>
DoublyLinkedListNode<T>::DoublyLinkedListNode(const DoublyLinkedListNode& dlln){
    element = dlln.element;
    lastnode = dlln.lastnode;
    nextnode = dlln.nextnode;
}
template <class T>
T& DoublyLinkedListNode<T>::get(){
    return element;
}
template <class T>
const T& DoublyLinkedListNode<T>::get() const{
    return element;
}
template <class T>
DoublyLinkedListNode<T>* DoublyLinkedListNode<T>::getLastnode(){
    return lastnode;
}
template <class T>
const DoublyLinkedListNode<T>* DoublyLinkedListNode<T>::getLastnode() const{
    return lastnode;
}
template <class T>
DoublyLinkedListNode<T>* DoublyLinkedListNode<T>::getNextnode(){
    return nextnode;
}
template <class T>
const DoublyLinkedListNode<T>* DoublyLinkedListNode<T>::getNextnode() const{
    return nextnode;
}
template <class T>
void DoublyLinkedListNode<T>::setNextnode(DoublyLinkedListNode* nextnode_){
    nextnode = nextnode_;
}
template <class T>
void DoublyLinkedListNode<T>::setLastnode(DoublyLinkedListNode* lastnode_){
    lastnode = lastnode_;
}
}
#endif // DOUBLYLINKEDLISTNODE_H
