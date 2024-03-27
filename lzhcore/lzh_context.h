#ifndef __LZH_CONTEXT_H__
#define __LZH_CONTEXT_H__

#include <lzh_type.h>

/*===========================================================================*/
/* �ڲ����Ͷ��� */
/*===========================================================================*/

/* �����ĸ��»ص����� */
typedef void (*LZH_CTX_UPDATE)(LZH_CONTEXT *ctx, void *args);
typedef void (*LZH_CTX_FIXED_UPDATE)(LZH_CONTEXT *ctx, void *args);

struct LZH_HASH_CODE
{
    
};

/* ���������� */
struct LZH_CONTEXT {
    /* �����߶��� */
    void *invoker;

    /* ������� */
    LZH_ENGINE *engine;

    /* ���»ص� */
    LZH_CTX_UPDATE update;
    LZH_CTX_FIXED_UPDATE fixed_update;

    /* �ص��������� */
    void *update_param;
    void *fixed_update_param;
};

/*===========================================================================*/

#endif /* __LZH_CONTEXT_H__ */
