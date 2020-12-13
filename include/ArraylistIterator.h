#ifndef ARRAYLISTITERATOR_H
#define ARRAYLISTITERATOR_H
namespace Huitoy{
template <class T>
class ArrayListIterator
{
    public:

        ArrayListIterator(T* tptr);
        ArrayListIterator(const ArrayListIterator& ali);
        ArrayListIterator operator++(int);
        ArrayListIterator& operator++();
        bool operator == (const ArrayListIterator& arraylistIterator) const;
        bool operator != (const ArrayListIterator& arraylistIterator) const;
        T& operator*() const;
        bool null_iter() const{
            return tptr==nullptr;
        }
        virtual ~ArrayListIterator() {}

    protected:
        T* tptr;
    private:
};
 template<class T>
 ArrayListIterator<T>::ArrayListIterator(T* tptr_){
    tptr = tptr_;
 }

 template<class T>
 ArrayListIterator<T>::ArrayListIterator(const ArrayListIterator& ali){
    tptr = ali.tptr;
 }
 template <class T>
 ArrayListIterator<T> ArrayListIterator<T>::operator++(int){
    ArrayListIterator ali = ArrayListIterator(tptr);
    tptr++;
    return ali;
 }

 template <class T>
 ArrayListIterator<T>& ArrayListIterator<T>::operator++(){
    tptr++;
    return *this;
 }

 template <class T>
 bool ArrayListIterator<T>::operator == (const ArrayListIterator& arraylistIterator) const{
    return tptr == arraylistIterator.tptr;
 }

 template <class T>
 bool ArrayListIterator<T>::operator != (const ArrayListIterator& arraylistIterator) const{
    return tptr != arraylistIterator.tptr;
 }

 template <class T>
 T& ArrayListIterator<T>::operator * () const{
    return *tptr;
 }

 template <class T>
class ConstArrayListIterator
{
    public:

        ConstArrayListIterator(const T* tptr);
        ConstArrayListIterator(const ConstArrayListIterator& cali);
        ConstArrayListIterator operator++(int);
        ConstArrayListIterator& operator++();
        bool operator == (const ConstArrayListIterator& arraylistIterator) const;
        bool operator != (const ConstArrayListIterator& arraylistIterator) const;
        const T& operator*() const;
        bool null_iter() const{
            return tptr==nullptr;
        }
        virtual ~ConstArrayListIterator() {}

    protected:
        const T* tptr;
    private:
};

template <class T>
ConstArrayListIterator<T>::ConstArrayListIterator(const T* tptr_){
    tptr = tptr_;
}
template <class T>
ConstArrayListIterator<T>::ConstArrayListIterator(const ConstArrayListIterator& cali){
    tptr = cali.tptr;
}
template <class T>
ConstArrayListIterator<T> ConstArrayListIterator<T>::operator ++(int){
    ConstArrayListIterator cali = ConstArrayListIterator(tptr);
    tptr++;
    return cali;
}

template <class T>
ConstArrayListIterator<T>& ConstArrayListIterator<T>::operator ++(){
    tptr++;
    return *this;
}

 template <class T>
 bool ConstArrayListIterator<T>::operator == (const ConstArrayListIterator& arraylistIterator) const{
    return tptr == arraylistIterator.tptr;
 }

 template <class T>
 bool ConstArrayListIterator<T>::operator != (const ConstArrayListIterator& arraylistIterator) const{
    return tptr != arraylistIterator.tptr;
 }

 template <class T>
 const T& ConstArrayListIterator<T>::operator * () const{
    return *tptr;
 }
}
#endif // ARRAYLISTITERATOR_H
