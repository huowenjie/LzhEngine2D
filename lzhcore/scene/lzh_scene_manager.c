#include <lzh_mem.h>
#include <lzh_scene.h>
#include <lzh_systool.h>

#include "lzh_scene_manager.h"

/*===========================================================================*/

static int scene_comp(const void *a, const void *b);
static void scene_visit_free(const LZH_SCENE_RB_NODE *node, void *args);

/*===========================================================================*/

LZH_SCENE_MANAGER *lzh_scene_manager_create(LZH_ENGINE *engine)
{
    LZH_SCENE_MANAGER *manager = NULL;

    if (!engine) {
        return NULL;
    }

    manager = LZH_MALLOC(sizeof(LZH_SCENE_MANAGER));
    if (!manager) {
        return NULL;
    }
    memset(manager, 0, sizeof(LZH_SCENE_MANAGER));

    manager->scene_tree = lzh_scene_rb_create(scene_comp);
    manager->scene_active = NULL;
    manager->scene_prepare = NULL;
    return manager;
}

void lzh_scene_manager_destroy(LZH_SCENE_MANAGER *manager)
{
    if (manager) {
        lzh_scene_rb_destroy(manager->scene_tree, scene_visit_free, NULL);
        LZH_FREE(manager);
    }
}

void lzh_sm_add_scene(LZH_SCENE_MANAGER *manager, LZH_SCENE *scene)
{
    LZH_HASH_CODE hash = 0;
    LZH_SCENE_RB_TREE *scene_tree = NULL;

    if (!manager || !scene) {
        return;
    }

    scene_tree = manager->scene_tree;
    if (!scene_tree) {
        return;
    }

    hash = lzh_base_get_hash((LZH_BASE *)scene);
    lzh_scene_rb_insert(manager->scene_tree, hash, scene);
}

void lzh_sm_remove_scene(LZH_SCENE_MANAGER *manager, const char *name)
{
    LZH_HASH_CODE hash = 0;

    if (!manager) {
        return;
    }

    if (!name || !*name) {
        return;
    }

    hash = lzh_gen_hash_code(name);
    lzh_scene_rb_delete(manager->scene_tree, hash, scene_visit_free, NULL);
}

void lzh_sm_set_active_scene(LZH_SCENE_MANAGER *manager, const char *name)
{
    LZH_HASH_CODE hash = 0;
    LZH_SCENE *scene = NULL;

    if (!manager) {
        return;
    }

    if (!name || !*name) {
        return;
    }

    hash = lzh_gen_hash_code(name);
    lzh_scene_rb_find(manager->scene_tree, hash, &scene);

    if (scene) {
        manager->scene_active = scene;
    }
}

void lzh_sm_update(LZH_SCENE_MANAGER *manager)
{
    if (manager && manager->scene_active) {
        LZH_BASE *active = (LZH_BASE *)manager->scene_active;
        if (active->update) {
            active->update(active, active->update_param);
        }
    }
}

void lzh_sm_fixedupdate(LZH_SCENE_MANAGER *manager)
{
    if (manager && manager->scene_active) {
        LZH_BASE *active = (LZH_BASE *)manager->scene_active;
        if (active->fixed_update) {
            active->fixed_update(active, active->fixed_update_param);
        }
    }
}

/*===========================================================================*/

int scene_comp(const void *a, const void *b)
{
    LZH_HASH_CODE i1 = *((LZH_HASH_CODE *)a);
    LZH_HASH_CODE i2 = *((LZH_HASH_CODE *)b);

    if (i1 < i2) {
        return -1;
    } else if (i1 > i2) {
        return 1;
    }

    return 0;
}

void scene_visit_free(const LZH_SCENE_RB_NODE *node, void *args)
{
    if (node) {
        LZH_SCENE *scene = node->value;
        lzh_scene_destroy(scene);
    }
}

RBTREE_IMPLEMENT(LZH_SCENE, lzh_scene, LZH_HASH_CODE, LZH_SCENE *)

/*===========================================================================*/
