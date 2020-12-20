#include "Pair.h"
#include "ArrayListIterator.h"
#ifndef SORTEDARRAYLISTITERATOR_H
#define SORTEDARRAYLISTITERATOR_H
namespace Huitoy{
template <class Key,class Value>
class sortedArrayListIterator
{
    public:
        sortedArrayListIterator(const ArrayListIterator<Pair<Key,Value>>& arr_iterator=nullptr):iterator_(arr_iterator) {}
        sortedArrayListIterator(const sortedArrayListIterator& iter_):iterator_(iter_.iterator_){}
        sortedArrayListIterator& operator = (const sortedArrayListIterator& iter_){
            iterator_ = iter_.iterator_;
            return *this;
        }
        sortedArrayListIterator operator++(int){
            sortedArrayListIterator iter_result(*this);
            iterator_++;
            return iter_result;
        }
        sortedArrayListIterator& operator++(){
            iterator_++;
            return *this;
        }
        bool operator == (const sortedArrayListIterator& other) const{
            return iterator_==other.iterator_;
        }
        bool operator != (const sortedArrayListIterator& other) const{
            return iterator_!=other.iterator_;
        }
        Value& operator*() const{
            return (*iterator_).value();
        }
        const Key& key() const{
            return (*iterator_).key();
        }
        bool null_iter() const{
            return iterator_.null_iter();
        }
        virtual ~sortedArrayListIterator() {}

    protected:
        ArrayListIterator<Pair<Key,Value>> iterator_;
    private:
};

template <class Key,class Value>
class ConstSortedArrayListIterator
{
    public:
        ConstSortedArrayListIterator(const ConstArrayListIterator<Pair<Key,Value>>& const_arr_iter=nullptr):iterator_(const_arr_iter){}
        ConstSortedArrayListIterator(const ConstSortedArrayListIterator& iter_):iterator_(iter_.iterator_){}
        ConstSortedArrayListIterator& operator=(const ConstSortedArrayListIterator& iter_){
            iterator_ = iter_.iterator_;
        }
        ConstSortedArrayListIterator operator++(int){
            ConstSortedArrayListIterator const_sorted_iter(*this);
            iterator_++;
            return const_sorted_iter;
        }
        ConstSortedArrayListIterator& operator++(){
            iterator_++;
            return *this;
        }
        bool operator==(const ConstSortedArrayListIterator& iter_) const{
            return iter_.iterator_ == iterator_;
        }
        bool operator!=(const ConstSortedArrayListIterator& iter_) const{
            return iter_.iterator_ != iterator_;
        }
        bool null_iter() const{
            return iterator_.null_iter();
        }
        const Value& operator*() const{
            return (*iterator_).value();
        }
        const Key& key() const{
            return (*iterator_).key();
        }
    protected:
        ConstArrayListIterator<Pair<Key,Value>> iterator_;
};
}
#endif // SORTEDARRAYLISTITERATOR_H
