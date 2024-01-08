#ifndef __LZH_ISTRUCT_H__
#define __LZH_ISTRUCT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lzh_type.h"
#include "lzh_render_queue.h"

/*===========================================================================*/
/* 内部结构 */
/*===========================================================================*/

/* 引擎对象 */
struct LZH_ENGINE {
    SDL_Window *window;
    SDL_Renderer *renderer;

    /* 渲染队列 */
    struct RENDER_LAYER_QUEUE *render_queue;

    LZH_LOOP_UPDATE render_update;
    LZH_LOOP_UPDATE fixed_update;
    void *render_args;
    void *fixed_args;

    float logic_fps;      /* 逻辑帧帧率 ms */
    float render_fps;     /* 渲染帧帧率 ms */
    float pause_delay;    /* 暂停延时 ms */
    float delta_time;     /* 帧间隔时间 ms */
};

/* 组合模式 */
typedef enum {
    SP_IMAGES = 0,          /* 多图模式 */
    SP_SHEET                /* 单图切片模式 */
} SPRITE_COMB_MODE;

/* 多图模式精灵节点 */
struct SPRITE_IMAGES_NODE {
    struct SPRITE_IMAGES_NODE *prev;
    struct SPRITE_IMAGES_NODE *next;

    SDL_Texture *texture;
};

/* 多图模式精灵结构 */
struct SPRITE_IMAGES {
    struct SPRITE_IMAGES_NODE *head;
    struct SPRITE_IMAGES_NODE *tail;

    int count;
};

/* 单图切片模式结构 */
struct SPRITE_SHEET {
    SDL_Texture *texture;

    SDL_Rect *rect_list;
    int count;
};

/* 精灵对象 */
struct LZH_SPRITE {
    SPRITE_COMB_MODE mode;

    union {
        struct SPRITE_IMAGES images;
        struct SPRITE_SHEET sheet;
    };
};

/* 对象结构 */
struct LZH_OBJECT {
    LZH_ENGINE *engine;

    int x, y;
    int w, h;

    LZH_SPRITE *sprite;
};

/*===========================================================================*/

#endif /* __LZH_ISTRUCT_H__ */
