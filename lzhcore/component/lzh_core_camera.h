#ifndef __LZH_CORE_CAMERA_H__
#define __LZH_CORE_CAMERA_H__

#include "../math/lzh_mat4x4f.h"
#include "lzh_component.h"

/*===========================================================================*/
/* ����������(�ڲ�) */
/*===========================================================================*/

#define LZH_CAMERA_PERSP 0 /* ͸����� */
#define LZH_CAMERA_ORTHO 1 /* ������� */

/* ������� */
struct LZH_CAMERA {
    LZH_COMPONENT base; /* ���������Ϣ */
    LZH_UINT32 type;    /* ������� */

    float view_port_w;  /* �ӿڿ�� */
    float view_port_h;  /* �ӿڸ߶� */

    LZH_MAT4X4F view;   /* ��ͼ���� */
    LZH_MAT4X4F prog;   /* ͶӰ���� */
};

/*===========================================================================*/

#endif /* __LZH_CORE_CAMERA_H__ */
