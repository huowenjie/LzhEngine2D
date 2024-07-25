#ifndef __LZH_ENGINE_H__
#define __LZH_ENGINE_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 窗口 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 初始化 */
LZH_API int lzh_init();

/* 终止 */
LZH_API void lzh_quit();

/* 创建渲染引擎对象 */
LZH_API LZH_ENGINE *lzh_engine_create(
    const char *title, int width, int height);

/* 销毁引擎 */
LZH_API void lzh_engine_destroy(LZH_ENGINE *engine);

/* 启动主循环渲染 */
LZH_API void lzh_engine_update(LZH_ENGINE *engine);

/* 获取当前帧间隔时间 ms */
LZH_API float lzh_engine_interval(LZH_ENGINE *engine);

/* 获取固定帧间隔 ms */
LZH_API float lzh_engine_fixed_interval(LZH_ENGINE *engine);

/* 获取当前帧间隔时间 ms */
LZH_API float lzh_engine_interval_msec(LZH_ENGINE *engine);

/* 获取窗口尺寸 */
LZH_API void lzh_engine_win_size(LZH_ENGINE *engine, int *w, int *h);

/* 获取窗口尺寸，浮点数 */
LZH_API void lzh_engine_win_sizef(LZH_ENGINE *engine, float *w, float *h);

/* 获取场景对象 */
LZH_API LZH_SCENE *lzh_engine_get_scene(LZH_ENGINE *engine, const char *name);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_ENGINE_H__ */
