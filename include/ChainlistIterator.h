#include "ChainNode.h"
#ifndef CHAINLISTITERATOR_H
#define CHAINLISTITERATOR_H
namespace Huitoy{
template <class T>
class ChainlistIterator
{
    public:
        ChainlistIterator(ChainNode<T>* chainNodePointer_);
        ChainlistIterator(const ChainlistIterator& cli);
        ChainlistIterator operator++(int);
        ChainlistIterator& operator++();
        bool operator == (const ChainlistIterator& chainlistIterator) const;
        bool operator != (const ChainlistIterator& chainlistIterator) const;
        T& operator*() const;
        bool null_iter() const{
            return chainNodePointer==nullptr;
        }
        ~ChainlistIterator();

    protected:
        ChainNode<T>* chainNodePointer;
    private:
};
template <class T>
ChainlistIterator<T>::ChainlistIterator(ChainNode<T>* chainNodePointer_){
    chainNodePointer = chainNodePointer_;
}
template <class T>
ChainlistIterator<T>::ChainlistIterator(const ChainlistIterator& cli){
    chainNodePointer = cli.chainNodePointer;
}
template <class T>
ChainlistIterator<T> ChainlistIterator<T>::operator++(int){
    ChainlistIterator cli = ChainlistIterator(chainNodePointer);
    if(chainNodePointer) chainNodePointer = chainNodePointer->getNextPointer();
    return cli;
}
template <class T>
ChainlistIterator<T>& ChainlistIterator<T>::operator++(){
    if(chainNodePointer) chainNodePointer = chainNodePointer->getNextPointer();
    return *this;
}
template <class T>
bool ChainlistIterator<T>::operator == (const ChainlistIterator& cli) const{
    return chainNodePointer == cli.chainNodePointer;
}
template <class T>
bool ChainlistIterator<T>::operator != (const ChainlistIterator& cli) const{
    return chainNodePointer != cli.chainNodePointer;
}
template <class T>
T& ChainlistIterator<T>::operator *() const{
    return chainNodePointer->get();
}
template <class T>
ChainlistIterator<T>::~ChainlistIterator(){}

template <class T>
class ConstChainlistIterator
{
    public:
        ConstChainlistIterator(const ChainNode<T>* chainNodePointer_);
        ConstChainlistIterator(const ConstChainlistIterator& cli);
        ConstChainlistIterator operator++(int);
        ConstChainlistIterator& operator++();
        bool operator == (const ConstChainlistIterator& constchainlistIterator) const;
        bool operator != (const ConstChainlistIterator& constchainlistIterator) const;
        const T& operator*() const;
        bool null_iter() const{
            return chainNodePointer==nullptr;
        }
        ~ConstChainlistIterator();

    protected:
        const ChainNode<T>* chainNodePointer;
    private:
};
template <class T>
ConstChainlistIterator<T>::ConstChainlistIterator(const ChainNode<T>* chainNodePointer_){
    chainNodePointer = chainNodePointer_;
}
template <class T>
ConstChainlistIterator<T>::ConstChainlistIterator(const ConstChainlistIterator& cli){
    chainNodePointer = cli.chainNodePointer;
}
template <class T>
ConstChainlistIterator<T> ConstChainlistIterator<T>::operator++(int){
    ConstChainlistIterator cli = ConstChainlistIterator(chainNodePointer);
    if(chainNodePointer) chainNodePointer = chainNodePointer->getNextPointer();
    return cli;
}
template <class T>
ConstChainlistIterator<T>& ConstChainlistIterator<T>::operator++(){
    if(chainNodePointer) chainNodePointer = chainNodePointer->getNextPointer();
    return *this;
}
template <class T>
bool ConstChainlistIterator<T>::operator == (const ConstChainlistIterator& cli) const{
    return chainNodePointer == cli.chainNodePointer;
}
template <class T>
bool ConstChainlistIterator<T>::operator != (const ConstChainlistIterator& cli) const{
    return chainNodePointer != cli.chainNodePointer;
}
template <class T>
const T& ConstChainlistIterator<T>::operator *() const{
    return chainNodePointer->get();
}
template <class T>
ConstChainlistIterator<T>::~ConstChainlistIterator(){}
}
#endif // CHAINLISTITERATOR_H
