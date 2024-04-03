#ifndef __LZH_CORE_TRANSFORM_H__
#define __LZH_CORE_TRANSFORM_H__

#include <lzh_mat4x4f.h>
#include <lzh_vec4f.h>

#include "lzh_component.h"

/*===========================================================================*/
/* �任������� */
/*===========================================================================*/

struct LZH_TRANSFORM {
    LZH_COMPONENT base;     /* ���������Ϣ */

    LZH_VEC3F world_pos;    /* ������������ */
    LZH_VEC3F local_pos;    /* ����ֲ����� */

    float world_angle;      /* ������ת�Ƕ� */
    float local_angle;      /* �ֲ���ת�Ƕ� */
    LZH_VEC2F center_pos;   /* ��ת���ĵ� */

    LZH_VEC3F world_scale;  /* ������������ */
    LZH_VEC3F local_scale;  /* ������������ */

    LZH_MAT4X4F world_mat;  /* �任���� */
};

/* ������� */
LZH_TRANSFORM *lzh_transform_create(LZH_ENGINE *engine);

/* ������� */
void lzh_transform_destroy(LZH_TRANSFORM *transform);

/*===========================================================================*/

#endif /* __LZH_CORE_TRANSFORM_H__ */
