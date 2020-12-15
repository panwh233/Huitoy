#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H
#include "Queue.h"
#include "Arraylist.h"
#include "illegalParameterValue.h"
namespace Huitoy{
template <class T>
class ArrayQueue : public Queue<T>
{
    public:
        /*构造函数：*/
        ArrayQueue(unsigned initial_capacity=5,float expand_factor=1.5);//默认构造函数，可以指定初始容量和扩张因子
        ArrayQueue(const ArrayQueue& aq,float expand_factor=1.5);//复制构造函数
        ArrayQueue(const Arraylist<T>& arr,float expand_factor=1.5);//由Arraylist对象构造一个队列
        ArrayQueue(const T* Tarray,unsigned n,float expand_factor=1.5);//由T的数组构造一个队列
        /*复制其他的数组、队列*/
        ArrayQueue& operator = (const ArrayQueue& aq);
        ArrayQueue& operator = (const Arraylist<T>& arr);
        ArrayQueue& copy(const T* Tarray,unsigned n);
        /*析构函数*/
        ~ArrayQueue(){}
        /*数组相关的参数*/
        bool change_expand_factor(float new_expand_factor);
        unsigned capacity() const;
        unsigned listsize() const;
        /*队列相关的参数*/
        bool empty() const;
        unsigned size() const;
        /*取出队首和队尾的元素*/
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        /*队列操作：入队和出队*/
        bool pop();
        bool push(const T& theElement);/*ps:这个函数比较难写*/
    protected:
        /*存储数据的数组*/
        Arraylist<T> arr_list;
        /*入指针和出指针*/
        unsigned front_;
        unsigned back_;
        /*储存队列的长度*/
        unsigned size_;
    private:
};
/*构造函数：
1. 默认构造函数
*/
template <class T>
ArrayQueue<T>::ArrayQueue(unsigned initial_capacity,float expand_factor):arr_list(initial_capacity,expand_factor),front_(0),back_(0),size_(0){}
/*2.复制构造函数*/
template <class T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue& aq,float expand_factor):arr_list(aq.arr_list,expand_factor),front_(aq.front_),back_(aq.back_),size_(aq.size_){}
/*3.由Arraylist对象创建队列*/
template <class T>
ArrayQueue<T>::ArrayQueue(const Arraylist<T>& arr,float expand_factor):arr_list(arr,expand_factor),front_(0),back_(arr.size()),size_(arr.size()){}
/*4.由T的数组创建队列*/
template <class T>
ArrayQueue<T>::ArrayQueue(const T* Tarray,unsigned n,float expand_factor):arr_list(Tarray,n,expand_factor),front_(0),back_(n),size_(n){}
/*复制其他数组，队列*/
template <class T>
ArrayQueue<T>& ArrayQueue<T>::operator = (const ArrayQueue& aq){
    arr_list = aq.arr_list;
    front_ = aq.front_;
    back_ = aq.back_;
    size_ = aq.size_;
    return *this;
}
template <class T>
ArrayQueue<T>& ArrayQueue<T>::operator = (const Arraylist<T>& arr){
    arr_list = arr;
    front_ = 0;
    back_ = arr.size();
    size_ = arr.size();
}
template <class T>
ArrayQueue<T>& ArrayQueue<T>::copy(const T* Tarray,unsigned n){
    arr_list.copy(Tarray,n);
    front_ = 0;
    back_ = n;
    size_ = n;
}
/*数组相关的参数*/
template <class T>
bool ArrayQueue<T>::change_expand_factor(float new_expand_factor){
    return arr_list.change_expand_factor(new_expand_factor);
}
template <class T>
unsigned ArrayQueue<T>::capacity() const{
    return arr_list.capacity();
}
template <class T>
unsigned ArrayQueue<T>::listsize() const{
    return arr_list.size();
}
/*队列相关的参数*/
template <class T>
bool ArrayQueue<T>::empty() const{
    return size_==0;
}
template <class T>
unsigned ArrayQueue<T>::size() const{
    return size_;
}
/*取出队首和队尾的元素*/
template <class T>
T& ArrayQueue<T>::front(){
    if(empty()) throw "Queue is empty!";
    return arr_list[front_];
}
template <class T>
T& ArrayQueue<T>::back(){
    if(empty()) throw "Queue is empty!";
    unsigned index;
    if(back_==0) index = arr_list.size()-1;
    else index = back_ - 1;
    return arr_list[index];
}
template <class T>
const T& ArrayQueue<T>::front() const{
    if(empty()) throw "Queue is empty!";
    return arr_list[front_];
}
template <class T>
const T& ArrayQueue<T>::back() const{
    if(empty()) throw "Queue is empty!";
    unsigned index;
    if(back_==0) index = arr_list.size()-1;
    else index = back_ - 1;
    return arr_list[index];
}
/*队列操作：入队和出队*/
template <class T>
bool ArrayQueue<T>::pop(){
    if(empty()) return false;
    size_--;
    front_ = (front_+1)%arr_list.size();
    return true;
}
template <class T>
bool ArrayQueue<T>::push(const T& element){
    if(arr_list.size()==0){
    /*
    如果arr_list为空，那么size_一定为空，此时只需要往arr_list里面插入一个元素即可
    */
        arr_list.changeSize(5);
        arr_list.insert(0,element);
        front_ = 0;
        back_ = 1;
        size_ = 1;
        return true;
    }
    if(size_ == arr_list.size()){
    /*
    如果上一个条件不满足并且size_等于arr_list，说明在目前的数组容量下，队列已满，需要扩张，则按照arr_list的扩张因子进行扩张即可。
    采用有复制扩张方式，并且将从back_到size_-1的所有元素移到arr_list的最后面
    相应地，front_指针也要往后移动，计算公式是167行的代码
    */
        unsigned newsize = size_*arr_list.expandFactor();
        arr_list.changeSize(newsize);
        unsigned diff = newsize - size_;
        for(unsigned i=size_-1;i>=back_;i--){
            unsigned j = i+diff;
            arr_list[j] = arr_list[i];
            if(i==0) break;//之所以加上这个，是因为如果back_为0的话，i-1会导致数组越界
        }
        front_ = (back_ + newsize - size_)%arr_list.size();//front_指针的计算公式
        size_++;//size+1
        arr_list[back_] = element;
        back_++;//back_一定会小于newsize-1，因此只需要++不用取余数
        return true;
    }
    size_++;
    arr_list[back_] = element;
    back_ = (back_+1)%arr_list.size();
    return true;
}
}
#endif // ARRAYQUEUE_H
