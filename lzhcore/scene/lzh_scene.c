#include <stdio.h>
#include <string.h>
#include <lzh_mem.h>
#include <lzh_scene.h>
#include <lzh_systool.h>

#include "../engine/lzh_core_engine.h"
#include "lzh_scene_manager.h"

/*===========================================================================*/

/* 场景渲染队列渲染回调 */
static void lzh_scene_update(LZH_BASE *base, void *args);
static void lzh_scene_fixedupdate(LZH_BASE *base, void *args);
static void lzh_scene_draw(LZH_BASE *base, void *args);

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
    base->fixed_update = lzh_scene_fixedupdate;
    base->draw = lzh_scene_draw;
    base->update_param = NULL;
    base->fixed_update_param = NULL;
    base->draw_param = NULL;

    /* 创建层级渲染树 */
    scene->layer_tree = scene_layer_rb_create(lzh_scene_layer_comp);

    /* 创建层级映射表 */
    scene->object_map = object_map_rb_create(lzh_scene_object_map_comp);

    /* 设置默认名称 */
    lzh_base_set_name(base, lzh_gen_new_name());

    /* 添加场景至全局场景树 */
    lzh_sm_add_scene(engine->scene_manager, scene);
    return scene;
}

void lzh_scene_destroy(LZH_SCENE *scene)
{
    if (scene) {
        LZH_ENGINE *engine = scene->base.engine;

        if (!engine) {
            return;
        }

        /* 从场景树删除场景 */
        lzh_sm_remove_scene(engine->scene_manager, scene->base.name, NULL);

        /* 移除映射表 */
        if (scene->object_map) {
            object_map_rb_destroy(scene->object_map, NULL, NULL);
            scene->object_map = NULL;
        }

        /* 移除层级渲染树 */
        if (scene->layer_tree) {
            scene_layer_rb_destroy(scene->layer_tree, lzh_scene_layer_visit_free, NULL);
            scene->layer_tree = NULL;
        }

        lzh_base_quit((LZH_BASE *)scene);
        LZH_FREE(scene);
    }
}

void lzh_scene_add_object(LZH_SCENE *scene, LZH_OBJECT *object)
{    
    SCENE_OBJ_RB_TREE *obj_tree = NULL;
    SCENE_LAYER_RB_TREE *layer_tree = NULL;
    OBJECT_MAP_RB_TREE *object_map = NULL;

    if (!scene || !object) {
        return;
    }

    layer_tree = scene->layer_tree;
    if (!layer_tree) {
        return;
    }

    object_map = scene->object_map;
    if (!object_map) {
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
    object_map_rb_insert(object_map, object->base.hash, object);
}

void lzh_scene_del_object(LZH_SCENE *scene, const char *name)
{
    SCENE_OBJ_RB_TREE *obj_tree = NULL;
    SCENE_LAYER_RB_TREE *layer_tree = NULL;
    OBJECT_MAP_RB_TREE *object_map = NULL;
    LZH_HASH_CODE code = 0;

    LZH_OBJECT *object = NULL;

    if (!scene) {
        return;
    }

    if (!name || !*name) {
        return;
    }

    layer_tree = scene->layer_tree;
    if (!layer_tree) {
        return;
    }

    object_map = scene->object_map;
    if (!object_map) {
        return;
    }

    code = lzh_gen_hash_code(name);
    if (object_map_rb_find(object_map, code, &object) != 0) {
        return;
    }

    if (scene_layer_rb_find(layer_tree, object->render_layer, &obj_tree) != 0) {
        return;
    }

    if (!obj_tree) {
        return;
    }

    object_map_rb_delete(object_map, code, NULL, NULL);
    scene_obj_rb_delete(obj_tree, object->render_sort, lzh_scene_objs_visit_free, NULL);
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
    LZH_SCENE *scene = NULL;
    SCENE_LAYER_RB_TREE *layer_tree = NULL;

    if (!base) {
        return;
    }

    scene = (LZH_SCENE *)base;
    layer_tree = scene->layer_tree;

    scene_layer_rb_iterate(layer_tree, lzh_scene_layer_visit_update, NULL);
}

void lzh_scene_fixedupdate(LZH_BASE *base, void *args)
{
    LZH_SCENE *scene = NULL;
    SCENE_LAYER_RB_TREE *layer_tree = NULL;

    if (!base) {
        return;
    }

    scene = (LZH_SCENE *)base;
    layer_tree = scene->layer_tree;

    scene_layer_rb_iterate(layer_tree, lzh_scene_layer_visit_fixedupdate, NULL);
}

void lzh_scene_draw(LZH_BASE *base, void *args)
{
    LZH_SCENE *scene = NULL;
    SCENE_LAYER_RB_TREE *layer_tree = NULL;

    if (!base) {
        return;
    }

    scene = (LZH_SCENE *)base;
    layer_tree = scene->layer_tree;

    scene_layer_rb_iterate(layer_tree, lzh_scene_layer_visit_draw, NULL);
}

const char *lzh_gen_new_name()
{
    static int global_order = 1;
    static char default_name[32] = "";

    sprintf(default_name, "New Scene%d", global_order++);
    return default_name;
}

/*===========================================================================*/
