#include <string.h>
#include <SDL2/SDL_image.h>
#include <lzh_sprite.h>
#include <lzh_mem.h>
#include <lzh_engine.h>

#include "lzh_core_sprite.h"
#include "../object/lzh_core_object.h"
#include "../engine/lzh_core_engine.h"
#include "../component/lzh_core_transform.h"
#include "../math/lzh_mathdef.h"

/*===========================================================================*/

/* 添加纹理 */
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

/* 计算坐标系转换矩阵 */
static LZH_MAT4X4F get_sdl_mat(LZH_TRANSFORM *transform)
{
    int iw = 0;
    int ih = 0;
    float fw = 0.0f;
    float fh = 0.0f;
    float hw = 0.0f;

    float fixed_w = 800.0f;
    float fixed_h = 0.0f;

    LZH_VEC3F refn;
    LZH_MAT4X4F refmat = lzh_mat4x4f_unit();
    LZH_MAT4X4F scalemat = lzh_mat4x4f_unit();
    LZH_MAT4X4F transmat = lzh_mat4x4f_unit();
    LZH_MAT4X4F sdlmat = lzh_mat4x4f_unit();

    if (!transform) {
        return sdlmat;
    }

    /* 获取屏幕尺寸 */
    lzh_engine_win_size(transform->base.base.engine, &iw, &ih);
    fw = (float)iw;
    fh = (float)ih;

    if (fw == 0 || fh == 0) {
        return sdlmat;
    }

    /* 计算屏幕高宽比 */
    hw = fh / fw;
    fixed_h = fixed_w * hw;

    /* 计算缩放比例 */
    scalemat = lzh_mat4x4f_scale(fw / fixed_w, fh / fixed_h, 1.0f);

    /* 先按比例进行缩放，然后 y 轴镜像翻转，最后平移 */
    refn = lzh_vec3f_xyz(0.0f, 1.0f, 0.0f);
    transmat = lzh_mat4x4f_translate(fw / 2.0f, fh / 2.0f, 0.0f);
    refmat = lzh_mat4x4f_reflect(&refn);
    sdlmat = lzh_mat4x4f_mul(&scalemat, &sdlmat);
    sdlmat = lzh_mat4x4f_mul(&refmat, &sdlmat);
    sdlmat = lzh_mat4x4f_mul(&transmat, &sdlmat);

    return sdlmat;
}

static LZH_BOOL get_target_rect(
    LZH_TRANSFORM *transform, SDL_Texture *texture, SDL_FRect *target, SDL_FPoint *center)
{
    int iw = 0;
    int ih = 0;
    float fw = 0.0f;
    float fh = 0.0f;

    float scalex = 0.0f;
    float scaley = 0.0f;

    LZH_MAT4X4F sdlmat;
    LZH_MAT4X4F scale;
    LZH_VEC3F center_pos;
    LZH_VEC4F screen_pos;
    LZH_VEC3F screen_scale;

    if (!transform || !texture || !target) {
        return LZH_FALSE;
    }

    if (SDL_QueryTexture(texture, NULL, NULL, &iw, &ih)) {
        return LZH_FALSE;
    }

    fw = (float)iw;
    fh = (float)ih;

    sdlmat = get_sdl_mat(transform);

    screen_pos = lzh_vec4f_vec3f(&transform->world_pos, 1.0f);
    screen_pos = lzh_mat4x4f_mul_vec(&sdlmat, &screen_pos);
    scale = lzh_mat4x4f_get_scale(&sdlmat);
    screen_scale = lzh_vec3f_xyz(scale.m00, scale.m11, scale.m22);

    scalex = screen_scale.x * transform->world_scale.x;
    scaley = screen_scale.y * transform->world_scale.y;

    target->x = screen_pos.x - fw / 2.0f * scalex;
    target->y = screen_pos.y - fh / 2.0f * scaley;
    target->w = scalex * fw;
    target->h = scaley * fh;
    center_pos = transform->center_pos;

    center->x = fw / 2.0f * scalex + center_pos.x;
    center->y = fh / 2.0f * scaley + center_pos.y;
    return LZH_TRUE;
}

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
            if (get_target_rect(
                transform, textures[cur_frame], &target, &center)) {
                float angle = LZH_R2A(transform->world_angle);
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
