#ifndef __LZH_CAMERA_H__
#define __LZH_CAMERA_H__

#include "lzh_type.h"

/*===========================================================================*/
/* �������� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* ���������� */
LZH_API LZH_CAMERA *lzh_camera_create(LZH_ENGINE *engine);

/* ���������� */
LZH_API void lzh_camera_destroy(LZH_CAMERA *camera);

/* �������ͶӰ�ӿڵ�λ���ȺͿ�� */
LZH_API void lzh_camera_set_viewport(
    LZH_CAMERA *camera, float width, float height);

/* ���������͸��ͶӰЧ�����رպ�Ϊ����ͶӰ */
LZH_API void lzh_camera_set_perspective(LZH_CAMERA *camera, LZH_BOOL perspective);

/* ���ע��Ŀ��λ�� */
LZH_API void lzh_camera_lookat(LZH_CAMERA *camera, float x, float y, float z);

/* ����Ϸ���Ĭ��Ϊ (0.0f, 1.0f, 0.0f) */
LZH_API void lzh_camera_set_updir(LZH_CAMERA *camera, float x, float y, float z);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_CAMERA_H__ */
