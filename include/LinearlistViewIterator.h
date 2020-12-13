#ifndef LINEARLISTVIEWITERATOR_H
#define LINEARLISTVIEWITERATOR_H
namespace Huitoy{
template <class T>
class LinearlistViewIterator
{
    public:
        /*构造函数*/
        LinearlistViewIterator():p_of_pointer(nullptr){}
        LinearlistViewIterator(const LinearlistViewIterator& iter_):p_of_pointer(iter_.p_of_pointer){}
        LinearlistViewIterator(T**const & the_pointer_of_pointer):p_of_pointer(the_pointer_of_pointer){}
        /*析构函数*/
        virtual ~LinearlistViewIterator() {}
        /*赋值运算符*/
        LinearlistViewIterator& operator = (const LinearlistViewIterator& iter_){
            p_of_pointer = iter_.p_of_pointer;
            return *this;
        }
        LinearlistViewIterator& operator = (T** const & the_pointer_of_pointer){
            p_of_pointer = the_pointer_of_pointer;
            return *this;
        }
        /*比较运算符*/
        bool operator==(const LinearlistViewIterator& iter_) const{
            return iter_.p_of_pointer==p_of_pointer;
        }
        bool operator !=(const LinearlistViewIterator& iter_) const{
            return iter_.p_of_pointer!=p_of_pointer;
        }
        /*解运算符*/
        T& operator *() const{
            return **p_of_pointer;
        }
        /*++运算符*/
        LinearlistViewIterator operator++(int){
            LinearlistViewIterator result = *this;
            p_of_pointer++;
            return result;
        }
        LinearlistViewIterator& operator++(){
            p_of_pointer++;
            return *this;
        }

    protected:
        T** p_of_pointer;
    private:
};

template <class T>
class ConstLinearlistViewIterator{
    public:
        /*构造函数*/
        ConstLinearlistViewIterator():p_of_pointer(nullptr){}
        ConstLinearlistViewIterator(const ConstLinearlistViewIterator& iter_):p_of_pointer(iter_.p_of_pointer){}
        ConstLinearlistViewIterator(const T** const & the_pointer_of_pointer):p_of_pointer(the_pointer_of_pointer){}
        /*析构函数*/
        ~ConstLinearlistViewIterator(){}
        /*赋值运算符*/
        ConstLinearlistViewIterator& operator = (const ConstLinearlistViewIterator& iter_){
            p_of_pointer = iter_.p_of_pointer;
            return *this;
        }
        ConstLinearlistViewIterator& operator = (const T** const & the_pointer_of_pointer){
            p_of_pointer = the_pointer_of_pointer;
            return *this;
        }
        /*比较运算符*/
        bool operator == (const ConstLinearlistViewIterator& iter_) const{
            return p_of_pointer == iter_.p_of_pointer;
        }
        bool operator != (const ConstLinearlistViewIterator& iter_) const{
            return p_of_pointer != iter_.p_of_pointer;
        }
        /*解运算符*/
        const T& operator*() const{
            return **p_of_pointer;
        }
        /*自增运算符*/
        ConstLinearlistViewIterator operator++(int){
            ConstLinearlistViewIterator result = *this;
            p_of_pointer++;
            return result;
        }
        ConstLinearlistViewIterator& operator++(){
            p_of_pointer++;
            return *this;
        }
    protected:
        const T** p_of_pointer;
};
}
#endif // LINEARLISTVIEWITERATOR_H
