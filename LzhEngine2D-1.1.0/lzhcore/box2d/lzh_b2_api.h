#ifndef __LZH_B2_API_H__
#define __LZH_B2_API_H__

#include "../math/lzh_vec2f.h"

/*===========================================================================*/
/* box2d 引擎 c api */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* box2d 对象 */
typedef struct LZH_B2_OBJECT LZH_B2_OBJECT;
typedef struct LZH_B2_WORLD LZH_B2_WORLD;
typedef struct LZH_B2_FIXUTRE LZH_B2_FIXUTRE;

typedef LZH_B2_OBJECT LZH_B2_BODY;
typedef LZH_B2_OBJECT LZH_B2_SHAPE;
typedef LZH_B2_OBJECT LZH_B2_SHAPE_CIRCLE;
typedef LZH_B2_OBJECT LZH_B2_SHAPE_BOX;

/* 物理体类型 */
typedef enum LZH_B2_BODY_TYPE {
    BT_STATIC = 0,                  /* 质量和速度为 0，由用户手动移动 */
	BT_KINEMATIC,                   /* 质量为 0，由用户设置速度，由引擎负责移动 */
	BT_DYNAMIC                      /* 质量和速度均由引擎完全接管 */
} LZH_B2_BODY_TYPE;

/* 碰撞信息 */
typedef struct LZH_B2_HITINFO {
    LZH_B2_FIXUTRE *fixture;        /* 碰撞体 */
    LZH_VEC2F point;                /* 碰撞点 */
    LZH_VEC2F normal;               /* 碰撞点法线 */
} LZH_B2_HITINFO;

/* 射线碰撞 */
typedef struct LZH_B2_RAYHIT {
    int count;                      /* 碰撞对象数量 */
    LZH_B2_HITINFO *infoList;       /* 碰撞信息列表 */
} LZH_B2_RAYHIT;

/* 射线碰撞选项 */
typedef enum LZH_B2_RAYHIT_OPT {
    RO_CLOSEST_HIT = 0,             /* 只查找最近的碰撞对象 */
    RO_ALL_HIT,                     /* 查找所有的碰撞对象 */
    RO_CHECK                        /* 只检查是否碰撞了对象 */
} LZH_B2_RAYHIT_OPT;

/* 接触回调 */
typedef void (*LZH_B2_BEGIN_CONTACT)(LZH_B2_FIXUTRE *fixA, LZH_B2_FIXUTRE *fixB, void *args);
typedef void (*LZH_B2_END_CONTACT)(LZH_B2_FIXUTRE *fixA, LZH_B2_FIXUTRE *fixB, void *args);

/* 射线接触回调 */
typedef void (*LZH_B2_RAYCAST)(LZH_B2_FIXUTRE *fixture, void *args);

/* 创建世界对象 */
LZH_B2_WORLD *lzh_b2_world_create(const LZH_VEC2F *gravity);

/* 销毁世界对象 */
void lzh_b2_world_destroy(LZH_B2_WORLD *world);

/* 设置重力加速度值 */
void lzh_b2_world_set_gravity(LZH_B2_WORLD *world, const LZH_VEC2F *gravity);

/* 设置接触回调 */
void lzh_b2_world_set_begin_contact(
    LZH_B2_WORLD *world, LZH_B2_BEGIN_CONTACT cb, void *args);

/* 设置结束接触回调 */
void lzh_b2_world_set_end_contact(
    LZH_B2_WORLD *world, LZH_B2_END_CONTACT cb, void *args);

/* 处理逻辑帧 */
void lzh_b2_world_step(LZH_B2_WORLD *world, float step, int vit, int pit);

/*
 * 发射射线，返回射线碰撞信息
 * 
 * 如果返回 LZH_TRUE，则说明有碰撞，调用本函数结束后需要调用 lzh_b2_rayhit_destroy 释放
 * 碰撞信息；
 * 
 * 如果返回 LZH_FALSE，则说明没有碰撞，无需调用 lzh_b2_rayhit_destroy 释放碰撞信息；
 * 
 * 如果 opt 参数为 RO_CHECK，则表明本函数仅检测是否碰撞，也无需调用 lzh_b2_rayhit_destroy
 * 来释放碰撞信息。
 */
LZH_BOOL lzh_b2_world_raycast(
    LZH_B2_WORLD *world,
    const LZH_VEC2F *start,
    const LZH_VEC2F *end,
    LZH_B2_RAYHIT *hit,
    LZH_B2_RAYHIT_OPT opt);

/* 销毁碰撞信息 */
void lzh_b2_rayhit_clear(LZH_B2_RAYHIT *hit);

/* 从世界对象中创建物理主体对象，pos 为位置 */
LZH_B2_BODY *lzh_b2_body_create(
    LZH_B2_WORLD *world, const LZH_VEC2F *pos, LZH_B2_BODY_TYPE type);

/* 销毁物理体对象 */
void lzh_b2_body_destroy(LZH_B2_WORLD *world, LZH_B2_BODY *body);

/* 设置物理体位置 */
void lzh_b2_body_set_transform(LZH_B2_BODY *body, const LZH_VEC2F *pos, float angle);

/* 设置物理体类型 */
void lzh_b2_body_set_type(LZH_B2_BODY *body, LZH_B2_BODY_TYPE type);

/* 创建外形组件 */
LZH_B2_FIXUTRE *lzh_b2_fixture_create(LZH_B2_BODY *body, LZH_B2_SHAPE *shape);

/* 销毁外形组件 */
void lzh_b2_fixture_destroy(LZH_B2_BODY *body, LZH_B2_FIXUTRE *fixture);

/* 设置密度 */
void lzh_b2_fixture_set_density(LZH_B2_FIXUTRE *fixture, float density);

/* 设置用户数据 */
void lzh_b2_fixture_set_data(LZH_B2_FIXUTRE *fixture, void *data);

/* 获取用户数据 */
void *lzh_b2_fixture_get_data(LZH_B2_FIXUTRE *fixture);

/* 创建圆形形状 */
LZH_B2_SHAPE_CIRCLE *lzh_b2_shape_circle_create(float cx, float cy, float radius);

/* 销毁圆形形状 */
void lzh_b2_shape_circle_destroy(LZH_B2_SHAPE_CIRCLE *circle);

/* 创建方盒形状 */
LZH_B2_SHAPE_BOX *lzh_b2_shape_box_create(float cx, float cy, float ew, float eh);

/* 销毁方盒形状 */
void lzh_b2_shape_box_destroy(LZH_B2_SHAPE_BOX *box);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_B2_API_H__ */