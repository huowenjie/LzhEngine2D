#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>
#include <lzh_object.h>

#include "lzh_istruct.h"
#include "lzh_mem.h"

/*===========================================================================*/

/* 渲染队列中的对象 */
static void render_queue_object(LZH_ENGINE *engine);

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
    struct RENDER_LAYER_QUEUE *render_queue = NULL;

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

    render_queue = create_render_layer_queue();
    if (!render_queue) {
        goto err;
    }

    engine->window = window;
    engine->renderer = renderer;
    engine->render_queue = render_queue;
    engine->logic_fps = 30.0f;
    engine->render_fps = 60.0f;
    engine->pause_delay = 250.0f;
    engine->delta_time = 0.0f;
    return engine;

err:
    if (render_queue) {
        destroy_render_layer_queue(render_queue);
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
        if (engine->render_queue) {
            destroy_render_layer_queue(engine->render_queue);
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
    float prev_time = 0.0f;
    float time_count = 0.0f;
    float render_count = 0.0f;

    if (!engine || !engine->logic_fps) {
        return;
    }

    renderer = engine->renderer;
    fix_time = 1000.0f / engine->logic_fps;
    render_time = 1000.0f / engine->render_fps;

    while (run)
    {
        /* 计算增量时间  */
        float start = 0.0f;

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
        } else {
            time_count = 0.0f;
        }

        if (engine->render_update) {
            engine->render_update(engine, engine->render_args);
        }

        SDL_RenderClear(renderer);
        render_queue_object(engine);
        SDL_RenderPresent(renderer);

        start = (float)SDL_GetTicks64();

        engine->delta_time = start - prev_time;
        prev_time = start;
        time_count += engine->delta_time;
        render_count += engine->delta_time;

        /* 渲染帧锁定 60 帧 */
        if (render_count > render_time) {
            render_count -= render_time;
            SDL_Delay((Uint32)render_time);
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

/*===========================================================================*/

void render_queue_object(LZH_ENGINE *engine)
{
    struct RENDER_LAYER_QUEUE_NODE *rlq_elem = NULL;
    struct RENDER_LAYER_QUEUE *rld_link = NULL;
    int i = 0;

    if (!engine || !engine->render_queue) {
        return;
    }

    rld_link = engine->render_queue;
    rlq_elem = rld_link->head;
    while (i++ < rld_link->count) {
        struct RENDER_QUEUE *rq_link = rlq_elem->render_queue;
        if (rq_link) {
            int j = 0;
            struct RENDER_QUEUE_NODE *rq_elem = rq_link->head;
            while (j++ < rq_link->count) {
                lzh_object_render(rq_elem->object);
                rq_elem = rq_elem->next;
            }
        }

        rlq_elem = rlq_elem->next;
    }
}

/*===========================================================================*/
