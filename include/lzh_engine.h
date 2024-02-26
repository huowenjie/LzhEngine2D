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

/* 设置更新回调 */
LZH_API void lzh_engine_set_update(
    LZH_ENGINE *engine, LZH_LOOP_UPDATE callback, void *args);

/* 设置固定帧率更新回调 */
LZH_API void lzh_engine_set_fixed_update(
    LZH_ENGINE *engine, LZH_LOOP_UPDATE callback, void *args);

/* 启动主循环渲染 */
LZH_API void lzh_engine_render(LZH_ENGINE *engine);

/* 获取当前帧间隔时间 ms */
LZH_API float lzh_engine_interval(LZH_ENGINE *engine);

/* 获取当前帧间隔时间 ms */
LZH_API float lzh_engine_interval_msec(LZH_ENGINE *engine);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_ENGINE_H__ */
