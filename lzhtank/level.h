#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <lzh_rbtree.h>
#include <lzh_type.h>

/*===========================================================================*/
/* 关卡 */
/*===========================================================================*/

RBTREE_DECLARE(LEVEL, level, char *, void *)

typedef struct
{
    /* 对象列表 */
    LEVEL_RB_TREE *objtree;

    /* 引擎对象 */
    LZH_ENGINE *engine;
} LEVEL;

LEVEL *level_create_level(LZH_ENGINE *engine);
void level_destroy_level(LEVEL *level);

/* 添加对象 */
LZH_BOOL level_add_object(LEVEL *level, const char *name, void *object);

/* 移除对象，返回对象指针 */
void *level_del_object(LEVEL *level, const char *name);

/* 查找对象 */
void *level_find_object(LEVEL *level, const char *name);

/* 迭代对象 */
void level_object_iterate(LEVEL *level, LEVEL_RB_VISIT visit, void *args);

/* 开启关卡 */
void level_start(LEVEL *level);

/* 关闭关卡并释放所有资源 */
void level_end(LEVEL *level);

/* 初始化教学关卡 */
void level_init_tutorials(LEVEL *level);

/* 退出教学关卡 */
void level_quit_tutorials(LEVEL *level);

/*===========================================================================*/

#endif /* __LEVEL_H__ */
