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
    #ifdef LZH_EXP
        #define LZH_API __attribute__((visibility("default")))
    #else
        #define LZH_API
    #endif /* LZH_EXP */
#endif /* _WINDOWS */

/*===========================================================================*/

/* ������������ */
typedef char                    LZH_INT8;
typedef unsigned char           LZH_UINT8;
typedef int                     LZH_INT32;
typedef unsigned int            LZH_UINT32;
typedef int                     LZH_BOOL;

#define LZH_TRUE                1
#define LZH_FALSE               0

typedef struct LZH_OBJECT       LZH_OBJECT;
typedef struct LZH_SPRITE       LZH_SPRITE;
typedef struct LZH_ENGINE       LZH_ENGINE;
typedef struct LZH_QUAD_TREE    LZH_QUAD_TREE;

/* ��ѭ�����»ص� */
typedef LZH_UINT32 (*LZH_LOOP_UPDATE)(LZH_ENGINE *, void *);

/* ������� */
typedef void (*LZH_OBJECT_UPDATE)(LZH_ENGINE *, LZH_OBJECT *, void *);

/* ����̶�ʱ����� */
typedef void (*LZH_OBJECT_FIXEDUPDATE)(LZH_ENGINE *, LZH_OBJECT *, void *);

/* �ؼ�֡�ص� */
typedef LZH_UINT32(*LZH_KEYFRAME_CB)(void *);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TYPE_H__ */
