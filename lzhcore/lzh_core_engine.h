#ifndef __LZH_CORE_ENGINE_H__
#define __LZH_CORE_ENGINE_H__

#include <SDL2/SDL.h>

#include "lzh_type.h"
#include "lzh_render_tree.h"

/*===========================================================================*/
/* ����(�ڲ�) */
/*===========================================================================*/

/* ������� */
struct LZH_ENGINE {
    SDL_Window *window;
    SDL_Renderer *renderer;

    RT_RB_TREE *render_tree;        /* ��Ⱦ������ */

    LZH_LOOP_UPDATE render_update;
    LZH_LOOP_UPDATE fixed_update;
    void *render_args;
    void *fixed_args;

    float logic_fps;                /* �߼�֡֡�� */
    float render_fps;               /* ��Ⱦ֡֡�� */
    float pause_delay;              /* ��ͣ��ʱ ms */
    float delta_time;               /* ֡���ʱ�� ms */
};

/*===========================================================================*/

#endif /* __LZH_CORE_ENGINE_H__ */