#include <stddef.h>
#include <lzh_engine.h>

#include "lzh_istruct.h"
#include "lzh_mem.h"

/*===========================================================================*/

int lzh_init()
{
    SDL_Init(SDL_INIT_VIDEO);

    LZH_MEM_START;
    return 0;
}

void lzh_quit() 
{
    LZH_PRINT_LEAK_INFO;
    LZH_MEM_END;

    SDL_Quit();
}

LZH_ENGINE *lzh_engine_create(
    const char *title, int width, int height)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    LZH_ENGINE *engine = LZH_MALLOC(sizeof(LZH_ENGINE));
    if (!engine) {
        return NULL;
    }

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        goto err;
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED);
    if (!window) {
        goto err;
    }

    engine->window = window;
    engine->renderer = renderer;
    return engine;

err:
    if (engine) {
        LZH_FREE(engine);
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }
    return NULL;
}

void lzh_engine_destroy(LZH_ENGINE *engine)
{
    if (engine) {
        if (engine->renderer) {
            SDL_DestroyRenderer(engine->renderer);
        }

        if (engine->window) {
            SDL_DestroyWindow(engine->window);
        }

        LZH_FREE(engine);
    }
}

void lzh_engine_set_update(
    LZH_ENGINE *engine, LZH_LOOP_UPDATE callback, void *args)
{
    if (engine) {
        engine->engine_update = callback;
        engine->args = args;
    }
}

void lzh_engine_render(LZH_ENGINE *engine)
{
    int run = 1;
    SDL_Event evt;
    SDL_Renderer *renderer = NULL;

    if (!engine) {
        return;
    }

    renderer = engine->renderer;

    while (run)
    {
        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_QUIT)
            {
                run = 0;
                break;
            }
        }

        if (engine->engine_update) {
            engine->engine_update(engine, engine->args);
        }

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }
}

/*===========================================================================*/
