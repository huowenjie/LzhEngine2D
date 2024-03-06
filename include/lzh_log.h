#ifndef __LZH_LOG_H__
#define __LZH_LOG_H__

#include "lzh_type.h"

/*===========================================================================*/
/* ��־���� */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ��������� */
typedef void* LZH_HANDLE;

/* ��־���� */
typedef LZH_HANDLE LZH_LOG;

/* �ַ������� */
typedef LZH_HANDLE LZH_CHARSET;

/* ��־������� */
typedef enum {
	LOG_LEVEL_NORMAL = 0x00000001U,         /* ���漶�𣬽����������Ϣ */
	LOG_LEVEL_LOW_DBG = 0x00000002U,        /* �ͼ����ԣ�������еĴ�����־�;�����Ϣ */
	LOG_LEVEL_FULL_DEBUG = 0x00000003U      /* ��������е���־��Ϣ */
} LZH_LOG_LEVEL;

/* ��־���� */
typedef enum {
	LOG_TYPE_INFO = 0x00000001U,            /* ��ͨ��Ϣ */
	LOG_TYPE_WARNING = 0x00000002U,         /* ������Ϣ */
	LOG_TYPE_ERROR = 0x00000003U            /* ������Ϣ */
} LZH_LOG_TYPE;

/* ��־�����ʽ */
typedef enum {
	LOG_OUTPUT_STD = 0x00000010U,           /* �����ʽ-��׼��� */
	LOG_OUTPUT_FILE = 0x00000020U,           /* �����ʽ-�ļ���� */
	LOG_OUTPUT_SYS = 0x00000030U            /* �����ʽ-ϵͳ�������Ҫ��� windows */
} LZH_OUTPUT_TYPE;

/* ��־����ѡ�� */
typedef enum {
	LOG_OPT_SHOW_DEF_OPT = 0x00000000U,     /* Ĭ������ */
	LOG_OPT_SHOW_FUNC_LINE = 0x10000000U,   /* ��ϸ��Ϣ��ʾ�������к� */
	LOG_OPT_SHOW_FILE_PATH = 0x20000000U,   /* ��ϸ��Ϣ��ʾ�ļ�·�� */
	LOG_OPT_SHOW_THREAD_ID = 0x40000000U,	/* ��ϸ��Ϣ��ʾ�߳� ID */
	LOG_OPT_SHOW_PROCESS_ID = 0x80000000U,	/* ��ϸ��Ϣ��ʾ���� ID */
	LOG_OPT_FLUSH_EVERYONE = 0x01000000U,   /* ���ʱÿ����־��ˢ�� */
	LOG_OPT_FILE_APPEND = 0x02000000U       /* �����ļ�׷��ģʽ */
} LZH_LOG_OPTION;

/*
 * ����/�ͷ���־����
 * Ӧ�ò�Ӧ��֤�ڴ�����־���߻����ͷ���־����ʱ������Ӧ���ڲ���״̬��
 * �� new/free Ӧ�ɶԳ��֣����������ڴ�й©��
 */
extern LZH_UINT32 lzh_log_new(LZH_LOG *log, const char *name, LZH_BOOL lock);
extern LZH_UINT32 lzh_log_free(LZH_LOG log);

/* ������ʱ������(��λ��byte�������øú���ʱ��Ĭ�ϴ�С�� 1024) */
extern LZH_UINT32 lzh_log_new_buff(LZH_LOG log, LZH_UINT32 len);

/* ������־���� */
extern LZH_UINT32 lzh_log_set_level(LZH_LOG log, LZH_LOG_LEVEL level);

/* ���������ʽ */
extern LZH_UINT32 lzh_log_set_output_type(LZH_LOG log, LZH_OUTPUT_TYPE type);

/* ������־ѡ�� */
extern LZH_UINT32 lzh_log_set_opt(LZH_LOG log, LZH_LOG_OPTION opt);

/* ������־�ļ�����·�� */
extern LZH_UINT32 lzh_log_set_file_path(LZH_LOG log, const char *path);

/* ���δ��ʽ����Ϣ */
extern LZH_UINT32 lzh_log_trace(LZH_LOG log, const char *info, ...);

/* �����������Ϣ */
extern LZH_UINT32 lzh_log_trace_bin(
	LZH_LOG log, const char *name, const LZH_UINT8 *data, LZH_UINT32 size);

/*
 * �����ʽ����Ϣ
 *
 * �������ʽ����Ϣ����ʽΪ��
 * [process-id thread-id name info-typename date]: info-string file:xxx/xxxx/ func:xxxxxx line:
 */
extern LZH_UINT32 lzh_log_trace_details(
	LZH_LOG	     log,
	LZH_LOG_TYPE type,	/* ��־���� */
	LZH_UINT32	  line,	/* ���� */
	const char	 *file,	/* �����ļ� */
	const char	 *func,	/* �������� */
	const char	 *info,	/* ��־��Ϣ */
	...);

/* ������ר��Ϊ�������ṩ����־���߿��ٶ���ģ�� */

/* ����ʹ�õ���־���� */
#define LOG_TRACE_DECLARE(prefix) \
	extern LZH_UINT32 prefix##_new(LZH_BOOL lock); \
	extern LZH_UINT32 prefix##_free(); \
	extern LZH_UINT32 prefix##_new_buff(LZH_UINT32 len); \
	extern LZH_UINT32 prefix##_set_level(LZH_UINT32 level); \
	extern LZH_UINT32 prefix##_set_output_type(LZH_UINT32 type); \
	extern LZH_UINT32 prefix##_set_opt(LZH_UINT32 opt); \
	extern LZH_UINT32 prefix##_set_file_path(const char *path); \
	extern LZH_UINT32 prefix##_trace_bin(const char *name, const LZH_UINT8 *data, LZH_UINT32 size); \
	extern LZH_LOG prefix##_get_log();

/*
 * ����ʹ�õ���־���ߣ�������Ӧ�ṩΨһ��ǰ׺(prefix)����־ģ������(name)
 *
 * ����˵�����û����ú궨�������Ĺ���:
 * LOG_TRACE_DECLARE(prefix)
 * LOG_TRACE_IMPLEMENT(prefix, name)
 *
 * #define LOG_TRACE_OUTPUT_FILE(path) \
 *		prefix_set_file_path((path))
 *
 * #define LOG_TRACE(str, ...) \
 *		lzh_log_trace(prefix_get_log(), (str), __VA_ARGS__)
 */
#define LOG_TRACE_IMPLEMENT(prefix, mode_name) \
	static LZH_LOG prefix##_handle = NULL; \
	\
	LZH_UINT32 prefix##_new(LZH_BOOL lock) { \
		return lzh_log_new(&prefix##_handle, #mode_name, lock); \
	} \
	LZH_UINT32 prefix##_free() { \
		return lzh_log_free(prefix##_handle); \
	} \
	LZH_UINT32 prefix##_new_buff(LZH_UINT32 len) { \
		return lzh_log_new_buff(prefix##_handle, len); \
	} \
	LZH_UINT32 prefix##_set_level(LZH_UINT32 level) { \
		return lzh_log_set_level(prefix##_handle, level); \
	} \
	LZH_UINT32 prefix##_set_output_type(LZH_UINT32 type) { \
		return lzh_log_set_output_type(prefix##_handle, type); \
	} \
	LZH_UINT32 prefix##_set_opt(LZH_UINT32 opt) { \
		return lzh_log_set_opt(prefix##_handle, opt); \
	} \
	LZH_UINT32 prefix##_set_file_path(const char *path) { \
		return lzh_log_set_file_path(prefix##_handle, path); \
	} \
	LZH_UINT32 prefix##_trace_bin(const char *name, const LZH_UINT8 *data, LZH_UINT32 size) { \
		return lzh_log_trace_bin(prefix##_handle, name, data, size); \
	} \
	LZH_LOG prefix##_get_log() { \
		return prefix##_handle; \
	}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*===========================================================================*/

#endif /* __LZH_LOG_API_H__ */
