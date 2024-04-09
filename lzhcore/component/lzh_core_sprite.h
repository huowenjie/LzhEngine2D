#ifndef __LZH_CORE_SPRITE_H__
#define __LZH_CORE_SPRITE_H__

#include <SDL2/SDL.h>
#include "lzh_component.h"

/*===========================================================================*/
/* 精灵(内部) */
/*===========================================================================*/

/* 判断状态 */
#define IS_SP_STATE(state, opt) (((state) & (opt)) == (opt))

/* 精灵状态 */
typedef enum {
    SSC_IMAGES_MODE = 0x00000001U,  /* 多图纹理模式*/
    SSC_SHEET_MODE = 0x00000002U,   /* 单图切片模式 */
    SSC_SHOW = 0x00000004U,         /* 显示精灵 */
    SSC_PLAY = 0x00000008U,         /* 播放帧动画 */
} SPRITE_STATE_CODE;

/* 关键帧 */
struct LZH_KEYFRAME {
    LZH_KEYFRAME_CB kf_cb;
    void *args;
};

/* 精灵对象 */
struct LZH_SPRITE {
    LZH_COMPONENT base;             /* 基本组件信息 */
    LZH_UINT32 state;               /* 精灵状态 */
    
    SDL_Vertex vertices[4];         /* 精灵顶点 */
    int indices[6];                 /* 矩形顶点索引 */

    SDL_Texture **textures;         /* 纹理列表 */
    int tex_count;                  /* 纹理数量 */

    SDL_Rect *rect_list;            /* 子切片区域列表 */
    int rect_count;                 /* 子切片数量 */

    int frame_count;                /* 帧数量 */
    int anim_fps;                   /* 动画帧数 */
    int prev_time;                  /* 播放上一帧的时间 */
    int cur_frame;                  /* 当前播放帧 */
    int start_frame;                /* 开始播放帧 */
    int end_frame;                  /* 结束播放帧 */

    struct LZH_KEYFRAME *kf_list;   /* 关键帧回调列表 */
};

/*===========================================================================*/

#endif /* __LZH_CORE_SPRITE_H__ */
