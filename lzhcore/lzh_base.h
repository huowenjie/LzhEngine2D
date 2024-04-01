#ifndef __LZH_BASE_H__
#define __LZH_BASE_H__

#include <lzh_type.h>

/*===========================================================================*/
/* 基础对象 */
/*===========================================================================*/

#define LZH_BT_NONE         0x00000000U /* 未定义 */
#define LZH_BT_OBJECT       0x00000001U /* 对象 */
#define LZH_BT_COMPONENT    0x00000002U /* 组件 */
#define LZH_BT_SCENE        0x00000003U /* 场景 */

typedef struct LZH_BASE LZH_BASE;

/* 上下文更新回调定义 */
typedef void (*LZH_BASE_UPDATE)(LZH_BASE *base, void *args);
typedef void (*LZH_BASE_FIXED_UPDATE)(LZH_BASE *base, void *args);
typedef void (*LZH_BASE_DRAW)(LZH_BASE *base, void *args);

/* 定义基类 */
struct LZH_BASE {
    /* 对象类型 */
    LZH_UINT32 type;

    /* 对象名称 */
    char *name;

    /* 对象哈希值 */
    LZH_HASH_CODE hash;

    /* 引擎对象 */
    LZH_ENGINE *engine;

    /* 更新回调 */
    LZH_BASE_UPDATE update;
    LZH_BASE_FIXED_UPDATE fixed_update;

    /* 绘制回调 */
    LZH_BASE_DRAW draw;

    /* 回调参数缓存 */
    void *update_param;
    void *fixed_update_param;
    void *draw_param;
};

/* 初始化终止 */
void lzh_base_init(LZH_BASE *base);
void lzh_base_quit(LZH_BASE *base);

/* 设置名称 */
void lzh_base_set_name(LZH_BASE *base, const char *name);

/* 获取名称 */
const char *lzh_base_get_name(LZH_BASE *base);

/* 获取hash值 */
LZH_HASH_CODE lzh_base_get_hash(LZH_BASE *base);

/*===========================================================================*/

#endif /* __LZH_BASE_H__ */
