#ifndef __LZH_CORE_TRANSFORM_H__
#define __LZH_CORE_TRANSFORM_H__

#include "../math/lzh_quat4f.h"
#include "lzh_component.h"

/*===========================================================================*/
/* �任������� */
/*===========================================================================*/

struct LZH_TRANSFORM {
    LZH_COMPONENT base;         /* ���������Ϣ */

    float screen_width;         /* ��Ļ�����ȣ�����������ϵ�ĵ�λ���궨�� */
    float screen_height;        /* ��Ļ����߶ȣ�����������ϵ�ĵ�λ���궨�� */

    LZH_VEC3F local_pos;        /* ����ֲ����� */
    LZH_VEC3F center_pos;       /* ���ĵ� */
    LZH_VEC3F local_scale;      /* ������������ */
    LZH_QUAT4F local_rotate;    /* ������ת */

    LZH_VEC3F forward;          /* ǰ���� x �������������ǰ���������ϵ */
    LZH_VEC3F backward;         /* ���� x �Ḻ���������ǰ���������ϵ */
    LZH_VEC3F leftward;         /* ���� y �������������ǰ���������ϵ */
    LZH_VEC3F rightward;        /* �ң��� y �Ḻ���������ǰ���������ϵ */

    LZH_MAT4X4F model_mat;      /* ģ�;��� */
};

/* ������� */
LZH_TRANSFORM *lzh_transform_create(LZH_ENGINE *engine, LZH_OBJECT *object);

/* ������� */
void lzh_transform_destroy(LZH_TRANSFORM *transform);

/* ˢ�±任���� */
void lzh_transform_flush(LZH_TRANSFORM *transform);

/*===========================================================================*/

#endif /* __LZH_CORE_TRANSFORM_H__ */
