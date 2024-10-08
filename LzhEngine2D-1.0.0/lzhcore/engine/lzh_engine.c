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
    
    LZH_SHADER *sprite = NULL;
    LZH_SHADER *text = NULL;
    LZH_SPRITE_VERTEX *sp_vert = NULL;
    LZH_TEXT_VERTEX *text_vert = NULL;

    FT_Library ft = NULL;

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

    sprite = lzh_shader_sprite();
    if (!sprite) {
        goto err;
    }

    text = lzh_shader_text();
    if (!text) {
        goto err;
    }

    sp_vert = lzh_vertex_sprite();
    if (!sp_vert) {
        goto err;
    }

    text_vert = lzh_vertex_text();
    if (!text_vert) {
        goto err;
    }

    if (FT_Init_FreeType(&ft)) {
        goto err;
    }

    engine->window = window;
    engine->glctx = glctx;
    engine->logic_fps = 60;
    engine->render_fps = 60;
    engine->delta_time = 0.0f;
    engine->scene_manager = manager;
    engine->sprite_shader = sprite;
    engine->text_shader = text;
    engine->sprite_vertex = sp_vert;
    engine->text_vertex = text_vert;
    engine->ft_lib = ft;
    engine->window_scale = 0.1f;

    lzh_engine_time_init(&engine->engine_time);
    return engine;

err:
    if (ft) {
        FT_Done_FreeType(ft);
    }

    if (text_vert) {
        lzh_vertex_destroy(text_vert);
    }

    if (sp_vert) {
        lzh_vertex_destroy(sp_vert);
    }

    if (text) {
        lzh_shader_destroy(text);
    }

    if (sprite) {
        lzh_shader_destroy(sprite);
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

        if (engine->text_vertex) {
            lzh_vertex_destroy(engine->text_vertex);
        }

        if (engine->sprite_vertex) {
            lzh_vertex_destroy(engine->sprite_vertex);
        }

        if (engine->text_shader) {
            lzh_shader_destroy(engine->text_shader);
        }

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

        if (engine->ft_lib) {
            FT_Done_FreeType(engine->ft_lib);
        }

        LZH_FREE(engine);
    }
}

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

void lzh_engine_win_sizef(LZH_ENGINE *engine, float *w, float *h)
{
    int nw = 0;
    int nh = 0;

    lzh_engine_win_size(engine, &nw, &nh);

    if (w) {
        *w = (float)nw;
    }

    if (h) {
        *h = (float)nh;
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

LZH_CAMERA *lzh_engine_get_main_camera(LZH_ENGINE *engine)
{
    LZH_OBJECT *camera = NULL;
    LZH_CAMERA *camera_cpnt = NULL;
    LZH_SCENE *scene = NULL;

    if (!engine) {
        return NULL;
    }

    scene = lzh_sm_get_active_scene(engine->scene_manager);
    if (!scene) {
        return NULL;
    }

    camera = scene->main_camera;
    if (!camera) {
        return NULL;
    }

    camera_cpnt = (LZH_CAMERA *)lzh_cpnt_get_type(
        camera->components, LZH_CPNT_CAMERA);
    return camera_cpnt;
}

/*===========================================================================*/
