#include "lzh_core_scene.h"

#include "../object/lzh_core_object.h"
#include "../component/lzh_core_transform.h"
#include "../component/lzh_core_camera.h"

/*===========================================================================*/

void lzh_scene_remove(LZH_SCENE *scene)
{
    if (scene) {
        /* 移除排序树 */
        if (scene->sort_tree) {
            scene_sort_rb_destroy(scene->sort_tree, NULL, NULL);
            scene->sort_tree = NULL;
        }

        /* 移除层级渲染树 */
        if (scene->render_tree) {
            scene_obj_rb_destroy(scene->render_tree, lzh_scene_objs_visit_free, NULL);
            scene->render_tree = NULL;
        }

        lzh_base_quit((LZH_BASE *)scene);
        LZH_FREE(scene);
    }
}

int lzh_scene_sort_comp(const void *a, const void *b)
{
    float f1 = *((float *)a);
    float f2 = *((float *)b);

    if ((f1 - f2) > 1e-6f) {
        return -1;
    }
    else if ((f1 - f2) < 1e-6f) {
        return 1;
    }

    return 0;
}

void lzh_scene_sort_visit_draw(const SCENE_SORT_RB_NODE *node, void *args)
{
    if (node) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base && base->sort_draw) {
            base->sort_draw(base, args);
        }
    }
}

int lzh_scene_objs_comp(const void *a, const void *b)
{
    LZH_HASH_CODE i1 = *((int *)a);
    LZH_HASH_CODE i2 = *((int *)b);

    if (i1 < i2) {
        return -1;
    } else if (i1 > i2) {
        return 1;
    }

    return 0;
}

void lzh_scene_objs_visit_free(const SCENE_OBJ_RB_NODE *node, void *args)
{
    if (node) {
        LZH_OBJECT *object = node->value;
        lzh_object_remove(object);
    }
}

void lzh_scene_objs_visit_update(const SCENE_OBJ_RB_NODE *node, void *args)
{
    if (node) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base && base->update) {
            base->update(base, base->update_param);
        }
    }
}

void lzh_scene_objs_visit_fixedupdate(const SCENE_OBJ_RB_NODE *node, void *args)
{
    if (node) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base && base->fixed_update) {
            base->fixed_update(base, base->fixed_update_param);
        }
    }
}

void lzh_scene_objs_visit_draw(const SCENE_OBJ_RB_NODE *node, void *args)
{
    if (node) {
        LZH_BASE *base = (LZH_BASE *)node->value;
        if (base && base->draw) {
            base->draw(base, args);
        }

        lzh_scene_objs_insert(node->value, (LZH_SCENE *)args);
    }
}

LZH_BOOL lzh_scene_objs_insert(LZH_OBJECT *object, LZH_SCENE *scene)
{
    SCENE_SORT_RB_TREE *sort_tree = NULL;
    LZH_OBJECT *main_camera = NULL;
    LZH_CAMERA *camera = NULL;

    LZH_TRANSFORM *camera_trans = NULL;
    LZH_TRANSFORM *object_trans = NULL;

    LZH_VEC3F camera_pos = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    LZH_VEC3F object_pos = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    LZH_VEC3F sort_dir = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    LZH_VEC3F view_dir = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    float len = 0.0f;

    if (!object || !scene) {
        return LZH_FALSE;
    }

    sort_tree = scene->sort_tree;
    main_camera = scene->main_camera;

    if (!object) {
        return LZH_FALSE;
    }

    if (!main_camera || !sort_tree) {
        return LZH_FALSE;
    }

    camera = (LZH_CAMERA *)lzh_cpnt_get_type(
        main_camera->components, LZH_CPNT_CAMERA);
    if (!camera) {
        return LZH_FALSE;
    }

    object_trans = object->transform;
    camera_trans = main_camera->transform;
    if (!camera_trans || !object_trans) {
        return LZH_FALSE;
    }

    camera_pos = camera_trans->local_pos;
    object_pos = object_trans->local_pos;
    sort_dir = lzh_vec3f_sub(&object_pos, &camera_pos);

    /* 物体和摄像机之间的距离 */
    len = lzh_vec3f_length(&sort_dir);

    view_dir = lzh_vec3f_sub(&camera->target, &camera_pos);

    /* 物体和摄像机坐标系 z 轴方向的夹角 */
    if (lzh_vec3f_dot(&view_dir, &sort_dir) < 0.0f) {
        len = -len;
    }

    scene_sort_rb_insert(sort_tree, len, object);
    return LZH_TRUE;
}

/*===========================================================================*/

RBTREE_IMPLEMENT(SCENE_OBJ, scene_obj, LZH_HASH_CODE, LZH_OBJECT *)

/*===========================================================================*/

RBTREE_IMPLEMENT(SCENE_SORT, scene_sort, float, LZH_OBJECT *)

/*===========================================================================*/
