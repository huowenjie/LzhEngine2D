#ifndef __GLOBAL_RES_H__
#define __GLOBAL_RES_H__

/*===========================================================================*/
/* 全局资源 */
/*===========================================================================*/

/* 程序目录 */
const char *get_exe_path();

/* 资源目录 */
const char *get_res_path();

/* 图片资源目录 */
const char *get_tank_res_path();
const char *get_tank_turret_path();

/* 控制对象名称 */
const char *get_player_name();

/* 初始化 */
void init_global_res();

/*===========================================================================*/

#endif /* __GLOBAL_RES_H__ */