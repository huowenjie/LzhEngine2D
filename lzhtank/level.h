#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <lzh_rbtree.h>
#include <lzh_type.h>

/*===========================================================================*/
/* �ؿ� */
/*===========================================================================*/

RBTREE_DECLARE(LEVEL, level, char *, void *)

typedef struct
{
    /* �����б� */
    LEVEL_RB_TREE *objtree;

    /* ������� */
    LZH_ENGINE *engine;
} LEVEL;

LEVEL *level_create_level(LZH_ENGINE *engine);
void level_destroy_level(LEVEL *level);

/* ��Ӷ��� */
LZH_BOOL level_add_object(LEVEL *level, const char *name, void *object);

/* �Ƴ����󣬷��ض���ָ�� */
void *level_del_object(LEVEL *level, const char *name);

/* ���Ҷ��� */
void *level_find_object(LEVEL *level, const char *name);

/* �������� */
void level_object_iterate(LEVEL *level, LEVEL_RB_VISIT visit, void *args);

/* �����ؿ� */
void level_start(LEVEL *level);

/* �رչؿ����ͷ�������Դ */
void level_end(LEVEL *level);

/* ��ʼ����ѧ�ؿ� */
void level_init_tutorials(LEVEL *level);

/* �˳���ѧ�ؿ� */
void level_quit_tutorials(LEVEL *level);

/*===========================================================================*/

#endif /* __LEVEL_H__ */
