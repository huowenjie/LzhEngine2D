#include <lzh_systool.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

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

/*===========================================================================*/
