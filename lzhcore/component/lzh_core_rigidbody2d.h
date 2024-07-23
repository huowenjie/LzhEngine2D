#ifndef __LZH_CORE_RIGIDBODY2D_H__
#define __LZH_CORE_RIGIDBODY2D_H__

#include <lzh_rigidbody2d.h>

#include "../box2d/lzh_b2_api.h"
#include "lzh_component.h"

/*===========================================================================*/
/* �����������(�ڲ�) */
/*===========================================================================*/

struct LZH_RIGIDBODY2D {
    LZH_COMPONENT base;                 /* ���������Ϣ */
    LZH_B2_BODY *b2_body;               /* 2d �������������� */
};

/*===========================================================================*/

#endif /* __LZH_CORE_RIGIDBODY2D_H__ */
