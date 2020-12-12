#include "LinearlistViewIterator.h"
#include "illegalParameterValue.h"
#ifndef LINEARLISTVIEW_H
#define LINEARLISTVIEW_H
namespace Huitoy{
template <class T>
class LinearlistView
{
    public:
        /*���캯��*/
        LinearlistView(unsigned initial_capacity=5,float expand_factor=1.5);
        LinearlistView(const LinearlistView& view,float expand_factor=1.5);
        LinearlistView(LinearlistView&& view,float expand_factor=1.5) noexcept;
        LinearlistView(T* Tarray,unsigned n,float expand_factor=1.5);
        LinearlistView(T** Tpointer_array,unsigned n,float expand_factor=1.5);
        /*��������*/
        virtual ~LinearlistView();
        /*��ͼ��ز���*/
        bool change_expand_factor(float new_expand_facotr);
        void changeSize(unsigned newSize,bool copy_=true);
        float expandFactor();
        bool empty() const;
        unsigned size() const;
        unsigned capacity() const;
        /*�����ͼ*/
        void clear();
        /*����*/
        T& operator[] (unsigned index) const;
        T*& operator() (unsigned index);
        /*����Ԫ��������*/
        unsigned search(const T& element) const;
        /*ɾ��Ԫ��*/
        void erase(unsigned index);
        void eraseback();
        void erasefront();
        /*����Ԫ��*/
        void insert(unsigned index,T* const& element);
        void insertback(T* const& element);
        void insertfront(T* const& element);
        /*��ͼ�ĸ�ֵ*/
        LinearlistView& operator = (const LinearlistView& view);
        LinearlistView& operator = (LinearlistView&& view) noexcept;
        LinearlistView& copy(T* Tarray,unsigned n);
        LinearlistView& copy(T** Tpointer_array,unsigned n);
        /*��ͼ�ı���*/
        LinearlistViewIterator<T> begin() const;
        LinearlistViewIterator<T> end() const;
    protected:
        T** pointer_array;
        unsigned listCapacity;
        unsigned listSize;
        float expand_factor;
        void changeLength(unsigned newCapacity,bool copy_ = true);
};
/*���캯��*/
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
/*��������*/
template <class T>
LinearlistView<T>::~LinearlistView(){
    if(listCapacity>=1) delete[] pointer_array;
}
/*���Ա���ͼ����ز���*/
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
        //����1������³��Ⱥ�ԭ���ĳ�����ȣ���ô�����κβ���
        return;
    }
    if (newCapacity == 0) {
        //����2������³���Ϊ0��˵������Ҫ������飬��ֱ��ɾ��element��Ȼ����listCapacity��listSize��Ϊ0
        delete[] pointer_array;
        pointer_array = nullptr;
        listCapacity = 0;
        listSize = 0;
        return;
    }
    //��������newCapacity��oldCapacity����
    T** temp = new T*[newCapacity];
    if(copy_){//�������copyģʽ����ԭ�������������Ԫ�ظ��Ƶ���������
        for(unsigned i = 0;i<listSize&&i<newCapacity;i++){
            temp[i] = pointer_array[i];
        }
    }
    //��������鳤�ȴ���0�����������ͷŵ�
    if (listCapacity > 0) delete pointer_array;
    //��������listSize�����listSize��newCapacityҪ��˵��ԭ����Ԫ����ɾ��������ֻ�øı�listCapacity�����øı�listSize
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
/*����ͼ��ɾ��һ��Ԫ��*/
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
/*����ͼ�в���һ��Ԫ��*/
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
        /*���캯��*/
        ConstLinearlistView(unsigned inital_capacity=5,float expand_factor=1.5);
        ConstLinearlistView(const LinearlistView<T>& view,float expand_factor=1.5);
        ConstLinearlistView(const ConstLinearlistView& view,float expand_factor=1.5);
        ConstLinearlistView(ConstLinearlistView&& view,float expand_factor=1.5) noexcept;
        ConstLinearlistView(T** Tpointer_array,unsigned n,float expand_factor=1.5);
        ConstLinearlistView(const T** Tpointer_array,unsigned n,float expand_factor=1.5);
        ConstLinearlistView(const T* Tarray,unsigned n,float expand_factor=1.5);
        /*��������*/
        virtual ~ConstLinearlistView();
        /*��ͼ��ز���*/
        bool change_expand_factor(float new_expand_facotr);
        void changeSize(unsigned newSize,bool copy_=true);
        float expandFactor();
        bool empty() const;
        unsigned size() const;
        unsigned capacity() const;
        /*�����ͼ*/
        void clear();
        /*����*/
        const T& operator[] (unsigned index) const;
        const T*& operator() (unsigned index);
        /*����Ԫ��������*/
        unsigned search(const T& element) const;
        /*ɾ��Ԫ��*/
        void erase(unsigned index);
        void eraseback();
        void erasefront();
        /*����Ԫ��*/
        void insert(unsigned index,const T* const & element);
        void insertback(const T* const & element);
        void insertfront(const T* const & element);
        /*��ͼ�ĸ�ֵ*/
        ConstLinearlistView& operator = (const LinearlistView<T>& view);
        ConstLinearlistView& operator = (const ConstLinearlistView& view);
        ConstLinearlistView& operator = (ConstLinearlistView&& view) noexcept;
        ConstLinearlistView& copy(const T** Tpointer_array,unsigned n);
        ConstLinearlistView& copy(T** Tpointer_array,unsigned n);
        ConstLinearlistView& copy(const T* Tarray,unsigned n);
        /*��ͼ�ı���*/
        ConstLinearlistViewIterator<T> begin() const;
        ConstLinearlistViewIterator<T> end() const;
    protected:
        const T** pointer_array;
        unsigned listCapacity;
        unsigned listSize;
        float expand_factor;
        void changeLength(unsigned newLength,bool copy_ = true);
};

/*���캯��*/
/*���캯��1��Ĭ�Ϲ��캯��*/
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
/*���캯��2����LinearlistView��ʼ��ConstLinearlistView*/
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
/*���캯��3�����ƹ��캯��*/
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
/*���캯��4����ָ��������ʼ��ConstLinearlistView*/
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
/*���캯��5����ָ������ָ�����������ʼ��ConstLinearlistView*/
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
/*���캯��6����T�������ʼ��ConstLinearlistView*/
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
/*���캯��7���ƶ����캯��*/
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
/*��������*/
template <class T>
ConstLinearlistView<T>::~ConstLinearlistView(){
    if(listCapacity>=1) delete[] pointer_array;
}
/*���Ա���ͼ����ز���*/
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
        //����1������³��Ⱥ�ԭ���ĳ�����ȣ���ô�����κβ���
        return;
    }
    if (newCapacity == 0) {
        //����2������³���Ϊ0��˵������Ҫ������飬��ֱ��ɾ��element��Ȼ����listCapacity��listSize��Ϊ0
        delete[] pointer_array;
        pointer_array = nullptr;
        listCapacity = 0;
        listSize = 0;
        return;
    }
    //��������newCapacity��oldCapacity����
    const T** temp = new const T*[newCapacity];
    if(copy_){//�������copyģʽ����ԭ�������������Ԫ�ظ��Ƶ���������
        for(unsigned i = 0;i<listSize&&i<newCapacity;i++){
            temp[i] = pointer_array[i];
        }
    }
    //��������鳤�ȴ���0�����������ͷŵ�
    if (listCapacity > 0) delete pointer_array;
    //��������listSize�����listSize��newCapacityҪ��˵��ԭ����Ԫ����ɾ��������ֻ�øı�listCapacity�����øı�listSize
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
/*����ͼ��ɾ��һ��Ԫ��*/
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
/*����ͼ�в���һ��Ԫ��*/
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
