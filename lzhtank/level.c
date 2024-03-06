#include <stdio.h>
#include <lzh_mem.h>
#include <lzh_engine.h>
#include <lzh_keyboard.h>
#include <lzh_quadtree.h>
#include <lzh_systool.h>
#include <lzh_object.h>

#include "tank.h"
#include "level.h"

/*===========================================================================*/

RBTREE_IMPLEMENT(LEVEL, level, char *, void *)

/*===========================================================================*/

static int level_tree_comp(const void *, const void *);
static void level_tree_visit(const LEVEL_RB_NODE *, void *);
static void level_clear_visit(const LEVEL_RB_NODE *, void *);
static void level_clear_objects(LEVEL *level, LEVEL_RB_VISIT visit);

static void update_player(LZH_ENGINE *eg, LZH_OBJECT *object, void *args);

/*===========================================================================*/

LEVEL *level_create_level(LZH_ENGINE *engine)
{
    LEVEL *level = LZH_MALLOC(sizeof(LEVEL));
    if (!level) {
        return NULL;
    }

    level->objtree = level_rb_create(level_tree_comp);
    level->engine = engine;
    return level;
}

void level_destroy_level(LEVEL *level)
{
    if (level) {
        level_rb_destroy(level->objtree, level_tree_visit, NULL);
        LZH_FREE(level);
    }
}

LZH_BOOL level_add_object(LEVEL *level, const char *name, void *object)
{
    char *key = NULL;
    int size = 0;
    OBJ_WIDGET *widget = NULL;

    if (!level || !level->objtree) {
        return LZH_FALSE;
    }

    if (!name || !*name) {
        return LZH_FALSE;
    }

    if (!object) {
        return LZH_FALSE;
    }

    widget = (OBJ_WIDGET *)object;

    size = (int)strlen(name) + 1;
    key = LZH_MALLOC(size);
    strcpy(key, name);

    level_rb_insert(level->objtree, key, object);
    lzh_object_set_name(widget->object, name);
    return LZH_TRUE;
}

void *level_del_object(LEVEL *level, const char *name)
{
    void *value = NULL;

    if (!level || !level->objtree) {
        return value;
    }

    if (!name || !*name) {
        return value;
    }

    level_rb_find(level->objtree, (char *)name, &value);
    level_rb_delete(level->objtree, (char *)name, level_tree_visit, NULL);

    return value;
}

void *level_find_object(LEVEL *level, const char *name)
{
    void *value = NULL;

    if (!level || !level->objtree) {
        return value;
    }

    if (!name || !*name) {
        return value;
    }

    level_rb_find(level->objtree, (char *)name, &value);
    return value;
}

void level_object_iterate(LEVEL *level, LEVEL_RB_VISIT visit, void *args)
{
    if (!level || !level->objtree) {
        return;
    }

    if (!visit) {
        return;
    }

    level_rb_iterate(level->objtree, visit, args);
}

void level_start(LEVEL *level)
{
    if (level) {
        level_init_tutorials(level);
    }
}

void level_end(LEVEL *level)
{
    if (level) {
        level_quit_tutorials(level);
    }
}

void level_init_tutorials(LEVEL *level)
{
    if (level) {
        TANK *player = tk_create_tank(level->engine, 30.0f, 30.0f);
        if (!player) {
            return;
        }
        tk_set_pos(player, 0.0f, 0.0f);
        level_add_object(level, "player", player);
        ow_set_update((OBJ_WIDGET *)player, update_player, player);
    }
}

void level_quit_tutorials(LEVEL *level)
{
    if (level) {
        level_clear_objects(level, level_clear_visit);
        lzh_engine_set_update(level->engine, NULL, NULL);
    }
}

/*===========================================================================*/

int level_tree_comp(const void *key1, const void *key2)
{
    const char **str1 = (const char **)(key1);
    const char **str2 = (const char **)(key2);
    int cmp = strcmp(*str1, *str2);
    return cmp;
}

void level_tree_visit(const LEVEL_RB_NODE *node, void *args)
{
    if (node->key) { 
        LZH_FREE(node->key);
    }
}

void level_clear_visit(const LEVEL_RB_NODE *node, void *args)
{
    if (node->key) { 
        LZH_FREE(node->key);
    }

    if (node->value) {
        TANK *player = (TANK *)node->value;
        if (player) {
            tk_destroy_tank(player);
        }
    }
}

void level_clear_objects(LEVEL *level, LEVEL_RB_VISIT visit)
{
    if (level) {
        level_rb_clear(level->objtree, visit, NULL);
    }
}

/*===========================================================================*/

void update_player(LZH_ENGINE *eg, LZH_OBJECT *object, void *args)
{
    float delta = 0.0f;
    float speed = 0.0f;
    TANK *player = NULL;

    if (!eg || !args) {
        return;
    }

    player = (TANK *)args;
    delta = lzh_engine_interval(eg);
    speed = 100.0f * delta;

    if (lzh_get_key_status(KEY_CODE_W)) {
        tk_move_forward(player, speed);
    }

    if (lzh_get_key_status(KEY_CODE_S)) {
        tk_move_backward(player, speed);
    }

    if (lzh_get_key_status(KEY_CODE_A)) {
        tk_rotate_left(player, speed);
    }

    if (lzh_get_key_status(KEY_CODE_D)) {
        tk_rotate_right(player, speed);
    }
}

/*===========================================================================*/
