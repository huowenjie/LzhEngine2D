#ifndef __LZH_ISTRUCT_H__
#define __LZH_ISTRUCT_H__

#include <SDL2/SDL.h>
#include "lzh_type.h"

/*===========================================================================*/
/* 内部结构 */
/*===========================================================================*/

struct LZH_ENGINE {
    SDL_Window *window;
    SDL_Renderer *renderer;

    LZH_UINT32 (*engine_update)(LZH_ENGINE *, void *);
    void *args;
};

/*===========================================================================*/

#endif /* __LZH_ISTRUCT_H__ */
