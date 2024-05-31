#ifndef __GLOBAL_RES_H__
#define __GLOBAL_RES_H__

/*===========================================================================*/
/* ȫ����Դ */
/*===========================================================================*/

/* ����Ŀ¼ */
const char *GetExePath();

/* ��ԴĿ¼ */
const char *GetResPath();

/* ͼƬ��ԴĿ¼ */
const char *GetTankResPath();
const char *GetTankTurretPath();
const char *GetTankBulletPath();

/* explode ��Դ */
const char **GetTankExplodePath();
int GetTankExplodeCount();

/* ���ƶ������� */
const char *GetPlayerName();

/* ��ʼ�� */
void InitGlobalRes();

/*===========================================================================*/

#endif /* __GLOBAL_RES_H__ */