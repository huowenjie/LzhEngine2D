#include <string.h>
#include <lzh_object.h>
#include <lzh_sprite.h>

#include "lzh_mem.h"
#include "lzh_istruct.h"

/*===========================================================================*/

static void lzh_obj_render_sprite(LZH_OBJECT *object, LZH_SPRITE *sprite);

/*===========================================================================*/

LZH_OBJECT *lzh_object_create(LZH_ENGINE *engine)
{
    LZH_OBJECT *obj = NULL;

    if (!engine) {
        return NULL;
    }

    obj = LZH_MALLOC(sizeof(LZH_OBJECT));
    if (!obj) {
        return NULL;
    }

    render_queue_push(engine->render_queue, 0, obj);

    obj->engine = engine;
    obj->x = 0;
    obj->y = 0;
    obj->w = 0;
    obj->h = 0;

    return obj;
}

void lzh_object_destroy(LZH_OBJECT *object)
{
    if (object) {
        LZH_FREE(object);
    }
}

void lzh_object_set_size(LZH_OBJECT *object, int w, int h)
{
    if (object) {
        object->w = w;
        object->h = h;
    }
}

void lzh_object_set_pos(LZH_OBJECT *object, int x, int y)
{
    if (object) {
        object->x = x;
        object->y = y;
    }
}

void lzh_object_render(LZH_OBJECT *object)
{
    if (object) {
        if (object->sprite) {
            lzh_obj_render_sprite(object, object->sprite);
        }
    }
}

void lzh_object_set_sprite(LZH_OBJECT *object, LZH_SPRITE *sp)
{
    if (object && sp) {
        object->sprite = sp;
    }
}

/*===========================================================================*/

void lzh_obj_render_sprite(LZH_OBJECT *object, LZH_SPRITE *sprite)
{
    LZH_ENGINE *engine = NULL;
    SDL_Rect target;

    if (!object || !sprite || !object->engine) {
        return;
    }

    engine = object->engine;

    target.x = object->x;
    target.y = object->y;
    target.w = object->w;
    target.h = object->h;

    if (sprite->mode == SP_IMAGES) {
        struct SPRITE_IMAGES_NODE *node = sprite->images.head;

        if (node) {
            SDL_Texture *texture = node->texture;
            if (texture) {
                SDL_RenderCopy(engine->renderer, texture, NULL, &target);
            }
        }
    }
}

/*===========================================================================*/
