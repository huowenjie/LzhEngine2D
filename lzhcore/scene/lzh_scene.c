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

    /* 创建层级映射表 */
    scene->layer_map = layer_map_rb_create(lzh_scene_layer_map_comp);

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

        if (scene->layer_map) {
            layer_map_rb_destroy(scene->layer_map, NULL, NULL);
            scene->layer_map = NULL;
        }

        LZH_FREE(scene);
    }
}

void lzh_scene_add_object(LZH_SCENE *scene, LZH_OBJECT *object)
{    
    SCENE_OBJ_RB_TREE *obj_tree = NULL;
    SCENE_LAYER_RB_TREE *layer_tree = NULL;
    LAYER_MAP_RB_TREE *layer_map = NULL;

    if (!scene || !object) {
        return;
    }

    layer_tree = scene->layer_tree;
    if (!layer_tree) {
        return;
    }

    layer_map = scene->layer_map;
    if (!layer_map) {
        return;
    }

    if (scene_layer_rb_find(layer_tree, object->render_layer, &obj_tree) != 0) {
        obj_tree = scene_obj_rb_create(lzh_scene_objs_comp);
        if (!obj_tree) {
            return;
        }
        scene_layer_rb_insert(layer_tree, object->render_layer, obj_tree);
    }

    scene_obj_rb_insert(obj_tree, object->render_sort, object);
    layer_map_rb_insert(layer_map, object->base.hash, object->render_sort);
}

void lzh_scene_del_object(LZH_SCENE *scene, const char *name)
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
