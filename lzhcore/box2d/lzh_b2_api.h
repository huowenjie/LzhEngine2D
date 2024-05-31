#ifndef __LZH_B2_API_H__
#define __LZH_B2_API_H__

#include "../math/lzh_vec2f.h"

/*===========================================================================*/
/* box2d ���� c api */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* box2d ���� */
typedef struct LZH_B2_OBJECT LZH_B2_OBJECT;
typedef struct LZH_B2_WORLD LZH_B2_WORLD;

typedef LZH_B2_OBJECT LZH_B2_BODY;
typedef LZH_B2_OBJECT LZH_B2_FIXUTRE;

typedef LZH_B2_OBJECT LZH_B2_SHAPE;
typedef LZH_B2_OBJECT LZH_B2_SHAPE_CIRCLE;
typedef LZH_B2_OBJECT LZH_B2_SHAPE_BOX;

/* ���������� */
typedef enum LZH_B2_BODY_TYPE {
    BT_STATIC = 0,  /* �������ٶ�Ϊ 0�����û��ֶ��ƶ� */
	BT_KINEMATIC,   /* ����Ϊ 0�����û������ٶȣ������渺���ƶ� */
	BT_DYNAMIC      /* �������ٶȾ���������ȫ�ӹ� */
} LZH_B2_BODY_TYPE;

/* �Ӵ��ص� */
typedef void (*LZH_B2_BEGIN_CONTACT)(void *dataA, void *dataB, void *args);
typedef void (*LZH_B2_END_CONTACT)(void *dataA, void *dataB, void *args);

/* ����������� */
LZH_B2_WORLD *lzh_b2_world_create(const LZH_VEC2F *gravity);

/* ����������� */
void lzh_b2_world_destroy(LZH_B2_WORLD *world);

/* �����������ٶ�ֵ */
void lzh_b2_world_set_gravity(LZH_B2_WORLD *world, const LZH_VEC2F *gravity);

/* ���ýӴ��ص� */
void lzh_b2_world_set_begin_contact(
    LZH_B2_WORLD *world, LZH_B2_BEGIN_CONTACT cb, void *args);

/* ���ý����Ӵ��ص� */
void lzh_b2_world_set_end_contact(
    LZH_B2_WORLD *world, LZH_B2_END_CONTACT cb, void *args);

/* �����߼�֡ */
void lzh_b2_world_step(LZH_B2_WORLD *world, float step, int vit, int pit);

/* ����������д��������������pos Ϊλ�� */
LZH_B2_BODY *lzh_b2_body_create(
    LZH_B2_WORLD *world, const LZH_VEC2F *pos, LZH_B2_BODY_TYPE type);

/* ������������� */
void lzh_b2_body_destroy(LZH_B2_WORLD *world, LZH_B2_BODY *body);

/* ����������λ�� */
void lzh_b2_body_set_position(LZH_B2_BODY *body, const LZH_VEC2F *pos);

/* �������������� */
void lzh_b2_body_set_type(LZH_B2_BODY *body, LZH_B2_BODY_TYPE type);

/* ����������� */
LZH_B2_FIXUTRE *lzh_b2_fixture_create(LZH_B2_BODY *body, LZH_B2_SHAPE *shape);

/* ����������� */
void lzh_b2_fixture_destroy(LZH_B2_BODY *body, LZH_B2_FIXUTRE *fixture);

/* �����ܶ� */
void lzh_b2_fixture_set_density(LZH_B2_FIXUTRE *fixture, float density);

/* �����û����� */
void lzh_b2_fixture_set_data(LZH_B2_FIXUTRE *fixture, void *data);

/* ��ȡ�û����� */
void *lzh_b2_fixture_get_data(LZH_B2_FIXUTRE *fixture);

/* ����Բ����״ */
LZH_B2_SHAPE_CIRCLE *lzh_b2_shape_circle_create(const LZH_VEC2F *center, float radius);

/* ����Բ����״ */
void lzh_b2_shape_circle_destroy(LZH_B2_SHAPE_CIRCLE *circle);

/* ����������״ */
LZH_B2_SHAPE_BOX *lzh_b2_shape_box_create(const LZH_VEC2F *center, float ew, float eh);

/* ���ٷ�����״ */
void lzh_b2_shape_box_destroy(LZH_B2_SHAPE_BOX *box);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_B2_API_H__ */