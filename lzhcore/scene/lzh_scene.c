#include <stdio.h>
#include <string.h>
#include <lzh_mem.h>
#include <lzh_scene.h>
#include <lzh_systool.h>
#include <lzh_object.h>

#include "../engine/lzh_core_engine.h"
#include "../component/lzh_core_camera.h"
#include "../component/lzh_core_collider2d.h"

#include "lzh_scene_manager.h"

/*===========================================================================*/

/* 场景渲染队列渲染回调 */
static void lzh_scene_update(LZH_BASE *base, void *args);
static void lzh_scene_fixedupdate(LZH_BASE *base, void *args);
static void lzh_scene_draw(LZH_BASE *base, void *args);

/* 生成新名称 */
static const char *lzh_gen_new_name();

/* 场景碰撞回调 */
static void lzh_scene_begine_contact(LZH_B2_FIXUTRE *fixa, LZH_B2_FIXUTRE *fixb, void *args);
static void lzh_scene_end_contact(LZH_B2_FIXUTRE *fixa, LZH_B2_FIXUTRE *fixb, void *args);

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

    /* 创建 2d 物理引擎世界对象 */
    scene->world2d = lzh_b2_world_create(NULL);

    /* 创建对象渲染树 */
    scene->render_tree = scene_obj_rb_create(lzh_scene_objs_comp);

    /* 创建深度排序树 */
    scene->sort_tree = scene_sort_rb_create(lzh_scene_sort_comp);

    /* 创建场景释放树 */
    scene->del_tree = scene_del_rb_create(lzh_scene_objs_comp);

    /* 初始化场景主相机 */
    scene->main_camera = NULL;

    /* 收尾过程 */
    scene->last_handle = NULL;
    scene->last_handle_args = NULL;

    /* 设置默认名称 */
    lzh_base_set_name(base, lzh_gen_new_name());

    /* 添加场景至全局场景树 */
    lzh_sm_add_scene(engine->scene_manager, scene);

    /* 设置场景碰撞回调 */
    lzh_b2_world_set_begin_contact(scene->world2d, lzh_scene_begine_contact, NULL);
    lzh_b2_world_set_end_contact(scene->world2d, lzh_scene_end_contact, NULL);
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
        lzh_scene_remove(scene);
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

    /* 需要更新场景树中对应的对象 */
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

LZH_BOOL lzh_scene_raycast2d(
    LZH_SCENE *scene, float sx, float sy, float ex, float ey, LZH_SCENE_RAYHIT_2D *info)
{
    LZH_B2_WORLD *bw = NULL;
    LZH_B2_RAYHIT rayhit = { 0 };
    LZH_B2_HITINFO hitinfo = { 0 };

    LZH_BOOL is_hit = LZH_FALSE;
    LZH_VEC2F start = lzh_vec2f_xy(sx, sy);
    LZH_VEC2F end = lzh_vec2f_xy(ex, ey);

    if (!scene || !scene->world2d) {
        return LZH_FALSE;
    }

    bw = scene->world2d;

    if (!info) {
        return lzh_b2_world_raycast(bw, &start, &end, NULL, RO_CHECK);
    }

    if (!lzh_b2_world_raycast(bw, &start, &end, &rayhit, RO_CLOSEST_HIT)) {
        return LZH_FALSE;
    }

    if (!rayhit.infoList || rayhit.count <= 0) {
        goto end;
    }

    is_hit = LZH_TRUE;

    hitinfo = rayhit.infoList[0];
    if (!hitinfo.fixture) {
        goto end;
    }

    info->hitobj = (LZH_OBJECT *)lzh_b2_fixture_get_data(hitinfo.fixture);
    info->hx = hitinfo.point.x;
    info->hy = hitinfo.point.y;
    info->nx = hitinfo.normal.x;
    info->ny = hitinfo.normal.y;

end:
    lzh_b2_rayhit_clear(&rayhit);
    return is_hit;
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
    LZH_ENGINE *engine = NULL;
    SCENE_OBJ_RB_TREE *render_tree = NULL;
    LZH_B2_WORLD *world = NULL;

    if (!base) {
        return;
    }

    scene = (LZH_SCENE *)base;
    engine = scene->base.engine;
    render_tree = scene->render_tree;

    world = scene->world2d;
    scene_obj_rb_iterate(render_tree, lzh_scene_objs_visit_fixedupdate, NULL);
    lzh_b2_world_step(world, engine->delta_time, 8, 3);
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

void lzh_scene_begine_contact(LZH_B2_FIXUTRE *fixa, LZH_B2_FIXUTRE *fixb, void *args)
{
    if (fixa && fixb) {
        /* 将碰撞结果回调到各个对象的 collider 组件 */
        LZH_OBJECT *oa = (LZH_OBJECT *)lzh_b2_fixture_get_data(fixa);
        LZH_OBJECT *ob = (LZH_OBJECT *)lzh_b2_fixture_get_data(fixb);

        if (!oa || !ob) {
            return;
        }

        LZH_COLLIDER2D *collider = 
            (LZH_COLLIDER2D *)lzh_cpnt_get_type(oa->components, LZH_CPNT_COLLIDER2D);
        if (collider && collider->start_contact) {
            collider->start_contact(oa, ob, collider->start_contact_args);
        }

        collider = (LZH_COLLIDER2D *)lzh_cpnt_get_type(ob->components, LZH_CPNT_COLLIDER2D);
        if (collider && collider->start_contact) {
            collider->start_contact(ob, oa, collider->start_contact_args);
        }
    }
}

void lzh_scene_end_contact(LZH_B2_FIXUTRE *fixa, LZH_B2_FIXUTRE *fixb, void *args)
{
    if (fixa && fixb) {
        LZH_OBJECT *oa = (LZH_OBJECT *)lzh_b2_fixture_get_data(fixa);
        LZH_OBJECT *ob = (LZH_OBJECT *)lzh_b2_fixture_get_data(fixb);

        if (!oa || !ob) {
            return;
        }

        LZH_COLLIDER2D *collider = 
            (LZH_COLLIDER2D *)lzh_cpnt_get_type(oa->components, LZH_CPNT_COLLIDER2D);
        if (collider && collider->end_contact) {
            collider->end_contact(oa, ob, collider->end_contact_args);
        }

        collider = (LZH_COLLIDER2D *)lzh_cpnt_get_type(ob->components, LZH_CPNT_COLLIDER2D);
        if (collider && collider->end_contact) {
            collider->end_contact(ob, oa, collider->end_contact_args);
        }
    }
}

/*===========================================================================*/
