#ifndef __LZH_CORE_ENGINE_H__
#define __LZH_CORE_ENGINE_H__

#include <SDL2/SDL.h>

#include "lzh_type.h"
#include "lzh_render_tree.h"

/*===========================================================================*/
/* 引擎(内部) */
/*===========================================================================*/

/* 引擎对象 */
struct LZH_ENGINE {
    SDL_Window *window;
    SDL_Renderer *renderer;

    RT_RB_TREE *render_tree;        /* 渲染树对象 */

    LZH_LOOP_UPDATE render_update;
    LZH_LOOP_UPDATE fixed_update;
    void *render_args;
    void *fixed_args;

    float logic_fps;                /* 逻辑帧帧数 */
    float render_fps;               /* 渲染帧帧数 */
    float pause_delay;              /* 暂停延时 ms */
    float delta_time;               /* 帧间隔时间 ms */
};

/*===========================================================================*/

#endif /* __LZH_CORE_ENGINE_H__ */