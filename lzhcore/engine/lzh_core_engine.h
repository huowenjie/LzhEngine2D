#ifndef __LZH_CORE_ENGINE_H__
#define __LZH_CORE_ENGINE_H__

#include <SDL.h>
#include <lzh_type.h>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "lzh_engine_time.h"

#include "../scene/lzh_scene_manager.h"
#include "../graphic/lzh_shader.h"

/*===========================================================================*/
/* 引擎对象 */
/*===========================================================================*/

#define LZH_EVT_NONE        0x00000000U /* 无事件*/
#define LZH_EVT_KEY_DOWN    0x00000001U /* 键盘按下事件 */

/* 引擎对象 */
struct LZH_ENGINE {
    SDL_Window *window;
    SDL_GLContext *glctx;

    int logic_fps;                      /* 逻辑帧数 */
    int render_fps;                     /* 渲染帧帧数 */
    float delta_time;                   /* 帧间隔时间 ms */

    LZH_UINT32 engine_event;            /* 引擎状态事件 */

    LZH_SCENE_MANAGER *scene_manager;   /* 场景管理 */
    LZH_SHADER *sprite_shader;          /* 通用的精灵着色器 */

    LZH_ENGINE_TIME engine_time;        /* 引擎时间 */

    FT_Library ft_lib;                  /* freeType 库对象 */
};

/*===========================================================================*/

#endif /* __LZH_CORE_ENGINE_H__ */