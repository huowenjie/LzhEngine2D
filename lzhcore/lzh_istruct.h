#ifndef __LZH_ISTRUCT_H__
#define __LZH_ISTRUCT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lzh_type.h"

/*===========================================================================*/
/* �ڲ��ṹ */
/*===========================================================================*/

/* ������� */
struct LZH_ENGINE {
    SDL_Window *window;
    SDL_Renderer *renderer;

    LZH_LOOP_UPDATE render_update;
    LZH_LOOP_UPDATE fixed_update;
    void *render_args;
    void *fixed_args;

    Uint32 logic_fps;      /* �߼�֡֡�� ms */
    Uint32 render_fps;     /* ��Ⱦ֡֡�� ms */
    Uint32 pause_delay;    /* ��ͣ��ʱ ms */
    Uint32 delta_time;     /* ֡���ʱ�� ms */
};

/* ����ģʽ */
typedef enum {
    SPM_SINGLE_IMAGES = 0,  /* ��ͼģʽ */
    SPM_MULT_IMAGES,        /* ��ͼģʽ */
    SPM_SINGLE_SHEET        /* ��ͼ�ָ�ģʽ */
} SPRITE_MODE;

/* ��ͼģʽ����ṹ */
struct SINGLE_SPRITE {
    SDL_Texture *texture;
};

/* ��ͼģʽ����ṹ */
struct MULT_SPRITE{
    SDL_Texture *texture;
    int count;
};

/* ��ͼ�ָ�ṹ */
struct SHEET_SPRITE {
    SDL_Texture *texture;

    SDL_Rect *rect_list;
    int count;
};

/* ������� */
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
