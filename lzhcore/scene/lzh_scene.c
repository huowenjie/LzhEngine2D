#include <stdio.h>
#include <string.h>
#include <lzh_mem.h>
#include <lzh_scene.h>

#include "lzh_core_scene.h"

/*===========================================================================*/

/* 场景渲染队列渲染回调 */
static void lzh_scene_update(LZH_BASE *base, void *args);
static void lzh_scene_fixedupdate(LZH_BASE *base, void *args);

/* 生成新名称 */
static const char *lzh_gen_new_name();

/*===========================================================================*/

LZH_SCENE *lzh_scene_create(LZH_ENGINE *engine)
{
    LZH_SCENE *scene = NULL;
    LZH_BASE *base = NULL;

    if (!engine) {
        return NULL;
    }

    scene = LZH_MALLOC(sizeof(LZH_SCENE));
    if (!scene) {
        return NULL;
    }
    memset(scene, 0, sizeof(LZH_SCENE));
    base = &scene->base;
    lzh_base_init(base);

    base->type = LZH_BT_SCENE;
    base->name = NULL;
    base->hash = 0;
    base->engine = engine;
    base->update = lzh_scene_update;
    base->update_param = NULL;
    base->fixed_update = lzh_scene_fixedupdate;
    base->fixed_update_param = NULL;

    /* 创建层级渲染树 */
    scene->layer_tree = scene_layer_rb_create(lzh_scene_layer_comp);

    /* 设置默认名称 */
    lzh_base_set_name(base, lzh_gen_new_name());
    return scene;
}

void lzh_scene_destroy(LZH_SCENE *scene)
{
    if (scene) {        
        lzh_base_quit((LZH_BASE *)scene);

        if (scene->layer_tree) {
            scene_layer_rb_destroy(scene->layer_tree, lzh_scene_layer_visit_free, NULL);
            scene->layer_tree = NULL;
        }

        LZH_FREE(scene);
    }
}

LZH_BOOL lzh_scene_add_object(LZH_SCENE *scene, LZH_OBJECT *object)
{
    return LZH_FALSE;
}

void lzh_scene_del_object(LZH_SCENE *scene, LZH_OBJECT *object)
{

}

void lzh_scene_set_name(LZH_SCENE *scene, const char *name)
{
    if (scene) {
        lzh_base_set_name((LZH_BASE *)scene, name);
    }
}

const char *lzh_scene_get_name(LZH_SCENE *scene)
{
    if (scene) {
        return scene->base.name;
    }
    return NULL;
}

/*===========================================================================*/

void lzh_scene_update(LZH_BASE *base, void *args)
{

}

void lzh_scene_fixedupdate(LZH_BASE *base, void *args)
{

}

const char *lzh_gen_new_name()
{
    static int global_order = 1;
    static char default_name[32] = "";

    sprintf(default_name, "New Scene%d", global_order++);
    return default_name;
}

/*===========================================================================*/
