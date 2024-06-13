#ifndef __LZH_ENGINE_TIME_H__
#define __LZH_ENGINE_TIME_H__

#include <lzh_type.h>

/*===========================================================================*/
/* 引擎时钟 */
/*===========================================================================*/

typedef struct LZH_ENGINE_TIME {
    /* 高精度时钟计数频率 次/s */
    LZH_UINT64 frequency;

    /* 初始时间计数 */
    LZH_UINT64 start;

    /* 目标时间计数器，用于计算帧延迟 */
    LZH_UINT64 target_counter;

    /* 固定时间间隔计数 */
    LZH_UINT64 fixed_steps;

    /* 固定时间累计，用于计算 fixed_steps */
    float fixed_accum;
} LZH_ENGINE_TIME;

/* 初始化终止 */
void lzh_engine_time_init(LZH_ENGINE_TIME *et);
void lzh_engine_time_quit(LZH_ENGINE_TIME *et);

/* 获取从初始化以来经过的微妙数 */
LZH_UINT64 lzh_engine_time_tick_usec(LZH_ENGINE_TIME *et);

/* 帧延迟，节省 cpu 时间 */
void lzh_engine_time_frame_delay(LZH_ENGINE_TIME *et);

/* 更新固定时间参数 */
void lzh_engine_time_fixed_accumulate(
    LZH_ENGINE_TIME *et, float delta, float logic_time, int logic_fps);

/* 微妙转换为秒 */
float lzh_engine_time_u2s(LZH_UINT64 usec);

/* 线程睡眠：微妙 */
void lzh_engine_time_delay(LZH_UINT64 usec);

/*===========================================================================*/

#endif /* __LZH_ENGINE_TIME_H__ */
