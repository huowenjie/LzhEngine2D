#ifndef __LZH_CORE_OBJECT_H__
#define __LZH_CORE_OBJECT_H__

#include <lzh_vec2f.h>
#include "lzh_core_engine.h"
#include "lzh_core_sprite.h"

/*===========================================================================*/
/* ����(�ڲ�) */
/*===========================================================================*/

/* ����ṹ */
struct LZH_OBJECT {
    LZH_ENGINE *engine;

    /* ����λ�� */
    float x, y;

    /* ����λ��ƫ��, Ĭ��Ϊ 0.0f */
    float offset_x, offset_y;

    /* ����ߴ� */
    float w, h;

    /* ˳ʱ�뷽�����ת�Ƕ� */
    float angle;

    /* ��ת���ģ�Ĭ��Ϊ�������ĵ� */
    float rx, ry;

    /* ���������� */
    LZH_VEC2F forward;

    /* ������� */
    LZH_SPRITE *sprite;
};

/*===========================================================================*/

#endif /* __LZH_CORE_OBJECT_H__ */
