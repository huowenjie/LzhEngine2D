#include <stdio.h>
#include <string.h>
#include <lzh_object.h>
#include <lzh_sprite.h>
#include <lzh_mem.h>
#include <lzh_systool.h>

#include "lzh_core_object.h"
#include "../engine/lzh_core_engine.h"
#include "../component/lzh_core_sprite.h"
#include "../component/lzh_core_transform.h"

/*===========================================================================*/

static int global_order = 1;

/* 场景渲染队列渲染回调 */
static void lzh_object_update(LZH_BASE *base, void *args);
static void lzh_object_fixedupdate(LZH_BASE *base, void *args);
static void lzh_object_draw(LZH_BASE *base, void *args);
static void lzh_object_sort_draw(LZH_BASE *base, void *args);

/* 生成新名称 */
static const char *lzh_gen_new_name(int order);

/*===========================================================================*/

LZH_OBJECT *lzh_object_create(LZH_ENGINE *engine, LZH_SCENE *scene)
{
    LZH_OBJECT *obj = NULL;
    LZH_BASE *base = NULL;

    if (!engine || !scene) {
        return NULL;
    }

    obj = LZH_MALLOC(sizeof(LZH_OBJECT));
    if (!obj) {
        return NULL;
    }
    memset(obj, 0, sizeof(LZH_OBJECT));
    base = &obj->base;
    lzh_base_init(base);

    base->type = LZH_BT_OBJECT;
    base->name = NULL;
    base->hash = 0;
    base->engine = engine;
    base->update = lzh_object_update;
    base->fixed_update = lzh_object_fixedupdate;
    base->draw = lzh_object_draw;
    base->sort_draw = lzh_object_sort_draw;
    base->update_param = NULL;
    base->fixed_update_param = NULL;
    base->draw_param = NULL;

    obj->parent = NULL;
    obj->children = lzh_obj_rb_create(lzh_object_rb_comp);
    obj->components = lzh_cpnt_rb_create(lzh_cpnt_rb_comp);
    obj->transform = lzh_transform_create(engine, obj);
    obj->transform->base.object = obj;

    obj->update = NULL;
    obj->update_param = NULL;
    obj->fixed_update = NULL;
    obj->fixed_update_param = NULL;
    obj->extension = lzh_ext_rb_create(lzh_object_rb_comp);
    obj->current_scene = scene;

    /* 设置默认名称 */
    lzh_base_set_name(base, lzh_gen_new_name(global_order++));

    /* 将对象添加至场景 */
    lzh_scene_add_object(scene, obj);
    return obj;
}

void lzh_object_set_parent(LZH_OBJECT *object, LZH_OBJECT *parent)
{
    LZH_SCENE *scene = NULL;

    if (!object) {
        return;
    }

    scene = object->current_scene;
    if (!scene) {
        return;
    }

    if (object->parent) {
        LZH_OBJECT *pobj = object->parent;
        lzh_obj_rb_delete(pobj->children, object->base.hash, NULL, NULL);
        object->parent = NULL;
    }

    if (parent && object != parent) {
        lzh_obj_rb_insert(parent->children, object->base.hash, object);
        object->parent = parent;
    }

    /* 必须调整渲染树中的对象 */
    if (object->parent) {
        scene_obj_rb_delete(scene->render_tree, object->base.hash, NULL, NULL);
    } else {
        scene_obj_rb_insert(scene->render_tree, object->base.hash, object);
    }
}

LZH_OBJECT *lzh_object_get_parent(LZH_OBJECT *object)
{
    if (object) {
        return object->parent;
    }
    return NULL;
}

void lzh_object_add_child(LZH_OBJECT *object, LZH_OBJECT *child)
{
    lzh_object_set_parent(child, object);
}

LZH_OBJECT *lzh_object_find_child(LZH_OBJECT *object, const char *name)
{
    LZH_OBJ_RB_TREE *children = NULL;
    LZH_HASH_CODE code = 0;
    LZH_OBJECT *child = NULL;

    if (!object) {
        return NULL;
    }

    if (!name || !*name) {
        return NULL;
    }

    code = lzh_gen_hash_code(name);
    children = object->children;

    lzh_obj_rb_find(children, code, &child);
    return child;
}

LZH_OBJECT *lzh_object_find_child_recursion(LZH_OBJECT *object, const char *name)
{
    LZH_OBJ_RB_TREE *children = NULL;
    LZH_HASH_CODE code = 0;
    LZH_OBJECT *child = NULL;

    if (!object) {
        return NULL;
    }

    if (!name || !*name) {
        return NULL;
    }

    code = lzh_gen_hash_code(name);
    children = object->children;

    /* 首先查找当前对象的子节点，查不到则沿着子节点查下去 */
    if (lzh_obj_rb_find(children, code, &child) == -1) {
        LZH_OBJ_RB_ITERATOR *it = lzh_obj_rb_create_iterator(children);

        while (lzh_obj_rb_it_next(it) != -1) {
            LZH_OBJECT *obj = NULL;
            lzh_obj_rb_it_value(it, &obj);

            child = lzh_object_find_child_recursion(obj, name);
            if (child) {
                break;
            }
        }

        lzh_obj_rb_destroy_iterator(it);
    }

    return child;
}

void lzh_object_del_child(LZH_OBJECT *object, const char *name)
{
    LZH_HASH_CODE code = 0;

    if (!object || !object->children) {
        return;
    }

    if (!name || !*name) {
        return;
    }

    code = lzh_gen_hash_code(name);
    lzh_obj_rb_delete(object->children, code, lzh_object_rb_visit, NULL);
}

void lzh_object_destroy(LZH_OBJECT *object)
{
    if (object) {        
        if (object->current_scene) {
            /* 移除场景中的本对象 */
            lzh_scene_del_object(object->current_scene, object->base.name);
            object->current_scene = NULL;
        }

        if (object->parent) {
            /* 移除父节点中缓存的子对象 */
            LZH_OBJECT *parent = object->parent;
            lzh_obj_rb_delete(parent->children, object->base.hash, lzh_object_rb_visit, NULL);
        }

        lzh_object_remove(object);
    }
}

LZH_TRANSFORM *lzh_object_get_transform(LZH_OBJECT *object)
{    
    if (object) {
        return object->transform;
    }
    return NULL;
}

LZH_SPRITE *lzh_object_get_sprite(LZH_OBJECT *object)
{
    LZH_SPRITE *sp = NULL;
    
    if (!object || !object->components) {
        return NULL;
    }

    lzh_cpnt_rb_find(object->components, LZH_CPNT_SPRITE, (LZH_COMPONENT **)&sp);
    return sp;
}

LZH_HASH_CODE lzh_object_hash_code(LZH_OBJECT *object)
{
    if (object) {
        return object->base.hash;
    }
    return 0;
}

LZH_ENGINE *lzh_object_get_engine(LZH_OBJECT *object)
{
    if (object) {
        return object->base.engine;
    }
    return NULL;
}

void lzh_object_set_name(LZH_OBJECT *object, const char *name)
{
    LZH_HASH_CODE code = 0;
    LZH_ENGINE *engine = NULL;

    if (!object || !name || !*name) {
        return;
    }

    /* 获取原有对象的名称 */
    code = lzh_gen_hash_code(object->base.name);

    engine = object->base.engine;
    if (!engine) {
        return;    
    }

    if (object->parent) {
        LZH_OBJECT *parent = object->parent;

        lzh_obj_rb_delete(parent->children, object->base.hash, NULL, NULL);
        lzh_base_set_name((LZH_BASE *)object, name);
        lzh_obj_rb_insert(parent->children, object->base.hash, object);
    } else {
        lzh_base_set_name((LZH_BASE *)object, name);
    }

    /* 更新场景树中对象的名称，其实这里将对象推到渲染循环的后方处理较为妥当，暂时这么处理 */
    if (object->current_scene) {
        LZH_SCENE *active = object->current_scene;
        scene_obj_rb_delete(active->render_tree, code, NULL, NULL);

        code = lzh_gen_hash_code(name);
        scene_obj_rb_insert(active->render_tree, code, object);
    }
}

const char *lzh_object_get_name(LZH_OBJECT *object)
{
    if (object) {
        return object->base.name;
    }
    return NULL;
}

void lzh_object_add_extension(
    LZH_OBJECT *object, const char *name, void *ext)
{
    if (object && name && *name) {
        LZH_HASH_CODE code = lzh_gen_hash_code(name);
        lzh_ext_rb_insert(object->extension, code, (LZH_UINTPTR)ext);
    }
}

void lzh_object_del_extension(LZH_OBJECT *object, const char *name)
{
    if (object && name && *name) {
        LZH_HASH_CODE code = lzh_gen_hash_code(name);
        lzh_ext_rb_delete(object->extension, code, NULL, NULL);
    }
}

void *lzh_object_get_extension(LZH_OBJECT *object, const char *name)
{
    if (object && name && *name) {
        LZH_HASH_CODE code = lzh_gen_hash_code(name);
        LZH_UINTPTR ext = 0;

        lzh_ext_rb_find(object->extension, code, &ext);
        return (void *)ext;
    }
    return NULL;
}

LZH_SCENE *lzh_object_get_current_scene(LZH_OBJECT *object)
{
    if (object) {
        return object->current_scene;
    }
    return NULL;
}

void lzh_object_set_update(
    LZH_OBJECT *object, LZH_OBJECT_UPDATE update, void *param)
{
    if (object) {
        object->update = update;
        object->update_param = param;
    }
}

void lzh_object_set_fixedupdate(
    LZH_OBJECT *object, LZH_OBJECT_FIXEDUPDATE update, void *param)
{
    if (object) {
        object->fixed_update = update;
        object->fixed_update_param = param;
    }
}

void lzh_object_show_object(LZH_OBJECT *object, LZH_BOOL show)
{
    if (object) {
        // lzh_sprite_show(object->sprite, show);
    }
}

/*===========================================================================*/

void lzh_object_update(LZH_BASE *base, void *args)
{
    if (base) {
        LZH_OBJECT *object = (LZH_OBJECT *)base;
        LZH_TRANSFORM *transform = object->transform;

        /* 更新子树 */
        if (object->children) {
            lzh_obj_rb_iterate(object->children, lzh_object_rb_visit_update, NULL);
        }

        /* 更新变换组件 */
        if (transform) {
            LZH_BASE *base = (LZH_BASE *)transform;
            if (base->update) {
                base->update(base, base->update_param);
            }
        }

        /* 更新组件 */
        if (object->components) {
            lzh_cpnt_rb_iterate(object->components, lzh_cpnt_rb_visit_update, NULL);
        }

        /* 用户层更新 */
        if (object->update) {
            object->update(base->engine, object, object->update_param);
        }
    }
}

void lzh_object_fixedupdate(LZH_BASE *base, void *args)
{
    if (base) {
        LZH_OBJECT *object = (LZH_OBJECT *)base;
        LZH_TRANSFORM *transform = object->transform;

        /* 更新子树 */
        if (object->children) {
            lzh_obj_rb_iterate(object->children, lzh_object_rb_visit_fixedupdate, NULL);
        }

        /* 更新变换组件 */
        if (transform) {
            LZH_BASE *base = (LZH_BASE *)transform;
            if (base->update) {
                base->fixed_update(base, base->fixed_update_param);
            }
        }

        /* 更新组件 */
        if (object->components) {
            lzh_cpnt_rb_iterate(object->components,lzh_cpnt_rb_visit_fixedupdate, NULL);
        }

        /* 用户层更新 */
        if (object->fixed_update) {
            object->fixed_update(base->engine, object, object->fixed_update_param);
        }
    }
}

void lzh_object_draw(LZH_BASE *base, void *args)
{
    if (base) {
        LZH_OBJECT *object = (LZH_OBJECT *)base;

        /* 绘制子树 */
        if (object->children) {
            lzh_obj_rb_iterate(object->children, lzh_object_rb_visit_draw, args);
        }

        /* 向最终的排序树插入绘制对象 */
        lzh_scene_objs_insert(object, (LZH_SCENE *)args);
    }
}

void lzh_object_sort_draw(LZH_BASE *base, void *args)
{
    if (base) {
        LZH_OBJECT *object = (LZH_OBJECT *)base;

        /* 绘制组件 */
        if (object->components) {
            lzh_cpnt_rb_iterate(object->components, lzh_cpnt_rb_visit_draw, NULL);
        }
    }
}

const char *lzh_gen_new_name(int order)
{
    static char default_name[32] = "";

    sprintf(default_name, "New Object%d", order);
    return default_name;
}

/*===========================================================================*/
