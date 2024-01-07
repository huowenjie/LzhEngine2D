#include <stddef.h>
#include <lzh_engine.h>

#include "lzh_istruct.h"
#include "lzh_mem.h"

/*===========================================================================*/

int lzh_init()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    LZH_MEM_START;
    return 0;
}

void lzh_quit() 
{
    LZH_PRINT_LEAK_INFO;
    LZH_MEM_END;

    IMG_Quit();
    SDL_Quit();
}

/*===========================================================================*/

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
    engine->logic_fps = 30;
    engine->render_fps = 60;
    engine->pause_delay = 250;
    engine->delta_time = 0;
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
        engine->render_update = callback;
        engine->render_args = args;
    }
}

void lzh_engine_set_fixed_update(
    LZH_ENGINE *engine, LZH_LOOP_UPDATE callback, void *args)
{
    if (engine) {
        engine->fixed_update = callback;
        engine->fixed_args = args;
    }
}

void lzh_engine_render(LZH_ENGINE *engine)
{
    int run = 1;
    SDL_Event evt;
    SDL_Renderer *renderer = NULL;

    Uint64 fix_time = 0;
    Uint64 render_time = 0;
    Uint64 prev_time = 0;
    Uint64 time_count = 0;
    Uint64 render_count = 0;

    if (!engine || !engine->logic_fps) {
        return;
    }

    renderer = engine->renderer;
    fix_time = 1000 / engine->logic_fps;
    render_time = 1000 / engine->render_fps;

    while (run)
    {
        /* 获取当前时间 */
        Uint64 start = 0;

        /* 如果帧时间过长（比如发生暂停等操作，这里则重置时间） */
        if (engine->delta_time > engine->pause_delay) {
            engine->delta_time = engine->pause_delay;
        }

        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_QUIT)
            {
                run = 0;
                break;
            }
        }

        /*
         * 假设某一帧渲染时间过长，导致时间累计大于当前的
         * 逻辑帧时间，则直接放弃这一帧的渲染，按照逻辑帧速率来追赶
         * 进度
         */
        if (engine->fixed_update) {
            while (time_count > fix_time) {
                time_count -= fix_time;
                engine->fixed_update(engine, engine->fixed_args);
            }
        }

        SDL_RenderClear(renderer);

        if (engine->render_update) {
            engine->render_update(engine, engine->render_args);
        }

        SDL_RenderPresent(renderer);

        /* 计算增量时间  */
        start = SDL_GetTicks64();
        engine->delta_time = (Uint32)(start - prev_time);
        prev_time = start;
        time_count += engine->delta_time;
        render_count += engine->delta_time;

        /* 渲染帧锁定 60 帧 */
        if (render_time > engine->delta_time) {
            SDL_Delay((Uint32)(render_time - engine->delta_time));
        }
    }
}

int lzh_engine_delta(LZH_ENGINE *engine)
{
    if (engine) {
        return engine->delta_time;
    }
    return 0;
}

/*===========================================================================*/
