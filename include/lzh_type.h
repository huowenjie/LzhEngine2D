#ifndef __LZH_TYPE_H__
#define __LZH_TYPE_H__

/*===========================================================================*/
/* 基本类型定义 */
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

/* 基本数据类型 */
typedef char                LZH_INT8;
typedef unsigned char       LZH_UINT8;
typedef int                 LZH_INT32;
typedef unsigned int        LZH_UINT32;
typedef int                 LZH_BOOL;

#define LZH_TRUE            1
#define LZH_FALSE           0

typedef struct LZH_OBJECT   LZH_OBJECT;
typedef struct LZH_SPRITE   LZH_SPRITE;
typedef struct LZH_ENGINE   LZH_ENGINE;

/* 主循环更新回调 */
typedef LZH_UINT32 (*LZH_LOOP_UPDATE)(LZH_ENGINE *, void *);

/* 关键帧回调 */
typedef LZH_UINT32 (*LZH_KEYFRAME_CB)(void *);

typedef struct LZH_RECT {
    int x, y;
    int w, h;
} LZH_RECT;

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TYPE_H__ */
