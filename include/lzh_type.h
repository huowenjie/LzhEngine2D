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
typedef char                        LZH_INT8;
typedef unsigned char               LZH_UINT8;
typedef unsigned char               LZH_BYTE;
typedef int                         LZH_INT32;
typedef unsigned int                LZH_UINT32;
typedef int                         LZH_BOOL;
typedef unsigned long long          LZH_UINTPTR;

#define LZH_TRUE                    1
#define LZH_FALSE                   0

typedef struct LZH_OBJECT           LZH_OBJECT;
typedef struct LZH_SCENE            LZH_SCENE;
typedef struct LZH_SPRITE           LZH_SPRITE;
typedef struct LZH_CAMERA           LZH_CAMERA;
typedef struct LZH_TRANSFORM        LZH_TRANSFORM;
typedef struct LZH_COLLIDER         LZH_COLLIDER;
typedef struct LZH_ENGINE           LZH_ENGINE;
typedef struct LZH_SCENE_MANAGER    LZH_SCENE_MANAGER;
typedef LZH_UINT32                  LZH_HASH_CODE;

/* ���ݶ��� */
typedef struct {
    LZH_UINT32 size;
    LZH_BYTE *value;
} LZH_DATA;

/* ��ѭ�����»ص� */
typedef LZH_UINT32 (*LZH_LOOP_UPDATE)(LZH_ENGINE *, void *);

/* ������� */
typedef void (*LZH_OBJECT_UPDATE)(LZH_ENGINE *, LZH_OBJECT *, void *);

/* ����̶�ʱ����� */
typedef void (*LZH_OBJECT_FIXEDUPDATE)(LZH_ENGINE *, LZH_OBJECT *, void *);

/* �ؼ�֡�ص� */
typedef LZH_UINT32 (*LZH_KEYFRAME_CB)(void *);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TYPE_H__ */
