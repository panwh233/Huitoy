#include "Linearlist.h"
#ifndef CHAIN_H
#define CHAIN_H
namespace Huitoy{
template <class T>
class Chain:public Linearlist<T>
{
    public:
        //�����ָ���ƶ�ģ��
        virtual void next() const=0;
        virtual void switch_to_begin() const=0;
        virtual T& thisElement()=0;
        virtual const T& thisElement() const=0;
        //�����µĲ����ɾ������
        virtual void erase()=0;
        virtual void insert(const T& theElement,bool front_ = true)=0;
        //��������
        virtual ~Chain() {}

    protected:

    private:
};
}
#endif // CHAIN_H
