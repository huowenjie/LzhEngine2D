#ifndef __LZH_CORE_CAMERA_H__
#define __LZH_CORE_CAMERA_H__

#include "../math/lzh_mat4x4f.h"
#include "lzh_component.h"

/*===========================================================================*/
/* 相机组件定义(内部) */
/*===========================================================================*/

#define LZH_CAMERA_PERSP 0 /* 透视相机 */
#define LZH_CAMERA_ORTHO 1 /* 正交相机 */

/* 相机对象 */
struct LZH_CAMERA {
    LZH_COMPONENT base; /* 基本组件信息 */
    LZH_UINT32 type;    /* 相机类型 */

    float view_port_w;  /* 视口宽度 */
    float view_port_h;  /* 视口高度 */

    LZH_MAT4X4F view;   /* 视图矩阵 */
    LZH_MAT4X4F prog;   /* 投影矩阵 */
};

/*===========================================================================*/

#endif /* __LZH_CORE_CAMERA_H__ */
