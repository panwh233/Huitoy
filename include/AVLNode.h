#include "ArrayQueue.h"
#include <functional>
#ifndef AVLNODE_H
#define AVLNODE_H

namespace Huitoy{
template <class T>
class AVLNode
{
    public:
        AVLNode(const T& element_=T(),AVLNode* leftChild=nullptr,AVLNode* rightChild=nullptr);
        AVLNode(const AVLNode& node);
        AVLNode(AVLNode&& node) noexcept;
        //清除结点以及析构函数
        ~AVLNode();
        void clearLeftChild();
        void clearRightChild();
        //深复制结点
        AVLNode& copy(const AVLNode* node);
        AVLNode& operator=(const AVLNode& tree);
        AVLNode& operator=(AVLNode&& tree) noexcept;
        //获取左右子树的指针
        AVLNode* getLeftChild();
        const AVLNode* getLeftChild() const;
        AVLNode* getRightChild();
        const AVLNode* getRightChild() const;
        //改变左右子树
        void changeLeftChild(AVLNode* leftChild_);
        void changeRightChild(AVLNode* rightChild_);
        //获取该结点的元素
        T& get();
        const T& get() const;
        //获取该结点的参数
        unsigned size() const;
        unsigned depth() const;
        void update_leftChild_depth();
        void update_rightChild_depth();
        int balance_factor() const;
        //遍历
        void preOrder(const std::function<void(T&)>& visit);
        void inOrder(const std::function<void(T&)>& visit);
        void postOrder(const std::function<void(T&)>& visit);
        void levelOrder(const std::function<void(T&)>& visit);
        void preOrder(const std::function<void(const T&)>& visit) const;
        void inOrder(const std::function<void(const T&)>& visit) const;
        void postOrder(const std::function<void(const T&)>& visit) const;
        void levelOrder(const std::function<void(const T&)>& visit) const;
    protected:
        AVLNode* leftChild;
        AVLNode* rightChild;
        mutable unsigned leftChild_depth;
        mutable unsigned rightChild_depth;
        mutable bool leftChild_updated;
        mutable bool rightChild_updated;
        T element;
};

template <class T>
AVLNode<T>::AVLNode(const T& element_,AVLNode* leftChild_,AVLNode* rightChild_){
    element = element_;
    leftChild = leftChild_;
    rightChild = rightChild_;
}
template <class T>
AVLNode<T>::AVLNode(const AVLNode& node){
    leftChild_depth = node.leftChild_depth;
    rightChild_depth = node.rightChild_depth;
    leftChild_updated = node.leftChild_updated;
    rightChild_updated = node.rightChild_updated;
    element = node.element;
    if(node.leftChild!=nullptr){
        leftChild->copy(node.leftChild);
    }
    if(node.rightChild!=nullptr){
        rightChild->copy(node.rightChild);
    }
}
template <class T>
AVLNode<T>::AVLNode(AVLNode&& node) noexcept{
    element = node.element;
    leftChild = node.leftChild;
    node.leftChild = nullptr;
    rightChild = node.rightChild;
    node.rightChild = nullptr;
    leftChild_depth = node.leftChild_depth;
    rightChild_depth = node.rightChild_depth;
    leftChild_updated = node.leftChild_updated;
    rightChild_updated = node.rightChild_updated;
}

//清理结点
template <class T>
AVLNode<T>::~AVLNode(){
    clearLeftChild();
    clearRightChild();
}
template <class T>
void AVLNode<T>::clearLeftChild(){
    if(leftChild!=nullptr) delete leftChild;
    leftChild_depth=0;
    leftChild_updated=true;
}
template <class T>
void AVLNode<T>::clearRightChild(){
    if(rightChild!=nullptr) delete rightChild;
    rightChild_depth=0;
    rightChild_updated=true;
}
//复制结点
template <class T>
AVLNode<T>& AVLNode<T>::copy(const AVLNode* node){
    if(node==nullptr){
        return *this;
    }
    else{
        clearLeftChild();
        clearRightChild();
        element = node->element;
        leftChild_depth = node->leftChild_depth;
        rightChild_depth = node->rightChild_depth;
        leftChild_updated = node->leftChild_updated;
        rightChild_updated = node->rightChild_updated;
        if(node->leftChild!=nullptr){
            leftChild = new AVLNode<T>;
            leftChild->copy(node->leftChild);
        }
        if(node->rightChild!=nullptr){
            rightChild = new AVLNode<T>;
            rightChild->copy(node->rightChild);
        }
    }
    return *this;
}
template <class T>
AVLNode<T>& AVLNode<T>::operator = (const AVLNode& node){
    clearLeftChild();
    clearRightChild();
    element = node.element;
    leftChild_depth = node.leftChild_depth;
    rightChild_depth = node.rightChild_depth;
    leftChild_updated = node.leftChild_updated;
    rightChild_updated = node.rightChild_updated;
    if(node.leftChild != nullptr){
        leftChild = new AVLNode<T>;
        leftChild->copy(node.leftChild);
    }else{
        leftChild_depth = 0;
        leftChild_updated = true;
    }
    if(node.rightChild!=nullptr){
        rightChild = new AVLNode<T>;
        rightChild->copy(node.rightChild);
    }else{
        rightChild_depth = 0;
        rightChild_updated = true;
    }
    return *this;
}
template <class T>
AVLNode<T>& AVLNode<T>::operator = (AVLNode&& node) noexcept{
    clearLeftChild();
    clearRightChild();
    element = node.element;
    leftChild_depth = node.leftChild_depth;
    node.leftChild_depth = 0;
    rightChild_depth = node.rightChild_depth;
    node.rightChild_depth = 0;
    leftChild_updated = node.leftChild_updated;
    node.leftChild_updated = true;
    rightChild_updated = node.rightChild_updated;
    node.leftChild_updated = true;
    leftChild = node.leftChild;
    node.leftChild = nullptr;
    rightChild = node.rightChild;
    node.rightChild = nullptr;
}
//获取左右孩子的指针
template <class T>
AVLNode<T>* AVLNode<T>::getLeftChild(){
    return leftChild;
}
template <class T>
const AVLNode<T>* AVLNode<T>::getLeftChild() const{
    return leftChild;
}
template <class T>
AVLNode<T>* AVLNode<T>::getRightChild(){
    return rightChild;
}
template <class T>
const AVLNode<T>* AVLNode<T>::getRightChild() const{
    return rightChild;
}
//更改左右孩子结点
template <class T>
void AVLNode<T>::changeLeftChild(AVLNode* leftChild_){
    leftChild = leftChild_;
    leftChild_updated = false;
}
template <class T>
void AVLNode<T>::changeRightChild(AVLNode* rightChild_){
    rightChild = rightChild_;
    rightChild_updated = false;
}
//获取该结点的元素
template <class T>
T& AVLNode<T>::get(){
    return element;
}
template <class T>
const T& AVLNode<T>::get() const{
    return element;
}
//结点参数
template <class T>
unsigned AVLNode<T>::size() const{
    unsigned leftChild_size = 0;
    unsigned rightChild_size = 0;
    if(leftChild!=nullptr) leftChild_size = leftChild->size();
    if(rightChild!=nullptr) rightChild_size = rightChild->size();
    return 1+leftChild_size+rightChild_size;
}
template <class T>
unsigned AVLNode<T>::depth() const{
    if(leftChild_updated==false){
        if(leftChild!=nullptr){
            leftChild_depth = leftChild->depth();
        }else{
            leftChild_depth = 0;
        }
        leftChild_updated = true;
    }
    if(rightChild_updated==false){
        if(rightChild!=nullptr){
            rightChild_depth = rightChild->depth();
        }else{
            rightChild_depth = 0;
        }
        rightChild_updated = true;
    }
    unsigned depth_ = leftChild_depth;
    if(rightChild_depth>leftChild_depth) depth_ = rightChild_depth;
    return 1+depth_;
}
template <class T>
void AVLNode<T>::update_leftChild_depth(){
    leftChild_updated = false;
}
template <class T>
void AVLNode<T>::update_rightChild_depth(){
    rightChild_updated = false;
}
template <class T>
int AVLNode<T>::balance_factor() const{
    if(leftChild_updated==false){
        if(leftChild!=nullptr){
            leftChild_depth = leftChild->depth();
        }else{
            leftChild_depth = 0;
        }
        leftChild_updated = true;
    }
    if(rightChild_updated==false){
        if(rightChild!=nullptr){
            rightChild_depth = rightChild->depth();
        }else{
            rightChild_depth = 0;
        }
        rightChild_updated = true;
    }
    int bf = static_cast<int>(leftChild_depth) - static_cast<int>(rightChild_depth);
    return bf;
}

//遍历树
template <class T>
void AVLNode<T>::preOrder(const std::function<void(T&)>& visit){
    visit(element);
    if(leftChild!=nullptr) leftChild->preOrder(visit);
    if(rightChild!=nullptr) rightChild->preOrder(visit);
}
template <class T>
void AVLNode<T>::inOrder(const std::function<void(T&)>& visit){
    if(leftChild!=nullptr)leftChild->inOrder(visit);
    visit(element);
    if(rightChild!=nullptr)rightChild->inOrder(visit);
}
template <class T>
void AVLNode<T>::postOrder(const std::function<void(T&)>& visit){
    if(leftChild!=nullptr)leftChild->postOrder(visit);
    if(rightChild!=nullptr)rightChild->postOrder(visit);
    visit(element);
}
template <class T>
void AVLNode<T>::levelOrder(const std::function<void(T&)>& visit){
    ArrayQueue<AVLNode<T>*> queue_;
    queue_.push(this);
    while(!queue_.empty()){
        AVLNode<T>* node = queue_.front();
        queue_.pop();
        visit(node->get());
        if(node->getLeftChild()!=nullptr) queue_.push(node->getLeftChild());
        if(node->getRightChild()!=nullptr) queue_.push(node->getRightChild());
    }
}

template <class T>
void AVLNode<T>::preOrder(const std::function<void(const T&)>& visit)const{
    visit(element);
    if(leftChild!=nullptr) leftChild->preOrder(visit);
    if(rightChild!=nullptr) rightChild->preOrder(visit);
}
template <class T>
void AVLNode<T>::inOrder(const std::function<void(const T&)>& visit)const{
    if(leftChild!=nullptr)leftChild->inOrder(visit);
    visit(element);
    if(rightChild!=nullptr)rightChild->inOrder(visit);
}
template <class T>
void AVLNode<T>::postOrder(const std::function<void(const T&)>& visit)const{
    if(leftChild!=nullptr)leftChild->postOrder(visit);
    if(rightChild!=nullptr)rightChild->postOrder(visit);
    visit(element);
}
template <class T>
void AVLNode<T>::levelOrder(const std::function<void(const T&)>& visit) const{
    ArrayQueue<const AVLNode<T>*> queue_;
    queue_.push(this);
    while(!queue_.empty()){
        const AVLNode<T>* node = queue_.front();
        queue_.pop();
        visit(node->get());
        if(node->getLeftChild()!=nullptr) queue_.push(node->getLeftChild());
        if(node->getRightChild()!=nullptr) queue_.push(node->getRightChild());
    }
}

}//namespace end
#endif // AVLNODE_H
