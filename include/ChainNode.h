#ifndef CHAINNODE_H
#define CHAINNODE_H
namespace Huitoy{
template <class T>
class ChainNode
{
    public:
        ChainNode();
        ChainNode(const T& element_,ChainNode<T>* nextPtr_=nullptr);
        ChainNode(const ChainNode& node,ChainNode<T>* nextPtr_ = nullptr);
        T& get();
        const T& get() const;
        ChainNode<T>& operator=(const ChainNode& node);
        ChainNode<T>& operator=(const T& element_);
        void changeNextPointer(ChainNode<T>* nextPtr_);
        const ChainNode<T>* getNextPointer() const;
        ChainNode<T>* getNextPointer();
        ~ChainNode();

    protected:
        T element;
        mutable ChainNode<T>* nextPtr;
    private:
};
template <class T>
ChainNode<T>::ChainNode(){
    nextPtr = nullptr;
}
template <class T>
ChainNode<T>::ChainNode(const T& element_,ChainNode<T>* nextPtr_){
    element = element_;
    nextPtr = nextPtr_;
}

template <class T>
ChainNode<T>::ChainNode(const ChainNode& node,ChainNode<T>* nextPtr_){
    element = node.element;
    nextPtr = nextPtr_;
}
template <class T>
ChainNode<T>::~ChainNode(){
}

template <class T>
T& ChainNode<T>::get(){
    return element;
}

template <class T>
const T& ChainNode<T>::get() const{
    return element;
}

template <class T>
ChainNode<T>& ChainNode<T>::operator = (const ChainNode<T>& node){
    element = node.element;
}

template <class T>
ChainNode<T>& ChainNode<T>::operator = (const T& element_){
    element = element_;
}

template <class T>
ChainNode<T>* ChainNode<T>::getNextPointer(){
    return nextPtr;
}
template <class T>
const ChainNode<T>* ChainNode<T>::getNextPointer() const{
    return nextPtr;
}
template <class T>
void ChainNode<T>::changeNextPointer(ChainNode<T>* nextPtr_){
    nextPtr=nextPtr_;
}
}
#endif // CHAINNODE_H
