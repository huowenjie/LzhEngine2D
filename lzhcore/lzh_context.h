#ifndef __LZH_CONTEXT_H__
#define __LZH_CONTEXT_H__

#include <lzh_type.h>

/*===========================================================================*/
/* 内部类型定义 */
/*===========================================================================*/

/* 上下文更新回调定义 */
typedef void (*LZH_CTX_UPDATE)(LZH_CONTEXT *ctx, void *args);
typedef void (*LZH_CTX_FIXED_UPDATE)(LZH_CONTEXT *ctx, void *args);

struct LZH_HASH_CODE
{
    
};

/* 定义上下文 */
struct LZH_CONTEXT {
    /* 所属者对象 */
    void *invoker;

    /* 引擎对象 */
    LZH_ENGINE *engine;

    /* 更新回调 */
    LZH_CTX_UPDATE update;
    LZH_CTX_FIXED_UPDATE fixed_update;

    /* 回调参数缓存 */
    void *update_param;
    void *fixed_update_param;
};

/*===========================================================================*/

#endif /* __LZH_CONTEXT_H__ */
