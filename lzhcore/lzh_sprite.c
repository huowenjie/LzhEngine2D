#include "lzh_sprite.h"
#include "lzh_istruct.h"
#include "lzh_mem.h"

/*===========================================================================*/

LZH_SPRITE *lzh_sprite_create(LZH_ENGINE *engine, const char *res)
{
    LZH_SPRITE *sprite = NULL;
    SDL_Texture *texture = NULL;
    SDL_Surface *surface = NULL;

    int defw = 0;
    int defh = 0;

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

    surface = IMG_Load(res);
    if (!surface) {
        goto err;
    }

    defw = surface->w;
    defh = surface->h;

    texture = SDL_CreateTextureFromSurface(engine->renderer, surface);
    if (!texture) {
        goto err;
    }
    SDL_FreeSurface(surface);

    sprite->engine = engine;
    sprite->texture = texture;
    sprite->x = 0;
    sprite->y = 0;
    sprite->w = defw;
    sprite->h = defh;
    return sprite;

err:
    if (surface) {
        SDL_FreeSurface(surface);
    }

    if (texture) {
        SDL_DestroyTexture(texture);
    }

    if (sprite) {
        LZH_FREE(sprite);
    }
    return NULL;
}

LZH_SPRITE *lzh_sprite_create_from_images(
    LZH_ENGINE *engine, const char *res_list[], int count)
{
}

LZH_SPRITE *lzh_sprite_create_from_sheets(
    LZH_ENGINE *engine, const LZH_RECT *rect_list, int count)
{
}

void lzh_sprite_destroy(LZH_SPRITE *sprite)
{
    if (sprite) {
        if (sprite->texture) {
            SDL_DestroyTexture(sprite->texture);
        }
        LZH_FREE(sprite);
    }
}

void lzh_sprite_set_size(LZH_SPRITE *sprite, int w, int h)
{
    if (sprite) {
        sprite->w = w;
        sprite->h = h;
    }
}

void lzh_sprite_set_pos(LZH_SPRITE *sprite, int x, int y)
{
    if (sprite) {
        sprite->x = x;
        sprite->y = y;
    }
}

void lzh_sprite_render(LZH_SPRITE *sprite)
{
    LZH_ENGINE *engine = NULL;
    SDL_Rect target;

    if (!sprite || !sprite->engine) {
        return;
    }

    engine = sprite->engine;

    target.x = sprite->x;
    target.y = sprite->y;
    target.w = sprite->w;
    target.h = sprite->h;

    SDL_RenderCopy(engine->renderer, sprite->texture, NULL, &target);
}

void lzh_sprite_render_sheet(LZH_SPRITE *sprite, int index)
{

}

void lzh_sprite_render_anim(LZH_SPRITE *sprite, int index)
{
}

/*===========================================================================*/
