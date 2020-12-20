#include "ArrayQueue.h"
#include "binaryTree.h"
#include "Pair.h"
#include "Dictionary.h"
#include "LinkedbinaryTreeNode.h"
#include "illegalParameterValue.h"
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
namespace Huitoy{


template <class Key,class Value>
class binarySearchTree:public binaryTree<Value>,public Dictionary<Key,Value>
{
    public:
        binarySearchTree();
        binarySearchTree(const binarySearchTree& tree);
        binarySearchTree(binarySearchTree&& tree) noexcept;
        binarySearchTree(const Pair<Key,Value>* pair_array,unsigned n,bool replace = true);
        binarySearchTree(const Key* key_array,const Value* value_array,unsigned n,bool replace = true);

        binarySearchTree& operator = (const binarySearchTree& tree);
        binarySearchTree& operator = (binarySearchTree&& tree) noexcept;
        binarySearchTree& copy(const Pair<Key,Value>* pair_array,unsigned n,bool replace = true);
        binarySearchTree& copy(const Key* key_array,const Value* value_array,unsigned n,bool replace = true);

        bool empty() const;
        unsigned size() const;
        unsigned depth() const;

        bool insert(const Key& key,const Value& value,bool replace=true);
        bool erase(const Key& key);
        Key search(const Value& value) const;
        Value& operator[](const Key& key);
        const Value& operator[](const Key& key) const;

        void preOrder(const std::function<void(Value&)>& visit);
        void inOrder(const std::function<void(Value&)>& visit);
        void postOrder(const std::function<void(Value&)>& visit);
        void levelOrder(const std::function<void(Value&)>& visit);
        void preOrder(const std::function<void(const Value&)>& visit) const;
        void inOrder(const std::function<void(const Value&)>& visit) const;
        void postOrder(const std::function<void(const Value&)>& visit)const;
        void levelOrder(const std::function<void(const Value&)>& visit)const;

        ~binarySearchTree();
        void clear();

    protected:
        LinkedbinaryTreeNode<Pair<Key,Value>>* root;
    private:
};

//Constructor
template <class Key,class Value>
binarySearchTree<Key,Value>::binarySearchTree(){
    root=nullptr;
}
template <class Key,class Value>
binarySearchTree<Key,Value>::binarySearchTree(const binarySearchTree& tree){
    if(tree.root==nullptr){
        root = nullptr;
        return;
    }
    root = new LinkedbinaryTreeNode<Pair<Key,Value>>;
    root->copy(tree.root);
}
template <class Key,class Value>
binarySearchTree<Key,Value>::binarySearchTree(binarySearchTree&& tree) noexcept{
    root = tree.root;
    tree.root = nullptr;
}
template <class Key,class Value>
binarySearchTree<Key,Value>::binarySearchTree(const Pair<Key,Value>* pair_array,unsigned n,bool replace){
    for(unsigned i = 0;i<n;i++){
        insert(pair_array[i].key(),pair_array[i].value(),replace);
    }
}
template <class Key,class Value>
binarySearchTree<Key,Value>::binarySearchTree(const Key* key_array,const Value* value_array,unsigned n,bool replace){
    for(unsigned i=0;i<n;i++){
        insert(key_array[0],value_array[0],replace);
    }
}
//Destructor
template <class Key,class Value>
binarySearchTree<Key,Value>::~binarySearchTree(){
    if(root!=nullptr){
        delete root;
    }
}
template <class Key,class Value>
void binarySearchTree<Key,Value>::clear(){
    if(root!=nullptr){
        delete root;
        root = nullptr;
    }
}
//operator = and copy
template <class Key,class Value>
binarySearchTree<Key,Value>& binarySearchTree<Key,Value>::operator = (const binarySearchTree& tree){
    clear();
    root = new LinkedbinaryTreeNode<Pair<Key,Value>>;
    root->copy(&tree);
    return *this;
}
template <class Key,class Value>
binarySearchTree<Key,Value>& binarySearchTree<Key,Value>::operator = (binarySearchTree&& tree) noexcept{
    clear();
    root = tree.root;
    tree.root = nullptr;
    return *this;
}
template <class Key,class Value>
binarySearchTree<Key,Value>& binarySearchTree<Key,Value>::copy(const Pair<Key,Value>* pair_array,unsigned n,bool replace){
    clear();
    for(unsigned i = 0;i<n;i++){
        insert(pair_array[i].key(),pair_array[i].value(),replace);
    }
}
template <class Key,class Value>
binarySearchTree<Key,Value>& binarySearchTree<Key,Value>::copy(const Key* key_array,const Value* value_array,unsigned n,bool replace){
    clear();
    for(unsigned i=0;i<n;i++){
        insert(key_array[0],value_array[0],replace);
    }
}
template <class Key,class Value>
bool binarySearchTree<Key,Value>::empty() const{
    return root==nullptr;
}
template <class Key,class Value>
unsigned binarySearchTree<Key,Value>::size() const{
    if(root==nullptr) return 0;
    else{
        return root->size();
    }
}
template <class Key,class Value>
unsigned binarySearchTree<Key,Value>::depth() const{
    if(root==nullptr) return 0;
    else{
        return root->depth();
    }
}
template <class Key,class Value>
bool binarySearchTree<Key,Value>::insert(const Key& key,const Value& value,bool replace){
    if(root==nullptr){
        root = new LinkedbinaryTreeNode<Pair<Key,Value>>(Pair<Key,Value>(key,value));
    }else{
        LinkedbinaryTreeNode<Pair<Key,Value>>* father_node = nullptr;
        LinkedbinaryTreeNode<Pair<Key,Value>>* node = root;
        unsigned sign_ = 0;
        while(node != nullptr){
            if(key>(node->get()).key()){
                father_node = node;
                node = node->getRightChild();
                sign_ = 1;
            }else if(key<(node->get()).key()){
                father_node = node;
                node = node->getLeftChild();
                sign_ = 0;
            }else{
                if(replace){
                    (node->get()).value() = value;
                    return true;
                }
                else return false;
            }
        }
        LinkedbinaryTreeNode<Pair<Key,Value>>* newnode = new LinkedbinaryTreeNode<Pair<Key,Value>>(Pair<Key,Value>(key,value));
        if(sign_==0){
            father_node->changeLeftChild(newnode);
        }else{
            father_node->changeRightChild(newnode);
        }
    }
    return true;
}
template <class Key,class Value>
bool binarySearchTree<Key,Value>::erase(const Key& key){
    //如果根结点为空，则返回false
    if(root==nullptr) return false;
    //否则，先搜索键为key的结点，如果root的key就是key，那么就删除根结点
    if((*root).get().key()==key){
        LinkedbinaryTreeNode<Pair<Key,Value>>* left = root->getLeftChild();
        LinkedbinaryTreeNode<Pair<Key,Value>>* right = root->getRightChild();
        if(left==nullptr&&right==nullptr){
            delete root;
            root=nullptr;
        }else if(left==nullptr&&right!=nullptr){
            root->changeRightChild(nullptr);
            delete root;
            root = right;
        }else if(left!=nullptr&&right==nullptr){
            root->changeLeftChild(nullptr);
            delete root;
            root = left;
        }else{
            root->changeLeftChild(nullptr);
            root->changeRightChild(nullptr);
            delete root;
            if(left->getRightChild()==nullptr){
                left->changeRightChild(right);
                root = left;
            }else{
                LinkedbinaryTreeNode<Pair<Key,Value>>* left_right_father = left;
                LinkedbinaryTreeNode<Pair<Key,Value>>* left_right = left->getRightChild();
                while(left_right->getRightChild()!=nullptr){
                    left_right_father = left_right;
                    left_right = left_right->getRightChild();
                }
                left_right_father->changeRightChild(left_right->getLeftChild());
                left_right->changeLeftChild(left);
                left_right->changeRightChild(right);
                root = left_right;
            }
        }
        return true;
    }
    LinkedbinaryTreeNode<Pair<Key,Value>>* father = nullptr;
    LinkedbinaryTreeNode<Pair<Key,Value>>* deletenode = root;
    Key key_;
    while(deletenode!=nullptr){
        key_ = (deletenode->get()).key();
        if(key_==key) {
            break;
        }
        else if(key_ < key){
            father = deletenode;
            deletenode = deletenode->getRightChild();
        }else{
            father = deletenode;
            deletenode = deletenode->getLeftChild();
        }
    }
    if(deletenode == nullptr) {
        return false;
    }
    //Get the left child and the right child
    LinkedbinaryTreeNode<Pair<Key,Value>>* left = deletenode->getLeftChild();
    LinkedbinaryTreeNode<Pair<Key,Value>>* right = deletenode->getRightChild();
    //Delete the node
    deletenode->changeLeftChild(nullptr);
    deletenode->changeRightChild(nullptr);
    delete deletenode;
    //Case 1:Children of deleted node are both null!
    if(left==nullptr&&right==nullptr){
        if(key<(father->get()).key()){
            father->changeLeftChild(nullptr);
        }else{
            father->changeRightChild(nullptr);
        }
    }//Case 2:Left Child of deleted node is not null and right child is null
    else if(left!=nullptr&&right==nullptr){
        if(key<(father->get()).key()){
            father->changeLeftChild(left);
        }else{
            father->changeRightChild(left);
        }
    }//Case 3:Right Child of deleted node is not null and right child is null
    else if(left==nullptr&&right!=nullptr){
        if(key<(father->get()).key()){
            father->changeLeftChild(right);
        }else{
            father->changeRightChild(right);
        }
    }//Case 4:Both children of deleted node are not null!The right child of left child is null
    else if(left->getRightChild()==nullptr){
        left->changeRightChild(right);
        if(key<(father->get()).key()){
            father->changeLeftChild(left);
        }else{
            father->changeRightChild(left);
        }
    }//Case 5:Both children of deleted node are not null!The right child of left child is not null
    else{
        LinkedbinaryTreeNode<Pair<Key,Value>>* left_right_father = left;
        LinkedbinaryTreeNode<Pair<Key,Value>>* left_right = left->getRightChild();
        while(left_right->getRightChild()!=nullptr){
            left_right_father = left_right;
            left_right = left_right->getRightChild();
        }
        left_right_father->changeRightChild(left_right->getLeftChild());
        left_right->changeLeftChild(left);
        left_right->changeRightChild(right);
        if(key<(father->get()).key()){
            father->changeLeftChild(left_right);
        }else{
            father->changeRightChild(left_right);
        }
    }
    return true;
}
template <class Key,class Value>
Key binarySearchTree<Key,Value>::search(const Value& value) const{
    ArrayQueue<const LinkedbinaryTreeNode<Pair<Key,Value>>*> queue_;
    if(root==nullptr){
        throw illegalParameterValue("Key not found!");
    }else{
        queue_.push(root);
        while(!queue_.empty()){
            if(((queue_.front())->get()).value()==value) return ((queue_.front())->get()).key();
            if((queue_.front())->getLeftChild()!=nullptr) queue_.push((queue_.front())->getLeftChild());
            if((queue_.front())->getRightChild()!=nullptr) queue_.push((queue_.front())->getRightChild());
            queue_.pop();
        }
        throw illegalParameterValue("Key not found!");
    }
    return Key();
}
template <class Key,class Value>
Value& binarySearchTree<Key,Value>::operator[](const Key& key){
    if(root==nullptr){
        throw illegalParameterValue("Key not found!");
    }else{
        LinkedbinaryTreeNode<Pair<Key,Value>>* node = root;
        while(node != nullptr){
            if(key == (node->get()).key()){
                return (node->get()).value();
            }else if(key < (node->get()).key()){
                node = node->getLeftChild();
            }else{
                node = node->getRightChild();
            }
        }
        throw illegalParameterValue("Key not found!");
    }
}
template <class Key,class Value>
const Value& binarySearchTree<Key,Value>::operator[](const Key& key) const{
    if(root==nullptr){
        throw illegalParameterValue("Key not found!");
    }else{
        const LinkedbinaryTreeNode<Pair<Key,Value>>* node = root;
        while(node != nullptr){
            if(key == (node->get()).key()){
                return (node->get()).value();
            }else if(key < (node->get()).key()){
                node = node->getLeftChild();
            }else{
                node = node->getRightChild();
            }
        }
        throw illegalParameterValue("Key not found!");
    }
}
template <class Key,class Value>
void binarySearchTree<Key,Value>::preOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->preOrder(new_visit);
}
template <class Key,class Value>
void binarySearchTree<Key,Value>::inOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->inOrder(new_visit);
}
template <class Key,class Value>
void binarySearchTree<Key,Value>::postOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->postOrder(new_visit);
}
template <class Key,class Value>
void binarySearchTree<Key,Value>::levelOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->levelOrder(new_visit);
}
template <class Key,class Value>
void binarySearchTree<Key,Value>::preOrder(const std::function<void(const Value&)>& visit) const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->preOrder(new_visit);
}
template <class Key,class Value>
void binarySearchTree<Key,Value>::inOrder(const std::function<void(const Value&)>& visit) const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->inOrder(new_visit);
}
template <class Key,class Value>
void binarySearchTree<Key,Value>::postOrder(const std::function<void(const Value&)>& visit)const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->postOrder(new_visit);
}
template <class Key,class Value>
void binarySearchTree<Key,Value>::levelOrder(const std::function<void(const Value&)>& visit)const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->postOrder(new_visit);
}
}//namespace end
#endif // BINARYSEARCHTREE_H
