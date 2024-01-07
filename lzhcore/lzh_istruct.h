#ifndef __LZH_ISTRUCT_H__
#define __LZH_ISTRUCT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lzh_type.h"

/*===========================================================================*/
/* 内部结构 */
/*===========================================================================*/

/* 引擎对象 */
struct LZH_ENGINE {
    SDL_Window *window;
    SDL_Renderer *renderer;

    LZH_LOOP_UPDATE render_update;
    LZH_LOOP_UPDATE fixed_update;
    void *render_args;
    void *fixed_args;

    Uint32 logic_fps;      /* 逻辑帧帧率 ms */
    Uint32 render_fps;     /* 渲染帧帧率 ms */
    Uint32 pause_delay;    /* 暂停延时 ms */
    Uint32 delta_time;     /* 帧间隔时间 ms */
};

/* 集合模式 */
typedef enum {
    SPM_SINGLE_IMAGES = 0,  /* 单图模式 */
    SPM_MULT_IMAGES,        /* 多图模式 */
    SPM_SINGLE_SHEET        /* 单图分割模式 */
} SPRITE_MODE;

/* 单图模式精灵结构 */
struct SINGLE_SPRITE {
    SDL_Texture *texture;
};

/* 多图模式精灵结构 */
struct MULT_SPRITE{
    SDL_Texture *texture;
    int count;
};

/* 单图分割结构 */
struct SHEET_SPRITE {
    SDL_Texture *texture;

    SDL_Rect *rect_list;
    int count;
};

/* 精灵对象 */
struct LZH_SPRITE {
    LZH_ENGINE *engine;
    SPRITE_MODE mode;

    int x, y;
    int w, h;

    union {
        struct SINGLE_SPRITE single_sp;
        struct MULT_SPRITE mult_sp;
        struct SHEET_SPRITE sheets_sp;
    };
};

/*===========================================================================*/

#endif /* __LZH_ISTRUCT_H__ */
