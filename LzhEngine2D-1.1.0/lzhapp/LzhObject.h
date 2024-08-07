#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <cstddef>

//=============================================================================
// ȫ�ֶ���
//=============================================================================

class Object
{
public:
    Object();
    virtual ~Object();

public:
    void *operator new(size_t size);
    void *operator new[](size_t size);
    void operator delete(void *pt);
    void operator delete[](void *pt);
};

//=============================================================================

#endif // __OBJECT_H__
