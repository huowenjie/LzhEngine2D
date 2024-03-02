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

RBTREE_IMPLEMENT(LEVEL, level, char *, void *);

static int level_tree_comp(const void *, const void *);
static void level_tree_visit(const LEVEL_RB_NODE *, void *);
static void level_clear_visit(const LEVEL_RB_NODE *, void *);
static void level_clear_objects(LEVEL *level, LEVEL_RB_VISIT visit);

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

static void level_visit(const LEVEL_RB_NODE *node, void *args)
{
    LZH_QUAD_TREE *quad = (LZH_QUAD_TREE *)args;
    if (!quad) {
        return;
    }

    TANK *tank = (TANK *)node->value;
    if (!tank) {
        return;
    }

    lzh_quad_tree_add(quad, tank->object);
}

static void test_quad(LEVEL *level, TANK *player)
{
    int w = 0;
    int h = 0;
    int count = 0;
    int i = 0;
    int collider = 0;

    LZH_OBJECT **other = NULL;

    LZH_VEC2F pos;
    LZH_RECTF region;
    LZH_QUAD_TREE *quad = NULL;

    lzh_engine_win_size(level->engine, &w, &h);
    lzh_rectf_init(&region, 0.0f, 0.0f, (float)w, (float)h);

    quad = lzh_quad_tree_create();
    lzh_quad_tree_init_root(quad, &region);

    // 添加所有的对象
    level_object_iterate(level, level_visit, quad);

    lzh_quad_tree_find(quad, player->object, NULL, &count);

    other = LZH_MALLOC(count * sizeof(LZH_OBJECT *));
    memset(other, 0, count * sizeof(LZH_OBJECT *));

    lzh_quad_tree_find(quad, player->object, other, &count);

    pos = lzh_object_get_pos(player->object);
    region = lzh_object_get_rect(player->object);

    for (i = 0; i < count; i++) {
        LZH_OBJECT *obj = other[i];
        LZH_RECTF objrect = lzh_object_get_rect(obj);

        if (lzh_rectf_intersection(&region, &objrect)) {
            collider = 1;
            break;
        }
    }

    printf("player pos = %.2f, %.2f, is Collider ? %d\n", pos.x, pos.y, collider);

    LZH_FREE(other);
    lzh_quad_tree_destroy(quad);
}

void level_init_tutorials(LEVEL *level)
{
    if (level) {
        TANK *player = NULL;

        char name[32] = { 0 };
        int i = 0;

        float x = 0.0f;
        float y = 0.0f;

        player = tk_create_tank(level->engine, 30.0f, 30.0f);
        if (!player) {
            return;
        }
        tk_set_pos(player, 400.0f, 400.0f);
        level_add_object(level, "player", player);

        for (; i < 32; i++) {
            x = lzh_random_float(50.0f, 750.0f);
            y = lzh_random_float(50.0f, 550.0f);

            TANK *t = tk_create_tank(level->engine, 30.0f, 30.0f);
            tk_set_pos(t, x, y);

            sprintf(name, "npc%d", i);
            level_add_object(level, name, t);
        }

        lzh_engine_set_update(level->engine, level_turtorials_update, level);
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

LZH_UINT32 level_turtorials_update(LZH_ENGINE *eg, void *args)
{
    LEVEL *level = NULL;
    TANK *player = NULL;

    level = (LEVEL *)args;
    player = (TANK *)level_find_object(level, "player");

    test_quad(level, player);
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
