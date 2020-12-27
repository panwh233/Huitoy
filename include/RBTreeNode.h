#include <functional>
#include "ArrayQueue.h"
#ifndef RBTREENODE_H
#define RBTREENODE_H
namespace Huitoy{
template <class T>
class RBTreeNode
{
    public:
        //Constructor
        RBTreeNode(const T& element_=T(),bool red = true,RBTreeNode* leftChild_=nullptr,RBTreeNode* rightChild_=nullptr);
        RBTreeNode(const RBTreeNode& node);
        RBTreeNode(RBTreeNode&& node) noexcept;
        //Get child
        RBTreeNode* getLeftChild();
        const RBTreeNode* getLeftChild() const;
        RBTreeNode* getRightChild();
        const RBTreeNode* getRightChild() const;
        //Change child
        void changeLeftChild(RBTreeNode* node);
        void changeRightChild(RBTreeNode* node);
        //Get element
        T& get();
        const T& get() const;
        //Node parameter
        unsigned size() const;
        unsigned depth() const;
        void changeColor(bool red);
        bool red() const;
        //
        void preOrder(const std::function<void(T&)>& visit);
        void inOrder(const std::function<void(T&)>& visit);
        void postOrder(const std::function<void(T&)>& visit);
        void levelOrder(const std::function<void(T&)>& visit);
        void preOrder(const std::function<void(const T&)>& visit) const;
        void inOrder(const std::function<void(const T&)>& visit) const;
        void postOrder(const std::function<void(const T&)>& visit) const;
        void levelOrder(const std::function<void(const T&)>& visit) const;
        //Clear the node
        ~RBTreeNode();
        void clearLeftChild();
        void clearRightChild();
        //Copy the node
        void copy(const RBTreeNode* node);
        RBTreeNode& operator=(const RBTreeNode& tree);
        RBTreeNode& operator=(RBTreeNode&& tree) noexcept;

    protected:
        T element;
        RBTreeNode* leftChild;
        RBTreeNode* rightChild;
        bool _red;

};
//Constructor
template <class T>
RBTreeNode<T>::RBTreeNode(const T& element_,bool red_,RBTreeNode<T>* leftChild_,RBTreeNode<T>* rightChild_){
    element = element_;
    _red = red_;
    leftChild = leftChild_;
    rightChild = rightChild_;
}
template <class T>
RBTreeNode<T>::RBTreeNode(const RBTreeNode& node){
    element = node.get();
    _red = node._red;
    if(node.getLeftChild()){
        leftChild = new RBTreeNode<T>;
        leftChild->copy(node.getLeftChild());
    }
    if(node.getRightChild()){
        rightChild = new RBTreeNode<T>;
        rightChild->copy(node.getRightChild());
    }
}
template <class T>
RBTreeNode<T>::RBTreeNode(RBTreeNode&& tree) noexcept{
    leftChild = tree.leftChild;
    _red = tree._red;
    tree.leftChild = nullptr;
    rightChild = tree.rightChild;
    tree.rightChild = nullptr;
    element = tree.element;
}
template<class T>
RBTreeNode<T>* RBTreeNode<T>::getLeftChild(){
    return leftChild;
}
template <class T>
const RBTreeNode<T>* RBTreeNode<T>::getLeftChild() const{
    return leftChild;
}
template <class T>
RBTreeNode<T>* RBTreeNode<T>::getRightChild(){
    return rightChild;
}
template <class T>
const RBTreeNode<T>* RBTreeNode<T>::getRightChild() const{
    return rightChild;
}
template <class T>
void RBTreeNode<T>::changeLeftChild(RBTreeNode<T>* leftChild_){
    leftChild = leftChild_;
}
template <class T>
void RBTreeNode<T>::changeRightChild(RBTreeNode<T>* rightChild_){
    rightChild = rightChild_;
}
template <class T>
T& RBTreeNode<T>::get(){
    return element;
}
template <class T>
const T& RBTreeNode<T>::get() const{
    return element;
}
template <class T>
unsigned RBTreeNode<T>::size() const{
    unsigned size_=1;
    if(leftChild!=nullptr) size_ += leftChild->size();
    if(rightChild!=nullptr) size_ += rightChild->size();
    return size_;
}
template <class T>
unsigned RBTreeNode<T>::depth() const{
    unsigned leftChild_depth = 0;
    unsigned rightChild_depth = 0;
    if(leftChild!=nullptr) leftChild_depth = leftChild->depth();
    if(rightChild!=nullptr) rightChild_depth = rightChild->depth();
    if(leftChild_depth>=rightChild_depth) return 1+leftChild_depth;
    else return 1+rightChild_depth;
}
template <class T>
bool RBTreeNode<T>::red() const{
    return _red;
}
template <class T>
void RBTreeNode<T>::changeColor(bool red_){
    _red = red_;
}
//遍历树
template <class T>
void RBTreeNode<T>::preOrder(const std::function<void(T&)>& visit){
    visit(element);
    if(leftChild!=nullptr) leftChild->preOrder(visit);
    if(rightChild!=nullptr) rightChild->preOrder(visit);
}
template <class T>
void RBTreeNode<T>::inOrder(const std::function<void(T&)>& visit){
    if(leftChild!=nullptr)leftChild->inOrder(visit);
    visit(element);
    if(rightChild!=nullptr)rightChild->inOrder(visit);
}
template <class T>
void RBTreeNode<T>::postOrder(const std::function<void(T&)>& visit){
    if(leftChild!=nullptr)leftChild->postOrder(visit);
    if(rightChild!=nullptr)rightChild->postOrder(visit);
    visit(element);
}
template <class T>
void RBTreeNode<T>::levelOrder(const std::function<void(T&)>& visit){
    ArrayQueue<RBTreeNode<T>*> queue_;
    queue_.push(this);
    while(!queue_.empty()){
        RBTreeNode<T>* node = queue_.front();
        queue_.pop();
        visit(node->get());
        if(node->getLeftChild()!=nullptr) queue_.push(node->getLeftChild());
        if(node->getRightChild()!=nullptr) queue_.push(node->getRightChild());
    }
}

template <class T>
void RBTreeNode<T>::preOrder(const std::function<void(const T&)>& visit)const{
    visit(element);
    if(leftChild!=nullptr) leftChild->preOrder(visit);
    if(rightChild!=nullptr) rightChild->preOrder(visit);
}
template <class T>
void RBTreeNode<T>::inOrder(const std::function<void(const T&)>& visit)const{
    if(leftChild!=nullptr)leftChild->inOrder(visit);
    visit(element);
    if(rightChild!=nullptr)rightChild->inOrder(visit);
}
template <class T>
void RBTreeNode<T>::postOrder(const std::function<void(const T&)>& visit)const{
    if(leftChild!=nullptr)leftChild->postOrder(visit);
    if(rightChild!=nullptr)rightChild->postOrder(visit);
    visit(element);
}
template <class T>
void RBTreeNode<T>::levelOrder(const std::function<void(const T&)>& visit) const{
    ArrayQueue<const RBTreeNode<T>*> queue_;
    queue_.push(this);
    while(!queue_.empty()){
        const RBTreeNode<T>* node = queue_.front();
        queue_.pop();
        visit(node->get());
        if(node->getLeftChild()!=nullptr) queue_.push(node->getLeftChild());
        if(node->getRightChild()!=nullptr) queue_.push(node->getRightChild());
    }
}
//析构函数与清除
template<class T>
RBTreeNode<T>::~RBTreeNode(){
    if(leftChild!=nullptr) delete leftChild;
    if(rightChild!=nullptr) delete rightChild;
}
template <class T>
void RBTreeNode<T>::clearLeftChild(){
    if(leftChild!=nullptr) delete leftChild;
    leftChild = nullptr;
}
template <class T>
void RBTreeNode<T>::clearRightChild(){
    if(rightChild!=nullptr) delete rightChild;
    rightChild = nullptr;
}
//深复制结点
template <class T>
void RBTreeNode<T>::copy(const RBTreeNode<T>* node){
    if(node==nullptr) return;
    element = node->get();
    _red = node->_red;
    clearLeftChild();
    clearRightChild();
    if(node->getLeftChild()){
        leftChild = new RBTreeNode<T>;
        leftChild->copy(node->getLeftChild());
    }
    if(node->getRightChild()){
        rightChild = new RBTreeNode<T>;
        rightChild->copy(node->getRightChild());
    }
}
template <class T>
RBTreeNode<T>& RBTreeNode<T>::operator = (const RBTreeNode& node){
    element = node.get();
    _red = node._red;
    clearLeftChild();
    clearRightChild();
    if(node->getLeftChild()){
        leftChild = new RBTreeNode<T>;
        leftChild->copy(node.getLeftChild());
    }
    if(node->getRightChild()){
        rightChild = new RBTreeNode<T>;
        rightChild->copy(node.getRightChild());
    }
    return *this;
}
template <class T>
RBTreeNode<T>& RBTreeNode<T>::operator = (RBTreeNode&& node) noexcept{
    clearLeftChild();
    clearRightChild();
    element = node.element;
    leftChild = node.leftChild;
    _red = node._red;
    node.leftChild = nullptr;
    rightChild = node.rightChild;
    node.rightChild = nullptr;
    return *this;
}
}//namespace end
#endif // RBTREENODE_H
