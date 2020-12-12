#include "LinearlistViewIterator.h"
#include "illegalParameterValue.h"
#ifndef LINEARLISTVIEW_H
#define LINEARLISTVIEW_H
namespace Huitoy{
template <class T>
class LinearlistView
{
    public:
        /*构造函数*/
        LinearlistView(unsigned initial_capacity=5,float expand_factor=1.5);
        LinearlistView(const LinearlistView& view,float expand_factor=1.5);
        LinearlistView(LinearlistView&& view,float expand_factor=1.5) noexcept;
        LinearlistView(T* Tarray,unsigned n,float expand_factor=1.5);
        LinearlistView(T** Tpointer_array,unsigned n,float expand_factor=1.5);
        /*析构函数*/
        virtual ~LinearlistView();
        /*视图相关参数*/
        bool change_expand_factor(float new_expand_facotr);
        void changeSize(unsigned newSize,bool copy_=true);
        float expandFactor();
        bool empty() const;
        unsigned size() const;
        unsigned capacity() const;
        /*清空视图*/
        void clear();
        /*索引*/
        T& operator[] (unsigned index) const;
        T*& operator() (unsigned index);
        /*按照元素找索引*/
        unsigned search(const T& element) const;
        /*删除元素*/
        void erase(unsigned index);
        void eraseback();
        void erasefront();
        /*插入元素*/
        void insert(unsigned index,T* const& element);
        void insertback(T* const& element);
        void insertfront(T* const& element);
        /*视图的赋值*/
        LinearlistView& operator = (const LinearlistView& view);
        LinearlistView& operator = (LinearlistView&& view) noexcept;
        LinearlistView& copy(T* Tarray,unsigned n);
        LinearlistView& copy(T** Tpointer_array,unsigned n);
        /*视图的遍历*/
        LinearlistViewIterator<T> begin() const;
        LinearlistViewIterator<T> end() const;
    protected:
        T** pointer_array;
        unsigned listCapacity;
        unsigned listSize;
        float expand_factor;
        void changeLength(unsigned newCapacity,bool copy_ = true);
};
/*构造函数*/
template <class T>
LinearlistView<T>::LinearlistView(unsigned initial_capacity,float new_expand_factor){
    if(new_expand_factor<=1) throw illegalParameterValue("Expand factor must be larger than 1.");
    else{
        expand_factor = new_expand_factor;
        if(initial_capacity==0){
            pointer_array = nullptr;
            listSize=0;
            listCapacity=0;
        }else{
            pointer_array = new T*[initial_capacity];
            listSize=0;
            listCapacity = initial_capacity;
        }
    }
}
template <class T>
LinearlistView<T>::LinearlistView(const LinearlistView& view,float new_expand_factor){
    if(new_expand_factor<=1) throw illegalParameterValue("Expand factor must  be larger than 1.");
    else{
        expand_factor=new_expand_factor;
        listCapacity = view.listCapacity;
        listSize = view.listSize;
        if(listCapacity==0){
            pointer_array = nullptr;
        }else{
            pointer_array = new T*[listCapacity];
            for(unsigned i=0;i<listSize;i++){
                pointer_array[i] = view.pointer_array[i];
            }
        }
    }
}
template <class T>
LinearlistView<T>::LinearlistView(T** Tarray,unsigned n,float new_expand_factor){
    if(new_expand_factor<=1) throw illegalParameterValue("Expand factor must be larger than 1!");
    expand_factor = new_expand_factor;
    listSize = n;
    listCapacity = n*expand_factor;
    if(n==0){
        pointer_array = nullptr;
    }else{
        pointer_array = new T*[listCapacity];
        for(unsigned i=0;i<n;i++){
            pointer_array[i] = Tarray[i];
        }
    }
}
template <class T>
LinearlistView<T>::LinearlistView(T* Tarray,unsigned n,float new_expand_factor){
    if(new_expand_factor<=1) throw illegalParameterValue("Expand factor must be larger than 1!");
    expand_factor = new_expand_factor;
    listSize=n;
    listCapacity = n*expand_factor;
    if(n==0){
        pointer_array = nullptr;
    }else{
        pointer_array = new T*[listCapacity];
        for(unsigned i=0;i<n;i++){
            pointer_array[i] = Tarray+i;
        }
    }
}
template <class T>
LinearlistView<T>::LinearlistView(LinearlistView&& view,float new_expand_factor) noexcept{
    if(new_expand_factor<=1) expand_factor = 1.5;
    else expand_factor = new_expand_factor;
    pointer_array = view.pointer_array;
    view.pointer_array = nullptr;
    listSize = view.listSize;
    view.listSize = 0;
    listCapacity = view.listCapacity;
    view.listCapacity = 0;
}
/*析构函数*/
template <class T>
LinearlistView<T>::~LinearlistView(){
    if(listCapacity>=1) delete[] pointer_array;
}
/*线性表视图的相关参数*/
template <class T>
bool LinearlistView<T>::change_expand_factor(float new_expand_factor){
    if(listCapacity<=1) return false;
    else{
        expand_factor = new_expand_factor;
    }
}
template <class T>
void LinearlistView<T>::changeLength(unsigned newCapacity,bool copy_){
    if (newCapacity == listCapacity){
        //情形1：如果新长度和原来的长度相等，那么不做任何操作
        return;
    }
    if (newCapacity == 0) {
        //情形2：如果新长度为0，说明我们要清空数组，则直接删掉element，然后让listCapacity和listSize都为0
        delete[] pointer_array;
        pointer_array = nullptr;
        listCapacity = 0;
        listSize = 0;
        return;
    }
    //否则，则是newCapacity和oldCapacity不等
    T** temp = new T*[newCapacity];
    if(copy_){//如果采用copy模式，则将原数组中有意义的元素复制到型数组中
        for(unsigned i = 0;i<listSize&&i<newCapacity;i++){
            temp[i] = pointer_array[i];
        }
    }
    //如果老数组长度大于0，则将老数组释放掉
    if (listCapacity > 0) delete pointer_array;
    //接下来求listSize，如果listSize比newCapacity要大，说明原来的元素有删减，否则只用改变listCapacity，不用改变listSize
    if (listSize>= newCapacity){
        listSize = newCapacity;
        listCapacity = newCapacity;
    }else{
        listCapacity = newCapacity;
    }
    pointer_array = temp;
}
template <class T>
void LinearlistView<T>::changeSize(unsigned newSize,bool copy_){
    if(newSize>listCapacity) changeLength(newSize*expand_factor,copy_);
    listSize = newSize;
}
template <class T>
bool LinearlistView<T>::empty() const{
    if (listSize == 0) return true;
    else return false;
}
template <class T>
unsigned LinearlistView<T>::size() const{
    return listSize;
}
template <class T>
unsigned LinearlistView<T>::capacity() const{
    return listCapacity;
}

template <class T>
void LinearlistView<T>::clear(){
    if(listCapacity>0) delete[] pointer_array;
    listCapacity=0;
    listSize=0;
}
template <class T>
T& LinearlistView<T>::operator [](unsigned index) const{
    if(index>=listSize) throw "Index out of range!";
    return *(pointer_array[index]);
}
template <class T>
T*& LinearlistView<T>::operator()(unsigned index){
    if(index>=listSize) throw illegalParameterValue("Index out of range!");
    return pointer_array[index];
}
template <class T>
unsigned LinearlistView<T>::search(const T& element) const{
    unsigned result=0;
    while(result < listSize){
        if(*(pointer_array[result]) == element) return result;
        result++;
    }
    return result;
}
/*从视图中删掉一个元素*/
template <class T>
void LinearlistView<T>::erase(unsigned index){
    if (index >= listSize){
        throw illegalParameterValue("index out of range.");
    }
    for(unsigned i=index+1;i<listSize;i++){
        pointer_array[i-1] = pointer_array[i];
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
void LinearlistView<T>::eraseback(){
    erase(listSize-1);
}
template <class T>
void LinearlistView<T>::erasefront(){
    erase(0);
}
/*从视图中插入一个元素*/
template <class T>
void LinearlistView<T>::insert(unsigned index,T* const& element_){
    if (index > listSize){
        throw illegalParameterValue("index out of range.");
    }
    if (listCapacity == 0){
        pointer_array = new T*[5];
        listCapacity =5;
        listSize = 0;
    }
    if (listSize == listCapacity){
        unsigned new_size = expand_factor*listCapacity;
        changeLength(new_size);
    }
    if (index == listSize){
        pointer_array[index] = element_;
        listSize++;
        return;
    }
    if (index < listSize){
        for(unsigned i = listSize-1;i>=index;i--){
            pointer_array[i+1] = pointer_array[i];
            if(i==0) break;
        }
        pointer_array[index] = element_;
        listSize++;
    }
}
template <class T>
void LinearlistView<T>::insertfront(T* const& element_){
    insert(0,element_);
}
template <class T>
void LinearlistView<T>::insertback(T* const& element_){
    if (listCapacity == 0){
        pointer_array = new T*[5];
        listCapacity =5;
        listSize = 0;
    }
    if (listSize == listCapacity){
        unsigned new_size = expand_factor*listCapacity;
        changeLength(new_size);
    }
    pointer_array[listSize] = element_;
    listSize++;
}
template <class T>
LinearlistView<T>& LinearlistView<T>::operator = (const LinearlistView& view){
    listCapacity = view.listCapacity;
    listSize = view.listSize;
    pointer_array = new T*[listCapacity];
    for(unsigned i=0;i<listSize;i++){
        pointer_array[i] = view.pointer_array[i];
    }
    return *this;
}
template <class T>
LinearlistView<T>& LinearlistView<T>::operator = (LinearlistView&& view) noexcept{
    clear();
    listCapacity = view.listCapacity;
    view.listCapacity = 0;
    pointer_array = view.pointer_array;
    view.pointer_array = nullptr;
    listSize = view.listSize;
    view.listSize = 0;
    return *this;
}
template <class T>
LinearlistView<T>& LinearlistView<T>::copy(T* Tarray,unsigned n){
    clear();
    listSize=n;
    listCapacity = n*expand_factor;
    if(n==0){
        pointer_array = nullptr;
    }else{
        pointer_array = new T*[listCapacity];
        for(unsigned i=0;i<n;i++){
            pointer_array[i] = Tarray+i;
        }
    }
}
template <class T>
LinearlistView<T>& LinearlistView<T>::copy(T** Tpointer_array,unsigned n){
    clear();
    listSize = n;
    listCapacity = n*expand_factor;
    if(n==0){
        pointer_array = nullptr;
    }else{
        pointer_array = new T*[listCapacity];
        for(unsigned i=0;i<n;i++){
            pointer_array[i] = Tpointer_array[i];
        }
    }
}
template <class T>
LinearlistViewIterator<T> LinearlistView<T>::begin() const{
    return LinearlistViewIterator<T>(pointer_array);
}
template <class T>
LinearlistViewIterator<T> LinearlistView<T>::end() const{
    return LinearlistViewIterator<T>(pointer_array+listSize);
}

template <class T>
class ConstLinearlistView{
    public:
        /*构造函数*/
        ConstLinearlistView(unsigned inital_capacity=5,float expand_factor=1.5);
        ConstLinearlistView(const LinearlistView<T>& view,float expand_factor=1.5);
        ConstLinearlistView(const ConstLinearlistView& view,float expand_factor=1.5);
        ConstLinearlistView(ConstLinearlistView&& view,float expand_factor=1.5) noexcept;
        ConstLinearlistView(T** Tpointer_array,unsigned n,float expand_factor=1.5);
        ConstLinearlistView(const T** Tpointer_array,unsigned n,float expand_factor=1.5);
        ConstLinearlistView(const T* Tarray,unsigned n,float expand_factor=1.5);
        /*析构函数*/
        virtual ~ConstLinearlistView();
        /*视图相关参数*/
        bool change_expand_factor(float new_expand_facotr);
        void changeSize(unsigned newSize,bool copy_=true);
        float expandFactor();
        bool empty() const;
        unsigned size() const;
        unsigned capacity() const;
        /*清空视图*/
        void clear();
        /*索引*/
        const T& operator[] (unsigned index) const;
        const T*& operator() (unsigned index);
        /*按照元素找索引*/
        unsigned search(const T& element) const;
        /*删除元素*/
        void erase(unsigned index);
        void eraseback();
        void erasefront();
        /*插入元素*/
        void insert(unsigned index,const T* const & element);
        void insertback(const T* const & element);
        void insertfront(const T* const & element);
        /*视图的赋值*/
        ConstLinearlistView& operator = (const LinearlistView<T>& view);
        ConstLinearlistView& operator = (const ConstLinearlistView& view);
        ConstLinearlistView& operator = (ConstLinearlistView&& view) noexcept;
        ConstLinearlistView& copy(const T** Tpointer_array,unsigned n);
        ConstLinearlistView& copy(T** Tpointer_array,unsigned n);
        ConstLinearlistView& copy(const T* Tarray,unsigned n);
        /*视图的遍历*/
        ConstLinearlistViewIterator<T> begin() const;
        ConstLinearlistViewIterator<T> end() const;
    protected:
        const T** pointer_array;
        unsigned listCapacity;
        unsigned listSize;
        float expand_factor;
        void changeLength(unsigned newLength,bool copy_ = true);
};

/*构造函数*/
/*构造函数1：默认构造函数*/
template <class T>
ConstLinearlistView<T>::ConstLinearlistView(unsigned initial_capacity,float new_expand_factor){
    if(new_expand_factor<=1) throw "Expand factor must be larger than 1.";
    else{
        expand_factor = new_expand_factor;
        if(initial_capacity==0){
            pointer_array = nullptr;
            listSize=0;
            listCapacity=0;
        }else{
            pointer_array = new const T*[initial_capacity];
            listSize=0;
            listCapacity = initial_capacity;
        }
    }
}
/*构造函数2：用LinearlistView初始化ConstLinearlistView*/
template <class T>
ConstLinearlistView<T>::ConstLinearlistView(const LinearlistView<T>& view,float new_expand_factor){
    if(new_expand_factor<=1) throw "Expand factor must  be larger than 1.";
    else{
        expand_factor=new_expand_factor;
        listCapacity = view.listCapacity;
        listSize = view.listSize;
        if(listCapacity==0){
            pointer_array = nullptr;
        }else{
            pointer_array = new const T*[listCapacity];
            for(unsigned i=0;i<listSize;i++){
                pointer_array[i] = view(i);
            }
        }
    }
}
/*构造函数3：复制构造函数*/
template <class T>
ConstLinearlistView<T>::ConstLinearlistView(const ConstLinearlistView& view,float new_expand_factor){
    if(new_expand_factor<=1) throw "Expand factor must  be larger than 1.";
    else{
        expand_factor=new_expand_factor;
        listCapacity = view.listCapacity;
        listSize = view.listSize;
        if(listCapacity==0){
            pointer_array = nullptr;
        }else{
            pointer_array = new const T*[listCapacity];
            for(unsigned i=0;i<listSize;i++){
                pointer_array[i] = view.pointer_array[i];
            }
        }
    }
}
/*构造函数4：用指针的数组初始化ConstLinearlistView*/
template <class T>
ConstLinearlistView<T>::ConstLinearlistView(T** Tarray,unsigned n,float new_expand_factor){
    if(new_expand_factor<=1) throw "Expand factor must be larger than 1!";
    expand_factor = new_expand_factor;
    listSize = n;
    listCapacity = n*expand_factor;
    if(n==0){
        pointer_array = nullptr;
    }else{
        pointer_array = new const T*[listCapacity];
        for(unsigned i=0;i<n;i++){
            pointer_array[i] = Tarray[i];
        }
    }
}
/*构造函数5：用指向常量的指针的数组来初始化ConstLinearlistView*/
template <class T>
ConstLinearlistView<T>::ConstLinearlistView(const T** Tarray,unsigned n,float new_expand_factor){
    if(new_expand_factor<=1) throw "Expand factor must be larger than 1!";
    expand_factor = new_expand_factor;
    listSize=n;
    listCapacity=n*expand_factor;
    if(n==0){
        pointer_array = nullptr;
    }else{
        pointer_array = new const T*[listCapacity];
        for(unsigned i=0;i<n;i++){
            pointer_array[i] = Tarray[i];
        }
    }
}
/*构造函数6：用T的数组初始化ConstLinearlistView*/
template <class T>
ConstLinearlistView<T>::ConstLinearlistView(const T* Tarray,unsigned n,float new_expand_factor){
    if(new_expand_factor<=1) throw "Expand factor must be larger than 1!";
    expand_factor = new_expand_factor;
    listSize=n;
    listCapacity = n*expand_factor;
    if(n==0){
        pointer_array = nullptr;
    }else{
        pointer_array = new const T*[listCapacity];
        for(unsigned i=0;i<n;i++){
            pointer_array[i] = Tarray+i;
        }
    }
}
/*构造函数7：移动构造函数*/
template <class T>
ConstLinearlistView<T>::ConstLinearlistView(ConstLinearlistView&& view,float new_expand_factor) noexcept{
    if(new_expand_factor<=1) expand_factor = 1.5;
    else expand_factor = new_expand_factor;
    expand_factor = new_expand_factor;
    listSize=view.listSize;
    view.listSize = 0;
    listCapacity = view.listCapacity;
    view.listCapacity = 0;
    pointer_array = view.pointer_array;
    view.pointer_array = nullptr;
}
/*析构函数*/
template <class T>
ConstLinearlistView<T>::~ConstLinearlistView(){
    if(listCapacity>=1) delete[] pointer_array;
}
/*线性表视图的相关参数*/
template <class T>
bool ConstLinearlistView<T>::change_expand_factor(float new_expand_factor){
    if(listCapacity<=1) return false;
    else{
        expand_factor = new_expand_factor;
    }
}
template <class T>
void ConstLinearlistView<T>::changeLength(unsigned newCapacity,bool copy_){
    if (newCapacity == listCapacity){
        //情形1：如果新长度和原来的长度相等，那么不做任何操作
        return;
    }
    if (newCapacity == 0) {
        //情形2：如果新长度为0，说明我们要清空数组，则直接删掉element，然后让listCapacity和listSize都为0
        delete[] pointer_array;
        pointer_array = nullptr;
        listCapacity = 0;
        listSize = 0;
        return;
    }
    //否则，则是newCapacity和oldCapacity不等
    const T** temp = new const T*[newCapacity];
    if(copy_){//如果采用copy模式，则将原数组中有意义的元素复制到型数组中
        for(unsigned i = 0;i<listSize&&i<newCapacity;i++){
            temp[i] = pointer_array[i];
        }
    }
    //如果老数组长度大于0，则将老数组释放掉
    if (listCapacity > 0) delete pointer_array;
    //接下来求listSize，如果listSize比newCapacity要大，说明原来的元素有删减，否则只用改变listCapacity，不用改变listSize
    if (listSize>= newCapacity){
        listSize = newCapacity;
        listCapacity = newCapacity;
    }else{
        listCapacity = newCapacity;
    }
    pointer_array = temp;
}
template <class T>
void ConstLinearlistView<T>::changeSize(unsigned newSize,bool copy_){
    if(newSize>listCapacity) changeLength(newSize*expand_factor,copy_);
    listSize = newSize;
}
template <class T>
bool ConstLinearlistView<T>::empty() const{
    if (listSize == 0) return true;
    else return false;
}
template <class T>
unsigned ConstLinearlistView<T>::size() const{
    return listSize;
}
template <class T>
unsigned ConstLinearlistView<T>::capacity() const{
    return listCapacity;
}

template <class T>
void ConstLinearlistView<T>::clear(){
    if(listCapacity>0) delete[] pointer_array;
    listCapacity=0;
    listSize=0;
}
template <class T>
const T& ConstLinearlistView<T>::operator [](unsigned index) const{
    if(index>=listSize) throw "Index out of range!";
    return *(pointer_array[index]);
}
template <class T>
const T*& ConstLinearlistView<T>::operator()(unsigned index){
    if(index>=listSize) throw "Index out of range!";
    return pointer_array[index];
}
template <class T>
unsigned ConstLinearlistView<T>::search(const T& element) const{
    unsigned result=0;
    while(result < listSize){
        if(*(pointer_array[result]) == element) return result;
        result++;
    }
    return result;
}
/*从视图中删掉一个元素*/
template <class T>
void ConstLinearlistView<T>::erase(unsigned index){
    if (index >= listSize){
        throw illegalParameterValue("index out of range.");
    }
    for(unsigned i=index+1;i<listSize;i++){
        pointer_array[i-1] = pointer_array[i];
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
void ConstLinearlistView<T>::eraseback(){
    erase(listSize-1);
}
template <class T>
void ConstLinearlistView<T>::erasefront(){
    erase(0);
}
/*从视图中插入一个元素*/
template <class T>
void ConstLinearlistView<T>::insert(unsigned index,const T* const& element_){
    if (index > listSize){
        throw illegalParameterValue("index out of range.");
    }
    if (listCapacity == 0){
        pointer_array = new const T*[5];
        listCapacity =5;
        listSize = 0;
    }
    if (listSize == listCapacity){
        unsigned new_size = expand_factor*listCapacity;
        changeLength(new_size);
    }
    if (index == listSize){
        pointer_array[index] = element_;
        listSize++;
        return;
    }
    if (index < listSize){
        for(unsigned i = listSize-1;i>=index;i--){
            pointer_array[i+1] = pointer_array[i];
            if(i==0) break;
        }
        pointer_array[index] = element_;
        listSize++;
    }
}
template <class T>
void ConstLinearlistView<T>::insertfront(const T* const& element_){
    insert(0,element_);
}
template <class T>
void ConstLinearlistView<T>::insertback(const T* const& element_){
    if (listCapacity == 0){
        pointer_array = new const T*[5];
        listCapacity =5;
        listSize = 0;
    }
    if (listSize == listCapacity){
        unsigned new_size = expand_factor*listCapacity;
        changeLength(new_size);
    }
    pointer_array[listSize] = element_;
    listSize++;
}
template <class T>
ConstLinearlistView<T>& ConstLinearlistView<T>::operator = (const ConstLinearlistView& view){
    listCapacity = view.listCapacity;
    listSize = view.listSize;
    pointer_array = new const T*[listCapacity];
    for(unsigned i=0;i<listSize;i++){
        pointer_array[i] = view.pointer_array[i];
    }
    return *this;
}
template <class T>
ConstLinearlistView<T>& ConstLinearlistView<T>::operator = (ConstLinearlistView&& view) noexcept{
    clear();
    listSize=view.listSize;
    view.listSize = 0;
    listCapacity = view.listCapacity;
    view.listCapacity = 0;
    pointer_array = view.pointer_array;
    view.pointer_array = nullptr;
}
template <class T>
ConstLinearlistView<T>& ConstLinearlistView<T>::copy(const T* Tarray,unsigned n){
    clear();
    listSize=n;
    listCapacity = n*expand_factor;
    if(n==0){
        pointer_array = nullptr;
    }else{
        pointer_array = new const T*[listCapacity];
        for(unsigned i=0;i<n;i++){
            pointer_array[i] = Tarray+i;
        }
    }
}
template <class T>
ConstLinearlistView<T>& ConstLinearlistView<T>::copy(T** Tpointer_array,unsigned n){
    clear();
    listSize = n;
    listCapacity = n*expand_factor;
    if(n==0){
        pointer_array = nullptr;
    }else{
        pointer_array = new const T*[listCapacity];
        for(unsigned i=0;i<n;i++){
            pointer_array[i] = Tpointer_array[i];
        }
    }
}
template <class T>
ConstLinearlistView<T>& ConstLinearlistView<T>::copy(const T** Tpointer_array,unsigned n){
    clear();
    listSize = n;
    listCapacity = n*expand_factor;
    if(n==0){
        pointer_array = nullptr;
    }else{
        pointer_array = new const T*[listCapacity];
        for(unsigned i=0;i<n;i++){
            pointer_array[i] = Tpointer_array[i];
        }
    }
}
template <class T>
ConstLinearlistViewIterator<T> ConstLinearlistView<T>::begin() const{
    return ConstLinearlistViewIterator<T>(pointer_array);
}
template <class T>
ConstLinearlistViewIterator<T> ConstLinearlistView<T>::end() const{
    return ConstLinearlistViewIterator<T>(pointer_array+listSize);
}
}
#endif // ARRAYLISTVIEW_H
