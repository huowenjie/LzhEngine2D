#ifndef __OBJECT_H__
#define __OBJECT_H__
#if 0
#include <cstddef>

/*===========================================================================*/
/* ȫ�ֶ��� */
/*===========================================================================*/

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

/*===========================================================================*/
#endif
#endif /* __OBJECT_H__ */
