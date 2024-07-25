#ifndef __LZH_TRACER_H__
#define __LZH_TRACER_H__

#include <lzh_log.h>

/*===========================================================================*/
/* ��Ԫ׷�ٹ��� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LZH_ENABLE_TRACE

/* ����ļ���Ҫ���������ڲ�ʹ�õ���־���� */
LOG_TRACE_DECLARE(lzh_trace)

/* ������־���߳�ʼ�� LZH_TRACE_START(1) ��ʾ�Ƿ�֧�ֶ��߳� */
#define LZH_TRACE_START(lock)		lzh_trace_new((lock))
#define LZH_TRACE_END()				lzh_trace_free()

/* ���ò�ͬ����־���� */
#define LZH_TRACE_LEVEL(level)		lzh_trace_set_level((level))
#define LZH_TRACE_LEVEL_NORMAL()	LZH_TRACE_LEVEL(LOG_LEVEL_NORMAL)
#define LZH_TRACE_LEVEL_LOW_DBG()	LZH_TRACE_LEVEL(LOG_LEVEL_LOW_DBG)
#define LZH_TRACE_LEVEL_DEBUG()		LZH_TRACE_LEVEL(LOG_LEVEL_FULL_DEBUG)

/* ���������־��ʽ */
#define LZH_TRACE_OUTPUT(output)	lzh_trace_set_output_type((output))
#define LZH_TRACE_OUTPUT_STD()		LZH_TRACE_OUTPUT(LOG_OUTPUT_STD)
#define LZH_TRACE_OUTPUT_FILE()		LZH_TRACE_OUTPUT(LOG_OUTPUT_FILE)
#define LZH_TRACE_OUTPUT_SYS()		LZH_TRACE_OUTPUT(LOG_OUTPUT_SYS)

/* ��־����·�� */
#define LZH_TRACE_FILE_PATH(path)	lzh_trace_set_file_path((path))

/* ��־��ʽ�����ʱ����ʾѡ�� */
#define LZH_TRACE_SHOW_OPT(opt)		lzh_trace_set_opt((opt))
#define LZH_TRACE_SHOW_DEF() \
		LZH_TRACE_SHOW_OPT( \
			LOG_OPT_SHOW_DEF_OPT | \
			LOG_OPT_FLUSH_EVERYONE | \
			LOG_OPT_FILE_APPEND)
#define LZH_TRACE_SHOW_DBG() \
	LZH_TRACE_SHOW_OPT( \
		LOG_OPT_SHOW_FUNC_LINE | \
		LOG_OPT_SHOW_FILE_PATH | \
		LOG_OPT_SHOW_THREAD_ID | \
		LOG_OPT_SHOW_PROCESS_ID| \
		LOG_OPT_FLUSH_EVERYONE | \
		LOG_OPT_FILE_APPEND)

/* �޸�ʽ����� */
#define LZH_TRACE(info, ...) \
	lzh_log_trace(lzh_trace_get_log(), info, ##__VA_ARGS__)

/* ��ʽ��������������� */
#define LZH_TRACE_BIN(name, data, len) \
	lzh_trace_trace_bin((name), (data), (len))

/* ��ʽ����� */
#define LZH_TRACE_INFO(info, ...) \
	lzh_log_trace_details( \
		lzh_trace_get_log(), \
		LOG_TYPE_INFO, \
		__LINE__, \
		__FILE__, \
		__FUNCTION__, \
		(info), ##__VA_ARGS__)

/* ������� */
#define LZH_TRACE_WARNING(warning, ...) \
	lzh_log_trace_details( \
		lzh_trace_get_log(), \
		LOG_TYPE_WARNING, \
		__LINE__, \
		__FILE__, \
		__FUNCTION__, \
		(warning), ##__VA_ARGS__)

/* ���������Ϣ */
#define LZH_TRACE_ERROR(error, ...) \
	lzh_log_trace_details( \
		lzh_trace_get_log(), \
		LOG_TYPE_ERROR, \
		__LINE__, \
		__FILE__, \
		__FUNCTION__, \
		(error), ##__VA_ARGS__)

#else
#define LZH_TRACE_START(lock)
#define LZH_TRACE_END()
#define LZH_TRACE_LEVEL(level)
#define LZH_TRACE_LEVEL_NORMAL()
#define LZH_TRACE_LEVEL_LOW_DBG()
#define LZH_TRACE_LEVEL_DEBUG()
#define LZH_TRACE_OUTPUT(output)
#define LZH_TRACE_OUTPUT_STD()
#define LZH_TRACE_OUTPUT_FILE()
#define LZH_TRACE_OUTPUT_SYS()
#define LZH_TRACE_FILE_PATH(path)
#define LZH_TRACE_SHOW_OPT(opt)
#define LZH_TRACE_SHOW_DEF()
#define LZH_TRACE_SHOW_DBG()
#define LZH_TRACE(info, ...)
#define LZH_TRACE_BIN(name, data, len)
#define LZH_TRACE_INFO(info, ...)
#define LZH_TRACE_WARNING(warning, ...)
#define LZH_TRACE_ERROR(error, ...)

#endif /* LZH_ENABLE_TRACE */

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_TRACER_H__ */
