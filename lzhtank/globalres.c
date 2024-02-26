#include <lzh_systool.h>
#include <string.h>

#include "globalres.h"

/*===========================================================================*/

static char cur_exe_path[256] = { 0 };
static char res_path[256] = { 0 };
static char tank_res[256] = { 0 };
static char turret_res[256] = { 0 };

static char player_name[] = "player";

/*===========================================================================*/

/* 一些和系统相关的常量定义 */
#ifdef _WINDOWS
#define CH_SEP '\\'
#define STR_SEP "\\"
#define NEWLINE "\r\n"
#else /* Linux */
#define CH_SEP '/'
#define STR_SEP "/"
#define NEWLINE "\n"
#endif

const char *get_exe_path()
{
    return cur_exe_path;
}

const char *get_res_path()
{
    return res_path;
}

const char *get_tank_res_path()
{
    return tank_res;
}

const char *get_tank_turret_path()
{
    return turret_res;
}

const char *get_player_name()
{
    return player_name;
}

void init_global_res()
{
    int size = sizeof(cur_exe_path) - 1;
    lzh_get_exe_path(cur_exe_path, &size);
    cur_exe_path[255] = '\0';

    strcpy(res_path, cur_exe_path);
    strcat(res_path, "res");
    strcat(res_path, STR_SEP);

    strcpy(tank_res, res_path);
    strcat(tank_res, "tank.png");

    strcpy(turret_res, res_path);
    strcat(turret_res, "turret.png");
}

/*===========================================================================*/
