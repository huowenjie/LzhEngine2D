#ifndef __LZH_TYPE_H__
#define __LZH_TYPE_H__

/*===========================================================================*/
/* �������Ͷ��� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WINDOWS
    #ifdef LZH_EXP
        #define LZH_API __declspec(dllexport)
    #else
        #define LZH_API __declspec(dllimport)
    #endif
#else
    #define LZH_API
#endif /* _WINDOWS */

/*===========================================================================*/

/* ������������ */
typedef char            LZH_INT8;
typedef unsigned char   LZH_UINT8;
typedef int             LZH_INT32;
typedef unsigned int    LZH_UINT32;
typedef int             LZH_BOOL;

#define LZH_TRUE  1
#define LZH_FALSE 0

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TYPE_H__ */
