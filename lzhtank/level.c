#include <lzh_mem.h>
#include <lzh_engine.h>
#include <lzh_keyboard.h>
#include <lzh_quadtree.h>

#include "tank.h"
#include "level.h"

/*===========================================================================*/

RBTREE_IMPLEMENT(LEVEL, level, char *, void *);

static int level_tree_comp(const void *, const void *);
static void level_tree_visit(const LEVEL_RB_NODE *, void *);

static LZH_UINT32 level_turtorials_update(LZH_ENGINE *eg, void *args);
static void update_player(LZH_ENGINE *eg, TANK *player);

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

    if (!level || !level->objtree) {
        return LZH_FALSE;
    }

    if (!name || !*name) {
        return LZH_FALSE;
    }

    size = (int)strlen(name) + 1;
    key = LZH_MALLOC(size);
    strcpy(key, name);

    level_rb_insert(level->objtree, key, object);
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
        LZH_RECT winrect = lzh_engine_get_winrect(level->engine);
        LZH_RECTF region = { 
            (float)winrect.x,
            (float)winrect.y,
            (float)winrect.w,
            (float)winrect.h,
        };
        LZH_QUAD_TREE *quad = lzh_quad_tree_create();
        lzh_quad_tree_init_root(quad, &region);

        TANK *player = tk_create_tank(level->engine, 30.0f, 30.0f);
        if (!player) {
            return;
        }
        tk_set_pos(player, 0.0f, 0.0f);
        level_add_object(level, "player", player);

        lzh_engine_set_update(level->engine, level_turtorials_update, level);
        lzh_quad_tree_destroy(quad);
    }
}

void level_quit_tutorials(LEVEL *level)
{
    if (level) {
        TANK *player = (TANK *)level_del_object(level, "player");
        if (player) {
            tk_destroy_tank(player);
        }
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

/*===========================================================================*/

LZH_UINT32 level_turtorials_update(LZH_ENGINE *eg, void *args)
{
    LEVEL *level = NULL;
    TANK *player = NULL;

    level = (LEVEL *)args;
    player = (TANK *)level_find_object(level, "player");

    update_player(eg, player);
    return 0;
}

void update_player(LZH_ENGINE *eg, TANK *player)
{
    float delta = 0.0f;
    float speed = 0.0f;

    if (!eg || !player) {
        return;
    }

    delta = lzh_engine_interval(eg);
    speed = 50.0f * delta;

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
