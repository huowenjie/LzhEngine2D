#include <stddef.h>
#include <stdio.h>
#include <time.h>

#include <lzh_engine.h>
#include <lzh_object.h>
#include <lzh_mem.h>

#include <SDL_image.h>

#include "lzh_core_engine.h"
#include "lzh_engine_time.h"

#include "../graphic/lzh_opengl.h"
#include "../object/lzh_core_object.h"
#include "../log/lzh_tracer.h"

/*===========================================================================*/

/* 渲染队列中的对象 */
static void render_objects(int layer, int order, LZH_OBJECT *object, void *args);
static void render_objects_fixed(
    int layer, int order, LZH_OBJECT *object, void *args);

/*===========================================================================*/

int lzh_init()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    
    srand((unsigned int)time(NULL));

    lzh_init_opengl(3, 3);

    LZH_MEM_START;
    LZH_TRACE_START(1);
    LZH_TRACE_SHOW_DBG();
    return 0;
}

void lzh_quit() 
{
    LZH_TRACE_END();
    LZH_PRINT_LEAK_INFO;
    LZH_MEM_END;

    SDL_Quit();
}

/*===========================================================================*/

LZH_ENGINE *lzh_engine_create(
    const char *title, int width, int height)
{
    SDL_Window *window = NULL;
    SDL_GLContext *glctx = NULL;
    LZH_SCENE_MANAGER *manager = NULL;
    LZH_SHADER *shader = NULL;

    LZH_ENGINE *engine = LZH_MALLOC(sizeof(LZH_ENGINE));
    if (!engine) {
        return NULL;
    }

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window) {
        goto err;
    }

    glctx = SDL_GL_CreateContext(window);
    if (!glctx) {
        goto err;
    }

    lzh_load_openglapi();
    glViewport(0, 0, width, height);

    manager = lzh_scene_manager_create();
    if (!manager) {
        goto err;
    }

    shader = lzh_shader_sprite();
    if (!shader) {
        goto err;
    }

    engine->window = window;
    engine->glctx = glctx;
    engine->logic_fps = 30;
    engine->render_fps = 60;
    engine->delta_time = 0.0f;
    engine->scene_manager = manager;
    engine->sprite_shader = shader;

    lzh_engine_time_init(&engine->engine_time);
    return engine;

err:
    if (shader) {
        lzh_shader_destroy(shader);
    }

    if (manager) {
        lzh_scene_manager_destroy(manager);
    }

    if (glctx) {
        SDL_GL_DeleteContext(glctx);
    }

    if (window) {
        SDL_DestroyWindow(window);
    }

    if (engine) {
        LZH_FREE(engine);
    }
    return NULL;
}

void lzh_engine_destroy(LZH_ENGINE *engine)
{
    if (engine) {
        lzh_engine_time_quit(&engine->engine_time);

        if (engine->sprite_shader) {
            lzh_shader_destroy(engine->sprite_shader);
        }

        if (engine->scene_manager) {
            lzh_scene_manager_destroy(engine->scene_manager);
        }

        if (engine->glctx) {
            SDL_GL_DeleteContext(engine->glctx);
        }

        if (engine->window) {
            SDL_DestroyWindow(engine->window);
        }

        LZH_FREE(engine);
    }
}

#if 0
void lzh_engine_update(LZH_ENGINE *engine)
{
    int run = 1;
    GLbitfield mask = GL_COLOR_BUFFER_BIT;
    SDL_Event evt;
    SDL_Window *window = NULL;

    float fix_time = 0.0f;
    float render_time = 0.0f;
    float time_count = 0.0f;
    Uint64 prev_time = SDL_GetPerformanceCounter();

    if (!engine || !engine->logic_fps) {
        return;
    }

    window = engine->window;
    fix_time = 1000.0f / engine->logic_fps;
    render_time = 1000.0f / engine->render_fps;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    if (glIsEnabled(GL_DEPTH_TEST))
    {
        mask |= GL_DEPTH_BUFFER_BIT;
    }

    while (run) {
        Uint64 start = 0;
        Uint64 frequency = 0;

        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                run = 0;
                break;
            }

            switch (evt.type) {
                case SDL_KEYDOWN:
                    engine->engine_event |= LZH_EVT_KEY_DOWN;
                    break;

                default:
                    break;
            }
        }

        glClear(mask);

        /*
         * 假设某一帧渲染时间过长，导致时间累计大于当前的
         * 逻辑帧时间，则直接放弃这一帧的渲染，按照逻辑帧速率来追赶
         * 进度
         */
        while (time_count > fix_time) {
            time_count -= fix_time;

            /*
             * 1.scences fixed update 更新
             *   |
             *   |
             * 2.objects fixed update 更新
             *   |
             *   |
             * 3.components fixed update 更新
             */
             lzh_sm_fixedupdate(engine->scene_manager);
        }

        /*
         * 1.scences update 更新
         *   |
         *   |
         * 2.objects update 更新
         *   |
         *   |
         * 3.components update 更新
         */
        lzh_sm_update(engine->scene_manager);

        /* 场景绘制，调用所有对象的 draw 方法绘制 */
        lzh_sm_draw(engine->scene_manager);
        SDL_GL_SwapWindow(window);

        /* 剩余工作 */
        lzh_sm_last_handle(engine->scene_manager);

        /* 清理场景需要删除的对象 */
        lzh_sm_clear_objects(engine->scene_manager);

        start = SDL_GetPerformanceCounter();
        frequency = SDL_GetPerformanceFrequency();
        engine->delta_time = ((start - prev_time) * 1000.0f) / (float)frequency;

        prev_time = start;
        time_count += engine->delta_time;

        /* 清空事件 */
        engine->engine_event = LZH_EVT_NONE;

        if (engine->delta_time < render_time) {
            SDL_Delay((Uint32)(render_time - engine->delta_time));
        } else if (engine->delta_time > 250.0f) {
            engine->delta_time = 250.0f;
        }
    }
}
#else
void lzh_engine_update(LZH_ENGINE *engine)
{
    int run = 1;
    GLbitfield mask = GL_COLOR_BUFFER_BIT;
    SDL_Event evt;
    SDL_Window *window = NULL;

    float fix_time = 0.0f;

    LZH_UINT64 curtime = 0;
    LZH_UINT64 lasttime = 0;
    LZH_UINT64 elapsed = 0;

    if (!engine || !engine->logic_fps) {
        return;
    }

    window = engine->window;
    fix_time = 1.0f / engine->logic_fps;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    if (glIsEnabled(GL_DEPTH_TEST))
    {
        mask |= GL_DEPTH_BUFFER_BIT;
    }

    while (run) {
        int i = 0;
        int steps = 0;

        curtime = lzh_engine_time_tick_usec(&engine->engine_time);
        elapsed = curtime - lasttime;
        lasttime = curtime;
        engine->delta_time = lzh_engine_time_u2s(elapsed);

        /* 固定时间累计 */
        lzh_engine_time_fixed_accumulate(
            &engine->engine_time, engine->delta_time, fix_time, engine->logic_fps);
        steps = engine->engine_time.fixed_steps;

        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                run = 0;
                break;
            }

            switch (evt.type) {
                case SDL_KEYDOWN:
                    engine->engine_event |= LZH_EVT_KEY_DOWN;
                    break;

                default:
                    break;
            }
        }

        glClear(mask);

        /*
         * 假设某一帧渲染时间过长，导致时间累计大于当前的
         * 逻辑帧时间，则直接放弃这一帧的渲染，按照逻辑帧速率来追赶
         * 进度
         */
        for (i = 0; i < steps; i++) {
            /*
             * 1.scences fixed update 更新
             *   |
             *   |
             * 2.objects fixed update 更新
             *   |
             *   |
             * 3.components fixed update 更新
             */
             lzh_sm_fixedupdate(engine->scene_manager);
        }

        /*
         * 1.scences update 更新
         *   |
         *   |
         * 2.objects update 更新
         *   |
         *   |
         * 3.components update 更新
         */
        lzh_sm_update(engine->scene_manager);

        /* 场景绘制，调用所有对象的 draw 方法绘制 */
        lzh_sm_draw(engine->scene_manager);
        SDL_GL_SwapWindow(window);

        /* 剩余工作 */
        lzh_sm_last_handle(engine->scene_manager);

        /* 清理场景需要删除的对象 */
        lzh_sm_clear_objects(engine->scene_manager);

        /* 清空事件 */
        engine->engine_event = LZH_EVT_NONE;

        /* 帧延迟，节省资源 */
        lzh_engine_time_frame_delay(&engine->engine_time);
    }
}
#endif

float lzh_engine_interval(LZH_ENGINE *engine)
{
    if (engine) {
        return engine->delta_time;
    }
    return 0.0f;
}

float lzh_engine_fixed_interval(LZH_ENGINE *engine)
{
    if (engine) {
        return 1.0f / engine->logic_fps;
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

LZH_SCENE *lzh_engine_get_scene(LZH_ENGINE *engine, const char *name)
{
    if (engine) {
        return lzh_sm_get_scene(engine->scene_manager, name);
    }
    return NULL;
}

/*===========================================================================*/

void render_objects(int layer, int order, LZH_OBJECT *object, void *args)
{
    if (object && object->base.update) {
        object->base.update(&object->base, object->base.update_param);
    }
}

void render_objects_fixed(
    int layer, int order, LZH_OBJECT *object, void *args)
{
    if (object && object->base.fixed_update) {
        object->base.fixed_update(&object->base, object->base.fixed_update_param);
    }
}

/*===========================================================================*/
