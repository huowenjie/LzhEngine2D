#include <string.h>
#include <SDL2/SDL_image.h>
#include <lzh_sprite.h>
#include <lzh_mem.h>

#include "lzh_core_sprite.h"
#include "../engine/lzh_core_engine.h"

/*===========================================================================*/

static void add_sprite_texture(
    LZH_ENGINE *engine, LZH_SPRITE *sp, const char *res[], int count);

/*===========================================================================*/

LZH_SPRITE *lzh_sprite_create(LZH_ENGINE *engine, const char *res)
{
    LZH_SPRITE *sprite = NULL;
    LZH_COMPONENT *base = NULL;

    if (!engine) {
        return NULL;
    }

    if (!res || !*res) {
        return NULL;
    }

    sprite = LZH_MALLOC(sizeof(LZH_SPRITE));
    if (!sprite) {
        return NULL;
    }
    memset(sprite, 0, sizeof(LZH_SPRITE));

    base = &sprite->base;
    base->context.engine = engine;
    base->type = LZH_CPNT_SPRITE;

    sprite->state = SSC_IMAGES_MODE | SSC_SHOW;
    sprite->frame_count = 1;
    sprite->anim_fps = 30;
    sprite->prev_time = 0;
    sprite->cur_frame = 0;
    sprite->start_frame = 0;
    sprite->end_frame = 0;
    add_sprite_texture(engine, sprite, &res, 1);
    return sprite;
}

LZH_SPRITE *lzh_sprite_create_from_images(
    LZH_ENGINE *engine, const char *res_list[], int count)
{
    LZH_SPRITE *sprite = NULL;
    LZH_COMPONENT *base = NULL;

    if (!engine) {
        return NULL;
    }

    if (!res_list || count <= 0) {
        return NULL;
    }

    sprite = LZH_MALLOC(sizeof(LZH_SPRITE));
    if (!sprite) {
        return NULL;
    }
    memset(sprite, 0, sizeof(LZH_SPRITE));

    base = &sprite->base;
    base->context.engine = engine;
    base->type = LZH_CPNT_SPRITE;

    sprite->state = SSC_IMAGES_MODE | SSC_SHOW | SSC_PLAY;
    sprite->frame_count = count;
    sprite->anim_fps = 30;
    sprite->prev_time = 0;
    sprite->cur_frame = 0;
    sprite->start_frame = 0;
    sprite->end_frame = count - 1;
    add_sprite_texture(engine, sprite, res_list, count);
    return sprite;
}

#if 0
LZH_SPRITE *lzh_sprite_create_from_sheets(
    LZH_ENGINE *engine, const LZH_RECT *rect_list, int count)
{
    return NULL;
}
#endif

void lzh_sprite_destroy(LZH_SPRITE *sprite)
{
    if (sprite) {
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

void lzh_sprite_show(LZH_SPRITE *sprite, LZH_BOOL show)
{
    if (sprite) {
        if (show) {
            sprite->state |= SSC_SHOW;
        } else {
            sprite->state &= (~SSC_SHOW);
        }
    }
}

void lzh_sprite_set_fps(LZH_SPRITE *sprite, int fps)
{
    if (sprite && fps > 0) {
        sprite->anim_fps = fps;
    }
}

void lzh_sprite_enable_play(LZH_SPRITE *sprite, LZH_BOOL enable)
{
    if (sprite) {
        if (enable) {
            sprite->state |= SSC_PLAY;
        } else {
            sprite->state &= (~SSC_PLAY);
        }
    }
}

void lzh_sprite_set_start_frame(LZH_SPRITE *sprite, int start)
{
    if (sprite && start >= 0 && start < sprite->frame_count) {
        sprite->start_frame = start;
    }
}

void lzh_sprite_set_end_frame(LZH_SPRITE *sprite, int end)
{
    if (sprite && end >= 0 && end < sprite->frame_count) {
        sprite->end_frame = end;
    }
}

void lzh_sprite_set_keyframe(
    LZH_SPRITE *sprite, int frame, LZH_KEYFRAME_CB cb, void *args)
{
    struct LZH_KEYFRAME *kf_list = NULL;
    int count = 0;

    if (!sprite || !cb) {
        return;
    }

    count = sprite->frame_count;
    if (count <= 1) {
        return;
    }

    if (frame < 0 || frame >= count) {
        return;
    }

    if (sprite->kf_list) {
        kf_list = sprite->kf_list;
    } else {
        kf_list = LZH_MALLOC(count * sizeof(struct LZH_KEYFRAME));
        if (!kf_list) {
            return;
        }
        memset(kf_list, 0, count * sizeof(struct LZH_KEYFRAME));

        sprite->kf_list = kf_list;
    }

    kf_list[frame].kf_cb = cb;
    kf_list[frame].args = args;
}

/*===========================================================================*/

void add_sprite_texture(
    LZH_ENGINE *engine, LZH_SPRITE *sp, const char *res[], int count)
{
    SDL_Texture **textures = NULL;
    int i = 0;

    if (!engine || !sp) {
        return;
    }

    if (!res) {
        return;
    }

    if (count <= 0) {
        return;
    }

    textures = LZH_MALLOC(count * sizeof(SDL_Texture *));
    if (!textures) {
        return;
    }
    memset(textures, 0, count * sizeof(SDL_Texture *));

    for (; i < count; i++) {
        SDL_Texture *texture = NULL;
        SDL_Surface *surface = IMG_Load(res[i]);

        if (surface) {
            texture = SDL_CreateTextureFromSurface(engine->renderer, surface);
            if (texture) {
                textures[i] = texture;
            }
            SDL_FreeSurface(surface);
        }
    }

    sp->tex_count = count;
    sp->textures = textures;
}

/*===========================================================================*/
