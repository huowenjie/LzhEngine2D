#ifndef __LZH_RIGIDBODY2D_H__
#define __LZH_RIGIDBODY2D_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* ����������� */
LZH_API LZH_RIGIDBODY2D *lzh_rigidbody2d_create(LZH_ENGINE *engine, LZH_OBJECT *object);

/* ���ٸ������ */
LZH_API void lzh_rigidbody2d_destroy(LZH_RIGIDBODY2D *body);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_RIGIDBODY2D_H__ */
