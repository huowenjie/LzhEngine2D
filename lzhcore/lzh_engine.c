#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <lzh_engine.h>
#include <lzh_object.h>
#include <SDL2/SDL_image.h>

#include "lzh_core_engine.h"
#include "lzh_core_object.h"
#include "lzh_mem.h"

/*===========================================================================*/

/* 渲染队列中的对象 */
static void render_objects(int layer, int order, LZH_OBJECT *object, void *args);
static void render_objects_fixed(
    int layer, int order, LZH_OBJECT *object, void *args);

/*===========================================================================*/

int lzh_init()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    srand((unsigned int)time(NULL));

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
    RT_RB_TREE *render_tree = NULL;

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

    render_tree = create_render_tree();
    if (!render_tree) {
        goto err;
    }

    engine->window = window;
    engine->renderer = renderer;
    engine->render_tree = render_tree;
    engine->logic_fps = 30.0f;
    engine->render_fps = 60.0f;
    engine->pause_delay = 250.0f;
    engine->delta_time = 0.0f;
    return engine;

err:
    if (render_tree) {
        destroy_render_tree(render_tree);
    }

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
        if (engine->render_tree) {
            destroy_render_tree(engine->render_tree);
        }

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

    float fix_time = 0.0f;
    float render_time = 0.0f;
    float time_count = 0.0f;
    Uint64 prev_time = SDL_GetPerformanceCounter();

    if (!engine || !engine->logic_fps) {
        return;
    }

    renderer = engine->renderer;
    fix_time = 1000.0f / engine->logic_fps;
    render_time = 1000.0f / engine->render_fps;

    while (run) {
        Uint64 start = 0;
        Uint64 frequency = 0;

        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                run = 0;
                break;
            }
        }

        SDL_RenderClear(renderer);

        /*
         * 假设某一帧渲染时间过长，导致时间累计大于当前的
         * 逻辑帧时间，则直接放弃这一帧的渲染，按照逻辑帧速率来追赶
         * 进度
         */
        if (engine->fixed_update) {
            while (time_count > fix_time) {
                time_count -= fix_time;

                render_tree_iterate(
                    engine->render_tree, render_objects_fixed, engine);

                engine->fixed_update(engine, engine->fixed_args);
            }
        } else {
            time_count = 0.0f;
        }

        render_tree_iterate(engine->render_tree, render_objects, engine);
        
        if (engine->render_update) {
            engine->render_update(engine, engine->render_args);
        }

        SDL_RenderPresent(renderer);

        start = SDL_GetPerformanceCounter();
        frequency = SDL_GetPerformanceFrequency();
        engine->delta_time = ((start - prev_time) * 1000.0f) / (float)frequency;

        prev_time = start;
        time_count += engine->delta_time;

        if (engine->delta_time < render_time) {
            SDL_Delay((Uint32)(render_time - engine->delta_time));
        } else if (engine->delta_time > 250.0f) {
            engine->delta_time = 250.0f;
        }
    }
}

float lzh_engine_interval(LZH_ENGINE *engine)
{
    if (engine) {
        return engine->delta_time / 1000.0f;
    }
    return 0.0f;
}

float lzh_engine_interval_msec(LZH_ENGINE *engine)
{
    if (engine) {
        return engine->delta_time;
    }
    return 0.0f;
}

void lzh_engine_win_size(LZH_ENGINE *engine, int *w, int *h)
{
    if (engine) {
        SDL_GetWindowSize(engine->window, w, h);
    }
}

/*===========================================================================*/

void render_objects(int layer, int order, LZH_OBJECT *object, void *args)
{
    if (object) {
        lzh_object_update(object);
    }
}

void render_objects_fixed(
    int layer, int order, LZH_OBJECT *object, void *args)
{
    if (object) {
        lzh_object_fixedupdate(object);
    }
}

/*===========================================================================*/
