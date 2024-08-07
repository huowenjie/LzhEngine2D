#ifndef __LZH_CORE_SPRITE_H__
#define __LZH_CORE_SPRITE_H__

#include <SDL.h>
#include "../graphic/lzh_texture.h"

#include "lzh_component.h"

/*===========================================================================*/
/* ����(�ڲ�) */
/*===========================================================================*/

/* �ж�״̬ */
#define IS_SP_STATE(state, opt) (((state) & (opt)) == (opt))

/* ����״̬ */
typedef enum {
    SSC_IMAGES_MODE = 0x00000001U,  /* ��ͼ����ģʽ*/
    SSC_SHEET_MODE = 0x00000002U,   /* ��ͼ��Ƭģʽ */
    SSC_SHOW = 0x00000004U,         /* ��ʾ���� */
    SSC_PLAY = 0x00000008U,         /* ����֡���� */
    SSC_REPLAY = 0x00000010U,       /* �Ƿ�ѭ������ */
} SPRITE_STATE_CODE;

/* �ؼ�֡ */
struct LZH_KEYFRAME {
    LZH_KEYFRAME_CB kf_cb;
    void *args;
};

/* ������� */
struct LZH_SPRITE {
    LZH_COMPONENT base;                 /* ���������Ϣ */
    LZH_UINT32 state;                   /* ����״̬ */

    LZH_TEXTURE **textures;             /* �����б� */
    int tex_count;                      /* �������� */

    SDL_Rect *rect_list;                /* ����Ƭ�����б� */
    int rect_count;                     /* ����Ƭ���� */

    int frame_count;                    /* ֡���� */
    int anim_fps;                       /* ����֡�� */
    int prev_time;                      /* ������һ֡��ʱ�� */
    int cur_frame;                      /* ��ǰ����֡ */
    int start_frame;                    /* ��ʼ����֡ */
    int end_frame;                      /* ��������֡ */
    int prev_frame;                     /* ��һ֡ */

    struct LZH_KEYFRAME *kf_list;       /* �ؼ�֡�ص��б� */
};

/*===========================================================================*/

#endif /* __LZH_CORE_SPRITE_H__ */