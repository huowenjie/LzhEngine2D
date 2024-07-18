#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <lzh_systool.h>
#include <SDL.h>

#ifdef _WINDOWS
	#define _WIN32_WINNT 0x0502
	#include <windows.h>
	#include <process.h>
#else /* Linux */
	#include <unistd.h>
#endif /* _WINDOWS & Linux */

#include "../iconv/iconv.h"

/*===========================================================================*/

LZH_BOOL lzh_get_exe_path(char *buff, int *len)
{
    char *path = NULL;
    int size = 0;
    LZH_BOOL ret = LZH_FALSE;

    if (!len) {
        return ret;
    }

    path = SDL_GetBasePath();
    if (!path || !*path) {
        return ret;
    }

    size = (int)strlen(path);
    *len = size;

    if (!buff) {
        goto end;
    }

    if (*len < size) {
        goto end;
    }

    strcpy(buff, path);
    ret = LZH_TRUE;
end:
    if (path) {
        SDL_free(path);
    }
    return ret;
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

LZH_BOOL lzh_read_file(const char *file, LZH_DATA *data)
{
    size_t len = 0;
    FILE *fp   = NULL;

    if (!file || !*file) {
        return LZH_FALSE;
    }

    if (!data || !data->value) {
        return LZH_FALSE;
    }

    fp = fopen(file, "rb");
    if (!fp) {
        return LZH_FALSE;
    }

    len = data->size;

    if (fread(data->value, sizeof(LZH_BYTE), len, fp) != len) {
        fclose(fp);
        return LZH_FALSE;
    }

    data->size = (LZH_UINT32)len;

    if (fp) {
        fclose(fp);
    }
    return LZH_TRUE;
}

LZH_BOOL lzh_write_file(const char *file, const LZH_DATA *data)
{
    size_t len = 0;
    FILE *fp   = NULL;

    if (!file || !*file) {
        return LZH_FALSE;
    }

    if (!data || !data->value) {
        return LZH_FALSE;
    }

    fp = fopen(file, "wb");
    if (!fp) {
        return LZH_FALSE;
    }

    len = data->size;

    if (fwrite(data->value, sizeof(LZH_BYTE), len, fp) != len) {
        fclose(fp);
        return LZH_FALSE;
    }

    if (fp) {
        fclose(fp);
    }
    return LZH_TRUE;
}

LZH_UINT32 lzh_get_file_size(const char *file)
{
	FILE *fp = NULL;
	long size = 0;

	if (!file || !*file) {
		return 0;
	}

	fp = fopen(file, "rb");
	if (!fp) {
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	fclose(fp);
	return (LZH_UINT32)size;
}

LZH_BOOL lzh_utf8_to_unicode(const LZH_DATA *utf8, LZH_DATA *unicode)
{
    #if 0
    char *utf = NULL;
    char *ucs = NULL;

    size_t inl = 0;
	size_t outl = 0;

    iconv_t it = NULL;

    if (!utf8 || !unicode) {
        return LZH_FALSE;
    }

    utf = (char *)utf8->value;
    ucs = (char *)unicode->value;

    if (!utf || !*utf) {
        return LZH_FALSE;
    }

    inl = utf8->size;
    it = iconv_open("UNICODE//IGNORE", "UTF-8");

    if (!it) {
        return LZH_FALSE;
    }
    #endif
    return LZH_FALSE;
}

/*===========================================================================*/
