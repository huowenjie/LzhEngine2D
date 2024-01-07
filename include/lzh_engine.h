#ifndef __LZH_ENGINE_H__
#define __LZH_ENGINE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* ��������� */
typedef struct LZH_ENGINE LZH_ENGINE;

/* ��ѭ�����»ص� */
typedef LZH_UINT32 (*LZH_LOOP_UPDATE)(LZH_ENGINE *, void *);

/*===========================================================================*/

/* ��ʼ�� */
LZH_API int lzh_init();

/* ��ֹ */
LZH_API void lzh_quit();

/* ������Ⱦ������� */
LZH_API LZH_ENGINE *lzh_engine_create(
    const char *title, int width, int height);

/* �������� */
LZH_API void lzh_engine_destroy(LZH_ENGINE *engine);

/* ���ø��»ص� */
LZH_API void lzh_engine_set_update(
    LZH_ENGINE *engine, LZH_LOOP_UPDATE callback, void *args);

/* ������ѭ����Ⱦ */
LZH_API void lzh_engine_render(LZH_ENGINE *engine);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_ENGINE_H__ */
