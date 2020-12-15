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
        /*���캯����*/
        ArrayQueue(unsigned initial_capacity=5,float expand_factor=1.5);//Ĭ�Ϲ��캯��������ָ����ʼ��������������
        ArrayQueue(const ArrayQueue& aq,float expand_factor=1.5);//���ƹ��캯��
        ArrayQueue(const Arraylist<T>& arr,float expand_factor=1.5);//��Arraylist������һ������
        ArrayQueue(const T* Tarray,unsigned n,float expand_factor=1.5);//��T�����鹹��һ������
        /*�������������顢����*/
        ArrayQueue& operator = (const ArrayQueue& aq);
        ArrayQueue& operator = (const Arraylist<T>& arr);
        ArrayQueue& copy(const T* Tarray,unsigned n);
        /*��������*/
        ~ArrayQueue(){}
        /*������صĲ���*/
        bool change_expand_factor(float new_expand_factor);
        unsigned capacity() const;
        unsigned listsize() const;
        /*������صĲ���*/
        bool empty() const;
        unsigned size() const;
        /*ȡ�����׺Ͷ�β��Ԫ��*/
        T& front();
        const T& front() const;
        T& back();
        const T& back() const;
        /*���в�������Ӻͳ���*/
        bool pop();
        bool push(const T& theElement);/*ps:��������Ƚ���д*/
    protected:
        /*�洢���ݵ�����*/
        Arraylist<T> arr_list;
        /*��ָ��ͳ�ָ��*/
        unsigned front_;
        unsigned back_;
        /*������еĳ���*/
        unsigned size_;
    private:
};
/*���캯����
1. Ĭ�Ϲ��캯��
*/
template <class T>
ArrayQueue<T>::ArrayQueue(unsigned initial_capacity,float expand_factor):arr_list(initial_capacity,expand_factor),front_(0),back_(0),size_(0){}
/*2.���ƹ��캯��*/
template <class T>
ArrayQueue<T>::ArrayQueue(const ArrayQueue& aq,float expand_factor):arr_list(aq.arr_list,expand_factor),front_(aq.front_),back_(aq.back_),size_(aq.size_){}
/*3.��Arraylist���󴴽�����*/
template <class T>
ArrayQueue<T>::ArrayQueue(const Arraylist<T>& arr,float expand_factor):arr_list(arr,expand_factor),front_(0),back_(arr.size()),size_(arr.size()){}
/*4.��T�����鴴������*/
template <class T>
ArrayQueue<T>::ArrayQueue(const T* Tarray,unsigned n,float expand_factor):arr_list(Tarray,n,expand_factor),front_(0),back_(n),size_(n){}
/*�����������飬����*/
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
/*������صĲ���*/
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
/*������صĲ���*/
template <class T>
bool ArrayQueue<T>::empty() const{
    return size_==0;
}
template <class T>
unsigned ArrayQueue<T>::size() const{
    return size_;
}
/*ȡ�����׺Ͷ�β��Ԫ��*/
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
/*���в�������Ӻͳ���*/
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
    ���arr_listΪ�գ���ôsize_һ��Ϊ�գ���ʱֻ��Ҫ��arr_list�������һ��Ԫ�ؼ���
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
    �����һ�����������㲢��size_����arr_list��˵����Ŀǰ�����������£�������������Ҫ���ţ�����arr_list���������ӽ������ż��ɡ�
    �����и������ŷ�ʽ�����ҽ���back_��size_-1������Ԫ���Ƶ�arr_list�������
    ��Ӧ�أ�front_ָ��ҲҪ�����ƶ������㹫ʽ��167�еĴ���
    */
        unsigned newsize = size_*arr_list.expandFactor();
        arr_list.changeSize(newsize);
        unsigned diff = newsize - size_;
        for(unsigned i=size_-1;i>=back_;i--){
            unsigned j = i+diff;
            arr_list[j] = arr_list[i];
            if(i==0) break;//֮���Լ������������Ϊ���back_Ϊ0�Ļ���i-1�ᵼ������Խ��
        }
        front_ = (back_ + newsize - size_)%arr_list.size();//front_ָ��ļ��㹫ʽ
        size_++;//size+1
        arr_list[back_] = element;
        back_++;//back_һ����С��newsize-1�����ֻ��Ҫ++����ȡ����
        return true;
    }
    size_++;
    arr_list[back_] = element;
    back_ = (back_+1)%arr_list.size();
    return true;
}
}
#endif // ARRAYQUEUE_H
