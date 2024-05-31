#ifndef __GLOBAL_RES_H__
#define __GLOBAL_RES_H__

/*===========================================================================*/
/* 全局资源 */
/*===========================================================================*/

/* 程序目录 */
const char *GetExePath();

/* 资源目录 */
const char *GetResPath();

/* 图片资源目录 */
const char *GetTankResPath();
const char *GetTankTurretPath();
const char *GetTankBulletPath();

/* explode 资源 */
const char **GetTankExplodePath();
int GetTankExplodeCount();

/* 控制对象名称 */
const char *GetPlayerName();

/* 初始化 */
void InitGlobalRes();

/*===========================================================================*/

#endif /* __GLOBAL_RES_H__ */