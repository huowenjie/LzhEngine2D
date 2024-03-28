#include <lzh_systool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#ifdef _WINDOWS
	#define _WIN32_WINNT 0x0502
	#include <windows.h>
	#include <process.h>
#else /* Linux */
	#include <unistd.h>
#endif /* _WINDOWS & Linux */

/*===========================================================================*/

LZH_BOOL lzh_get_exe_path(char *buff, int *len)
{
    char *path = NULL;
    int size = 0;

    if (!len) {
        return LZH_FALSE;
    }

    path = SDL_GetBasePath();
    if (!path || !*path) {
        return LZH_FALSE;
    }

    size = (int)strlen(path);
    *len = size;

    if (!buff) {
        return LZH_TRUE;
    }

    if (*len < size) {
        return LZH_FALSE;
    }

    strcpy(buff, path);
    return LZH_TRUE;
}

int lzh_random_int(int min, int max)
{
    int num = 0;

    if (min > max) {
        return 0;
    } else if (min == max) {
        return min;
    }
    
    num = rand() % (max - min + 1) + min;
    return num;
}

float lzh_random_float(float min, float max)
{
    float num = 0.0f;
    float a = 0.0f;
    float b = 1.0f;

    if (min > max) {
        return 0.0f;
    }

    a = (float)rand();
    b = (float)RAND_MAX;

    num = min + (a / b) * (max - min);
    return num;
}

LZH_PROCESS_ID lzh_getpid()
{
    /* ��ȡ���� ID */
#ifdef _WINDOWS
	return (LZH_PROCESS_ID)GetCurrentProcessId();
#else
	return (LZH_PROCESS_ID)getpid();
#endif	/* _WINDOWS & Linux */
}

LZH_THREAD_ID lzh_gettid()
{
    return SDL_ThreadID();
}

LZH_BOOL lzh_get_curtime(const char *format, char *buf, int len)
{
	time_t lc_time = 0;
	size_t ret = 0;
	struct tm *lctm = NULL;

	if (!format || !format[0])
	{
		return LZH_FALSE;
	}

	if (!buf)
	{
		return LZH_FALSE;
	}

	if (len <= 0)
	{
		return LZH_FALSE;
	}

	memset(buf, 0, len);

	/* ��ȡ����ʱ�� */
	lc_time = time(NULL);
	lctm = localtime(&lc_time);

	if (!lctm)
	{
		return LZH_FALSE;
	}

	/* ת��ʱ����ϢΪ�ַ��� */
	ret = strftime(buf, len, format, lctm);
	return !ret ? LZH_FALSE : LZH_TRUE;
}

LZH_HASH_CODE lzh_gen_hash_code(const char *src)
{
    /* BKDRHash �㷨 */
    LZH_UINT32 seed = 131; /* 31 131 1313 13131 131313 etc.. */
    LZH_UINT32 hash = 0;

    if (!src || !*src) {
        return 0;
    }

    while (*src) {
        hash = hash * seed + (*src++);
    }

    hash = (hash & 0x7FFFFFFFU);
    return hash;
}

/*===========================================================================*/
