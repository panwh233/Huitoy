#ifndef STACK_H
#define STACK_H
namespace Huitoy{
template <class T>
class Stack
{
    public:
        virtual bool empty() const =0;
        virtual unsigned size() const =0;
        virtual T& top() =0;
        virtual const T& top() const =0;
        virtual bool pop() =0;
        virtual bool push(const T& theElement) = 0;

};
}
#endif // ARRAYSTACK_H
