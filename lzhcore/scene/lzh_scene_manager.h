#ifndef __LZH_SCENE_MANAGER_H__
#define __LZH_SCENE_MANAGER_H__

#include "lzh_core_scene.h"

/*===========================================================================*/
/* 场景管理 */
/*===========================================================================*/

/**
 * 定义场景树
 * 
 * LZH_SCENE_RB_NODE
 * LZH_SCENE_RB_TREE
 * 
 * lzh_scene_rb_create
 * lzh_scene_rb_destroy
 * lzh_scene_rb_insert
 * lzh_scene_rb_delete
 * lzh_scene_rb_find
 * lzh_scene_rb_iterate
 */
RBTREE_DECLARE(LZH_SCENE, lzh_scene, LZH_HASH_CODE, LZH_SCENE *)

typedef struct LZH_SCENE_MANAGER {
    LZH_SCENE_RB_TREE *scene_tree;

    LZH_SCENE *scene_active;
    LZH_SCENE *scene_prepare;
} LZH_SCENE_MANAGER;

/* 创建、销毁场景管理器 */
LZH_SCENE_MANAGER *lzh_scene_manager_create(LZH_ENGINE *engine);
void lzh_scene_manager_destroy(LZH_SCENE_MANAGER *manager);

/* 添加场景 */
void lzh_sm_add_scene(LZH_SCENE_MANAGER *manager, LZH_SCENE *scene);

/* 移除场景 */
void lzh_sm_remove_scene(LZH_SCENE_MANAGER *manager, const char *name);

/* 设置当前场景 */
void lzh_sm_set_active_scene(LZH_SCENE_MANAGER *manager, const char *name);

/* 场景更新 */
void lzh_sm_update(LZH_SCENE_MANAGER *manager);

/* 固定时间更新 */
void lzh_sm_fixedupdate(LZH_SCENE_MANAGER *manager);

/*===========================================================================*/

#endif /* __LZH_SCENE_MANAGER_H__ */