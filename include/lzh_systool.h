#ifndef __LZH_SYSTOOL_H__
#define __LZH_SYSTOOL_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ϵͳ���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* ��ȡ��ִ�г���Ŀ¼���ɹ����� LZH_TRUE��ʧ�ܷ��� LZH_FALSE */
LZH_API LZH_BOOL lzh_get_exe_path(char *buff, int *len);

#ifdef __cplusplus
}
#endif

#endif /* __LZH_SYSTOOL_H__ */