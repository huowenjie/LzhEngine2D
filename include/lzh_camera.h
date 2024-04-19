#ifndef __LZH_CAMERA_H__
#define __LZH_CAMERA_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 摄像机组件 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 创建相机组件 */
LZH_API LZH_CAMERA *lzh_camera_create(LZH_ENGINE *engine);

/* 销毁相机组件 */
LZH_API void lzh_camera_destroy(LZH_CAMERA *camera);

/* 设置相机投影视口单位长度和宽度 */
LZH_API void lzh_camera_set_viewport(
    LZH_CAMERA *camera, float width, float height);

/* 开启相机的透视投影效果，关闭后为正交投影 */
LZH_API void lzh_camera_set_perspective(LZH_CAMERA *camera, LZH_BOOL perspective);

/* 相机注视目标位置 */
LZH_API void lzh_camera_lookat(LZH_CAMERA *camera, float x, float y, float z);

/* 相机上方向，默认为 (0.0f, 1.0f, 0.0f) */
LZH_API void lzh_camera_set_updir(LZH_CAMERA *camera, float x, float y, float z);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_CAMERA_H__ */
