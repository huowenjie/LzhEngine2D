#ifndef __LZH_B2_API_H__
#define __LZH_B2_API_H__

#include "../math/lzh_vec2f.h"

/*===========================================================================*/
/* lzh box2d c api */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* box2d 对象 */
typedef struct LZH_B2_OBJECT LZH_B2_OBJECT;

typedef LZH_B2_OBJECT LZH_B2_WORLD;
typedef LZH_B2_OBJECT LZH_B2_BODY;
typedef LZH_B2_OBJECT LZH_B2_FIXUTRE;

typedef LZH_B2_OBJECT LZH_B2_SHAPE;
typedef LZH_B2_OBJECT LZH_B2_SHAPE_CIRCLE;
typedef LZH_B2_OBJECT LZH_B2_SHAPE_BOX;

/* 物理体类型 */
typedef enum LZH_B2_BODY_TYPE {
    BT_STATIC = 0,  /* 质量和速度为 0，由用户手动移动 */
	BT_KINEMATIC,   /* 质量为 0，由用户设置速度，由引擎负责移动 */
	BT_DYNAMIC      /* 质量和速度均由引擎完全接管 */
} LZH_B2_BODY_TYPE;

/* 创建世界对象 */
LZH_B2_WORLD *lzh_b2_world_create(const LZH_VEC2F *gravity);

/* 销毁世界对象 */
void lzh_b2_world_destroy(LZH_B2_WORLD *world);

/* 设置重力加速度值 */
void lzh_b2_world_set_gravity(LZH_B2_WORLD *world, const LZH_VEC2F *gravity);

/* 设置接触回调 */
//void lzh_b2_world_set_contact_cb(LZH_B2_WORLD *world, );

/* 从世界对象中创建物理主体对象，pos 为位置 */
LZH_B2_BODY *lzh_b2_body_create(
    LZH_B2_WORLD *world, const LZH_VEC2F *pos, LZH_B2_BODY_TYPE type);

/* 销毁物理体对象 */
void lzh_b2_body_destroy(LZH_B2_WORLD *world, LZH_B2_BODY *body);

/* 设置物理体位置 */
void lzh_b2_body_set_position(LZH_B2_BODY *body, const LZH_VEC2F *pos);

/* 设置物理体类型 */
void lzh_b2_body_set_type(LZH_B2_BODY *body, LZH_B2_BODY_TYPE type);

/* 创建外形组件 */
LZH_B2_FIXUTRE *lzh_b2_fixture_create(LZH_B2_BODY *body, LZH_B2_SHAPE *shape);

/* 销毁外形组件 */
void lzh_b2_fixture_destroy(LZH_B2_BODY *body, LZH_B2_FIXUTRE *fixture);

/* 设置密度 */
void lzh_b2_fixture_set_density(LZH_B2_FIXUTRE *fixture, float density);

/* 创建圆形形状 */
LZH_B2_SHAPE_CIRCLE *lzh_b2_shape_circle_create(const LZH_VEC2F *center, float radius);

/* 销毁圆形形状 */
void lzh_b2_shape_circle_destroy(LZH_B2_SHAPE_CIRCLE *circle);

/* 创建方盒形状 */
LZH_B2_SHAPE_BOX *lzh_b2_shape_box_create(const LZH_VEC2F *center, float ew, float eh);

/* 销毁方盒形状 */
void lzh_b2_shape_box_destroy(LZH_B2_SHAPE_BOX *box);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_B2_API_H__ */