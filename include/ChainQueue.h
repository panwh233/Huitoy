#include "Queue.h"
#include "Chainlist.h"

#ifndef CHAINQUEUE_H
#define CHAINQUEUE_H
namespace Huitoy{
template <class T>
class ChainQueue : public Queue<T>
{
    public:
        ChainQueue():chain(){}
        ChainQueue(const ChainQueue& cq):chain(cq.chain){};
        ChainQueue(const T* Tarray,unsigned n):chain(Tarray,n){}
        ChainQueue& operator=(const ChainQueue& cq){
            chain = cq.chain;
            return *this;
        }
        ChainQueue& copy(const T* Tarray,unsigned n){
            chain.copy(Tarray,n);
            return *this;
        }
        virtual ~ChainQueue(){}
        bool empty() const{
            return chain.empty();
        }
        unsigned size() const{
            return chain.size();
        }
        T& front(){
            if(chain.empty()) throw "Queue is empty!";
            return chain[0];
        }
        const T& front() const{
            if(chain.empty()) throw "Queue is empty!";
            return chain[0];
        }
        T& back() {
            if(chain.empty()) throw "Queue is empty!";
            return chain[chain.size()-1];
        }
        const T& back() const{
            if(chain.empty()) throw "Queue is empty!";
            return chain[chain.size()-1];
        }
        bool pop(){
            chain.erasefront();
            return true;
        }
        bool push(const T& theElement){
            chain.insertback(theElement);
            return true;
        }
    protected:
        Chainlist<T> chain;
};
}
#endif // CHAINQUEUE_H
