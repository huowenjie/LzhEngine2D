#include <stdio.h>
#include <lzh_mem.h>
#include <lzh_engine.h>
#include <lzh_keyboard.h>
#include <lzh_quadtree.h>
#include <lzh_systool.h>
#include <lzh_object.h>
#include <lzh_sprite.h>
#include <lzh_scene.h>
#include <lzh_transform.h>

#include "globalres.h"

/*===========================================================================*/

static const char *level_names[] = {
    "tutorial level",
    "first level",
    "second level",
    "final level",
    NULL
};

static const char *object_names[] = {
    "player",
    "enemy1",
    "enemy2",
    "enemy3",
    NULL
};

static const char *tank_widget[] = {
    "chassis",
    "turret",
    NULL
};

#define LEVEL_COUNT (sizeof(level_names) / sizeof(const char *))
#define OBJECT_COUNT (sizeof(object_names) / sizeof(const char *))

static void load_player(LZH_ENGINE *engine, LZH_SCENE *scene);
//static void load_enemys(LZH_ENGINE *engine, LZH_SCENE *scene);

/* 对象控制 */
static void update_player(LZH_ENGINE *eg, LZH_OBJECT *object, void *args);

/*===========================================================================*/

void level_load_scenes(LZH_ENGINE *engine)
{
    int i = 0;
    LZH_SCENE_MANAGER *manager = NULL;
    LZH_SCENE *tutorial  = NULL;

    if (!engine) {
        return;
    }

    manager = lzh_scene_get_manager(engine);
    if (!manager) {
        return;
    }

    for (; i < LEVEL_COUNT; i++) {
        LZH_SCENE *scene = lzh_scene_create(engine);
        lzh_scene_set_name(scene, level_names[i]);

        if (i == 0) {
            tutorial = scene;
        }
    }

    lzh_scene_manager_load(manager, level_names[0]);
    load_player(engine, tutorial);
}

const char *level_get_name(int index)
{
    if (index < 0 || index >= LEVEL_COUNT) {
        return NULL;
    }
    return level_names[index];
}

/*===========================================================================*/

void load_player(LZH_ENGINE *engine, LZH_SCENE *scene)
{
    LZH_OBJECT *player = NULL;
    LZH_OBJECT *chassis = NULL;
    LZH_OBJECT *turret = NULL;

    LZH_SPRITE *chassis_sp = NULL;
    LZH_SPRITE *turret_sp = NULL;

    LZH_TRANSFORM *transform = NULL;
    LZH_TRANSFORM *turret_transform = NULL;
    LZH_TRANSFORM *chassis_transform = NULL;
    LZH_VEC3F scale = lzh_vec3f_xyz(20.0f, 20.0f, 20.0f);
    LZH_VEC3F turret_scale = lzh_vec3f_xyz(15.0f, 20.0f, 20.0f);
    LZH_VEC3F trans = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    LZH_VEC3F center = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);

    if (!engine || !scene) {
        return;
    }

    player = lzh_object_create(engine);
    chassis = lzh_object_create(engine);
    turret = lzh_object_create(engine);

    chassis_sp = lzh_sprite_create(engine, get_tank_res_path());
    turret_sp = lzh_sprite_create(engine, get_tank_turret_path());

    transform = lzh_object_get_transform(player);
    turret_transform = lzh_object_get_transform(turret);
    chassis_transform = lzh_object_get_transform(chassis);

    lzh_object_add_component(turret, turret_sp);
    lzh_object_add_component(chassis, chassis_sp);

    lzh_object_set_name(player, object_names[0]);
    lzh_object_set_name(chassis, tank_widget[0]);
    lzh_object_set_name(turret, tank_widget[1]);

    lzh_object_add_child(player, chassis);
    lzh_object_add_child(player, turret);
    lzh_object_set_update(player, update_player, turret_transform);

    lzh_transform_scale(turret_transform, &turret_scale);
    lzh_transform_scale(chassis_transform, &scale);
    lzh_transform_rotate_z(turret_transform, 180.0f);
    lzh_transform_rotate_z(chassis_transform, 180.0f);
    lzh_transform_translate(turret_transform, &trans);
    lzh_transform_set_center(turret_transform, &center);

    trans = lzh_vec3f_xyz(0.0f, 0.0f, 0.0f);
    lzh_transform_translate(transform, &trans);
    lzh_scene_add_object(scene, player);
}

void update_player(LZH_ENGINE *eg, LZH_OBJECT *object, void *args)
{
    float delta = 0.0f;
    float speed = 0.0f;

    LZH_TRANSFORM *transform = NULL;
    LZH_TRANSFORM *turret_transform = NULL;

    if (!eg || !object) {
        return;
    }

    transform = lzh_object_get_transform(object);
    if (!transform) {
        return;
    }

    turret_transform = (LZH_TRANSFORM *)args;
    if (!turret_transform) {
        return;
    }

    delta = lzh_engine_interval(eg);
    speed = 100.0f * delta;

    if (lzh_get_key_status(KEY_CODE_W)) {
        LZH_VEC3F forward = lzh_transform_get_leftward(transform);
        forward = lzh_vec3f_mul(&forward, speed);

        lzh_transform_translate(transform , &forward);
    }

    if (lzh_get_key_status(KEY_CODE_S)) {
        LZH_VEC3F move = lzh_vec3f_xyz(0.0f, -speed, 0.0f);
        lzh_transform_translate(transform, &move);
    }

    speed = 30.0f * delta;

    if (lzh_get_key_status(KEY_CODE_A)) {
        lzh_transform_rotate_z(transform, speed);
    }

    if (lzh_get_key_status(KEY_CODE_D)) {
        lzh_transform_rotate_z(transform, -speed);
    }

    if (lzh_get_key_status(KEY_CODE_Q)) {
        lzh_transform_rotate_z(turret_transform, speed);
    }

    if (lzh_get_key_status(KEY_CODE_E)) {
        lzh_transform_rotate_z(turret_transform, -speed);
    }
}

// void load_enemys(LZH_ENGINE *engine, LZH_SCENE *scene)
// {

// }

/*===========================================================================*/

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
