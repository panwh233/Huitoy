#include "Dictionary.h"
#include "Pair.h"
#include "Arraylist.h"
#include "sortedArrayListIterator.h"
#include <iostream>
#include <math.h>
#include <utility>
using std::ostream;
using std::cout;
using std::endl;
#ifndef SORTEDARRAYLIST_H
#define SORTEDARRAYLIST_H
namespace Huitoy{
template <class Key,class Value>
class sortedArrayList:public Dictionary<Key,Value>
{
    public:
        //���캯��
        sortedArrayList();
        sortedArrayList(const sortedArrayList& sorted_arraylist);
        sortedArrayList(sortedArrayList&& sorted_arraylist) noexcept;
        sortedArrayList(const Pair<Key,Value>* pair_array,unsigned n,bool replace = true);
        sortedArrayList(const Key* key_array,const Value* value_array,unsigned n,bool replace = true);
        //��������
        ~sortedArrayList(){}
        //���ظ�ֵ�����
        sortedArrayList& operator= (const sortedArrayList& sorted_arraylist);
        sortedArrayList& operator= (sortedArrayList&& sorted_arraylist) noexcept;
        sortedArrayList& copy(const Pair<Key,Value>* pair_array,unsigned n,bool replace = true);
        sortedArrayList& copy(const Key* key_array,const Value* value_array,unsigned n,bool replace = true);
        //����ȡԪ��
        Value& operator[](const Key& key);
        const Value& operator[] (const Key& key) const;
        //����Ԫ��
        bool insert(const Key& key,const Value& value,bool replace = true);
        //ɾ��Ԫ��
        bool erase(const Key& key);
        //�����ض�Ԫ�صļ�
        Key search(const Value& value) const;
        //�ֵ�Ĺ�ģ
        unsigned size() const;
        //�ֵ��Ƿ�Ϊ��
        bool empty() const;
        //begin��end
        sortedArrayListIterator<Key,Value> begin(){
            sortedArrayListIterator<Key,Value> iter(pair_array.begin());
            return iter;
        }
        sortedArrayListIterator<Key,Value> end(){
            sortedArrayListIterator<Key,Value> iter(pair_array.end());
            return iter;
        }
        ConstSortedArrayListIterator<Key,Value> begin() const{
            ConstSortedArrayListIterator<Key,Value> iter(pair_array.begin());
            return iter;
        }
        ConstSortedArrayListIterator<Key,Value> end() const{
            ConstSortedArrayListIterator<Key,Value> iter(pair_array.end());
            return iter;
        }
    protected:
        Arraylist<Pair<Key,Value>> pair_array;
        unsigned search_index_of_pair(const Key& key) const;
    private:
};

template <class Key,class Value>
sortedArrayList<Key,Value>::sortedArrayList():pair_array(0){}
template <class Key,class Value>
sortedArrayList<Key,Value>::sortedArrayList(const sortedArrayList& sorted_arraylist):pair_array(0){
    unsigned size_ = sorted_arraylist.size();
    if(size_==0) return;
    else{
        pair_array = sorted_arraylist.pair_array;
    }
}
template <class Key,class Value>
sortedArrayList<Key,Value>::sortedArrayList(sortedArrayList&& dict) noexcept{
    pair_array.operator = (std::move(dict.pair_array));
}
template <class Key,class Value>
unsigned sortedArrayList<Key,Value>::search_index_of_pair(const Key& key) const{
    unsigned left = 0;
    unsigned right = pair_array.size()-1;
    unsigned mid = (left+right)/2;
    while(right-left>=2){
        if(pair_array[mid].key()==key){
            return mid;
        }else if(pair_array[mid].key()>key){
            right = mid;
            mid = (left+right)/2;
        }else{
            left = mid;
            mid = (left+right)/2;
        }
    }
    return right;
}
template <class Key,class Value>
sortedArrayList<Key,Value>::sortedArrayList(const Pair<Key,Value>* pair_array_,unsigned n,bool replace):pair_array(n){
    if(n==0) return;
    if(replace){
        /*
        ��������滻ģʽ�����ҵ���Ӧ������������ҵ�ĳһ����ֵ�Եļ�ǡ��Ϊkey����ô��ֱ���滻��Ӧ�ļ�ֵ�ԣ�
        ���򣬲����ֵ�ԡ�
        */
        for(unsigned i=0;i<n;i++){
            /*ȡ������Ҫ����ļ�ֵ��*/
            const Pair<Key,Value>& pair_ = pair_array_[i];
            if(i==0) {
                /*����ֵ����Ѿ�����*/
                pair_array.insert(0,pair_);
                continue;
            }
            const Key& key = pair_. key();
            unsigned left = 0;
            unsigned right = pair_array.size()-1;
            //���keyС����С��
            if(key<pair_array[left].key()){
                pair_array.insertfront(pair_);
            }else if(key>pair_array[right].key()){
                pair_array.insertback(pair_);
            }else if(key==pair_array[left].key()){
                pair_array[left] = pair_;
            }else if(key==pair_array[right].key()){
                pair_array[right] = pair_;
            }else{
                unsigned index = search_index_of_pair(key);
                if(pair_array[index].key()==key){
                    pair_array[index] = pair_;
                    continue;
                }else{
                    pair_array.insert(index,pair_);
                }
            }
        }
    }else{
        for(unsigned i=0;i<n;i++){
            const Pair<Key,Value>& pair_ = pair_array_[i];
            if(i==0) {
                pair_array.insert(0,pair_);
                continue;
            }
            const Key& key = pair_. key();
            unsigned left = 0;
            unsigned right = pair_array.size()-1;
            //���keyС����С��
            if(key<pair_array[left].key()){
                pair_array.insertfront(pair_);
            }else if(key>pair_array[right].key()){
                pair_array.insertback(pair_);
            }else if(key==pair_array[left].key()){
                continue;
            }else if(key==pair_array[right].key()){
                continue;
            }else{
                unsigned index = search_index_of_pair(key);
                if(pair_array[index].key()==key) continue;
                pair_array.insert(index,pair_);
            }
        }
    }
}
template <class Key,class Value>
sortedArrayList<Key,Value>::sortedArrayList(const Key* key_array,const Value* value_array,unsigned n,bool replace):pair_array(n){
    if(n==0) return;
    if(replace){
        /*
        ��������滻ģʽ�����ҵ���Ӧ������������ҵ�ĳһ����ֵ�Եļ�ǡ��Ϊkey����ô��ֱ���滻��Ӧ�ļ�ֵ�ԣ�
        ���򣬲����ֵ�ԡ�
        */
        for(unsigned i=0;i<n;i++){
            /*ȡ������Ҫ����ļ�ֵ��*/
            const Key& key = key_array[i];
            const Value& value = value_array[i];
            Pair<Key,Value> pair_(key,value);
            if(i==0) {
                /*����ֵ����Ѿ�����*/
                pair_array.insert(0,pair_);
                continue;
            }
            unsigned left = 0;
            unsigned right = pair_array.size()-1;
            //���keyС����С��
            if(key<pair_array[left].key()){
                pair_array.insertfront(pair_);
            }else if(key>pair_array[right].key()){
                pair_array.insertback(pair_);
            }else if(key==pair_array[left].key()){
                pair_array[left] = pair_;
            }else if(key==pair_array[right].key()){
                pair_array[right] = pair_;
            }else{
                unsigned index = search_index_of_pair(key);
                if(pair_array[index].key()==key){
                    pair_array[index] = pair_;
                    continue;
                }else{
                    pair_array.insert(index,pair_);
                }
            }
        }
    }else{
        for(unsigned i=0;i<n;i++){
            const Key& key = key_array[i];
            const Value& value = value_array[i];
            Pair<Key,Value> pair_(key,value);
            if(i==0) {
                pair_array.insert(0,pair_);
                continue;
            }
            unsigned left = 0;
            unsigned right = pair_array.size()-1;
            //���keyС����С��
            if(key<pair_array[left].key()){
                pair_array.insertfront(pair_);
            }else if(key>pair_array[right].key()){
                pair_array.insertback(pair_);
            }else if(key==pair_array[left].key()){
                continue;
            }else if(key==pair_array[right].key()){
                continue;
            }else{
                unsigned index = search_index_of_pair(key);
                if(pair_array[index].key()==key) continue;
                pair_array.insert(index,pair_);
            }
        }
    }
}
template<class Key,class Value>
sortedArrayList<Key,Value>& sortedArrayList<Key,Value>::operator=(const sortedArrayList& sorted_arraylist){
    unsigned size_ = sorted_arraylist.size();
    if(size_==0){
        pair_array.clear();
    }
    else{
        pair_array = sorted_arraylist.pair_array;
    }
    return *this;
}
template <class Key,class Value>
sortedArrayList<Key,Value>& sortedArrayList<Key,Value>::operator=(sortedArrayList&& sorted_arraylist) noexcept{
    pair_array.operator = (std::move(sorted_arraylist.pair_array));
    return *this;
}
template<class Key,class Value>
Key sortedArrayList<Key,Value>::search(const Value& value) const{
    bool find_value = false;
    Key result;
    for(auto pair_:pair_array){
        if(pair_.value()==value){
            result = pair_.key();
            find_value = true;
        }
    }
    if(!find_value) throw "Value not found.";
    return result;
}
template<class Key,class Value>
Value& sortedArrayList<Key,Value>::operator[] (const Key& key){
    if(pair_array.size()==0){
        throw "Key not found.";
    }
    if(key<pair_array[0].key()||key>pair_array[pair_array.size()-1].key()){
        throw "Key not found.";
    }
    if(key==pair_array[0].key()){
        return pair_array[0].value();
    }
    if(key==pair_array[pair_array.size()-1].key()){
        return pair_array[pair_array.size()-1].value();
    }
    unsigned index = search_index_of_pair(key);
    if(pair_array[index].key()!=key){
        throw "Key not found.";
    }else{
        return pair_array[index].value();
    }
}
template <class Key,class Value>
const Value& sortedArrayList<Key,Value>::operator[](const Key& key) const{
    if(pair_array.size()==0){
        throw "Key not found.";
    }
    if(key<pair_array[0].key()||key>pair_array[pair_array.size()-1].key()){
        throw "Key not found.";
    }
    if(key==pair_array[0].key()){
        return pair_array[0].value();
    }
    if(key==pair_array[pair_array.size()-1].key()){
        return pair_array[pair_array.size()-1].value();
    }
    unsigned index = search_index_of_pair(key);
    if(pair_array[index].key()!=key){
        throw "Key not found.";
    }else{
        return pair_array[index].value();
    }
}
template <class Key,class Value>
unsigned sortedArrayList<Key,Value>::size() const{
    return pair_array.size();
}
template <class Key,class Value>
bool sortedArrayList<Key,Value>::empty() const{
    return pair_array.empty();
}
template <class Key,class Value>
bool sortedArrayList<Key,Value>::insert(const Key& key,const Value& value,bool replace){
    Pair<Key,Value> pair_(key,value);
    if(pair_array.size()==0){
        pair_array.insert(0,Pair<Key,Value>(key,value));
        return true;
    }
    if(key<pair_array[0].key()){
        pair_array.insertfront(pair_);
        return true;
    }
    if(key>pair_array[pair_array.size()-1].key()){
        pair_array.insertback(pair_);
        return true;
    }
    if(key==pair_array[0].key()){
        if(replace){
            pair_array[0].value() = value;
            return true;
        }else{
            return false;
        }
    }
    if(key==pair_array[pair_array.size()-1].key()){
        if(replace){
            pair_array[pair_array.size()-1].value() = value;
            return true;
        }else{
            return false;
        }
    }
    unsigned index = search_index_of_pair(key);
    const Key& key1 = pair_array[index].key();
    if(key1==key){
        if(replace){
            pair_array[index].value() = value;
            return true;
        }else{
            return false;
        }
    }else{
        pair_array.insert(index,pair_);
        return true;
    }
}
template <class Key,class Value>
bool sortedArrayList<Key,Value>::erase(const Key& key){//��������и���
    if(pair_array.empty()) return false;
	if(key<pair_array[0].key()) return false;
	if(key>pair_array[pair_array.size()-1].key()) return false;
	if(key==pair_array[0].key()){
		pair_array.erasefront();
		return true;
	}
	if(key==pair_array[pair_array.size()-1].key()){
		pair_array.eraseback();
		return true;
	}
	unsigned index = search_index_of_pair(key);
    if(pair_array[index].key()==key){
        pair_array.erase(index);
        return true;
    }else{
        return false;
    }
}
}
#endif // SORTEDARRAYLIST_H
