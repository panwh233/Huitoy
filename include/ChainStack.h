#include "Chainlist.h"
#include "Stack.h"
#ifndef CHAINSTACK_H
#define CHAINSTACK_H
namespace Huitoy{
template <class T>
class ChainStack:public Stack<T>
{
    public:
        ChainStack():chain(){}
        ChainStack(const ChainStack& cs):chain(cs.chain){}
        ChainStack(const T* Tarray,unsigned n):chain(Tarray,n){}
        ChainStack& operator = (const ChainStack& cs){
            chain=cs.chain;
            return *this;
        }
        ChainStack& copy(const T* Tarray,unsigned n){
            chain.copy(Tarray,n);
            return *this;
        }
        bool empty() const{
            return chain.empty();
        }
        unsigned size() const{
            return chain.size();
        }
        T& top(){
            if(chain.empty()) throw "Stack is empty!";
            return chain[0];
        }
        const T& top() const{
            if(chain.empty()) throw "Stack is empty!";
            return chain[0];
        }
        bool pop(){
            chain.erasefront();
            return true;
        }
        bool push(const T& theElement){
            chain.insertfront(theElement);
            return true;
        }
        ~ChainStack(){}
    protected:
        Chainlist<T> chain;
    private:
};
}
#endif // CHAINSTACK_H
