#ifndef __LZH_MAP_H__
#define __LZH_MAP_H__

#include <map>

//-----------------------------------------------------------------------------
// 红黑树
//-----------------------------------------------------------------------------

template <class K, class V>
class LzhMap
{
public:
    LzhMap()
    {
    }

    ~LzhMap()
    {
    }

public:

    // 迭代器
    class Iterator
    {
    public:
        K &Key()
        {
            return it->first;
        }

        V &Value()
        {
            return it->second;
        }

        bool operator==(const Iterator &o)
        {
            return it == o.it;
        }

        bool operator!=(const Iterator &o)
        {
            return it != o.it;
        }

        Iterator &operator++()
        {
            ++it;
            return *this;
        }

        Iterator &operator--()
        {
            --it;
            return *this;
        }

        Iterator &operator++(int)
        {
            Iterator last = *this;
            it++;
            return last;
        }

        Iterator &operator--(int)
        {
            Iterator last = *this;
            it--;
            return last;
        }

    private:
        std::map<K, V>::iterator it;
    };

    // 插入元素
    bool Insert(const K &key, const V &value);

    // 删除元素
    bool Remove(const K &key);

    // 查找元素
    V & Find(const K &key);
    const V & Find(const K &key) const;

    // 获取迭代器第一个元素
    Iterator Begin();

    // 获取迭代器末尾元素
    Iterator End();

private:
    std::map<K, V> rbtreeMap;
};

//-----------------------------------------------------------------------------

#endif // __LZH_MAP_H__