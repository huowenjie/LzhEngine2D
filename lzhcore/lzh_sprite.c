#include <string.h>

#include "lzh_sprite.h"
#include "lzh_istruct.h"
#include "lzh_mem.h"
#include "lzh_link.h"

/*===========================================================================*/

static void add_sprite_texture(
    LZH_ENGINE *engine, LZH_SPRITE *sp, const char *res);

/*===========================================================================*/

LZH_SPRITE *lzh_sprite_create(LZH_ENGINE *engine, const char *res)
{
    LZH_SPRITE *sprite = NULL;

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

    sprite->mode = SP_IMAGES;
    add_sprite_texture(engine, sprite, res);
    return sprite;
}

LZH_SPRITE *lzh_sprite_create_from_images(
    LZH_ENGINE *engine, const char *res_list[], int count)
{
    LZH_SPRITE *sprite = NULL;
    int i = 0;

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

    sprite->mode = SP_IMAGES;

    for (; i < count; i++) {
        add_sprite_texture(engine, sprite, res_list[i]);
    }
    return sprite;
}

LZH_SPRITE *lzh_sprite_create_from_sheets(
    LZH_ENGINE *engine, const LZH_RECT *rect_list, int count)
{
    return NULL;
}

void lzh_sprite_destroy(LZH_SPRITE *sprite)
{
    if (sprite) {
        if (sprite->mode == SP_IMAGES) {
            LINK *link = (LINK *)&sprite->images;
            while (link->count > 0) {
                struct SPRITE_IMAGES_NODE *node = 
                    (struct SPRITE_IMAGES_NODE *)link_pop(link);
                if (node && node->texture) {
                    SDL_DestroyTexture(node->texture);
                    LZH_FREE(node);
                }
            }
        }

        LZH_FREE(sprite);
    }
}

void lzh_sprite_render(LZH_SPRITE *sprite)
{
}

void lzh_sprite_render_sheet(LZH_SPRITE *sprite, int index)
{

}

void lzh_sprite_render_anim(LZH_SPRITE *sprite, int index)
{
}

/*===========================================================================*/

void add_sprite_texture(
    LZH_ENGINE *engine, LZH_SPRITE *sp, const char *res)
{
    struct SPRITE_IMAGES *sp_images = NULL;
    struct SPRITE_IMAGES_NODE *node = NULL;

    SDL_Texture *texture = NULL;
    SDL_Surface *surface = NULL;

    if (!engine || !sp) {
        return;
    }

    if (!res || !*res) {
        return;
    }

    sp_images = &sp->images;

    node = LZH_MALLOC(sizeof(struct SPRITE_IMAGES_NODE));
    if (!node) {
        return;
    }
    memset(node, 0, sizeof(struct SPRITE_IMAGES_NODE));

    surface = IMG_Load(res);
    if (!surface) {
        goto err;
    }

    texture = SDL_CreateTextureFromSurface(engine->renderer, surface);
    if (!texture) {
        goto err;
    }
    SDL_FreeSurface(surface);

    node->texture = texture;
    link_push((LINK *)sp_images, (LINK_NODE *)node);
    return;

err:
    if (node) {
        LZH_FREE(node);
    }

    if (surface) {
        SDL_FreeSurface(surface);
    }

    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

/*===========================================================================*/
