#include <functional>
#ifndef BINARYTREE_H
#define BINARYTREE_H
namespace Huitoy{
template <class T>
class binaryTree
{
    public:
        /*树的参数*/
        virtual bool empty() const=0;
        virtual unsigned size() const=0;
        virtual unsigned depth() const =0;
        /*遍历一棵树*/
        virtual void preOrder(const std::function<void(T&)>& visit)=0;
        virtual void inOrder(const std::function<void(T&)>& visit)=0;
        virtual void postOrder(const std::function<void(T&)>& visit)=0;
        virtual void levelOrder(const std::function<void(T&)>& visit)=0;
        virtual void preOrder(const std::function<void(const T&)>& visit) const=0;
        virtual void inOrder(const std::function<void(const T&)>& visit) const=0;
        virtual void postOrder(const std::function<void(const T&)>& visit) const= 0;
        virtual void levelOrder(const std::function<void(const T&)>& visit) const=0;
        /*虚析构函数*/
        virtual ~binaryTree() {}
};
}
#endif // BINARYTREE_H
