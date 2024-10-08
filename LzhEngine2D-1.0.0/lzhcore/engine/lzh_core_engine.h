#ifndef __LZH_CORE_ENGINE_H__
#define __LZH_CORE_ENGINE_H__

#include <SDL.h>
#include <lzh_type.h>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "lzh_engine_time.h"

#include "../scene/lzh_scene_manager.h"
#include "../graphic/lzh_shader.h"
#include "../graphic/lzh_vertex.h"

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
    LZH_SHADER *text_shader;            /* 通用的文本渲染着色器 */
    LZH_SPRITE_VERTEX *sprite_vertex;   /* 通用 sprite 顶点 */
    LZH_TEXT_VERTEX *text_vertex;       /* 通用 text 顶点 */

    LZH_ENGINE_TIME engine_time;        /* 引擎时间 */

    FT_Library ft_lib;                  /* freeType 库对象 */

    float window_scale;                 /* 窗口缩放系数 */
};

/* 获取主相机 */
LZH_CAMERA *lzh_engine_get_main_camera(LZH_ENGINE *engine);

/*===========================================================================*/

#endif /* __LZH_CORE_ENGINE_H__ */