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

struct LZH_SCENE_MANAGER {
    LZH_SCENE_RB_TREE *scene_tree;

    LZH_SCENE *scene_active;
    LZH_SCENE *scene_prepare;
};

/* 创建、销毁场景管理器 */
LZH_SCENE_MANAGER *lzh_scene_manager_create();
void lzh_scene_manager_destroy(LZH_SCENE_MANAGER *manager);

/* 添加场景 */
void lzh_sm_add_scene(LZH_SCENE_MANAGER *manager, LZH_SCENE *scene);

/* 获取场景对象 */
LZH_SCENE *lzh_sm_get_scene(LZH_SCENE_MANAGER *manager, const char *name);

/* 移除并返回场景 */
void lzh_sm_remove_scene(
    LZH_SCENE_MANAGER *manager, const char *name, LZH_SCENE **scene);

/* 设置当前场景 */
void lzh_sm_set_active_scene(LZH_SCENE_MANAGER *manager, const char *name);

/* 场景更新 */
void lzh_sm_update(LZH_SCENE_MANAGER *manager);

/* 固定时间更新 */
void lzh_sm_fixedupdate(LZH_SCENE_MANAGER *manager);

/* 场景绘制 */
void lzh_sm_draw(LZH_SCENE_MANAGER *manager);

/*===========================================================================*/

#endif /* __LZH_SCENE_MANAGER_H__ */