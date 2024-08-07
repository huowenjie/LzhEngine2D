#ifndef __LZH_MAP_H__
#define __LZH_MAP_H__

#include <map>

//-----------------------------------------------------------------------------
// �����
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

    // ������
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

    // ����Ԫ��
    bool Insert(const K &key, const V &value);

    // ɾ��Ԫ��
    bool Remove(const K &key);

    // ����Ԫ��
    V & Find(const K &key);
    const V & Find(const K &key) const;

    // ��ȡ��������һ��Ԫ��
    Iterator Begin();

    // ��ȡ������ĩβԪ��
    Iterator End();

private:
    std::map<K, V> rbtreeMap;
};

//-----------------------------------------------------------------------------

#endif // __LZH_MAP_H__