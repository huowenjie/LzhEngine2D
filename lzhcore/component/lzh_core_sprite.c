#include <lzh_sprite.h>

#include "lzh_core_sprite.h"
#include "../object/lzh_core_object.h"

/*===========================================================================*/

/* 渲染帧动画 */
static int calc_images_frame(LZH_SPRITE *sprite);

/*===========================================================================*/

void lzh_sprite_render(LZH_OBJECT *object, LZH_SPRITE *sprite)
{
#if 0
    LZH_ENGINE *engine = NULL;

    int cur_frame = 0;
    SDL_FRect target;
    SDL_FPoint center;

    if (!object || !sprite || !object->context.engine) {
        return;
    }

    if (!IS_SP_STATE(sprite->state, SSC_SHOW)) {
        return;
    }

    engine = object->context.engine;

    target.x = object->x;
    target.y = object->y;
    target.w = object->w;
    target.h = object->h;

    center.x = object->rx;
    center.y = object->ry;

    cur_frame = calc_images_frame(sprite);

    if (IS_SP_STATE(sprite->state, SSC_IMAGES_MODE)) {
        SDL_Texture **textures = sprite->textures;

        if (textures && textures[cur_frame]) {
            SDL_RenderCopyExF(
                engine->renderer,
                textures[cur_frame],
                NULL,
                &target,
                object->angle,
                &center,
                SDL_FLIP_NONE);
        }
    }

    /* 调用关键帧回调 */
    if (sprite->kf_list && IS_SP_STATE(sprite->state, SSC_PLAY)) {
        struct LZH_KEYFRAME *kf = sprite->kf_list + cur_frame;

        if (kf->kf_cb) {
            kf->kf_cb(kf->args);
        }
    }
#endif
}

/*===========================================================================*/

void lzh_sprite_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_SPRITE *sprite = (LZH_SPRITE *)cpnt;

        if (IS_SP_STATE(sprite->state, SSC_IMAGES_MODE)) {
            SDL_Texture **textures = sprite->textures;
            if (textures) {
                int i;
                for (i = 0; i < sprite->tex_count; i++) {
                    if (textures[i]) {
                        SDL_DestroyTexture(textures[i]);
                    }
                }
                LZH_FREE(textures);
            }
        }

        if (sprite->kf_list) {
            LZH_FREE(sprite->kf_list);
        }

        LZH_FREE(sprite);
    }
}

/*===========================================================================*/

int calc_images_frame(LZH_SPRITE *sprite)
{
    int per_frame = 0;
    int cur_frame = 0;
    int cur_time = 0;
    int start = 0;
    int end = 0;

    if (!sprite || !IS_SP_STATE(sprite->state, SSC_PLAY)) {
        return 0;
    }

    per_frame = 1000 / sprite->anim_fps;
    cur_frame = sprite->cur_frame;
    start = sprite->start_frame;
    end = sprite->end_frame + 1;
    cur_time = (int)SDL_GetTicks64();

    if ((cur_time - sprite->prev_time) > per_frame) {
        cur_frame = start + (cur_frame + 1) % end;
        sprite->cur_frame = cur_frame;
        sprite->prev_time = cur_time;
    }

    return cur_frame;
}

/*===========================================================================*/
