#ifndef __LZH_ISTRUCT_H__
#define __LZH_ISTRUCT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lzh_type.h"
#include "lzh_render_queue.h"

/*===========================================================================*/
/* �ڲ��ṹ */
/*===========================================================================*/

/* ������� */
struct LZH_ENGINE {
    SDL_Window *window;
    SDL_Renderer *renderer;

    /* ��Ⱦ���� */
    struct RENDER_LAYER_QUEUE *render_queue;

    LZH_LOOP_UPDATE render_update;
    LZH_LOOP_UPDATE fixed_update;
    void *render_args;
    void *fixed_args;

    float logic_fps;      /* �߼�֡֡�� ms */
    float render_fps;     /* ��Ⱦ֡֡�� ms */
    float pause_delay;    /* ��ͣ��ʱ ms */
    float delta_time;     /* ֡���ʱ�� ms */
};

/* ���ģʽ */
typedef enum {
    SP_IMAGES = 0,          /* ��ͼģʽ */
    SP_SHEET                /* ��ͼ��Ƭģʽ */
} SPRITE_COMB_MODE;

/* ��ͼģʽ����ڵ� */
struct SPRITE_IMAGES_NODE {
    struct SPRITE_IMAGES_NODE *prev;
    struct SPRITE_IMAGES_NODE *next;

    SDL_Texture *texture;
};

/* ��ͼģʽ����ṹ */
struct SPRITE_IMAGES {
    struct SPRITE_IMAGES_NODE *head;
    struct SPRITE_IMAGES_NODE *tail;

    int count;
};

/* ��ͼ��Ƭģʽ�ṹ */
struct SPRITE_SHEET {
    SDL_Texture *texture;

    SDL_Rect *rect_list;
    int count;
};

/* ������� */
struct LZH_SPRITE {
    SPRITE_COMB_MODE mode;

    union {
        struct SPRITE_IMAGES images;
        struct SPRITE_SHEET sheet;
    };
};

/* ����ṹ */
struct LZH_OBJECT {
    LZH_ENGINE *engine;

    int x, y;
    int w, h;

    LZH_SPRITE *sprite;
};

/*===========================================================================*/

#endif /* __LZH_ISTRUCT_H__ */
