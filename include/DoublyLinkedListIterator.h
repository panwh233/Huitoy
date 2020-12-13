#include "DoublyLinkedListNode.h"
#ifndef DOUBLYLINKEDLISTITERATOR_H
#define DOUBLYLINKEDLISTITERATOR_H
namespace Huitoy{
template <class T>
class DoublyLinkedListIterator
{
    public:
        DoublyLinkedListIterator(DoublyLinkedListNode<T>* node_);
        DoublyLinkedListIterator(const DoublyLinkedListIterator& theDoublyLinkedListIterator);
        T& operator*() const;
        DoublyLinkedListIterator& operator++();
        DoublyLinkedListIterator operator++(int);
        DoublyLinkedListIterator& operator--();
        DoublyLinkedListIterator operator--(int);
        bool operator == (const DoublyLinkedListIterator& theDoublyLinkedListIterator) const;
        bool operator != (const DoublyLinkedListIterator& theDoublyLinkedListIterator) const;
    protected:
        DoublyLinkedListNode<T>* node;
    private:
};
template <class T>
class ConstDoublyLinkedListIterator
{
    public:
        ConstDoublyLinkedListIterator(const DoublyLinkedListNode<T>* node_);
        ConstDoublyLinkedListIterator(const ConstDoublyLinkedListIterator& theConstDoublyLinkedListIterator);
        const T& operator*() const;
        ConstDoublyLinkedListIterator& operator++();
        ConstDoublyLinkedListIterator operator++(int);
        ConstDoublyLinkedListIterator& operator--();
        ConstDoublyLinkedListIterator operator--(int);
        bool operator == (const ConstDoublyLinkedListIterator& theConstDoublyLinkedListIterator) const;
        bool operator != (const ConstDoublyLinkedListIterator& theConstDoublyLinkedListIterator) const;
    protected:
        const DoublyLinkedListNode<T>* node;
};
//构造函数
template <class T>
DoublyLinkedListIterator<T>::DoublyLinkedListIterator(DoublyLinkedListNode<T>* node_){
    node = node_;
}
template <class T>
DoublyLinkedListIterator<T>::DoublyLinkedListIterator(const DoublyLinkedListIterator& theDoublyLinkedListIterator){
    node = theDoublyLinkedListIterator.node;
}
template <class T>
ConstDoublyLinkedListIterator<T>::ConstDoublyLinkedListIterator(const DoublyLinkedListNode<T>* node_){
    node = node_;
}
template <class T>
ConstDoublyLinkedListIterator<T>::ConstDoublyLinkedListIterator(const ConstDoublyLinkedListIterator& theConstDoublyLinkedListIterator){
    node = theConstDoublyLinkedListIterator.node;
}
//解运算符
template <class T>
T& DoublyLinkedListIterator<T>::operator*() const{
    return node->get();
}
//++运算符
template<class T>
DoublyLinkedListIterator<T> DoublyLinkedListIterator<T>::operator++(int){
    DoublyLinkedListNode<T>* thisnode = node;
    if(thisnode){
        node = node->getNextnode();
    }
    return DoublyLinkedListIterator(thisnode);
}
template <class T>
DoublyLinkedListIterator<T>& DoublyLinkedListIterator<T>::operator++(){
    if(node){
        node = node->getNextnode();
    }
    return *this;
}
template <class T>
ConstDoublyLinkedListIterator<T> ConstDoublyLinkedListIterator<T>::operator++(int){
    const DoublyLinkedListNode<T>* thisnode = node;
    if(thisnode){
        node = node->getNextnode();
    }
    return ConstDoublyLinkedListIterator(thisnode);
}
template <class T>
ConstDoublyLinkedListIterator<T>& ConstDoublyLinkedListIterator<T>::operator++(){
    if(node) node = node->getNextnode();
    return *this;
}
//--运算符
template <class T>
DoublyLinkedListIterator<T> DoublyLinkedListIterator<T>::operator--(int){
    DoublyLinkedListNode<T>* thisnode = node;
    if(node) node = node->getLastnode();
    return DoublyLinkedListIterator(thisnode);
}
template <class T>
DoublyLinkedListIterator<T>& DoublyLinkedListIterator<T>::operator--(){
    if(node) node = node->getLastnode();
    return *this;
}
template <class T>
ConstDoublyLinkedListIterator<T> ConstDoublyLinkedListIterator<T>::operator--(int){
    const DoublyLinkedListNode<T>* thisnode = node;
    if(node) node = node->getLastnode();
    return ConstDoublyLinkedListIterator(thisnode);
}
template <class T>
ConstDoublyLinkedListIterator<T>& ConstDoublyLinkedListIterator<T>::operator--(){
    if(node) node=node->getLastnode();
    return *this;
}
//==号
template <class T>
bool ConstDoublyLinkedListIterator<T>::operator==(const ConstDoublyLinkedListIterator& theConstDoublyLinkedListIterator) const{
    return node == theConstDoublyLinkedListIterator.node;
}
template <class T>
bool DoublyLinkedListIterator<T>::operator==(const DoublyLinkedListIterator& theDoublyLinkedListIterator) const{
    return node == theDoublyLinkedListIterator.node;
}
//!=号
template <class T>
bool ConstDoublyLinkedListIterator<T>::operator!=(const ConstDoublyLinkedListIterator& theConstDoublyLinkedListIterator) const{
    return node != theConstDoublyLinkedListIterator.node;
}
template <class T>
bool DoublyLinkedListIterator<T>::operator!=(const DoublyLinkedListIterator& theDoublyLinkedListIterator) const{
    return node != theDoublyLinkedListIterator.node;
}
//*运算符

template <class T>
const T& ConstDoublyLinkedListIterator<T>::operator *() const{
    if(node==nullptr) throw "Node is null!";
    return node->get();
}
}
#endif // DOUBLELINKEDLISTITERATOR_H
