#ifndef LINEARLISTVIEWITERATOR_H
#define LINEARLISTVIEWITERATOR_H
namespace Huitoy{
template <class T>
class LinearlistViewIterator
{
    public:
        /*���캯��*/
        LinearlistViewIterator():p_of_pointer(nullptr){}
        LinearlistViewIterator(const LinearlistViewIterator& iter_):p_of_pointer(iter_.p_of_pointer){}
        LinearlistViewIterator(T**const & the_pointer_of_pointer):p_of_pointer(the_pointer_of_pointer){}
        /*��������*/
        virtual ~LinearlistViewIterator() {}
        /*��ֵ�����*/
        LinearlistViewIterator& operator = (const LinearlistViewIterator& iter_){
            p_of_pointer = iter_.p_of_pointer;
            return *this;
        }
        LinearlistViewIterator& operator = (T** const & the_pointer_of_pointer){
            p_of_pointer = the_pointer_of_pointer;
            return *this;
        }
        /*�Ƚ������*/
        bool operator==(const LinearlistViewIterator& iter_) const{
            return iter_.p_of_pointer==p_of_pointer;
        }
        bool operator !=(const LinearlistViewIterator& iter_) const{
            return iter_.p_of_pointer!=p_of_pointer;
        }
        /*�������*/
        T& operator *() const{
            return **p_of_pointer;
        }
        /*++�����*/
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
        /*���캯��*/
        ConstLinearlistViewIterator():p_of_pointer(nullptr){}
        ConstLinearlistViewIterator(const ConstLinearlistViewIterator& iter_):p_of_pointer(iter_.p_of_pointer){}
        ConstLinearlistViewIterator(const T** const & the_pointer_of_pointer):p_of_pointer(the_pointer_of_pointer){}
        /*��������*/
        ~ConstLinearlistViewIterator(){}
        /*��ֵ�����*/
        ConstLinearlistViewIterator& operator = (const ConstLinearlistViewIterator& iter_){
            p_of_pointer = iter_.p_of_pointer;
            return *this;
        }
        ConstLinearlistViewIterator& operator = (const T** const & the_pointer_of_pointer){
            p_of_pointer = the_pointer_of_pointer;
            return *this;
        }
        /*�Ƚ������*/
        bool operator == (const ConstLinearlistViewIterator& iter_) const{
            return p_of_pointer == iter_.p_of_pointer;
        }
        bool operator != (const ConstLinearlistViewIterator& iter_) const{
            return p_of_pointer != iter_.p_of_pointer;
        }
        /*�������*/
        const T& operator*() const{
            return **p_of_pointer;
        }
        /*���������*/
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
