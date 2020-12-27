#include "ArrayStack.h"
#include "RBTreeNode.h"
#include "Dictionary.h"
#include "binaryTree.h"
#include "Pair.h"
#ifndef RBTREEDICTIONARY_H
#define RBTREEDICTIONARY_H

namespace Huitoy{
template <class Key,class Value>
class RBTreeDictionary:public binaryTree<Value>,public Dictionary<Key,Value>
{
    public:
        RBTreeDictionary();
        RBTreeDictionary(const RBTreeDictionary& tree);
        RBTreeDictionary(RBTreeDictionary&& tree) noexcept;
        RBTreeDictionary(const Pair<Key,Value>* pair_array,unsigned n,bool replace = true);
        RBTreeDictionary(const Key* key_array,const Value* value_array,unsigned n,bool replace = true);

        RBTreeDictionary& operator = (const RBTreeDictionary& tree);
        RBTreeDictionary& operator = (RBTreeDictionary&& tree) noexcept;
        RBTreeDictionary& copy(const Pair<Key,Value>* pair_array,unsigned n,bool replace = true);
        RBTreeDictionary& copy(const Key* key_array,const Value* value_array,unsigned n,bool replace = true);

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

        ~RBTreeDictionary();
        void clear();

    protected:
        RBTreeNode<Pair<Key,Value>>* root;
        RBTreeNode<Pair<Key,Value>>* balance_node(RBTreeNode<Pair<Key,Value>>* node_alpha,RBTreeNode<Pair<Key,Value>>* brother,bool& rebalance);
};

//Constructor
template <class Key,class Value>
RBTreeDictionary<Key,Value>::RBTreeDictionary(){
    root=nullptr;
}
template <class Key,class Value>
RBTreeDictionary<Key,Value>::RBTreeDictionary(const RBTreeDictionary& tree){
    if(tree.root==nullptr){
        root = nullptr;
        return;
    }
    root = new RBTreeNode<Pair<Key,Value>>;
    root->copy(tree.root);
}
template <class Key,class Value>
RBTreeDictionary<Key,Value>::RBTreeDictionary(RBTreeDictionary&& tree) noexcept{
    root = tree.root;
    tree.root = nullptr;
}
template <class Key,class Value>
RBTreeDictionary<Key,Value>::RBTreeDictionary(const Pair<Key,Value>* pair_array,unsigned n,bool replace){
    for(unsigned i = 0;i<n;i++){
        insert(pair_array[i].key(),pair_array[i].value(),replace);
    }
}
template <class Key,class Value>
RBTreeDictionary<Key,Value>::RBTreeDictionary(const Key* key_array,const Value* value_array,unsigned n,bool replace){
    for(unsigned i=0;i<n;i++){
        insert(key_array[0],value_array[0],replace);
    }
}
//Destructor
template <class Key,class Value>
RBTreeDictionary<Key,Value>::~RBTreeDictionary(){
    if(root!=nullptr){
        delete root;
    }
}
template <class Key,class Value>
void RBTreeDictionary<Key,Value>::clear(){
    if(root!=nullptr){
        delete root;
        root = nullptr;
    }
}
//operator = and copy
template <class Key,class Value>
RBTreeDictionary<Key,Value>& RBTreeDictionary<Key,Value>::operator = (const RBTreeDictionary& tree){
    clear();
    root = new RBTreeNode<Pair<Key,Value>>;
    root->copy(&tree);
    return *this;
}
template <class Key,class Value>
RBTreeDictionary<Key,Value>& RBTreeDictionary<Key,Value>::operator = (RBTreeDictionary&& tree) noexcept{
    clear();
    root = tree.root;
    tree.root = nullptr;
    return *this;
}
template <class Key,class Value>
RBTreeDictionary<Key,Value>& RBTreeDictionary<Key,Value>::copy(const Pair<Key,Value>* pair_array,unsigned n,bool replace){
    clear();
    for(unsigned i = 0;i<n;i++){
        insert(pair_array[i].key(),pair_array[i].value(),replace);
    }
}
template <class Key,class Value>
RBTreeDictionary<Key,Value>& RBTreeDictionary<Key,Value>::copy(const Key* key_array,const Value* value_array,unsigned n,bool replace){
    clear();
    for(unsigned i=0;i<n;i++){
        insert(key_array[0],value_array[0],replace);
    }
}
template <class Key,class Value>
bool RBTreeDictionary<Key,Value>::empty() const{
    return root==nullptr;
}
template <class Key,class Value>
unsigned RBTreeDictionary<Key,Value>::size() const{
    if(root==nullptr) return 0;
    else{
        return root->size();
    }
}
template <class Key,class Value>
unsigned RBTreeDictionary<Key,Value>::depth() const{
    if(root==nullptr) return 0;
    else{
        return root->depth();
    }
}
template <class Key,class Value>
Key RBTreeDictionary<Key,Value>::search(const Value& value) const{
    ArrayQueue<const RBTreeNode<Pair<Key,Value>>*> queue_;
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
Value& RBTreeDictionary<Key,Value>::operator[](const Key& key){
    if(root==nullptr){
        throw illegalParameterValue("Key not found!");
    }else{
        RBTreeNode<Pair<Key,Value>>* node = root;
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
const Value& RBTreeDictionary<Key,Value>::operator[](const Key& key) const{
    if(root==nullptr){
        throw illegalParameterValue("Key not found!");
    }else{
        const RBTreeNode<Pair<Key,Value>>* node = root;
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
void RBTreeDictionary<Key,Value>::preOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->preOrder(new_visit);
}
template <class Key,class Value>
void RBTreeDictionary<Key,Value>::inOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->inOrder(new_visit);
}
template <class Key,class Value>
void RBTreeDictionary<Key,Value>::postOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->postOrder(new_visit);
}
template <class Key,class Value>
void RBTreeDictionary<Key,Value>::levelOrder(const std::function<void(Value&)>& visit){
    if(root==nullptr) return;
    Processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->levelOrder(new_visit);
}
template <class Key,class Value>
void RBTreeDictionary<Key,Value>::preOrder(const std::function<void(const Value&)>& visit) const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->preOrder(new_visit);
}
template <class Key,class Value>
void RBTreeDictionary<Key,Value>::inOrder(const std::function<void(const Value&)>& visit) const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->inOrder(new_visit);
}
template <class Key,class Value>
void RBTreeDictionary<Key,Value>::postOrder(const std::function<void(const Value&)>& visit)const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->postOrder(new_visit);
}
template <class Key,class Value>
void RBTreeDictionary<Key,Value>::levelOrder(const std::function<void(const Value&)>& visit)const{
    if(root==nullptr) return;
    Const_processed_visit_function<Key,Value> new_visit;
    new_visit.f1 = visit;
    root->postOrder(new_visit);
}
template <class Key,class Value>
bool RBTreeDictionary<Key,Value>::insert(const Key& key,const Value& value,bool replace){
    if(root==nullptr){
        root = new RBTreeNode<Pair<Key,Value>>(Pair<Key,Value>(key,value),false);
        return true;
    }
    ArrayStack<RBTreeNode<Pair<Key,Value>>*> stack_;
    RBTreeNode<Pair<Key,Value>>* node = root;
    while(node!=nullptr){
        if((node->get()).key()==key){
            if(replace){
                (node->get()).value() = value;
                return true;
            }else{
                return false;
            }
        }
        else if(key<(node->get()).key()){
            stack_.push(node);
            node = node->getLeftChild();
        }else{
            stack_.push(node);
            node = node->getRightChild();
        }
    }
    RBTreeNode<Pair<Key,Value>>* newnode = new RBTreeNode<Pair<Key,Value>>(Pair<Key,Value>(key,value));
    RBTreeNode<Pair<Key,Value>>* father = stack_.top();
    if(key<(father->get()).key()){
        father->changeLeftChild(newnode);
        if(!father->red()){
            return true;
        }
    }else{
        father->changeRightChild(newnode);
        if(!father->red()){
            return true;
        }
    }
    RBTreeNode<Pair<Key,Value>>* node_alpha = newnode;
    while(node_alpha!=nullptr){
        stack_.pop();
        RBTreeNode<Pair<Key,Value>>* grandfather = stack_.top();
        //determine the type
        unsigned type1_L,type2_L,type3_R;
        if(father==grandfather->getLeftChild()) {
            type1_L = 1;
            if(grandfather->getRightChild()!=nullptr&&grandfather->getRightChild()->red()) type3_R = 1;
            else type3_R = 0;
        }
        else{
            type1_L = 0;
            if(grandfather->getLeftChild()!=nullptr&&grandfather->getLeftChild()->red()) type3_R = 1;
            else type3_R = 0;
        }
        if(node_alpha==father->getLeftChild()) type2_L = 1;
        else type2_L = 0;
        if(type3_R==1){
            RBTreeNode<Pair<Key,Value>>* uncle;
            if(type1_L==1) uncle = grandfather->getRightChild();
            else uncle = grandfather->getLeftChild();
            if(grandfather==root){
                father->changeColor(false);
                uncle->changeColor(false);
                return true;
            }else{
                father->changeColor(false);
                uncle->changeColor(false);
                grandfather->changeColor(true);
                stack_.pop();
                RBTreeNode<Pair<Key,Value>>* grandgrandfather = stack_.top();
                if(grandgrandfather->red()){
                    node_alpha = grandfather;
                    father = grandgrandfather;
                }else{
                    node_alpha = nullptr;
                }
            }
        }else if(type1_L==1&&type2_L==1){//LLB
            //Recolor the nodes
            father->changeColor(false);
            grandfather->changeColor(true);
            //rotate the nodes
            RBTreeNode<Pair<Key,Value>>* node_III = father->getRightChild();
            father->changeRightChild(grandfather);
            grandfather->changeLeftChild(node_III);
            if(grandfather==root){
                root = father;
            }else{
                stack_.pop();
                RBTreeNode<Pair<Key,Value>>* grandgrandfather = stack_.top();
                if(grandfather==grandgrandfather->getLeftChild()){
                    grandgrandfather->changeLeftChild(father);
                }else{
                    grandgrandfather->changeRightChild(father);
                }
            }
            node_alpha=nullptr;
        }else if(type1_L==1&&type2_L==0){//LRb
            RBTreeNode<Pair<Key,Value>>* node_II = node_alpha->getLeftChild();
            RBTreeNode<Pair<Key,Value>>* node_III = node_alpha->getRightChild();
            father->changeRightChild(node_II);
            grandfather->changeLeftChild(node_III);
            node_alpha->changeLeftChild(father);
            node_alpha->changeRightChild(grandfather);
            if(grandfather==root){
                root = node_alpha;
            }else{
                stack_.pop();
                RBTreeNode<Pair<Key,Value>>* grandgrandfather = stack_.top();
                if(grandfather==grandgrandfather->getLeftChild()){
                    grandgrandfather->changeLeftChild(node_alpha);
                }else{
                    grandgrandfather->changeRightChild(node_alpha);
                }
            }
            node_alpha=nullptr;
        }else if(type1_L==0&&type2_L==1){//RL
            //recolor the nodes
            node_alpha->changeColor(false);
            grandfather->changeColor(true);
            RBTreeNode<Pair<Key,Value>>* node_II = node_alpha->getLeftChild();
            RBTreeNode<Pair<Key,Value>>* node_III = node_alpha->getRightChild();
            //rotate the nodes
            grandfather->changeRightChild(node_II);
            father->changeLeftChild(node_III);
            node_alpha->changeLeftChild(grandfather);
            node_alpha->changeRightChild(father);
            if(grandfather==root){
                root = node_alpha;
            }else{
                stack_.pop();
                RBTreeNode<Pair<Key,Value>>* grandgrandfather = stack_.top();
                if(grandfather==grandgrandfather->getLeftChild()){
                    grandgrandfather->changeLeftChild(node_alpha);
                }else{
                    grandgrandfather->changeRightChild(node_alpha);
                }
            }
            node_alpha=nullptr;
        }else{//RR
            //recolor the nodes
            grandfather->changeColor(true);
            father->changeColor(false);
            //rotate the nodes
            RBTreeNode<Pair<Key,Value>>* node_II = father->getLeftChild();
            grandfather->changeRightChild(node_II);
            father->changeLeftChild(grandfather);
            father->changeRightChild(node_alpha);
            if(grandfather==root){
                root = father;
            }else{
                stack_.pop();
                RBTreeNode<Pair<Key,Value>>* grandgrandfather = stack_.top();
                if(grandfather==grandgrandfather->getLeftChild()){
                    grandgrandfather->changeLeftChild(father);
                }else{
                    grandgrandfather->changeRightChild(father);
                }
            }
            node_alpha = nullptr;
        }
    }
    return true;
}
template <class Key,class Value>
RBTreeNode<Pair<Key,Value>>* RBTreeDictionary<Key,Value>::balance_node(RBTreeNode<Pair<Key,Value>>* node_alpha,RBTreeNode<Pair<Key,Value>>* node_brother,bool& rebalance){
    RBTreeNode<Pair<Key,Value>>* alpha = node_alpha;
    RBTreeNode<Pair<Key,Value>>* brother = node_brother;
    //Determine the type:
    unsigned type1,type2,type3,type4;
    if(brother==alpha->getRightChild()) type1 = 1;
    else type1 = 0;
    if(brother->red()) type2 = 0;
    else type2 = 1;
    if(brother->getLeftChild()!=nullptr&&brother->getLeftChild()->red()) type3 = 0;
    else type3 = 1;
    if(brother->getRightChild()!=nullptr&&brother->getRightChild()->red()) type4 = 0;
    else type4 = 1;
    //Balance the node
    if(type1==1&&type2==1){
        //LB
        if(type3==1&&type4==1){
            //LB0
            bool color_alpha = alpha->red();
            alpha->changeColor(false);
            brother->changeColor(true);
            if(color_alpha) rebalance = false;
            else rebalance = true;
            return alpha;
        }else if(type3==0&&type4==1){
            //LB1,RL red,RR black
            bool color_alpha = alpha->red();
            RBTreeNode<Pair<Key,Value>>* rl = brother->getLeftChild();
            RBTreeNode<Pair<Key,Value>>* rll = rl->getLeftChild();
            RBTreeNode<Pair<Key,Value>>* rlr = rl->getRightChild();
            alpha->changeRightChild(rll);
            brother->changeLeftChild(rlr);
            rl->changeLeftChild(alpha);
            rl->changeRightChild(brother);
            alpha->changeColor(false);
            brother->changeColor(false);
            rl->changeColor(color_alpha);
            rebalance = false;
            return rl;
        }else if(type3==1&&type4==0){
            //LB1,RR red,RL black
            bool color_alpha = alpha->red();
            RBTreeNode<Pair<Key,Value>>* rr = brother->getRightChild();
            RBTreeNode<Pair<Key,Value>>* rl = brother->getLeftChild();
            alpha->changeRightChild(rl);
            brother->changeLeftChild(alpha);
            brother->changeRightChild(rr);
            alpha->changeColor(false);
            rr->changeColor(false);
            brother->changeColor(color_alpha);
            rebalance = false;
            return brother;
        }else{
            //LB2
            bool color_alpha = alpha->red();
            RBTreeNode<Pair<Key,Value>>* rl = brother->getLeftChild();
            RBTreeNode<Pair<Key,Value>>* rr = brother->getRightChild();
            alpha->changeRightChild(rl);
            brother->changeLeftChild(alpha);
            rl->changeColor(true);
            alpha->changeColor(false);
            rr->changeColor(false);
            brother->changeColor(color_alpha);
            rebalance = false;
            return brother;
        }
    }else if(type1==1&&type2==0){
        //LR
        unsigned rll_red,rlr_red;
        RBTreeNode<Pair<Key,Value>>* rl = brother->getLeftChild();
        RBTreeNode<Pair<Key,Value>>* rll = rl->getLeftChild();
        RBTreeNode<Pair<Key,Value>>* rlr = rl->getRightChild();
        if(rll!=nullptr&&rll->red()) rll_red=1;
        else rll_red = 0;
        if(rlr!=nullptr&&rlr->red()) rlr_red=1;
        else rlr_red = 0;
        if(rll_red==1){
            RBTreeNode<Pair<Key,Value>>* rlll = rll->getLeftChild();
            RBTreeNode<Pair<Key,Value>>* rllr = rll->getRightChild();
            alpha->changeRightChild(rlll);
            rl->changeLeftChild(rllr);
            rll->changeLeftChild(alpha);
            rll->changeRightChild(rl);
            brother->changeLeftChild(rll);
            brother->changeColor(false);
            rll->changeColor(true);
            alpha->changeColor(false);
            rl->changeColor(false);
            rebalance = false;
            return brother;
        }else if(rlr_red==1){
            alpha->changeRightChild(rll);
            rl->changeLeftChild(alpha);
            brother->changeLeftChild(rl);
            brother->changeColor(false);
            rl->changeColor(true);
            alpha->changeColor(false);
            rlr->changeColor(false);
            rebalance = false;
            return brother;
        }else{
            alpha->changeRightChild(rl);
            brother->changeLeftChild(alpha);
            brother->changeColor(false);
            alpha->changeColor(false);
            rl->changeColor(true);
            rebalance = false;
            return brother;
        }
    }else if(type1==0&&type2==1){
        if(type3==1&&type4==1){
            bool alpha_red = alpha->red();
            alpha->changeColor(false);
            brother->changeColor(true);
            if(alpha_red) rebalance=false;
            else rebalance=true;
            return alpha;
        }else if(type3==1&&type4==0){
            bool alpha_red = alpha->red();
            RBTreeNode<Pair<Key,Value>>* lr = brother->getRightChild();
            RBTreeNode<Pair<Key,Value>>* lrl = lr->getLeftChild();
            RBTreeNode<Pair<Key,Value>>* lrr = lr->getRightChild();
            brother->changeRightChild(lrl);
            alpha->changeLeftChild(lrr);
            lr->changeLeftChild(brother);
            lr->changeRightChild(alpha);
            lr->changeColor(alpha_red);
            brother->changeColor(false);
            alpha->changeColor(false);
            rebalance = false;
            return lr;
        }else if(type3==0&&type4==1){
            bool alpha_red = alpha->red();
            RBTreeNode<Pair<Key,Value>>* ll = brother->getLeftChild();
            RBTreeNode<Pair<Key,Value>>* lr = brother->getRightChild();
            alpha->changeLeftChild(lr);
            brother->changeRightChild(alpha);
            ll->changeColor(false);
            alpha->changeColor(false);
            brother->changeColor(alpha_red);
            rebalance = false;
            return brother;
        }else{
            bool alpha_red = alpha->red();
            RBTreeNode<Pair<Key,Value>>* ll = brother->getLeftChild();
            RBTreeNode<Pair<Key,Value>>* lr = brother->getRightChild();
            alpha->changeLeftChild(lr);
            brother->changeRightChild(alpha);
            ll->changeColor(false);
            alpha->changeColor(false);
            brother->changeColor(alpha_red);
            rebalance = false;
            return brother;
        }
    }else{
        //RR
        RBTreeNode<Pair<Key,Value>>* lr = brother->getRightChild();
        RBTreeNode<Pair<Key,Value>>* lrl = lr->getLeftChild();
        RBTreeNode<Pair<Key,Value>>* lrr = lr->getRightChild();
        unsigned lrl_red,lrr_red;
        if(lrl!=nullptr&&lrl->red()) lrl_red = 1;
        else lrl_red = 0;
        if(lrr!=nullptr&&lrr->red()) lrr_red=1;
        else lrr_red = 0;
        if(lrl_red==1){
            alpha->changeLeftChild(lrr);
            lr->changeRightChild(alpha);
            brother->changeRightChild(lr);
            lrl->changeColor(false);
            lr->changeColor(true);
            brother->changeColor(false);
            rebalance=false;
            return brother;
        }else if(lrr_red==1){
            RBTreeNode<Pair<Key,Value>>* lrrl = lrr->getLeftChild();
            RBTreeNode<Pair<Key,Value>>* lrrr = lrr->getRightChild();
            lr->changeRightChild(lrrl);
            alpha->changeLeftChild(lrrr);
            lrr->changeLeftChild(lr);
            lrr->changeRightChild(alpha);
            brother->changeRightChild(lrr);
            lr->changeColor(false);
            rebalance = false;
            return brother;
        }else{
            alpha->changeLeftChild(lr);
            brother->changeRightChild(alpha);
            brother->changeColor(false);
            lr->changeColor(true);
            rebalance=false;
            return brother;
        }
    }
}
template <class Key,class Value>
bool RBTreeDictionary<Key,Value>::erase(const Key& key){
    //if RBTree is null, return false
    if(root==nullptr) return false;
    //find the node to delete
    ArrayStack<RBTreeNode<Pair<Key,Value>>*> stack_;
    RBTreeNode<Pair<Key,Value>>* node_delete = root;
    while(node_delete!=nullptr){
        Key key_ = (node_delete->get()).key();
        if(key_==key){
            //if key of node_alpha == key , break the loop
            break;
        }else if(key<key_){
            stack_.push(node_delete);
            node_delete = node_delete->getLeftChild();
        }else{
            stack_.push(node_delete);
            node_delete = node_delete->getRightChild();
        }
    }
    //if node_delete is null, return false
    if(node_delete==nullptr) return false;
    RBTreeNode<Pair<Key,Value>>* alpha;
    RBTreeNode<Pair<Key,Value>>* brother;
    //if node_delete==nullptr
    if(node_delete==root){
        RBTreeNode<Pair<Key,Value>>* left = root->getLeftChild();
        RBTreeNode<Pair<Key,Value>>* right = root->getRightChild();
        if(left==nullptr&&right==nullptr){
            delete root;
            root=nullptr;
            return true;
        }else if(left!=nullptr&&right==nullptr){
            root->changeLeftChild(nullptr);
            delete root;
            root=left;
            root->changeColor(false);
            return true;
        }else if(left==nullptr&&right!=nullptr){
            root->changeRightChild(nullptr);
            delete root;
            root=right;
            root->changeColor(false);
            return true;
        }else if(left->getRightChild()==nullptr){
            bool left_red = left->red();
            root->changeLeftChild(nullptr);
            root->changeRightChild(nullptr);
            delete root;
            left->changeRightChild(right);
            left->changeColor(false);
            root=left;
            if(!left_red){
                alpha = left;
                brother = right;
                bool rebalance;
                root = balance_node(alpha,brother,rebalance);
            }
            return true;
        }else{
            ArrayQueue<RBTreeNode<Pair<Key,Value>>*> queue_;
            RBTreeNode<Pair<Key,Value>>* lrf = left;
            RBTreeNode<Pair<Key,Value>>* lr = left->getRightChild();
            queue_.push(left);
            while(lr->getRightChild()!=nullptr){
                queue_.push(lr);
                lrf = lr;
                lr = lr->getRightChild();
            }
            RBTreeNode<Pair<Key,Value>>* lrl = lr->getLeftChild();
            root->changeLeftChild(nullptr);
            root->changeRightChild(nullptr);
            delete root;
            bool lr_red = lr->red();
            if(lr_red){
                //lrl==nullptr
                lr->changeLeftChild(left);
                lr->changeRightChild(right);
                lrf->changeRightChild(nullptr);
                lr->changeColor(false);
                root = lr;
                return true;
            }else if(lrl!=nullptr){
                lr->changeLeftChild(left);
                lr->changeRightChild(right);
                lrf->changeRightChild(lrl);
                lr->changeColor(false);
                lrl->changeColor(false);
                root=lr;
                return true;
            }else{
                stack_.push(lr);
                while(!queue_.empty()){
                    stack_.push(queue_.front());
                    queue_.pop();
                }
                stack_.pop();
                lr->changeLeftChild(left);
                lr->changeRightChild(right);
                lrf->changeRightChild(nullptr);
                lr->changeColor(false);
                root=lr;
                brother = lrf->getLeftChild();
                alpha = lrf;
            }
        }
    }else{
        RBTreeNode<Pair<Key,Value>>* left = node_delete->getLeftChild();
        RBTreeNode<Pair<Key,Value>>* right = node_delete->getRightChild();
        RBTreeNode<Pair<Key,Value>>* father = stack_.top();
        if(left==nullptr&&right==nullptr){
            bool node_delete_red = node_delete->red();
            if(node_delete==father->getLeftChild()){
                father->changeLeftChild(nullptr);
                brother = father->getRightChild();
            }else{
                father->changeRightChild(nullptr);
                brother = father->getLeftChild();
            }
            delete node_delete;
            if(node_delete_red) return true;
            else{
                alpha = father;
                stack_.pop();
            }
        }else if(left!=nullptr&&right==nullptr){
            if(node_delete==father->getLeftChild()){
                father->changeLeftChild(left);
                left->changeColor(false);
                node_delete->changeLeftChild(nullptr);
                delete node_delete;
            }else{
                father->changeRightChild(left);
                left->changeColor(false);
                node_delete->changeLeftChild(nullptr);
                delete node_delete;
            }
            return true;
        }else if(left==nullptr&&right!=nullptr){
            if(node_delete==father->getLeftChild()){
                father->changeLeftChild(right);
                right->changeColor(false);
                node_delete->changeRightChild(nullptr);
                delete node_delete;
            }else{
                father->changeRightChild(right);
                right->changeColor(false);
                node_delete->changeRightChild(nullptr);
                delete node_delete;
            }
            return true;
        }else if(left->getRightChild()==nullptr){
            RBTreeNode<Pair<Key,Value>>* left_left = left->getLeftChild();
            bool node_delete_color = node_delete->red();
            left->changeRightChild(right);
            if(node_delete==father->getLeftChild()){
                father->changeLeftChild(left);
            }else{
                father->changeRightChild(left);
            }
            node_delete->changeLeftChild(nullptr);
            node_delete->changeRightChild(nullptr);
            delete node_delete;
            if(node_delete_color){
                left->changeColor(true);
                if(left_left!=nullptr){
                    left_left->changeColor(false);
                    return true;
                }else{
                    alpha = left;
                    brother = right;
                }
            }else if(left->red()){
                left->changeColor(false);
                return true;
            }else if(left_left!=nullptr){
                left_left->changeColor(false);
                return true;
            }else{
                alpha = left;
                brother = right;
            }
        }else{
            ArrayQueue<RBTreeNode<Pair<Key,Value>>*> queue_;
            bool node_delete_color = node_delete->red();
            RBTreeNode<Pair<Key,Value>>* lrf = left;
            RBTreeNode<Pair<Key,Value>>* lr = left->getRightChild();
            queue_.push(left);
            while(lr->getRightChild()!=nullptr){
                queue_.push(lr);
                lrf = lr;
                lr = lr->getRightChild();
            }
            bool lr_color = lr->red();
            RBTreeNode<Pair<Key,Value>>* lrl = lr->getLeftChild();
            if(lr_color){
                lr->changeColor(node_delete_color);
                lr->changeLeftChild(left);
                lr->changeRightChild(right);
                lrf->changeRightChild(nullptr);
                if(node_delete==father->getLeftChild()) father->changeLeftChild(lr);
                else father->changeRightChild(lr);
                node_delete->changeLeftChild(nullptr);
                node_delete->changeRightChild(nullptr);
                delete node_delete;
                return true;
            }else if(lrl!=nullptr){
                lr->changeColor(node_delete_color);
                lr->changeLeftChild(left);
                lr->changeRightChild(right);
                lrf->changeRightChild(lrl);
                lrl->changeColor(false);
                if(node_delete==father->getLeftChild()) father->changeLeftChild(lr);
                else father->changeRightChild(lr);
                node_delete->changeLeftChild(nullptr);
                node_delete->changeRightChild(nullptr);
                delete node_delete;
                return true;
            }else{
                lr->changeColor(node_delete_color);
                lr->changeLeftChild(left);
                lr->changeRightChild(right);
                lrf->changeRightChild(nullptr);
                if(node_delete==father->getLeftChild()) father->changeLeftChild(lr);
                else father->changeRightChild(lr);
                node_delete->changeLeftChild(nullptr);
                node_delete->changeRightChild(nullptr);
                delete node_delete;
                stack_.push(lr);
                while(!queue_.empty()){
                    stack_.push(queue_.front());
                    queue_.pop();
                }
                stack_.pop();
                alpha = lrf;
                brother = lrf->getLeftChild();
            }
        }
    }
    //balance nodes
    bool rebalance = true;
    while(rebalance){
        if(alpha==root){
            root=balance_node(alpha,brother,rebalance);
            root->changeColor(false);
            rebalance=false;
        }else{
            RBTreeNode<Pair<Key,Value>>* father = stack_.top();
            stack_.pop();
            if(alpha==father->getLeftChild()){
                father->changeLeftChild(balance_node(alpha,brother,rebalance));
                alpha = father;
                brother = father->getRightChild();
            }else{
                father->changeRightChild(balance_node(alpha,brother,rebalance));
                alpha = father;
                brother = father->getLeftChild();
            }
        }
    }
    return true;
}

}//namespace end
#endif // RBTREEDICTIONARY_H
