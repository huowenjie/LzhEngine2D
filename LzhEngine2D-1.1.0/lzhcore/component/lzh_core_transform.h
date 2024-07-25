#ifndef __LZH_CORE_TRANSFORM_H__
#define __LZH_CORE_TRANSFORM_H__

#include "../math/lzh_quat4f.h"
#include "lzh_component.h"

/*===========================================================================*/
/* 变换组件定义 */
/*===========================================================================*/

struct LZH_TRANSFORM {
    LZH_COMPONENT base;         /* 基本组件信息 */

    float screen_width;         /* 屏幕坐标宽度（以世界坐标系的单位来标定） */
    float screen_height;        /* 屏幕坐标高度（以世界坐标系的单位来标定） */

    LZH_VEC3F local_pos;        /* 对象局部坐标 */
    LZH_VEC3F center_pos;       /* 中心点 */
    LZH_VEC3F local_scale;      /* 本地坐标缩放 */
    LZH_QUAT4F local_rotate;    /* 本地旋转 */

    LZH_VEC3F forward;          /* 前，沿 x 轴正方向，相对向前对象的坐标系 */
    LZH_VEC3F backward;         /* 后，沿 x 轴负方向，相对向前对象的坐标系 */
    LZH_VEC3F leftward;         /* 左，沿 y 轴正方向，相对向前对象的坐标系 */
    LZH_VEC3F rightward;        /* 右，沿 y 轴负方向，相对向前对象的坐标系 */

    LZH_MAT4X4F model_mat;      /* 模型矩阵 */
};

/* 创建组件 */
LZH_TRANSFORM *lzh_transform_create(LZH_ENGINE *engine, LZH_OBJECT *object);

/* 销毁组件 */
void lzh_transform_destroy(LZH_TRANSFORM *transform);

/* 刷新变换数据 */
void lzh_transform_flush(LZH_TRANSFORM *transform);

/*===========================================================================*/

#endif /* __LZH_CORE_TRANSFORM_H__ */
