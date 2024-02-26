#include <lzh_systool.h>
#include <string.h>
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

    size = strlen(path);
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

/*===========================================================================*/
