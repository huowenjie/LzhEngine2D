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

/* 初始化顶点数据 */
static void init_sprite_vertex(LZH_SPRITE *sp);

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

    init_sprite_vertex(sprite);
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

void lzh_sprite_get_img_size(LZH_SPRITE *sprite, int index, float *w, float *h)
{
    
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

void init_sprite_vertex(LZH_SPRITE *sp)
{
    SDL_Vertex *vertex = NULL;
    int *indices = NULL;

    if (!sp) {
        return;
    }

    vertex = sp->vertices;
    indices = sp->indices;

    /*
     * SDL_Vertex vertices[] = {
     *     { { -1.0f, -1.0f }, { 255, 255, 255, 255 }, { 0.0f, 0.0f } },
     *     { {  1.0f, -1.0f }, { 255, 255, 255, 255 }, { 1.0f, 0.0f } },
     *     { {  1.0f,  1.0f }, { 255, 255, 255, 255 }, { 1.0f, 1.0f } },
     *     { { -1.0f,  1.0f }, { 255, 255, 255, 255 }, { 0.0f, 1.0f } }
     * };
     * 
     * int indices[] = { 0, 1, 2, 2, 3, 0 };
     */
    vertex[0].position.x = -1.0f;
    vertex[0].position.y = -1.0f;
    vertex[0].color.r = 255;
    vertex[0].color.g = 255;
    vertex[0].color.b = 255;
    vertex[0].color.a = 255;
    vertex[0].tex_coord.x = 0.0f;
    vertex[0].tex_coord.y = 0.0f;

    vertex[1].position.x = 1.0f;
    vertex[1].position.y = -1.0f;
    vertex[1].color.r = 255;
    vertex[1].color.g = 255;
    vertex[1].color.b = 255;
    vertex[1].color.a = 255;
    vertex[1].tex_coord.x = 1.0f;
    vertex[1].tex_coord.y = 0.0f;

    vertex[2].position.x = 1.0f;
    vertex[2].position.y = 1.0f;
    vertex[2].color.r = 255;
    vertex[2].color.g = 255;
    vertex[2].color.b = 255;
    vertex[2].color.a = 255;
    vertex[2].tex_coord.x = 1.0f;
    vertex[2].tex_coord.y = 1.0f;

    vertex[3].position.x = -1.0f;
    vertex[3].position.y = 1.0f;
    vertex[3].color.r = 255;
    vertex[3].color.g = 255;
    vertex[3].color.b = 255;
    vertex[3].color.a = 255;
    vertex[3].tex_coord.x = 0.0f;
    vertex[3].tex_coord.y = 1.0f;

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;
}

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

    float fixed_w = 0.0f;
    float fixed_h = 0.0f;

    LZH_VEC3F l;
    LZH_VEC3F h;
    LZH_VEC3F lp;
    LZH_VEC3F hp;
    LZH_VEC3F refn;
    LZH_MAT4X4F refmat = lzh_mat4x4f_unit();
    LZH_MAT4X4F projmat = lzh_mat4x4f_unit();
    LZH_MAT4X4F sdlmat = lzh_mat4x4f_unit();

    if (!transform) {
        return sdlmat;
    }

    fixed_w = transform->screen_width;
    fixed_h = transform->screen_height;

    /* 获取屏幕尺寸 */
    lzh_engine_win_size(transform->base.base.engine, &iw, &ih);
    fw = (float)iw;
    fh = (float)ih;

    if (fw == 0 || fh == 0) {
        return sdlmat;
    }

    fw = fixed_w / 2.0f;
    fh = fixed_h / 2.0f;

    /* 对 y 轴镜像翻转，最后平移 */
    refn = lzh_vec3f_xyz(0.0f, 1.0f, 0.0f);
    l = lzh_vec3f_xyz(-fw, -fh, 0.0f);
    h = lzh_vec3f_xyz(fw, fh, 1.0f);
    lp = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    hp = lzh_vec3f_xyz((float)iw, (float)ih, 1.0f);

    refmat = lzh_mat4x4f_reflect(&refn);
    projmat = lzh_mat4x4f_volume_map(&l, &h, &lp, &hp);

    sdlmat = lzh_mat4x4f_mul(&refmat, &sdlmat);
    sdlmat = lzh_mat4x4f_mul(&projmat, &sdlmat);
    return sdlmat;
}

static void update_sprite_vertex(LZH_TRANSFORM *transform, LZH_SPRITE *sprite)
{
    LZH_MAT4X4F sdlmat;
    LZH_MAT4X4F worldmat;

    LZH_VEC4F vertext_pos;
    SDL_Vertex *vertices = NULL;

    if (!transform || !sprite) {
        return;
    }

    worldmat = transform->world_mat;
    sdlmat = get_sdl_mat(transform);
    worldmat = lzh_mat4x4f_mul(&sdlmat, &worldmat);

    vertices = sprite->vertices;

    vertext_pos = lzh_vec4f_xyzw(-1.0f, -1.0f, 0.0f, 1.0f);
    vertext_pos = lzh_mat4x4f_mul_vec(&worldmat, &vertext_pos);
    vertices[0].position.x = vertext_pos.x;
    vertices[0].position.y = vertext_pos.y;

    vertext_pos = lzh_vec4f_xyzw(1.0f, -1.0f, 0.0f, 1.0f);
    vertext_pos = lzh_mat4x4f_mul_vec(&worldmat, &vertext_pos);
    vertices[1].position.x = vertext_pos.x;
    vertices[1].position.y = vertext_pos.y;

    vertext_pos = lzh_vec4f_xyzw(1.0f, 1.0f, 0.0f, 1.0f);
    vertext_pos = lzh_mat4x4f_mul_vec(&worldmat, &vertext_pos);
    vertices[2].position.x = vertext_pos.x;
    vertices[2].position.y = vertext_pos.y;

    vertext_pos = lzh_vec4f_xyzw(-1.0f, 1.0f, 0.0f, 1.0f);
    vertext_pos = lzh_mat4x4f_mul_vec(&worldmat, &vertext_pos);
    vertices[3].position.x = vertext_pos.x;
    vertices[3].position.y = vertext_pos.y;
}

void lzh_sprite_draw(LZH_BASE *base, void *args)
{
    LZH_SPRITE *sprite = NULL;
    LZH_OBJECT *object = NULL;
    LZH_ENGINE *engine = NULL;
    LZH_TRANSFORM *transform = NULL;

    int cur_frame = 0;

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
            update_sprite_vertex(transform, sprite);
            SDL_RenderGeometry(
                engine->renderer,
                textures[cur_frame],
                sprite->vertices,
                sizeof(sprite->vertices) / sizeof(SDL_Vertex),
                sprite->indices,
                sizeof(sprite->indices) / sizeof(int));
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
