#include <lzh_systool.h>
#include <string.h>

#include "globalres.h"

/*===========================================================================*/

#define BUFFER_LEN 256
#define EXPLODE_RES_COUNT 9

static char cur_exe_path[BUFFER_LEN] = { 0 };
static char res_path[BUFFER_LEN] = { 0 };
static char tank_res[BUFFER_LEN] = { 0 };
static char turret_res[BUFFER_LEN] = { 0 };
static char bullet_res[BUFFER_LEN] = { 0 };
static char explode_path[EXPLODE_RES_COUNT][BUFFER_LEN] = { 0 };
static char *explode_res[EXPLODE_RES_COUNT] = { 0 };
static char font_path[BUFFER_LEN] = { 0 };

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

const char *GetExePath()
{
    return cur_exe_path;
}

const char *GetResPath()
{
    return res_path;
}

const char *GetTankResPath()
{
    return tank_res;
}

const char *GetTankTurretPath()
{
    return turret_res;
}

const char *GetTankBulletPath()
{
    return bullet_res;
}

const char *GetFontPath()
{
    return font_path;
}

const char **GetTankExplodePath()
{
    return (const char **)explode_res;
}

int GetTankExplodeCount()
{
    return EXPLODE_RES_COUNT;
}

const char *GetPlayerName()
{
    return player_name;
}

void InitGlobalRes()
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

    strcpy(bullet_res, res_path);
    strcat(bullet_res, "bullet.png");

    strcpy(explode_path[0], res_path);
    strcat(explode_path[0], "explode1.png");

    strcpy(explode_path[1], res_path);
    strcat(explode_path[1], "explode2.png");

    strcpy(explode_path[2], res_path);
    strcat(explode_path[2], "explode3.png");

    strcpy(explode_path[3], res_path);
    strcat(explode_path[3], "explode4.png");

    strcpy(explode_path[4], res_path);
    strcat(explode_path[4], "explode5.png");

    strcpy(explode_path[5], res_path);
    strcat(explode_path[5], "explode6.png");

    strcpy(explode_path[6], res_path);
    strcat(explode_path[6], "explode7.png");

    strcpy(explode_path[7], res_path);
    strcat(explode_path[7], "explode8.png");

    strcpy(explode_path[8], res_path);
    strcat(explode_path[8], "explode9.png");

    for (int i = 0; i < EXPLODE_RES_COUNT; i++) {
        explode_res[i] = explode_path[i];
    }

    strcpy(font_path, res_path);
    strcat(font_path, "I.Ming-8.10.ttf");
}

/*===========================================================================*/
