#ifndef __LZH_ENGINE_TIME_H__
#define __LZH_ENGINE_TIME_H__

#include <lzh_type.h>

/*===========================================================================*/
/* ����ʱ�� */
/*===========================================================================*/

typedef struct LZH_ENGINE_TIME {
    /* �߾���ʱ�Ӽ���Ƶ�� ��/s */
    LZH_UINT64 frequency;

    /* ��ʼʱ����� */
    LZH_UINT64 start;

    /* ��ʱ������ */
    LZH_UINT64 delay_counter;
} LZH_ENGINE_TIME;

/* ��ʼ����ֹ */
void lzh_engine_time_init(LZH_ENGINE_TIME *et);
void lzh_engine_time_quit(LZH_ENGINE_TIME *et);

/* ��ȡ�ӳ�ʼ������������΢���� */
LZH_UINT64 lzh_engine_time_tick_usec(LZH_ENGINE_TIME *et);

/* ֡�ӳ٣���ʡ cpu ʱ�� */
void lzh_engine_time_frame_delay(LZH_ENGINE_TIME *et);

/* ΢��ת��Ϊ�� */
float lzh_engine_time_u2s(LZH_UINT64 usec);

/* �߳�˯�ߣ�΢�� */
void lzh_engine_time_delay(LZH_UINT64 usec);

/*===========================================================================*/

#endif /* __LZH_ENGINE_TIME_H__ */
