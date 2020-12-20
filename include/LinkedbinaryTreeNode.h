#include "ArrayQueue.h"
#include <functional>
#ifndef LINKEDBINARYTREENODE_H
#define LINKEDBINARYTREENODE_H
namespace Huitoy{
template <class T>
class LinkedbinaryTreeNode
{
    public:
        LinkedbinaryTreeNode(const T& element_=T(),LinkedbinaryTreeNode<T>* leftChild_ = nullptr,LinkedbinaryTreeNode<T>* rightChild_=nullptr);
        LinkedbinaryTreeNode(const LinkedbinaryTreeNode& node);
        LinkedbinaryTreeNode(LinkedbinaryTreeNode&& node) noexcept;
        //获取左右子树的指针
        LinkedbinaryTreeNode<T>* getLeftChild();
        const LinkedbinaryTreeNode<T>* getLeftChild() const;
        LinkedbinaryTreeNode<T>* getRightChild();
        const LinkedbinaryTreeNode<T>* getRightChild() const;
        //改变左右子树
        void changeLeftChild(LinkedbinaryTreeNode<T>* leftChild_);
        void changeRightChild(LinkedbinaryTreeNode<T>* rightChild_);
        //获取该结点的元素
        T& get();
        const T& get() const;
        //获取该结点的参数
        unsigned size() const;
        unsigned depth() const;
        //遍历
        void preOrder(const std::function<void(T&)>& visit);
        void inOrder(const std::function<void(T&)>& visit);
        void postOrder(const std::function<void(T&)>& visit);
        void levelOrder(const std::function<void(T&)>& visit);
        void preOrder(const std::function<void(const T&)>& visit) const;
        void inOrder(const std::function<void(const T&)>& visit) const;
        void postOrder(const std::function<void(const T&)>& visit) const;
        void levelOrder(const std::function<void(const T&)>& visit) const;
        //清除结点以及析构函数
        ~LinkedbinaryTreeNode();
        void clearLeftChild();
        void clearRightChild();
        //深复制结点
        void copy(const LinkedbinaryTreeNode<T>* node);
        LinkedbinaryTreeNode<T>& operator=(const LinkedbinaryTreeNode<T>& tree);
        LinkedbinaryTreeNode<T>& operator=(LinkedbinaryTreeNode<T>&& tree) noexcept;
    protected:
        T element;
        LinkedbinaryTreeNode<T>* leftChild;
        LinkedbinaryTreeNode<T>* rightChild;
    private:
};
template <class T>
LinkedbinaryTreeNode<T>::LinkedbinaryTreeNode(const T& element_,LinkedbinaryTreeNode<T>* leftChild_,LinkedbinaryTreeNode<T>* rightChild_){
    element = element_;
    leftChild = leftChild_;
    rightChild = rightChild_;
}
template <class T>
LinkedbinaryTreeNode<T>::LinkedbinaryTreeNode(const LinkedbinaryTreeNode& node){
    element = node.get();
    if(node.getLeftChild()){
        leftChild = new LinkedbinaryTreeNode<T>;
        leftChild->copy(node.getLeftChild());
    }
    if(node.getRightChild()){
        rightChild = new LinkedbinaryTreeNode<T>;
        rightChild->copy(node.getRightChild());
    }
}
template <class T>
LinkedbinaryTreeNode<T>::LinkedbinaryTreeNode(LinkedbinaryTreeNode&& tree) noexcept{
    leftChild = tree.leftChild;
    tree.leftChild = nullptr;
    rightChild = tree.rightChild;
    tree.rightChild = nullptr;
    element = tree.element;
}
template<class T>
LinkedbinaryTreeNode<T>* LinkedbinaryTreeNode<T>::getLeftChild(){
    return leftChild;
}
template <class T>
const LinkedbinaryTreeNode<T>* LinkedbinaryTreeNode<T>::getLeftChild() const{
    return leftChild;
}
template <class T>
LinkedbinaryTreeNode<T>* LinkedbinaryTreeNode<T>::getRightChild(){
    return rightChild;
}
template <class T>
const LinkedbinaryTreeNode<T>* LinkedbinaryTreeNode<T>::getRightChild() const{
    return rightChild;
}
template <class T>
void LinkedbinaryTreeNode<T>::changeLeftChild(LinkedbinaryTreeNode<T>* leftChild_){
    leftChild = leftChild_;
}
template <class T>
void LinkedbinaryTreeNode<T>::changeRightChild(LinkedbinaryTreeNode<T>* rightChild_){
    rightChild = rightChild_;
}
template <class T>
T& LinkedbinaryTreeNode<T>::get(){
    return element;
}
template <class T>
const T& LinkedbinaryTreeNode<T>::get() const{
    return element;
}
template <class T>
unsigned LinkedbinaryTreeNode<T>::size() const{
    unsigned size_=1;
    if(leftChild!=nullptr) size_ += leftChild->size();
    if(rightChild!=nullptr) size_ += rightChild->size();
    return size_;
}
template <class T>
unsigned LinkedbinaryTreeNode<T>::depth() const{
    unsigned leftChild_depth = 0;
    unsigned rightChild_depth = 0;
    if(leftChild!=nullptr) leftChild_depth = leftChild->depth();
    if(rightChild!=nullptr) rightChild_depth = rightChild->depth();
    if(leftChild_depth>=rightChild_depth) return 1+leftChild_depth;
    else return 1+rightChild_depth;
}
//遍历树
template <class T>
void LinkedbinaryTreeNode<T>::preOrder(const std::function<void(T&)>& visit){
    visit(element);
    if(leftChild!=nullptr) leftChild->preOrder(visit);
    if(rightChild!=nullptr) rightChild->preOrder(visit);
}
template <class T>
void LinkedbinaryTreeNode<T>::inOrder(const std::function<void(T&)>& visit){
    if(leftChild!=nullptr)leftChild->inOrder(visit);
    visit(element);
    if(rightChild!=nullptr)rightChild->inOrder(visit);
}
template <class T>
void LinkedbinaryTreeNode<T>::postOrder(const std::function<void(T&)>& visit){
    if(leftChild!=nullptr)leftChild->postOrder(visit);
    if(rightChild!=nullptr)rightChild->postOrder(visit);
    visit(element);
}
template <class T>
void LinkedbinaryTreeNode<T>::levelOrder(const std::function<void(T&)>& visit){
    ArrayQueue<LinkedbinaryTreeNode<T>*> queue_;
    queue_.push(this);
    while(!queue_.empty()){
        LinkedbinaryTreeNode<T>* node = queue_.front();
        queue_.pop();
        visit(node->get());
        if(node->getLeftChild()!=nullptr) queue_.push(node->getLeftChild());
        if(node->getRightChild()!=nullptr) queue_.push(node->getRightChild());
    }
}

template <class T>
void LinkedbinaryTreeNode<T>::preOrder(const std::function<void(const T&)>& visit)const{
    visit(element);
    if(leftChild!=nullptr) leftChild->preOrder(visit);
    if(rightChild!=nullptr) rightChild->preOrder(visit);
}
template <class T>
void LinkedbinaryTreeNode<T>::inOrder(const std::function<void(const T&)>& visit)const{
    if(leftChild!=nullptr)leftChild->inOrder(visit);
    visit(element);
    if(rightChild!=nullptr)rightChild->inOrder(visit);
}
template <class T>
void LinkedbinaryTreeNode<T>::postOrder(const std::function<void(const T&)>& visit)const{
    if(leftChild!=nullptr)leftChild->postOrder(visit);
    if(rightChild!=nullptr)rightChild->postOrder(visit);
    visit(element);
}
template <class T>
void LinkedbinaryTreeNode<T>::levelOrder(const std::function<void(const T&)>& visit) const{
    ArrayQueue<const LinkedbinaryTreeNode<T>*> queue_;
    queue_.push(this);
    while(!queue_.empty()){
        const LinkedbinaryTreeNode<T>* node = queue_.front();
        queue_.pop();
        visit(node->get());
        if(node->getLeftChild()!=nullptr) queue_.push(node->getLeftChild());
        if(node->getRightChild()!=nullptr) queue_.push(node->getRightChild());
    }
}
//析构函数与清除
template<class T>
LinkedbinaryTreeNode<T>::~LinkedbinaryTreeNode(){
    if(leftChild!=nullptr) delete leftChild;
    if(rightChild!=nullptr) delete rightChild;
}
template <class T>
void LinkedbinaryTreeNode<T>::clearLeftChild(){
    if(leftChild!=nullptr) delete leftChild;
    leftChild = nullptr;
}
template <class T>
void LinkedbinaryTreeNode<T>::clearRightChild(){
    if(rightChild!=nullptr) delete rightChild;
    rightChild = nullptr;
}
//深复制结点
template <class T>
void LinkedbinaryTreeNode<T>::copy(const LinkedbinaryTreeNode<T>* node){
    if(node==nullptr) return;
    element = node->get();
    clearLeftChild();
    clearRightChild();
    if(node->getLeftChild()){
        leftChild = new LinkedbinaryTreeNode<T>;
        leftChild->copy(node->getLeftChild());
    }
    if(node->getRightChild()){
        rightChild = new LinkedbinaryTreeNode<T>;
        rightChild->copy(node->getRightChild());
    }
}
template <class T>
LinkedbinaryTreeNode<T>& LinkedbinaryTreeNode<T>::operator = (const LinkedbinaryTreeNode& node){
    element = node->get();
    clearLeftChild();
    clearRightChild();
    if(node->getLeftChild()){
        leftChild = new LinkedbinaryTreeNode<T>;
        leftChild->copy(node.getLeftChild());
    }
    if(node->getRightChild()){
        rightChild = new LinkedbinaryTreeNode<T>;
        rightChild->copy(node.getRightChild());
    }
    return *this;
}
template <class T>
LinkedbinaryTreeNode<T>& LinkedbinaryTreeNode<T>::operator = (LinkedbinaryTreeNode&& node) noexcept{
    clearLeftChild();
    clearRightChild();
    element = node.element;
    leftChild = node.leftChild;
    node.leftChild = nullptr;
    rightChild = node.rightChild;
    node.rightChild = nullptr;
    return *this;
}
}//命名空间结束
#endif // LINKEDBINARYTREENODE_H
