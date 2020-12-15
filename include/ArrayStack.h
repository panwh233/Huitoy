#include "Stack.h"
#include "Arraylist.h"
#include "illegalParameterValue.h"
#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
namespace Huitoy{
template <class T>
class ArrayStack:public Stack<T>
{
    public:
        /*���캯��*/
        ArrayStack(unsigned initial_capacity=5,float expand_factor=1.5):arr_list(initial_capacity,expand_factor){}
        ArrayStack(const ArrayStack& as,float expand_factor=1.5):arr_list(as.arr_list,expand_factor){}
        ArrayStack(const Arraylist<T>& arr,float expand_factor=1.5):arr_list(arr,expand_factor){}
        ArrayStack(const T& Tarray,unsigned n,float expand_factor=1.5):arr_list(Tarray,n,expand_factor){}
        /*����ջ*/
        ArrayStack& operator = (const ArrayStack& as){
            arr_list = as.arr_list;
            return *this;
        }
        ArrayStack& operator = (const Arraylist<T>& arr){
            arr_list = arr;
            return *this;
        }
        ArrayStack& copy(const T& Tarray,unsigned n){
            arr_list.copy(Tarray,n);
            return *this;
        }
        /*��������*/
        ~ArrayStack(){}
        /*������صĲ����Ͳ���*/
        bool empty() const{return arr_list.empty();}
        unsigned size() const{return arr_list.size();}
        unsigned capacity() const{return arr_list.capacity();}
        bool change_expand_factor(float new_expand_factor){
            arr_list.change_expand_factor(new_expand_factor);
            return true;
        }
        /*ȡ���Ѷ�Ԫ��*/
        T& top(){
            if(arr_list.empty()) throw "Stack is empty!";
            return arr_list[arr_list.size()-1];
        }
        const T& top() const{
            if(arr_list.empty()) throw "Stack is empty!";
            return arr_list[arr_list.size()-1];
        }
        /*�ѵ���ز���*/
        bool pop(){
            if(arr_list.empty()) return false;
            arr_list.eraseback();
            return true;
        }
        bool push(const T& theElement){
            arr_list.insertback(theElement);
            return true;
        }

    protected:
        Arraylist<T> arr_list;
    private:
};
}

#endif // ARRAYSTACK_H
