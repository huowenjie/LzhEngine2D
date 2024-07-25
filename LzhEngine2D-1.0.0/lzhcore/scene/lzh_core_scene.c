#include <lzh_systool.h>
#include <lzh_object.h>

#include "lzh_core_scene.h"

#include "../object/lzh_core_object.h"
#include "../component/lzh_core_transform.h"
#include "../component/lzh_core_camera.h"

/*===========================================================================*/

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
        /* 不能直接删除对象，要先放入删除树，在帧末尾再清理对象 */
        scene_del_rb_insert(scene->del_tree, hash, obj);
    }
}

void lzh_scene_remove(LZH_SCENE *scene)
{
    if (scene) {
        /* 移除释放树 */
        if (scene->del_tree) {
            scene_del_rb_destroy(scene->del_tree, NULL, NULL);
            scene->del_tree = NULL;
        }

        /* 移除排序树 */
        if (scene->sort_tree) {
            scene_sort_rb_destroy(scene->sort_tree, NULL, NULL);
            scene->sort_tree = NULL;
        }

        /* 移除渲染树 */
        if (scene->render_tree) {
            scene_obj_rb_destroy(scene->render_tree, lzh_scene_objs_visit_free, NULL);
            scene->render_tree = NULL;
        }

        /* 移除物理引擎 */
        if (scene->world2d) {
            lzh_b2_world_destroy(scene->world2d);
            scene->world2d = NULL;
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
    } else if ((f1 - f2) < 1e-6f) {
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
        object->base.state |= LZH_BST_SCENE_CLEAR;
        lzh_object_remove(object);
    }
}

void lzh_scene_del_visit_free(const SCENE_DEL_RB_NODE *node, void *args)
{
    if (node && node->value && args) {
        LZH_SCENE *scene = (LZH_SCENE *)args;
        if (scene->render_tree) {
            scene_obj_rb_delete(scene->render_tree, node->key, lzh_scene_objs_visit_free, NULL);
        }
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

    LZH_MAT4X4F ca_mat = lzh_mat4x4f_unit();
    LZH_MAT4X4F obj_mat = lzh_mat4x4f_unit();
    LZH_VEC4F ca_tmp = lzh_vec4f_xyzw(0.0f, 0.0f, 0.0f, 1.0f);
    LZH_VEC4F obj_tmp = lzh_vec4f_xyzw(0.0f, 0.0f, 0.0f, 1.0f);

    float cos_val = 0.0f;

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

    /* 提取仿射矩阵 */
    ca_mat = lzh_mat4x4f_get_translate(&camera_trans->model_mat);
    obj_mat = lzh_mat4x4f_get_translate(&object_trans->model_mat);

    camera_pos = camera_trans->local_pos;
    object_pos = object_trans->local_pos;
    
    /* 变换为世界坐标 */
    ca_tmp = lzh_vec4f_vec3f(&camera_pos, 1.0f);
    obj_tmp = lzh_vec4f_vec3f(&object_pos, 1.0f);

    ca_tmp = lzh_mat4x4f_mul_vec(&ca_mat, &ca_tmp);
    obj_tmp = lzh_mat4x4f_mul_vec(&obj_mat, &obj_tmp);

    camera_pos = lzh_vec3f_xyz(ca_tmp.x, ca_tmp.y, ca_tmp.z);
    object_pos = lzh_vec3f_xyz(obj_tmp.x, obj_tmp.y, obj_tmp.z);

    sort_dir = lzh_vec3f_sub(&object_pos, &camera_pos);

    /* 物体和摄像机之间的距离 */
    len = lzh_vec3f_length(&sort_dir);

    view_dir = lzh_vec3f_sub(&camera->target, &camera_pos);
    view_dir = lzh_vec3f_normalize(&view_dir);
    sort_dir = lzh_vec3f_normalize(&sort_dir);

    /* 计算夹角的余弦值 */
    cos_val = lzh_vec3f_dot(&view_dir, &sort_dir);

    /* 物体和摄像机坐标系 z 轴方向的夹角 */
    len *= cos_val;

    scene_sort_rb_insert(sort_tree, len, object);
    return LZH_TRUE;
}

/*===========================================================================*/

RBTREE_IMPLEMENT(SCENE_OBJ, scene_obj, LZH_HASH_CODE, LZH_OBJECT *)

/*===========================================================================*/

RBTREE_IMPLEMENT(SCENE_SORT, scene_sort, float, LZH_OBJECT *)

/*===========================================================================*/

RBTREE_IMPLEMENT(SCENE_DEL, scene_del, LZH_HASH_CODE, LZH_OBJECT *)

/*===========================================================================*/
