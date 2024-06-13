#include <SDL.h>
#include <math.h>

#include "lzh_engine_time.h"
#include "../math/lzh_mathdef.h"

/*===========================================================================*/

void lzh_engine_time_init(LZH_ENGINE_TIME *et)
{
    if (et) {
        et->frequency = SDL_GetPerformanceFrequency();
        et->start = SDL_GetPerformanceCounter();
        et->target_counter = 0;
        et->fixed_steps = 0;
        et->fixed_accum = 0.0f;
    }
}

void lzh_engine_time_quit(LZH_ENGINE_TIME *et)
{
    if (et) {
        et->frequency = 0;
        et->start = 0;
        et->target_counter = 0;
        et->fixed_steps = 0;
        et->fixed_accum = 0.0f;
    }
}

LZH_UINT64 lzh_engine_time_tick_usec(LZH_ENGINE_TIME *et)
{
    LZH_UINT64 ticks = 0;
    LZH_UINT64 sec = 0;
    LZH_UINT64 left = 0;
    LZH_UINT64 persec = 0;

    if (!et) {
        return ticks;
    }

    persec = et->frequency;
    ticks = SDL_GetPerformanceCounter();
    ticks -= et->start;

    /* 计算秒 */
    sec = ticks / persec;

    /* 计算剩下的时间 */
    left = ticks % persec;

    /* 转换为微秒 */
    ticks = (left * 1000000) / persec;
    ticks += (sec * 1000000);
	return ticks;
}

void lzh_engine_time_frame_delay(LZH_ENGINE_TIME *et)
{
    /* 大于 144 fps 会限制帧率 */
    LZH_UINT64 delay = 6900;
    LZH_UINT64 cur = 0;
    LZH_UINT64 tmp = 0;

    if (!et) {
        return;
    }

    /* 先累计下一帧时间节点 */
    et->target_counter += delay;
    cur = lzh_engine_time_tick_usec(et);

    /* 如果真实进度速度过快，则休眠等待 */
    if (cur < et->target_counter) {
        lzh_engine_time_delay(et->target_counter - cur);
    }

    /* 由于大部分操作系统的 delay 操作都有误差，这里重新获取cpu时间进行矫正 */
    cur = lzh_engine_time_tick_usec(et);

    /* 将 target_counter 限制在 -delay - +delay 的误差范围 */
    tmp = LZH_MAX(et->target_counter, cur - delay);
    et->target_counter = LZH_MIN(tmp, cur + delay);
}

void lzh_engine_time_fixed_accumulate(
    LZH_ENGINE_TIME *et, float delta, float logic_time, int logic_fps)
{
    if (!et) {
        return;
    }

    /* 每帧累计间隔时间 */
    et->fixed_accum += delta;

    /* 计算累计时间下的循环次数 */
    et->fixed_steps = floorf(et->fixed_accum * logic_fps);

    if (et->fixed_steps < 0) {
        et->fixed_steps = 0;
    }

    /* 减掉固定帧时间 */
    et->fixed_accum -= (logic_time * et->fixed_steps);
}

float lzh_engine_time_u2s(LZH_UINT64 usec)
{
    usec = LZH_MAX(usec, 1);
    return usec / 1000000.0f;
}

void lzh_engine_time_delay(LZH_UINT64 usec)
{
    if (usec < 1000) {
		SDL_Delay(1);
	} else {
		SDL_Delay(usec / 1000);
	}
}

/*===========================================================================*/
