#include <lzh_mem.h>
#include <lzh_sprite.h>
#include <lzh_object.h>
#include <lzh_engine.h>
#include <string.h>
#include <stdio.h>

#include "globalres.h"
#include "tank.h"

/*===========================================================================*/

#define PI (3.1415926536f)

static char bullet_name[16] = { 0 };
static int bullet_code = 1;

static void update_turret_pos(TANK *tank);
static void update_bullet_pos(TANK *tank, BULLET *bullet);

/*===========================================================================*/

TANK *tk_create_tank(LZH_ENGINE *engine, float w, float h)
{
    TURRET *turret = NULL;
    TANK *tk = NULL;

    if (!engine) {
        return NULL;
    }

    tk = LZH_MALLOC(sizeof(TANK));
    if (!tk) {
        return NULL;
    }
    memset(tk, 0, sizeof(TANK));

    turret = LZH_MALLOC(sizeof(TURRET));
    if (!turret) {
        LZH_FREE(tk);
        return NULL;
    }
    memset(turret, 0, sizeof(TURRET));

    ow_init_widget((OBJ_WIDGET *)tk, engine, w, h, OBJ_TYPE_TANK, get_tank_res_path());
    ow_init_widget((OBJ_WIDGET *)turret, engine, w / 2.0f, h, OBJ_TYPE_TURRET, get_tank_turret_path());

    tk->turret = turret;
    update_turret_pos(tk);
    return tk;
}

void tk_destroy_tank(TANK *tank)
{
    if (tank) {
        if (tank->turret) {
            ow_quit_widget((OBJ_WIDGET *)tank->turret);
            LZH_FREE(tank->turret);
            tank->turret = NULL;
        }

        ow_quit_widget((OBJ_WIDGET *)tank);
        LZH_FREE(tank);
    }
}

void tk_set_pos(TANK *tank, float x, float y)
{
    if (tank) {
        ow_set_pos((OBJ_WIDGET *)tank, x, y);
        update_turret_pos(tank);
    }
}

void tk_move_forward(TANK *tank, float speed)
{
    if (tank) {
        LZH_OBJECT *object = tank->widget.object;

        LZH_VEC2F forward = lzh_object_get_forward(object);
        LZH_VEC2F pos = lzh_object_get_pos(object);

        forward = lzh_vec2f_mul(&forward, speed);
        pos = lzh_vec2f_add(&pos, &forward);
        lzh_object_set_pos(object, &pos);
        update_turret_pos(tank);
    }
}

void tk_move_backward(TANK *tank, float speed)
{
    if (tank) {
        LZH_OBJECT *object = tank->widget.object;

        LZH_VEC2F forward = lzh_object_get_forward(object);
        LZH_VEC2F pos = lzh_object_get_pos(object);

        forward = lzh_vec2f_reverse(&forward);
        forward = lzh_vec2f_mul(&forward, speed);
        pos = lzh_vec2f_add(&pos, &forward);
        lzh_object_set_pos(object, &pos);
        update_turret_pos(tank);
    }
}

void tk_rotate_left(TANK *tank, float speed)
{
    if (tank) {
        LZH_OBJECT *object = tank->widget.object;

        float angle = lzh_object_get_angle(object) - speed;
        lzh_object_set_angle(object, angle);
        update_turret_pos(tank);
    }
}

void tk_rotate_right(TANK *tank, float speed)
{
    if (tank) {
        LZH_OBJECT *object = tank->widget.object;

        float angle = lzh_object_get_angle(object) + speed;
        lzh_object_set_angle(object, angle);
        update_turret_pos(tank);
    }
}

BULLET *tk_fire(TANK *tank)
{
    BULLET *bullet = NULL;
    LZH_ENGINE *engine = NULL;

    if (!tank) {
        return NULL;
    }

    engine = ow_get_engine((OBJ_WIDGET *)tank);
    if (!engine) {
        return NULL;
    }

    bullet = blt_create_bullet(engine, 5.0f, 10.0f);
    if (!bullet) {
        return NULL;
    }

    bullet->from = (OBJ_WIDGET *)tank;

    ow_set_level((OBJ_WIDGET *)bullet, tank->widget.level);
    sprintf(bullet_name, "bullet%d", bullet_code++);
    ow_set_name((OBJ_WIDGET *)bullet, bullet_name);
    update_bullet_pos(tank, bullet);
    return bullet;
}

/*===========================================================================*/

void update_turret_pos(TANK *tank)
{
    LZH_RECTF tk_rect;
    LZH_RECTF tr_rect;

    LZH_VEC2F tk_center;
    LZH_VEC2F tr_center;
    LZH_VEC2F tr_start;
    LZH_VEC2F tr_end;
    LZH_VEC2F offset;
    TURRET *turret = NULL;

    float angle = 0.0f;
    float theta = 0.0f;
    LZH_VEC2F forward;

    if (!tank || !tank->turret) {
        return;
    }

    turret = tank->turret;
    tk_rect = lzh_object_get_rect(tank->widget.object);
    tr_rect = lzh_object_get_rect(turret->widget.object);

    /* 起点相同，计算两个对象中心点的位移向量 */
    tk_center = lzh_vec2f_xy(tk_rect.w / 2.0f, tk_rect.h / 2.0f);
    tr_center = lzh_vec2f_xy(tr_rect.w / 2.0f, tr_rect.h / 2.0f);
    offset = lzh_vec2f_sub(&tk_center, &tr_center);

    tr_start = lzh_vec2f_xy(tk_rect.x, tk_rect.y);
    tr_end = lzh_vec2f_add(&tr_start, &offset);

    angle = lzh_object_get_angle(tank->widget.object);
    theta = angle * (PI / 180.0f);

    forward = lzh_vec2f_xy(0.0f, -1.0f);
    forward = lzh_vec2f_rotate(&forward, theta);
    forward = lzh_vec2f_mul(&forward, 6.0f);
    tr_end = lzh_vec2f_add(&tr_end, &forward);

    lzh_object_set_pos(turret->widget.object, &tr_end);
    lzh_object_set_angle(turret->widget.object, angle);
}

void update_bullet_pos(TANK *tank, BULLET *bullet)
{
    LZH_RECTF tk_rect;
    LZH_RECTF bl_rect;

    LZH_VEC2F tk_center;
    LZH_VEC2F bl_center;
    LZH_VEC2F bl_start;
    LZH_VEC2F bl_end;
    LZH_VEC2F offset;

    float angle = 0.0f;
    float theta = 0.0f;
    LZH_VEC2F forward;

    if (!tank || !bullet) {
        return;
    }

    tk_rect = lzh_object_get_rect(tank->widget.object);
    bl_rect = lzh_object_get_rect(bullet->widget.object);

    tk_center = lzh_vec2f_xy(tk_rect.w / 2.0f, tk_rect.h / 2.0f);
    bl_center = lzh_vec2f_xy(bl_rect.w / 2.0f, bl_rect.h / 2.0f);
    offset = lzh_vec2f_sub(&tk_center, &bl_center);

    bl_start = lzh_vec2f_xy(tk_rect.x, tk_rect.y);
    bl_end = lzh_vec2f_add(&bl_start, &offset);

    angle = lzh_object_get_angle(tank->widget.object);
    theta = angle * (PI / 180.0f);

    forward = lzh_vec2f_xy(0.0f, -1.0f);
    forward = lzh_vec2f_rotate(&forward, theta);
    forward = lzh_vec2f_mul(&forward, 25.0f);
    bl_end = lzh_vec2f_add(&bl_end, &forward);

    lzh_object_set_pos(bullet->widget.object, &bl_end);
    lzh_object_set_angle(bullet->widget.object, angle);
}

/*===========================================================================*/
