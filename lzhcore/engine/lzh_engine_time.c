#include <SDL.h>
#include "lzh_engine_time.h"
#include "../math/lzh_mathdef.h"

/*===========================================================================*/

void lzh_engine_time_init(LZH_ENGINE_TIME *et)
{
    if (et) {
        et->frequency = SDL_GetPerformanceFrequency();
        et->start = SDL_GetPerformanceCounter();
        et->delay_counter = 0;
    }
}

void lzh_engine_time_quit(LZH_ENGINE_TIME *et)
{
    if (et) {
        et->frequency = 0;
        et->start = 0;
        et->delay_counter = 0;
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

    et->delay_counter += delay;
    cur = lzh_engine_time_tick_usec(et);

    if (cur < et->delay_counter) {
        lzh_engine_time_delay(et->delay_counter - cur);
    }

    cur = lzh_engine_time_tick_usec(et);
    tmp = LZH_MAX(et->delay_counter, cur - delay);
    et->delay_counter = LZH_MIN(tmp, cur + delay);
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
