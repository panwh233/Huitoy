#include "illegalParameterValue.h"
#include "Linearlist.h"
#include "ArraylistIterator.h"
#ifndef ARRAYLIST_H
#define ARRAYLIST_H
namespace Huitoy{
template <class T>
class Arraylist:public Linearlist<T>{
    public:
        /*Arraylist的构造函数*/
        Arraylist(unsigned initial_Capacity=5,float expand_factor=1.5);
        Arraylist(const T& element_,unsigned n,float expand_factor=1.5);
        Arraylist(const Arraylist& arr,float expand_factor=1.5);
        Arraylist(Arraylist&& arr,float expand_factor=1.5) noexcept;
        Arraylist(const T* Tarray,unsigned n,float expand_factor=1.5);
        Arraylist(const initializer_list<T>& init_list,float expand_factor=1.5);
        Arraylist(const LinearlistView<T>& view,float expand_factor=1.5);
        Arraylist(const ConstLinearlistView<T>& view,float expand_factor=1.5);
        Arraylist(const Linearlist<T>& theLinearList,float expand_factor=1.5);
        /*Arraylist的析构函数*/
        ~Arraylist();
        /*Arraylist的相关参数*/
        bool change_expand_factor(float new_expand_facotr);
        void changeSize(unsigned newSize,bool copy_=true);
        float expandFactor();
        bool empty() const;
        unsigned size() const;
        unsigned capacity() const;
        /*清空Arraylist*/
        void clear();
        /*索引*/
        T& operator[] (unsigned index);
        const T& operator[] (unsigned index) const;
        /*按照元素找索引*/
        unsigned search(const T& element) const;
        /*删除元素*/
        void erase(unsigned index);
        void eraseback();
        void erasefront();
        /*插入元素*/
        void insert(unsigned index,const T& element);
        void insertback(const T& element);
        void insertfront(const T& element);
        /*合并两个数组*/
        void merge(const Arraylist& arr);
        void merge(const T* Tarray,unsigned n);
        void merge(const initializer_list<T>& init_list);
        void merge(const LinearlistView<T>& view);
        void merge(const ConstLinearlistView<T>& view);
        void merge(const Linearlist<T>& theLinearlist);
        /*数组赋值和复制*/
        Arraylist& operator = (const Arraylist& arr);
        Arraylist& operator = (Arraylist&& arr) noexcept;
        Arraylist& operator = (const LinearlistView<T>& view);
        Arraylist& operator = (const ConstLinearlistView<T>& view);
        Arraylist& operator = (const Linearlist<T>& theLinearlist);
        Arraylist& operator = (const initializer_list<T>& init_list);
        Arraylist& copy(const T* Tarray,unsigned n);
        /*创建线性表视图*/
        LinearlistView<T> createView();
        ConstLinearlistView<T> createConstView() const;
        ConstLinearlistView<T> createView() const;
        /*取子串*/
        LinearlistView<T> sublist(unsigned start_,unsigned end_);
        ConstLinearlistView<T> sublist(unsigned start_,unsigned end_) const;
        /*迭代器*/
        ArrayListIterator<T> begin();
        ArrayListIterator<T> end();
        ConstArrayListIterator<T> begin() const;
        ConstArrayListIterator<T> end() const;
    protected:
        T* element;
        float expand_factor;
        unsigned listSize;
        unsigned listCapacity;
        void changeLength(unsigned newCapacity,bool copy_ = true);
    private:
};
/*构造函数的实现*/
template <class T>
Arraylist<T>::Arraylist(unsigned initial_Capacity,float new_expand_factor){
    if(new_expand_factor<=1){
        throw illegalParameterValue("expand factor must be larger than 1.");
    }
    expand_factor = new_expand_factor;
    if(initial_Capacity==0){
        listCapacity=0;
        listSize =0;
        element=nullptr;
        return;
    }
    element = new T[initial_Capacity];
    listCapacity = initial_Capacity;
    listSize = 0;
}
template <class T>
Arraylist<T>::Arraylist(const Arraylist& arr,float new_expand_factor){
    if(new_expand_factor<=1){
        throw illegalParameterValue("expand factor must be larger than 1.");
    }
    expand_factor = new_expand_factor;
    if (arr.listCapacity == 0){
        listCapacity = 0;
        listSize = 0;
        element = nullptr;
        return;
    }
    element = new T[arr.listCapacity];
    listCapacity = arr.listCapacity;
    listSize = arr.listSize;
    for(unsigned i=0;i<listSize;i++){
        element[i] = arr[i];
    }
}
template <class T>
Arraylist<T>::Arraylist(Arraylist&& arr,float new_expand_factor) noexcept{
    if(new_expand_factor<=1) throw illegalParameterValue("Expand factor must be larger than 1.");
    element = arr.element;
    arr.element = nullptr;
    listCapacity = arr.listCapacity;
    arr.listCapacity = 0;
    listSize = arr.listSize;
    arr.listSize = 0;
}
template <class T>
Arraylist<T>::Arraylist(const T& element_,unsigned n,float new_expand_factor){
    if(new_expand_factor<=1){
        throw illegalParameterValue("expand factor must be larger than 1.");
    }
    expand_factor = new_expand_factor;
    listCapacity = expand_factor*n;
    listSize = n;
    element = new T[listCapacity];
    for(unsigned i=0;i<n;i++){
        element[i] = element_;
    }
}
template <class T>
Arraylist<T>::Arraylist(const T* Tarray,unsigned n,float new_expand_factor){
    if(new_expand_factor<=1){
        throw illegalParameterValue("expand factor must be larger than 1.");
    }
    expand_factor = new_expand_factor;
    listCapacity = expand_factor*n;
    listSize = n;
    element = new T[listCapacity];
    for(unsigned i=0;i<n;i++){
        element[i] = Tarray[i];
    }
}
template <class T>
Arraylist<T>::Arraylist(const initializer_list<T>& init_list,float new_expand_factor){
    if(new_expand_factor<=1){
        throw illegalParameterValue("expand factor must be larger than 1.");
    }
    expand_factor = new_expand_factor;
    listSize = init_list.size();
    listCapacity = listSize*expand_factor;
    if(listCapacity==0){
        element = nullptr;
    }else{
        element = new T[listCapacity];
        unsigned i=0;
        for(const T& element_:init_list){
            element[i] = element_;
            i++;
        }
    }
}
template <class T>
Arraylist<T>::Arraylist(const LinearlistView<T>& view,float new_expand_factor){
    if(new_expand_factor<=1){
        throw illegalParameterValue("expand factor must be larger than 1.");
    }
    expand_factor = new_expand_factor;
    listSize = view.size();
    listCapacity = view.capacity();
    if(listCapacity>0) element = new T[listCapacity];
    else element = nullptr;
    for(unsigned i=0;i<listSize;i++){
        element[i] = view[i];
    }
}
template <class T>
Arraylist<T>::Arraylist(const ConstLinearlistView<T>& view,float new_expand_factor){
    if(new_expand_factor<=1){
        throw illegalParameterValue("expand factor must be larger than 1.");
    }
    expand_factor = new_expand_factor;
    listSize = view.size();
    listCapacity = view.capacity();
    if(listCapacity>0) element = new T[listCapacity];
    else element = nullptr;
    for(unsigned i=0;i<listSize;i++){
        element[i] = view[i];
    }
}
template <class T>
Arraylist<T>::Arraylist(const Linearlist<T>& theLinearlist,float new_expand_factor){
    if(new_expand_factor<=1){
        throw illegalParameterValue("expand factor must be larger than 1.");
    }
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    expand_factor = new_expand_factor;
    listSize = view.size();
    listCapacity = view.capacity();
    if(listCapacity>0) element = new T[listCapacity];
    else element = nullptr;
    for(unsigned i=0;i<listSize;i++){
        element[i] = view[i];
    }
}
/*析构函数的实现*/
template <class T>
Arraylist<T>::~Arraylist(){
    if(listCapacity>0){
        delete[] element;
    }
}
/*清空数组*/
template <class T>
void Arraylist<T>::clear(){
    if(listCapacity>0){
        delete[] element;
    }
    listSize=0;
    listCapacity=0;
    element = nullptr;
}
/*改变数组的扩张因子*/
template <class T>
bool Arraylist<T>::change_expand_factor(float new_expand_factor){
    if(new_expand_factor<=1){
        return false;
    }
    expand_factor = new_expand_factor;
    return true;
}
/*改变数组的长度*/
template <class T>
void Arraylist<T>::changeLength(unsigned newCapacity,bool copy_){
    if (newCapacity == listCapacity){
        //情形1：如果新长度和原来的长度相等，那么不做任何操作
        return;
    }
    if (newCapacity == 0) {
        //情形2：如果新长度为0，说明我们要清空数组，则直接删掉element，然后让listCapacity和listSize都为0
        delete[] element;
        element = nullptr;
        listCapacity = 0;
        listSize = 0;
        return;
    }
    //否则，则是newCapacity和oldCapacity不等
    T* temp = new T[newCapacity];
    if(copy_){//如果采用copy模式，则将原数组中有意义的元素复制到型数组中
        for(unsigned i = 0;i<listSize&&i<newCapacity;i++){
            temp[i] = element[i];
        }
    }
    //如果老数组长度大于0，则将老数组释放掉
    if (listCapacity > 0) delete element;
    //接下来求listSize，如果listSize比newCapacity要大，说明原来的元素有删减，否则只用改变listCapacity，不用改变listSize
    if (listSize>= newCapacity){
        listSize = newCapacity;
        listCapacity = newCapacity;
    }else{
        listCapacity = newCapacity;
    }
    element = temp;
}
/*数组参数*/
template <class T>
float Arraylist<T>::expandFactor(){
    return expand_factor;
}
template <class T>
void Arraylist<T>::changeSize(unsigned newSize,bool copy_){
    if(newSize>listCapacity) changeLength(newSize*expand_factor,copy_);
    listSize = newSize;
}
template <class T>
bool Arraylist<T>::empty() const{
    if (listSize == 0) return true;
    else return false;
}
template <class T>
unsigned Arraylist<T>::size() const{
    return listSize;
}
template <class T>
unsigned Arraylist<T>::capacity() const{
    return listCapacity;
}
/*数组索引*/
template<class T>
T& Arraylist<T>::operator[] (unsigned index){
    if(index >= listSize){
        throw illegalParameterValue("index out of range.");
    }
    return element[index];
}
template<class T>
const T& Arraylist<T>::operator[] (unsigned index) const{
    if(index >= listSize){
        throw illegalParameterValue("index out of range.");
    }
    return element[index];
}
/*按元素搜索索引*/
template <class T>
unsigned Arraylist<T>::search(const T& element_)const{
    if(listSize == 0){
        return 0;
    }else{
        for(unsigned i = 0;i<listSize;i++){
            if(element[i]==element_) return i;
        }
        return listSize;
    }
}
/*从数组中删掉一个元素*/
template <class T>
void Arraylist<T>::erase(unsigned index){
    if (index >= listSize){
        throw illegalParameterValue("index out of range.");
    }
    for(unsigned i=index+1;i<listSize;i++){
        element[i-1] = element[i];
    }
    listSize--;
    if(listSize == 0){
        changeLength(0);
    }
    if(listSize < listCapacity/4){
        changeLength(listCapacity/2);
    }
}
template <class T>
void Arraylist<T>::eraseback(){
    erase(listSize-1);
}
template <class T>
void Arraylist<T>::erasefront(){
    erase(0);
}
/*从数组中插入一个元素*/
template <class T>
void Arraylist<T>::insert(unsigned index,const T& element_){
    if (index > listSize){
        throw illegalParameterValue("index out of range.");
    }
    if (listCapacity == 0){
        element = new T[5];
        listCapacity =5;
        listSize = 0;
    }
    if (listSize == listCapacity){
        unsigned new_size = expand_factor*listCapacity;
        changeLength(new_size);
    }
    if (index == listSize){
        element[index] = element_;
        listSize++;
        return;
    }
    if (index < listSize){
        for(unsigned i = listSize-1;i>=index;i--){
            element[i+1] = element[i];
            if(i==0) break;
        }
        element[index] = element_;
        listSize++;
    }
}
template <class T>
void Arraylist<T>::insertfront(const T& element_){
    insert(0,element_);
}
template <class T>
void Arraylist<T>::insertback(const T& element_){
    if (listCapacity == 0){
        element = new T[5];
        listCapacity =5;
        listSize = 0;
    }
    if (listSize == listCapacity){
        unsigned new_size = expand_factor*listCapacity;
        changeLength(new_size);
    }
    element[listSize] = element_;
    listSize++;
}
/*复制数组*/
template <class T>
Arraylist<T>& Arraylist<T>::operator = (const Arraylist& arr){
    if(listCapacity < arr.listCapacity){
        changeLength(arr.listCapacity);
    }
    if(listCapacity == 0){
        return *this;
    }
    listSize = arr.listSize;
    if(listSize == 0) return *this;
    for(unsigned i = 0;i<arr.listSize;i++){
        element[i] = arr.element[i];
    }
    return *this;
}
template <class T>
Arraylist<T>& Arraylist<T>::operator = (Arraylist&& arr) noexcept{
    clear();
    element = arr.element;
    arr.element = nullptr;
    listSize = arr.listSize;
    arr.listSize = 0;
    listCapacity = arr.listCapacity;
    arr.listCapacity = 0;
    return *this;
}
template <class T>
Arraylist<T>& Arraylist<T>::operator = (const LinearlistView<T>& view){
    clear();
    listSize = view.size();
    listCapacity = view.capacity();
    if(listCapacity>0) element = new T[listCapacity];
    else element = nullptr;
    for(unsigned i=0;i<listSize;i++){
        element[i] = view[i];
    }
    return *this;
}
template <class T>
Arraylist<T>& Arraylist<T>::operator = (const ConstLinearlistView<T>& view){
    clear();
    listSize = view.size();
    listCapacity = view.capacity();
    if(listCapacity>0) element = new T[listCapacity];
    else element = nullptr;
    for(unsigned i=0;i<listSize;i++){
        element[i] = view[i];
    }
    return *this;
}
template <class T>
Arraylist<T>& Arraylist<T>::operator = (const Linearlist<T>& theLinearlist){
    clear();
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    listSize = view.size();
    listCapacity = view.capacity();
    if(listCapacity>0) element = new T[listCapacity];
    else element = nullptr;
    for(unsigned i=0;i<listSize;i++){
        element[i] = view[i];
    }
    return *this;
}
template <class T>
Arraylist<T>& Arraylist<T>::copy(const T* Tarray,unsigned n){
    if(listCapacity < n){
        changeLength(n,false);
    }
    listSize = n;
    if(listSize==0) return *this;
    for(unsigned i=0;i<n;i++){
        element[i] = Tarray[i];
    }
    return *this;
}
template <class T>
Arraylist<T>& Arraylist<T>::operator = (const initializer_list<T>& init_list){
    unsigned newSize = init_list.size();
    if(listCapacity<newSize){
        changeLength(newSize,false);
    }
    listSize = newSize;
    if(listSize==0) return *this;
    unsigned index = 0;
    for(const T& element_:init_list){
        element[index] = element_;
        index++;
    }
    return *this;
}
/*合并数组*/
template <class T>
void Arraylist<T>::merge(const Arraylist& arr){
    if(listSize + arr.listSize > listCapacity){
        changeLength(expand_factor*(listSize+arr.listSize));
    }
    for(unsigned i=listSize;i<listSize+arr.listSize;i++){
        element[i] = arr.element[i-listSize];
    }
    listSize = listSize+arr.listSize;
}
template<class T>
void Arraylist<T>::merge(const T* Tptr,unsigned n){
    if(listSize+n>listCapacity){
        changeLength(expand_factor*(listSize+n));
    }
    for(unsigned i = listSize;i<listSize+n;i++){
        element[i] = Tptr[i-listSize];
    }
    listSize = listSize+n;
}
template <class T>
void Arraylist<T>::merge(const initializer_list<T>& init_list){
    unsigned n = init_list.size();
    if(listSize+n>listCapacity){
        changeLength(expand_factor*(listSize+n));
    }
    unsigned index = listSize;
    for(const T& element_:init_list){
        element[index] = element_;
        index++;
    }
    listSize+=n;
}
template <class T>
void Arraylist<T>::merge(const LinearlistView<T>& view){
    if(listSize + view.size() > listCapacity){
        changeLength(expand_factor*(listSize+view.size()));
    }
    for(unsigned i=listSize;i<listSize+view.size();i++){
        element[i] = view[i-listSize];
    }
    listSize+= view.size();
}
template <class T>
void Arraylist<T>::merge(const ConstLinearlistView<T>& view){
    if(listSize + view.size() > listCapacity){
        changeLength(expand_factor*(listSize+view.size()));
    }
    for(unsigned i=listSize;i<listSize+view.size();i++){
        element[i] = view[i-listSize];
    }
    listSize+= view.size();
}
template <class T>
void Arraylist<T>::merge(const Linearlist<T>& theLinearlist){
    ConstLinearlistView<T> view = theLinearlist.createConstView();
    if(listSize + view.size() > listCapacity){
        changeLength(expand_factor*(listSize+view.size()));
    }
    for(unsigned i=listSize;i<listSize+view.size();i++){
        element[i] = view[i-listSize];
    }
    listSize+= view.size();
}
/*数组迭代器*/
template <class T>
ArrayListIterator<T> Arraylist<T>::begin(){
    return ArrayListIterator<T>(element);
}

template <class T>
ArrayListIterator<T> Arraylist<T>::end(){
    return ArrayListIterator<T>(element+listSize);
}

template <class T>
ConstArrayListIterator<T> Arraylist<T>::begin() const{
    return ConstArrayListIterator<T>(element);

}
template <class T>
ConstArrayListIterator<T> Arraylist<T>::end() const{
    return ConstArrayListIterator<T>(element+listSize);
}
/*创建视图*/
template <class T>
LinearlistView<T> Arraylist<T>::createView(){
    return LinearlistView<T>(element,listSize);
}
template <class T>
ConstLinearlistView<T> Arraylist<T>::createView() const{
    return ConstLinearlistView<T>(element,listSize);
}
template <class T>
ConstLinearlistView<T> Arraylist<T>::createConstView() const{
    return ConstLinearlistView<T>(element,listSize);
}
/*创建子串*/
template <class T>
LinearlistView<T> Arraylist<T>::sublist(unsigned begin_,unsigned end_){
    if(begin_>end_||begin_>=listSize||end_>=listSize) throw illegalParameterValue("illegal parameter: begin>end Or Index out of range!");
    unsigned viewsize = end_-begin_+1;
    LinearlistView<T> result(viewsize);
    result.changeSize(viewsize,false);
    for(unsigned i=begin_;i<=end_;i++){
        result(i-begin_) = element+i;
    }
    return result;
}
template <class T>
ConstLinearlistView<T> Arraylist<T>::sublist(unsigned begin_,unsigned end_) const{
    if(begin_>end_||begin_>=listSize||end_>=listSize) throw illegalParameterValue("illegal parameter: begin>end Or Index out of range!");
    unsigned viewsize = end_-begin_+1;
    ConstLinearlistView<T> result(viewsize);
    result.changeSize(viewsize,false);
    for(unsigned i=begin_;i<=end_;i++){
        result(i-begin_) = element+i;
    }
    return result;
}
}

#endif // ARRAYLIST_H
