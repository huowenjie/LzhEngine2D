#ifndef __LZH_CORE_ENGINE_H__
#define __LZH_CORE_ENGINE_H__

#include <SDL2/SDL.h>

#include "lzh_type.h"
#include "../scene/lzh_scene_manager.h"

/*===========================================================================*/
/* 引擎(内部) */
/*===========================================================================*/

#define LZH_EVT_NONE        0x00000000U /* 无事件*/
#define LZH_EVT_KEY_DOWN    0x00000001U /* 键盘按下事件 */

/* 引擎对象 */
struct LZH_ENGINE {
    SDL_Window *window;
    SDL_Renderer *renderer;

    float logic_fps;                    /* 逻辑帧帧数 */
    float render_fps;                   /* 渲染帧帧数 */
    float pause_delay;                  /* 暂停延时 ms */
    float delta_time;                   /* 帧间隔时间 ms */

    LZH_UINT32 engine_event;            /* 引擎状态事件 */

    LZH_SCENE_MANAGER *scene_manager;   /* 场景管理 */
};

/*===========================================================================*/

#endif /* __LZH_CORE_ENGINE_H__ */