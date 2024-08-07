#ifndef __LZH_ENGINE_H__
#define __LZH_ENGINE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* ��ʼ�� */
LZH_API int lzh_init();

/* ��ֹ */
LZH_API void lzh_quit();

/* ������Ⱦ������� */
LZH_API LZH_ENGINE *lzh_engine_create(
    const char *title, int width, int height);

/* �������� */
LZH_API void lzh_engine_destroy(LZH_ENGINE *engine);

/* ������ѭ����Ⱦ */
LZH_API void lzh_engine_update(LZH_ENGINE *engine);

/* ��ȡ��ǰ֡���ʱ�� ms */
LZH_API float lzh_engine_interval(LZH_ENGINE *engine);

/* ��ȡ�̶�֡��� ms */
LZH_API float lzh_engine_fixed_interval(LZH_ENGINE *engine);

/* ��ȡ��ǰ֡���ʱ�� ms */
LZH_API float lzh_engine_interval_msec(LZH_ENGINE *engine);

/* ��ȡ���ڳߴ� */
LZH_API void lzh_engine_win_size(LZH_ENGINE *engine, int *w, int *h);

/* ��ȡ���ڳߴ磬������ */
LZH_API void lzh_engine_win_sizef(LZH_ENGINE *engine, float *w, float *h);

/* ��ȡ�������� */
LZH_API LZH_SCENE *lzh_engine_get_scene(LZH_ENGINE *engine, const char *name);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_ENGINE_H__ */