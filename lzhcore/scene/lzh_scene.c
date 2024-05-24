#include <stdio.h>
#include <string.h>
#include <lzh_mem.h>
#include <lzh_scene.h>
#include <lzh_systool.h>

#include "../engine/lzh_core_engine.h"
#include "../component/lzh_core_camera.h"

#include "lzh_scene_manager.h"

/*===========================================================================*/

/* ������Ⱦ������Ⱦ�ص� */
static void lzh_scene_update(LZH_BASE *base, void *args);
static void lzh_scene_fixedupdate(LZH_BASE *base, void *args);
static void lzh_scene_draw(LZH_BASE *base, void *args);

/* ���������� */
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

    /* ����������Ⱦ�� */
    scene->render_tree = scene_obj_rb_create(lzh_scene_objs_comp);

    /* ������������� */
    scene->sort_tree = scene_sort_rb_create(lzh_scene_sort_comp);

    /* ���������ͷ��� */
    scene->del_tree = scene_del_rb_create(lzh_scene_objs_comp);

    /* ��ʼ����������� */
    scene->main_camera = NULL;

    /* ��β���� */
    scene->last_handle = NULL;
    scene->last_handle_args = NULL;

    /* ����Ĭ������ */
    lzh_base_set_name(base, lzh_gen_new_name());

    /* ��ӳ�����ȫ�ֳ����� */
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

        /* �ӳ�����ɾ������ */
        lzh_sm_remove_scene(engine->scene_manager, scene->base.name, NULL);
        lzh_scene_remove(scene);
    }
}

void lzh_scene_add_object(LZH_SCENE *scene, LZH_OBJECT *object)
{
    SCENE_OBJ_RB_TREE *render_tree = NULL;

    if (!scene || !object) {
        return;
    }

    render_tree = scene->render_tree;
    if (!render_tree) {
        return;
    }

    scene_obj_rb_insert(render_tree, object->base.hash, object);
}

void lzh_scene_del_object(LZH_SCENE *scene, const char *name)
{
    SCENE_OBJ_RB_TREE *render_tree = NULL;
    LZH_HASH_CODE hash = 0;
    LZH_OBJECT *obj = NULL;

    if (!scene) {
        return;
    }

    if (!name || !*name) {
        return;
    }

    render_tree = scene->render_tree;
    if (!render_tree) {
        return;
    }

    hash = lzh_gen_hash_code(name);
    scene_obj_rb_find(render_tree, hash, &obj);

    if (obj) {
        /* ����ֱ��ɾ������Ҫ�ȷ���ɾ��������֡ĩβ��������� */
        scene_del_rb_insert(scene->del_tree, hash, obj);
    }
}

void lzh_scene_set_name(LZH_SCENE *scene, const char *name)
{
    LZH_ENGINE *engine = NULL;

    if (!scene) {
        return;
    }

    if (!name || !*name) {
        return;
    }

    engine = scene->base.engine;
    if (!engine) {
        return;
    }

    /* ��Ҫ���³������ж�Ӧ�Ķ��� */
    lzh_sm_remove_scene(engine->scene_manager, scene->base.name, NULL);
    lzh_base_set_name((LZH_BASE *)scene, name);
    lzh_sm_add_scene(engine->scene_manager, scene);
}

const char *lzh_scene_get_name(LZH_SCENE *scene)
{
    if (scene) {
        return scene->base.name;
    }
    return NULL;
}

void lzh_scene_set_main_camera(LZH_SCENE *scene, LZH_OBJECT *camera)
{
    if (scene) {
        scene->main_camera = camera;
        LZH_COMPONENT *cpnt = lzh_cpnt_get_type(camera->components, LZH_CPNT_CAMERA);
        if (cpnt) {
            lzh_camera_flush((LZH_CAMERA *)cpnt);
        }
    }
}

void lzh_scene_set_last_callback(LZH_SCENE *scene, LZH_SCENE_LAST cb, void *args)
{
    if (scene) {
        scene->last_handle = cb;
        scene->last_handle_args = args;
    }
}

/*===========================================================================*/

void lzh_scene_update(LZH_BASE *base, void *args)
{
    LZH_SCENE *scene = NULL;
    SCENE_OBJ_RB_TREE *render_tree = NULL;

    if (!base) {
        return;
    }

    scene = (LZH_SCENE *)base;
    render_tree = scene->render_tree;

    scene_obj_rb_iterate(render_tree, lzh_scene_objs_visit_update, NULL);
}

void lzh_scene_fixedupdate(LZH_BASE *base, void *args)
{
    LZH_SCENE *scene = NULL;
    SCENE_OBJ_RB_TREE *render_tree = NULL;

    if (!base) {
        return;
    }

    scene = (LZH_SCENE *)base;
    render_tree = scene->render_tree;

    scene_obj_rb_iterate(render_tree, lzh_scene_objs_visit_fixedupdate, NULL);
}

void lzh_scene_draw(LZH_BASE *base, void *args)
{
    LZH_SCENE *scene = NULL;
    SCENE_OBJ_RB_TREE *render_tree = NULL;
    SCENE_SORT_RB_TREE *sort_tree = NULL;

    if (!base) {
        return;
    }

    scene = (LZH_SCENE *)base;
    render_tree = scene->render_tree;
    sort_tree = scene->sort_tree;

    if (!sort_tree) {
        return;
    }

    scene_sort_rb_clear(sort_tree, NULL, NULL);
    scene_obj_rb_iterate(render_tree, lzh_scene_objs_visit_draw, scene);
    scene_sort_rb_iterate(sort_tree, lzh_scene_sort_visit_draw, scene);
}

const char *lzh_gen_new_name()
{
    static int global_order = 1;
    static char default_name[32] = "";

    sprintf(default_name, "New Scene%d", global_order++);
    return default_name;
}

/*===========================================================================*/
