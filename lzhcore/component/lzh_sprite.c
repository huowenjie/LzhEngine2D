#include <string.h>
#include <SDL2/SDL_image.h>
#include <lzh_sprite.h>
#include <lzh_mem.h>

#include "lzh_core_sprite.h"
#include "../object/lzh_core_object.h"
#include "../engine/lzh_core_engine.h"
#include "../component/lzh_core_transform.h"

/*===========================================================================*/

static void add_sprite_texture(
    LZH_ENGINE *engine, LZH_SPRITE *sp, const char *res[], int count);

/* 精灵渲染 */
static void lzh_sprite_draw(LZH_BASE *base, void *args);

/* 移除子组件，不更改所属对象的信息 */
static void lzh_sprite_remove(LZH_COMPONENT *cpnt);

/* 渲染帧动画 */
static int calc_images_frame(LZH_SPRITE *sprite);

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
    lzh_cpnt_init(base);

    base->base.engine = engine;
    base->base.draw = lzh_sprite_draw;
    base->type = LZH_CPNT_SPRITE;
    base->remove_component = lzh_sprite_remove;

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
    lzh_cpnt_init(base);

    base->base.engine = engine;
    base->type = LZH_CPNT_SPRITE;
    base->remove_component = lzh_sprite_remove;

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
        /* 从所属对象组件表中移除组件对象 */
        if (sprite->base.object) {
            LZH_OBJECT *obj = sprite->base.object;
            lzh_cpnt_rb_delete(obj->components, LZH_CPNT_SPRITE, NULL, NULL);
            sprite->base.object = NULL;
        }
        lzh_sprite_remove((LZH_COMPONENT *)sprite);
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

void lzh_sprite_draw(LZH_BASE *base, void *args)
{
    LZH_SPRITE *sprite = NULL;
    LZH_OBJECT *object = NULL;
    LZH_ENGINE *engine = NULL;
    LZH_TRANSFORM *transform = NULL;

    int cur_frame = 0;
    SDL_FRect target;
    SDL_FPoint center;

    if (!base) {
        return;
    }

    sprite = (LZH_SPRITE *)base;
    object = sprite->base.object;
    engine = object->base.engine;

    if (!object || !engine) {
        return;
    }

    transform = object->transform;
    if (!transform) {
        return;
    }

    if (!IS_SP_STATE(sprite->state, SSC_SHOW)) {
        return;
    }

    cur_frame = calc_images_frame(sprite);

    if (IS_SP_STATE(sprite->state, SSC_IMAGES_MODE)) {
        SDL_Texture **textures = sprite->textures;
        if (textures && textures[cur_frame]) {
            int iw = 0;
            int ih = 0;
            float fw = 0.0f;
            float fh = 0.0f;
            float angle = 0.0f;
            
            if (!SDL_QueryTexture(
                textures[cur_frame], NULL, NULL, &iw, &ih)) {
                fw = (float)iw;
                fh = (float)ih;

                target.x = transform->world_pos.x;
                target.y = transform->world_pos.y;
                target.w = transform->world_scale.x * fw;
                target.h = transform->world_scale.y * fh;

                center.x = transform->center_pos.x;
                center.y = transform->center_pos.y;
                angle = transform->world_angle;

                transform->world_pos;

                SDL_RenderCopyExF(
                    engine->renderer,
                    textures[cur_frame],
                    NULL,
                    &target,
                    angle,
                    &center,
                    SDL_FLIP_NONE);
            }
        }
    }

    /* 调用关键帧回调 */
    if (sprite->kf_list && IS_SP_STATE(sprite->state, SSC_PLAY)) {
        struct LZH_KEYFRAME *kf = sprite->kf_list + cur_frame;

        if (kf->kf_cb) {
            kf->kf_cb(kf->args);
        }
    }
}

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

        lzh_cpnt_quit((LZH_COMPONENT *)sprite);
        LZH_FREE(sprite);
    }
}

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
