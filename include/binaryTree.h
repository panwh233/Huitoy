#include <functional>
#ifndef BINARYTREE_H
#define BINARYTREE_H
namespace Huitoy{
template <class T>
class binaryTree
{
    public:
        /*���Ĳ���*/
        virtual bool empty() const=0;
        virtual unsigned size() const=0;
        virtual unsigned depth() const =0;
        /*����һ����*/
        virtual void preOrder(const std::function<void(T&)>& visit)=0;
        virtual void inOrder(const std::function<void(T&)>& visit)=0;
        virtual void postOrder(const std::function<void(T&)>& visit)=0;
        virtual void levelOrder(const std::function<void(T&)>& visit)=0;
        virtual void preOrder(const std::function<void(const T&)>& visit) const=0;
        virtual void inOrder(const std::function<void(const T&)>& visit) const=0;
        virtual void postOrder(const std::function<void(const T&)>& visit) const= 0;
        virtual void levelOrder(const std::function<void(const T&)>& visit) const=0;
        /*����������*/
        virtual ~binaryTree() {}
};
}
#endif // BINARYTREE_H
