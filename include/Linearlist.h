#include "LinearlistView.h"
#include <initializer_list>
#ifndef LINEARLIST_H
#define LINEARLIST_H
using std::initializer_list;
namespace Huitoy{
template <class T>
class Linearlist
{
    public:
        virtual ~Linearlist() {}
        //Check whether the linearlist is empty and get size of the Linear list.
        virtual bool empty() const = 0;
        virtual unsigned size() const = 0;
        //get an element by its index
        virtual T& operator [] (unsigned index) =0;
        virtual const T& operator [](unsigned index) const =0;
        //find the minimal index of an element
        virtual unsigned search (const T& element) const=0;
        //delete an index from the linear list
        virtual void erase(unsigned index)=0;
        virtual void eraseback() =0;
        virtual void erasefront() =0;
        //insert an element into the linear list
        virtual void insert(unsigned index,const T& element_)=0;
        virtual void insertback(const T& element)=0;
        virtual void insertfront(const T& element)=0;
        //create a view of the linear list
        virtual LinearlistView<T> createView()=0;
        virtual ConstLinearlistView<T> createConstView() const=0;
        virtual ConstLinearlistView<T> createView() const=0;
        //copy the linear list
        virtual Linearlist& copy(const T* Tarray,unsigned n)=0;
        virtual Linearlist& operator = (const initializer_list<T>& init_list) = 0;
        virtual Linearlist& operator = (const LinearlistView<T>& view)=0;
        virtual Linearlist& operator = (const ConstLinearlistView<T>& view)=0;
        virtual Linearlist& operator = (const Linearlist& theLinearlist)=0;
        //merge two linear lists
        virtual void merge(const T* Tarray,unsigned n)=0;
        virtual void merge(const initializer_list<T>& init_list) = 0;
        virtual void merge(const LinearlistView<T>& view)=0;
        virtual void merge(const ConstLinearlistView<T>& view)=0;
        virtual void merge(const Linearlist& theLinearlist)=0;
        //get elements of the linear list of which indexs are larget than start_ and smaller than end_
        virtual LinearlistView<T> sublist(unsigned start_,unsigned end_)=0;
        virtual ConstLinearlistView<T> sublist(unsigned start_,unsigned end_) const=0;
};
}
#endif // LINEARLIST_H
