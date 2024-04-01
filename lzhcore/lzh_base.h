#ifndef __LZH_BASE_H__
#define __LZH_BASE_H__

#include <lzh_type.h>

/*===========================================================================*/
/* �������� */
/*===========================================================================*/

#define LZH_BT_NONE         0x00000000U /* δ���� */
#define LZH_BT_OBJECT       0x00000001U /* ���� */
#define LZH_BT_COMPONENT    0x00000002U /* ��� */
#define LZH_BT_SCENE        0x00000003U /* ���� */

typedef struct LZH_BASE LZH_BASE;

/* �����ĸ��»ص����� */
typedef void (*LZH_BASE_UPDATE)(LZH_BASE *base, void *args);
typedef void (*LZH_BASE_FIXED_UPDATE)(LZH_BASE *base, void *args);
typedef void (*LZH_BASE_DRAW)(LZH_BASE *base, void *args);

/* ������� */
struct LZH_BASE {
    /* �������� */
    LZH_UINT32 type;

    /* �������� */
    char *name;

    /* �����ϣֵ */
    LZH_HASH_CODE hash;

    /* ������� */
    LZH_ENGINE *engine;

    /* ���»ص� */
    LZH_BASE_UPDATE update;
    LZH_BASE_FIXED_UPDATE fixed_update;

    /* ���ƻص� */
    LZH_BASE_DRAW draw;

    /* �ص��������� */
    void *update_param;
    void *fixed_update_param;
    void *draw_param;
};

/* ��ʼ����ֹ */
void lzh_base_init(LZH_BASE *base);
void lzh_base_quit(LZH_BASE *base);

/* �������� */
void lzh_base_set_name(LZH_BASE *base, const char *name);

/* ��ȡ���� */
const char *lzh_base_get_name(LZH_BASE *base);

/* ��ȡhashֵ */
LZH_HASH_CODE lzh_base_get_hash(LZH_BASE *base);

/*===========================================================================*/

#endif /* __LZH_BASE_H__ */
