#if 0
#include <lzh_mem.h>
#include "object.h"

/*===========================================================================*/

Object::Object()
{
}
    
Object::~Object()
{
}

/*===========================================================================*/

void *Object::operator new(size_t size)
{
    return LZH_MALLOC(size);
}

void *Object::operator new[](size_t size)
{
    return LZH_MALLOC(size);
}

void Object::operator delete(void *pt)
{
    LZH_FREE(pt);
}

void Object::operator delete[](void *pt)
{
    LZH_FREE(pt);
}

/*===========================================================================*/
#endif