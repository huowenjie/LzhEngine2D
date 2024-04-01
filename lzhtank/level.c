#include <stdio.h>
#include <lzh_mem.h>
#include <lzh_engine.h>
#include <lzh_keyboard.h>
#include <lzh_quadtree.h>
#include <lzh_systool.h>
#include <lzh_object.h>

#include "tank.h"

#if 0
/*===========================================================================*/

RBTREE_IMPLEMENT(LEVEL, level, char *, void *)

/*===========================================================================*/

static int level_tree_comp(const void *, const void *);
static void level_tree_visit(const LEVEL_RB_NODE *, void *);
static void level_clear_visit(const LEVEL_RB_NODE *, void *);
static void level_clear_objects(LEVEL *level, LEVEL_RB_VISIT visit);

static void level_tree_add_collider(const LEVEL_RB_NODE *, void *);

static LZH_UINT32 update_tutorials_level(LZH_ENGINE *eg, void *args);
static void update_player(LZH_ENGINE *eg, LZH_OBJECT *object, void *args);
static void update_bullet(LZH_ENGINE *eg, LZH_OBJECT *object, void *args);

/*===========================================================================*/

LEVEL *level_create_level(LZH_ENGINE *engine)
{
    LZH_QUAD_TREE *quad = NULL;
    LEVEL *level = NULL;

    if (!engine) {
        return NULL;
    }

    level = LZH_MALLOC(sizeof(LEVEL));
    if (!level) {
        return NULL;
    }

    quad = lzh_quad_tree_create();
    if (!quad) {
        LZH_FREE(level);
        return NULL;
    }

    level->objtree = level_rb_create(level_tree_comp);
    level->engine = engine;
    level->quad_tree = quad;
    return level;
}

void level_destroy_level(LEVEL *level)
{
    if (level) {
        lzh_quad_tree_destroy(level->quad_tree);
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

    if (!object) {
        return LZH_FALSE;
    }

    size = (int)strlen(name) + 1;
    key = LZH_MALLOC(size);
    strcpy(key, name);

    level_rb_insert(level->objtree, key, object);
    return LZH_TRUE;
}

void level_add_colliders(LEVEL *level)
{
    if (level) {
        int w = 0;
        int h = 0;
        LZH_RECTF region;

        /* 默认的碰撞区域为屏幕大小的区域 */
        lzh_engine_win_size(level->engine, &w, &h);
        lzh_rectf_init(&region, 0.0f, 0.0f, (float)w, (float)h);
        lzh_quad_tree_init_root(level->quad_tree, &region);

        level_rb_iterate(level->objtree, level_tree_add_collider, level);
    }
}

LZH_OBJECT *level_get_collider(LEVEL *level, const LZH_OBJECT *target)
{
    int count = 0;
    int i = 0;

    LZH_OBJECT **list = NULL;
    LZH_OBJECT *ret = NULL;
    LZH_RECTF tg_rect;
    LZH_RECTF cl_rect;

    if (!level || !target) {
        return ret;
    }

    lzh_quad_tree_find(level->quad_tree, target, list, &count);

    if (!count) {
        return ret;
    }

    list = LZH_MALLOC(sizeof(LZH_OBJECT *) * count);
    if (!list) {
        return ret;
    }
    memset(list, 0, sizeof(LZH_OBJECT *) * count);

    lzh_quad_tree_find(level->quad_tree, target, list, &count);

    tg_rect = lzh_object_get_rect(target);
    for (i = 0; i < count; i++) {
        LZH_OBJECT *obj = list[i];
        cl_rect = lzh_object_get_rect(obj);
        if (obj != target && lzh_rectf_intersection(&tg_rect, &cl_rect)) {
            ret = obj;
            break;
        }    
    }

    LZH_FREE(list);
    return ret;
}

void level_clear_colliders(LEVEL *level)
{
    if (level) {
        lzh_quad_tree_clear(level->quad_tree);
    }
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
#if 0
    if (level) {
        TANK *dog = NULL;
        TANK *pig = NULL;
        TANK *player = NULL;

        lzh_engine_set_update(level->engine, update_tutorials_level, level);

        player = tk_create_tank(level->engine, 10.0f, 10.0f);
        if (!player) {
            return;
        }

        tk_set_pos(player, 0.0f, 0.0f);
        ow_set_name((OBJ_WIDGET *)player, "player");
        ow_set_update((OBJ_WIDGET *)player, update_player, player);
        ow_set_level((OBJ_WIDGET *)player, level);

        level_add_object(level, "player", player);

        dog = tk_create_tank(level->engine, 10.0f, 10.0f);
        if (!dog) {
            return;
        }

        tk_set_pos(dog, 100.0f, 0.0f);
        ow_set_name((OBJ_WIDGET *)dog, "dog");
        ow_set_level((OBJ_WIDGET *)dog, level);

        level_add_object(level, "dog", dog);

        pig = tk_create_tank(level->engine, 10.0f, 10.0f);
        if (!pig) {
            return;
        }

        tk_set_pos(pig, 0.0f, 100.0f);
        ow_set_name((OBJ_WIDGET *)pig, "pig");
        ow_set_level((OBJ_WIDGET *)pig, level);

        level_add_object(level, "pig", pig);
    }
#endif
}

void level_quit_tutorials(LEVEL *level)
{
#if 0
    if (level) {
        level_clear_objects(level, level_clear_visit);
        lzh_engine_set_update(level->engine, NULL, NULL);
    }
#endif
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
        ow_destroy_widget((OBJ_WIDGET *)node->value);
    }
}

void level_clear_objects(LEVEL *level, LEVEL_RB_VISIT visit)
{
    if (level) {
        level_rb_clear(level->objtree, visit, NULL);
    }
}

void level_tree_add_collider(const LEVEL_RB_NODE *node, void *args)
{
    LEVEL *level = (LEVEL *)args;
    if (!level) {
        return;
    }

    if (node->value) {
        OBJ_WIDGET *obj = (OBJ_WIDGET *)node->value;
        if (obj->type == OBJ_TYPE_TANK || obj->type == OBJ_TYPE_BULLET) {
            lzh_quad_tree_add(level->quad_tree, obj->object);
        }
    }
}

/*===========================================================================*/

LZH_UINT32 update_tutorials_level(LZH_ENGINE *eg, void *args)
{
#if 0
    LEVEL *level = NULL;
    LZH_OBJECT *collider = NULL;
    OBJ_WIDGET *target = NULL;

    if (!args) {
        return 0;
    }

    level = (LEVEL *)args;
    
    level_add_colliders(level);
    target = (OBJ_WIDGET *)level_find_object(level, "bullet1");
    if (!target) {
        return 0;
    }

    collider = level_get_collider(level, target->object);
    if (collider && collider != target->object) {
        const char *name = lzh_object_get_name(collider);
        printf("collider!!! -- %s\n", name);
    }

    level_clear_colliders(level);
#endif
    return 0;
}

void update_player(LZH_ENGINE *eg, LZH_OBJECT *object, void *args)
{
    float delta = 0.0f;
    float speed = 0.0f;

    TANK *player = NULL;
    LEVEL *level = NULL;

    if (!eg || !args) {
        return;
    }

    player = (TANK *)args;
    delta = lzh_engine_interval(eg);
    speed = 100.0f * delta;
    level = player->widget.level;

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

    if (lzh_get_key_down(eg, KEY_CODE_SPACE)) {
        const char *name = NULL;
        BULLET *bullet = tk_fire(player);

        if (!bullet) {
            return;
        }

        ow_set_update((OBJ_WIDGET *)bullet, update_bullet, bullet);

        name = lzh_object_get_name(bullet->widget.object);
        level_add_object(level, name, bullet);
    }
}

void update_bullet(LZH_ENGINE *eg, LZH_OBJECT *object, void *args)
{    
    LEVEL *level = NULL;
    LZH_OBJECT *collider = NULL;
    OBJ_WIDGET *target = NULL;

    float delta = 0.0f;
    float speed = 0.0f;
    BULLET *bullet = NULL;

    if (!eg || !args) {
        return;
    }

    bullet = (BULLET *)args;
    delta = lzh_engine_interval(eg);
    speed = 100.0f * delta;
    level = bullet->widget.level;

    blt_move_forward(bullet, speed);

    level_add_colliders(level);
    target = (OBJ_WIDGET *)bullet;

    collider = level_get_collider(level, target->object);
    if (collider) {
        const char *name = lzh_object_get_name(bullet->widget.object);
        OBJ_WIDGET *widget = NULL;

        /* explode，然后bullet销毁 */
        blt_explode(bullet);
        blt_destroy_bullet((BULLET *)bullet);
        level_del_object(level, name);

        /* 目标被击中然后销毁 TODO ，后期可以添加限定条件 */
        name = lzh_object_get_name(collider);
        widget = (OBJ_WIDGET *)level_del_object(level, name);
        ow_destroy_widget(widget);
    }

    level_clear_colliders(level);
}

#endif

/*===========================================================================*/
