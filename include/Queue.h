#ifndef QUEUE_H
#define QUEUE_H
namespace Huitoy{
template <class T>
class Queue
{
    public:
        virtual ~Queue() {}
        virtual bool empty() const =0;
        virtual unsigned size() const=0;
        virtual T& front() =0;
        virtual const T& front() const=0;
        virtual T& back() = 0;
        virtual const T& back() const=0;
        virtual bool pop() =0;
        virtual bool push(const T& theElement) = 0;
};
}
#endif // QUEUE_H
