#ifndef __LZH_RIGIDBODY2D_H__
#define __LZH_RIGIDBODY2D_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 刚体 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 创建刚体组件 */
LZH_API LZH_RIGIDBODY2D *lzh_rigidbody2d_create(LZH_ENGINE *engine, LZH_OBJECT *object);

/* 销毁刚体组件 */
LZH_API void lzh_rigidbody2d_destroy(LZH_RIGIDBODY2D *body);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_RIGIDBODY2D_H__ */
