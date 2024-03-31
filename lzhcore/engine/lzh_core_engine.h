#ifndef __LZH_CORE_ENGINE_H__
#define __LZH_CORE_ENGINE_H__

#include <SDL2/SDL.h>

#include "lzh_type.h"

/*===========================================================================*/
/* ����(�ڲ�) */
/*===========================================================================*/

#define LZH_EVT_NONE        0x00000000U /* ���¼�*/
#define LZH_EVT_KEY_DOWN    0x00000001U /* ���̰����¼� */

/* ������� */
struct LZH_ENGINE {
    SDL_Window *window;
    SDL_Renderer *renderer;

    float logic_fps;                /* �߼�֡֡�� */
    float render_fps;               /* ��Ⱦ֡֡�� */
    float pause_delay;              /* ��ͣ��ʱ ms */
    float delta_time;               /* ֡���ʱ�� ms */

    LZH_UINT32 engine_event;        /* ����״̬�¼� */
};

/*===========================================================================*/

#endif /* __LZH_CORE_ENGINE_H__ */