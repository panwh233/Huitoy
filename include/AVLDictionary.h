#include "ArrayQueue.h"
#include "ArrayStack.h"
#include "Pair.h"
#include "Dictionary.h"
#include "binaryTree.h"
#include "AVLNode.h"
#ifndef AVLDICTIONARY_H
#define AVLDICTIONARY_H
namespace Huitoy{
template <class Key,class Value>
class AVLDictionary:public binaryTree<Value>,public Dictionary<Key,Value>
{
    public:
        AVLDictionary();
        AVLDictionary(const AVLDictionary& tree);
        AVLDictionary(AVLDictionary&& tree) noexcept;
        AVLDictionary(const Pair<Key,Value>* pair_array,unsigned n,bool replace = true);
        AVLDictionary(const Key* key_array,const Value* value_array,unsigned n,bool replace = true);

        AVLDictionary& operator = (const AVLDictionary& tree);
        AVLDictionary& operator = (AVLDictionary&& tree) noexcept;
        AVLDictionary& copy(const Pair<Key,Value>* pair_array,unsigned n,bool replace = true);
        AVLDictionary& copy(const Key* key_array,const Value* value_array,unsigned n,bool replace = true);

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

        ~AVLDictionary();
        void clear();

    protected:
        AVLNode<Pair<Key,Value>>* root;
};

//Constructor
template <class Key,class Value>
AVLDictionary<Key,Value>::AVLDictionary(){
    root=nullptr;
}
template <class Key,class Value>
AVLDictionary<Key,Value>::AVLDictionary(const AVLDictionary& tree){
    if(tree.root==nullptr){
        root = nullptr;
        return;
    }
    root = new AVLNode<Pair<Key,Value>>;
    root->copy(tree.root);
}
template <class Key,class Value>
AVLDictionary<Key,Value>::AVLDictionary(AVLDictionary&& tree) noexcept{
    root = tree.root;
    tree.root = nullptr;
}
template <class Key,class Value>
AVLDictionary<Key,Value>::AVLDictionary(const Pair<Key,Value>* pair_array,unsigned n,bool replace){
    for(unsigned i = 0;i<n;i++){
        insert(pair_array[i].key(),pair_array[i].value(),replace);
    }
}
template <class Key,class Value>
AVLDictionary<Key,Value>::AVLDictionary(const Key* key_array,const Value* value_array,unsigned n,bool replace){
    for(unsigned i=0;i<n;i++){
        insert(key_array[0],value_array[0],replace);
    }
}
//Destructor
template <class Key,class Value>
AVLDictionary<Key,Value>::~AVLDictionary(){
    if(root!=nullptr){
        delete root;
    }
}
template <class Key,class Value>
void AVLDictionary<Key,Value>::clear(){
    if(root!=nullptr){
        delete root;
        root = nullptr;
    }
}
//operator = and copy
template <class Key,class Value>
AVLDictionary<Key,Value>& AVLDictionary<Key,Value>::operator = (const AVLDictionary& tree){
    clear();
    root = new AVLNode<Pair<Key,Value>>;
    root->copy(&tree);
    return *this;
}
template <class Key,class Value>
AVLDictionary<Key,Value>& AVLDictionary<Key,Value>::operator = (AVLDictionary&& tree) noexcept{
    clear();
    root = tree.root;
    tree.root = nullptr;
    return *this;
}
template <class Key,class Value>
AVLDictionary<Key,Value>& AVLDictionary<Key,Value>::copy(const Pair<Key,Value>* pair_array,unsigned n,bool replace){
    clear();
    for(unsigned i = 0;i<n;i++){
        insert(pair_array[i].key(),pair_array[i].value(),replace);
    }
}
template <class Key,class Value>
AVLDictionary<Key,Value>& AVLDictionary<Key,Value>::copy(const Key* key_array,const Value* value_array,unsigned n,bool replace){
    clear();
    for(unsigned i=0;i<n;i++){
        insert(key_array[0],value_array[0],replace);
    }
}
template <class Key,class Value>
bool AVLDictionary<Key,Value>::empty() const{
    return root==nullptr;
}
template <class Key,class Value>
unsigned AVLDictionary<Key,Value>::size() const{
    if(root==nullptr) return 0;
    else{
        return root->size();
    }
}
template <class Key,class Value>
unsigned AVLDictionary<Key,Value>::depth() const{
    if(root==nullptr) return 0;
    else{
        return root->depth();
    }
}


template <class Key,class Value>
Key AVLDictionary<Key,Value>::search(const Value& value) const{
    ArrayQueue<const AVLNode<Pair<Key,Value>>*> queue_;
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
Value& AVLDictionary<Key,Value>::operator[](const Key& key){
    if(root==nullptr){
        throw illegalParameterValue("Key not found!");
    }else{
        AVLNode<Pair<Key,Value>>* node = root;
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
const Value& AVLDictionary<Key,Value>::operator[](const Key& key) const{
    if(root==nullptr){
        throw illegalParameterValue("Key not found!");
    }else{
        const AVLNode<Pair<Key,Value>>* node = root;
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
void AVLDictionary<Key,Value>::preOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->preOrder(new_visit);
}
template <class Key,class Value>
void AVLDictionary<Key,Value>::inOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->inOrder(new_visit);
}
template <class Key,class Value>
void AVLDictionary<Key,Value>::postOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->postOrder(new_visit);
}
template <class Key,class Value>
void AVLDictionary<Key,Value>::levelOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->levelOrder(new_visit);
}
template <class Key,class Value>
void AVLDictionary<Key,Value>::preOrder(const std::function<void(const Value&)>& visit) const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->preOrder(new_visit);
}
template <class Key,class Value>
void AVLDictionary<Key,Value>::inOrder(const std::function<void(const Value&)>& visit) const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->inOrder(new_visit);
}
template <class Key,class Value>
void AVLDictionary<Key,Value>::postOrder(const std::function<void(const Value&)>& visit)const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->postOrder(new_visit);
}
template <class Key,class Value>
void AVLDictionary<Key,Value>::levelOrder(const std::function<void(const Value&)>& visit)const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->postOrder(new_visit);
}

template <class Key,class Value>
bool AVLDictionary<Key,Value>::insert(const Key& key,const Value& value,bool replace){
    if(root==nullptr){
        root = new AVLNode<Pair<Key,Value>>;
        root->get() = Pair<Key,Value>(key,value);
    }else{
        AVLNode<Pair<Key,Value>>* father = nullptr;
        AVLNode<Pair<Key,Value>>* node = root;
        ArrayStack<AVLNode<Pair<Key,Value>>*>  stack1;
        while(node!=nullptr){
            stack1.push(node);
            Key key_ = (node->get()).key();
            father = node;
            if(key<key_){
                node->update_leftChild_depth();
                node = node->getLeftChild();
            }else if(key>key_){
                node->update_rightChild_depth();
                node = node->getRightChild();
            }else{
                root->depth();
                if(replace){
                    (root->get()).value() = value;
                    return true;
                }else{
                    return false;
                }
            }
        }
        AVLNode<Pair<Key,Value>>* newnode = new AVLNode<Pair<Key,Value>>(Pair<Key,Value>(key,value));
        if(key<(father->get()).key()){
            father->changeLeftChild(newnode);
        }else{
            father->changeRightChild(newnode);
        }
        stack1.push(newnode);
        root->depth();//更新沿路的所有子树的深度
        AVLNode<Pair<Key,Value>>* node_alpha = nullptr;
        while(!stack1.empty()){
            node_alpha = stack1.top();
            int bf = node_alpha->balance_factor();
            if(bf>1){
                stack1.pop();
                AVLNode<Pair<Key,Value>>* node_father_ = nullptr;//失衡点的父结点
                if(!stack1.empty()){
                    node_father_ = stack1.top();
                }
                AVLNode<Pair<Key,Value>>* node_x = node_alpha->getLeftChild();//失衡点的左子结点
                int bf2 = node_x->balance_factor();
                if(bf2>0){
                    //这种情况是LL型
                    AVLNode<Pair<Key,Value>>* node_right = node_x->getRightChild();
                    node_alpha->changeLeftChild(node_right);
                    node_x->changeRightChild(node_alpha);
                    if(node_father_==nullptr){
                        root = node_x;
                        break;
                    }
                    else if((node_x->get()).key()<(node_father_->get()).key()){
                        node_father_->changeLeftChild(node_x);
                    }else{
                        node_father_->changeRightChild(node_x);
                    }
                    node_father_->depth();
                    break;
                }else{
                    //这种情况是LR型
                    AVLNode<Pair<Key,Value>>* node_x0 = node_x->getRightChild();
                    AVLNode<Pair<Key,Value>>* node_y = node_x0->getLeftChild();
                    AVLNode<Pair<Key,Value>>* node_b = node_x0->getRightChild();
                    node_x->changeRightChild(node_y);
                    node_alpha->changeLeftChild(node_b);
                    node_x0->changeLeftChild(node_x);
                    node_x0->changeRightChild(node_alpha);
                    if(node_father_ == nullptr){
                        root = node_x0;
                        break;
                    }else if((node_x0->get()).key()<(node_father_->get()).key()){
                        node_father_->changeLeftChild(node_x0);
                    }else{
                        node_father_->changeRightChild(node_x0);
                    }
                    node_father_->depth();
                    break;
                }
            }
            if(bf<-1){
                stack1.pop();
                AVLNode<Pair<Key,Value>>* node_father_ = nullptr;
                if(!stack1.empty()) node_father_ = stack1.top();//失衡点的父结点
                AVLNode<Pair<Key,Value>>* node_x = node_alpha->getRightChild();
                int bf2 = node_x->balance_factor();
                if(bf2<0){//RR型
                    AVLNode<Pair<Key,Value>>* node_left = node_x->getLeftChild();
                    node_alpha->changeRightChild(node_left);
                    node_x->changeLeftChild(node_alpha);
                    if(node_father_ ==nullptr){
                        root = node_x;
                        break;
                    }else if((node_x->get()).key() < (node_father_->get()).key()){
                        node_father_->changeLeftChild(node_x);
                    }else{
                        node_father_->changeRightChild(node_x);
                    }
                    node_father_->depth();
                    break;
                }else{//RL型
                    AVLNode<Pair<Key,Value>>* node_x0 = node_x->getLeftChild();
                    AVLNode<Pair<Key,Value>>* node_b = node_x0->getLeftChild();
                    AVLNode<Pair<Key,Value>>* node_y = node_x0->getRightChild();
                    node_alpha->changeRightChild(node_b);
                    node_x->changeLeftChild(node_y);
                    node_x0->changeLeftChild(node_alpha);
                    node_x0->changeRightChild(node_x);
                    if(node_father_==nullptr){
                        root = node_x0;
                        break;
                    }
                    else if((node_x0->get()).key()<(node_father_->get()).key()){
                        node_father_->changeLeftChild(node_x0);
                    }else{
                        node_father_->changeRightChild(node_x0);
                    }
                    node_father_->depth();
                    break;
                }
            }
            stack1.pop();
        }
        while(!stack1.empty()){
            AVLNode<Pair<Key,Value>>* update_node = stack1.top();
            if((node_alpha->get()).key()<(update_node->get()).key()){
                update_node->update_leftChild_depth();
            }else{
                update_node->update_rightChild_depth();
            }
            node_alpha = update_node;
            stack1.pop();
        }
        root->depth();
    }
    return true;
}
template <class Key,class Value>
bool AVLDictionary<Key,Value>::erase(const Key& key){
    if(root==nullptr) return false;
    ArrayStack<AVLNode<Pair<Key,Value>>*> stack1;
    ArrayQueue<AVLNode<Pair<Key,Value>>*> queue1;
    //Find the node key of which is the key
    AVLNode<Pair<Key,Value>>* father1 = nullptr;
    AVLNode<Pair<Key,Value>>* delete_node = root;
    while(delete_node!=nullptr){
        if((delete_node->get()).key()==key){
            break;
        }else if((delete_node->get()).key()>key){
            stack1.push(delete_node);
            delete_node->update_leftChild_depth();
            father1 = delete_node;
            delete_node = delete_node->getLeftChild();
        }else{
            stack1.push(delete_node);
            delete_node->update_rightChild_depth();
            father1 = delete_node;
            delete_node = delete_node->getRightChild();
        }
    }
    //if deletenode is a null pointer,then the node to delete is not found. Return false
    if(delete_node==nullptr){
        root->depth();
        return false;
    }
    //Case 1: father1 is null. Then node to delete is the root node;
    else if(father1==nullptr){
        AVLNode<Pair<Key,Value>>* left = root->getLeftChild();
        AVLNode<Pair<Key,Value>>* right = root->getRightChild();
        if(left==nullptr&&right==nullptr){
            delete root;
            root = nullptr;
            return true;
        }else if(left!=nullptr&&right==nullptr){
            root->changeLeftChild(nullptr);
            delete root;
            root = left;
            return true;
        }else if(left==nullptr&&right!=nullptr){
            root->changeRightChild(nullptr);
            delete root;
            root = right;
            return true;
        }else if(left->getRightChild()==nullptr){
            root->changeLeftChild(nullptr);
            root->changeRightChild(nullptr);
            delete root;
            left->changeRightChild(right);
            root = left;
            stack1.push(root);
        }//Case 2: father 1 is not null. Then the node to delete is not father node
        else{
            root->changeLeftChild(nullptr);
            root->changeRightChild(nullptr);
            delete root;
            AVLNode<Pair<Key,Value>>* left_right_father = left;
            AVLNode<Pair<Key,Value>>* left_right = left->getRightChild();
            queue1.push(left);
            while(left_right->getRightChild()!=nullptr){
                queue1.push(left_right);
                left_right_father->update_rightChild_depth();
                left_right_father = left_right;
                left_right = left_right->getRightChild();
            }
            left_right_father->changeRightChild(left_right->getLeftChild());
            left_right->changeLeftChild(left);
            left_right->changeRightChild(right);
            root = left_right;
            stack1.push(root);
            while(!queue1.empty()){
                stack1.push(queue1.front());
                queue1.pop();
            }
        }
    }else{
        AVLNode<Pair<Key,Value>>* left = delete_node->getLeftChild();
        AVLNode<Pair<Key,Value>>* right = delete_node->getRightChild();
        if(left==nullptr&&right==nullptr){
            if((delete_node->get()).key()<(father1->get()).key()) father1->changeLeftChild(nullptr);
            else father1->changeRightChild(nullptr);
            delete delete_node;
        }else if(left!=nullptr&&right==nullptr){
            if((delete_node->get()).key()<(father1->get()).key()) father1->changeLeftChild(left);
            else father1->changeRightChild(left);
            delete_node->changeLeftChild(nullptr);
            delete delete_node;
        }else if(left==nullptr&&right!=nullptr){
            if((delete_node->get()).key()<(father1->get()).key()) father1->changeLeftChild(right);
            else father1->changeRightChild(right);
            delete_node->changeRightChild(nullptr);
            delete delete_node;
        }else if(left->getRightChild()==nullptr){
            stack1.push(left);
            left->changeRightChild(right);
            if((delete_node->get()).key()<(father1->get()).key()) father1->changeLeftChild(left);
            else father1->changeRightChild(left);
            delete_node->changeLeftChild(nullptr);
            delete_node->changeRightChild(nullptr);
            delete delete_node;
        }else{
            AVLNode<Pair<Key,Value>>* left_right_father = left;
            AVLNode<Pair<Key,Value>>* left_right = left->getRightChild();
            queue1.push(left);
            while(left_right->getRightChild()!=nullptr){
                queue1.push(left_right);
                left_right_father->update_rightChild_depth();
                left_right_father = left_right;
                left_right = left_right->getRightChild();
            }
            left_right_father->changeRightChild(left_right->getLeftChild());
            left_right->changeLeftChild(left);
            left_right->changeRightChild(right);
            if(delete_node==father1->getLeftChild()) father1->changeLeftChild(left_right);
            else father1->changeRightChild(left_right);
            stack1.push(left_right);
            while(!queue1.empty()){
                stack1.push(queue1.front());
                queue1.pop();
            }
            delete_node->changeLeftChild(nullptr);
            delete_node->changeRightChild(nullptr);
            delete delete_node;
        }
    }
    //Balance the tree
    while(!stack1.empty()){
        AVLNode<Pair<Key,Value>>* node_alpha = stack1.top();
        AVLNode<Pair<Key,Value>>* node_father = nullptr;
        stack1.pop();
        if(!stack1.empty()) node_father = stack1.top();
        int bf = node_alpha->balance_factor();
        if(bf>1){
            AVLNode<Pair<Key,Value>>* node_x = node_alpha->getLeftChild();
            int bf2 = node_x->balance_factor();
            if(bf2==-1){
                AVLNode<Pair<Key,Value>>* node_x0 = node_x->getRightChild();
                AVLNode<Pair<Key,Value>>* node_L = node_x0->getLeftChild();
                AVLNode<Pair<Key,Value>>* node_R = node_x0->getRightChild();
                node_x->changeRightChild(node_L);
                node_alpha->changeLeftChild(node_R);
                node_x0->changeLeftChild(node_x);
                node_x0->changeRightChild(node_alpha);
                if(node_father!=nullptr){
                    if((node_x0->get()).key()<(node_father->get()).key()) node_father->changeLeftChild(node_x0);
                    else node_father->changeRightChild(node_x0);
                }else{
                    root = node_x0;
                }
            }else{
                AVLNode<Pair<Key,Value>>* node_R = node_x->getRightChild();
                node_alpha->changeLeftChild(node_R);
                node_x->changeRightChild(node_alpha);
                if(node_father!=nullptr){
                    if((node_x->get()).key()<(node_father->get()).key()) node_father->changeLeftChild(node_x);
                    else node_father->changeRightChild(node_x);
                }else{
                    root = node_x;
                }
            }
        }else{
            if(bf<-1){
                AVLNode<Pair<Key,Value>>* node_x = node_alpha->getRightChild();
                int bf2 = node_x->balance_factor();
                if(bf2==1){
                    AVLNode<Pair<Key,Value>>* node_x0 = node_x->getLeftChild();
                    AVLNode<Pair<Key,Value>>* node_L = node_x0->getLeftChild();
                    AVLNode<Pair<Key,Value>>* node_R = node_x0->getRightChild();
                    node_alpha->changeRightChild(node_L);
                    node_x->changeLeftChild(node_R);
                    node_x0->changeLeftChild(node_alpha);
                    node_x0->changeRightChild(node_x);
                    if(node_father!=nullptr){
                        if((node_x0->get()).key()<(node_father->get()).key()) node_father->changeLeftChild(node_x0);
                        else node_father->changeRightChild(node_x0);
                    }else{
                        root = node_x0;
                    }
                }else{
                    AVLNode<Pair<Key,Value>>* node_L = node_x->getLeftChild();
                    node_alpha->changeRightChild(node_L);
                    node_x->changeLeftChild(node_alpha);
                    if(node_father!=nullptr){
                        if((node_x->get()).key()<(node_father->get()).key()) node_father->changeLeftChild(node_x);
                        else node_father->changeRightChild(node_x);
                    }else{
                        root = node_x;
                    }
                }
            }
        }
    }
    root->depth();
    return true;
}
}//namespace end
#endif // AVLDICTIONARY_H
