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
/* ������� */
/*===========================================================================*/

#define LZH_EVT_NONE        0x00000000U /* ���¼�*/
#define LZH_EVT_KEY_DOWN    0x00000001U /* ���̰����¼� */

/* ������� */
struct LZH_ENGINE {
    SDL_Window *window;
    SDL_GLContext *glctx;

    int logic_fps;                      /* �߼�֡�� */
    int render_fps;                     /* ��Ⱦ֡֡�� */
    float delta_time;                   /* ֡���ʱ�� ms */

    LZH_UINT32 engine_event;            /* ����״̬�¼� */

    LZH_SCENE_MANAGER *scene_manager;   /* �������� */

    LZH_SHADER *sprite_shader;          /* ͨ�õľ�����ɫ�� */
    LZH_SHADER *text_shader;            /* ͨ�õ��ı���Ⱦ��ɫ�� */
    LZH_SPRITE_VERTEX *sprite_vertex;   /* ͨ�� sprite ���� */
    LZH_TEXT_VERTEX *text_vertex;       /* ͨ�� text ���� */

    LZH_ENGINE_TIME engine_time;        /* ����ʱ�� */

    FT_Library ft_lib;                  /* freeType ����� */

    float window_scale;                 /* ��������ϵ�� */
};

/* ��ȡ����� */
LZH_CAMERA *lzh_engine_get_main_camera(LZH_ENGINE *engine);

/*===========================================================================*/

#endif /* __LZH_CORE_ENGINE_H__ */