#ifndef DICTIONARY_H
#define DICTIONARY_H
namespace Huitoy{
template <class Key,class Value>
class Dictionary
{
    public:
        virtual Value& operator[](const Key& key)=0;
        virtual const Value& operator[] (const Key& key) const=0;
        virtual bool insert(const Key& key,const Value& value,bool replace)=0;
        virtual bool erase(const Key& key)=0;
        virtual Key search(const Value& value) const = 0;
        virtual unsigned size() const=0;
        virtual bool empty() const=0;
        virtual ~Dictionary() {}
    protected:
    private:
};
}
#endif // DICTIONARY_H
