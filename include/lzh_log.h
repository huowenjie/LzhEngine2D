#ifndef __LZH_LOG_H__
#define __LZH_LOG_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 日志工具 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 定义对象句柄 */
typedef void* LZH_HANDLE;

/* 日志对象 */
typedef LZH_HANDLE LZH_LOG;

/* 字符集对象 */
typedef LZH_HANDLE LZH_CHARSET;

/* 日志输出级别 */
typedef enum {
	LOG_LEVEL_NORMAL = 0x00000001U,         /* 常规级别，仅输出错误信息 */
	LOG_LEVEL_LOW_DBG = 0x00000002U,        /* 低级调试，输出所有的错误日志和警告信息 */
	LOG_LEVEL_FULL_DEBUG = 0x00000003U      /* 可输出所有的日志信息 */
} LZH_LOG_LEVEL;

/* 日志类型 */
typedef enum {
	LOG_TYPE_INFO = 0x00000001U,            /* 普通信息 */
	LOG_TYPE_WARNING = 0x00000002U,         /* 警告信息 */
	LOG_TYPE_ERROR = 0x00000003U            /* 错误信息 */
} LZH_LOG_TYPE;

/* 日志输出方式 */
typedef enum {
	LOG_OUTPUT_STD = 0x00000010U,           /* 输出方式-标准输出 */
	LOG_OUTPUT_FILE = 0x00000020U,           /* 输出方式-文件输出 */
	LOG_OUTPUT_SYS = 0x00000030U            /* 输出方式-系统输出，主要针对 windows */
} LZH_OUTPUT_TYPE;

/* 日志工具选项 */
typedef enum {
	LOG_OPT_SHOW_DEF_OPT = 0x00000000U,     /* 默认设置 */
	LOG_OPT_SHOW_FUNC_LINE = 0x10000000U,   /* 详细信息显示函数及行号 */
	LOG_OPT_SHOW_FILE_PATH = 0x20000000U,   /* 详细信息显示文件路径 */
	LOG_OPT_SHOW_THREAD_ID = 0x40000000U,	/* 详细信息显示线程 ID */
	LOG_OPT_SHOW_PROCESS_ID = 0x80000000U,	/* 详细信息显示进程 ID */
	LOG_OPT_FLUSH_EVERYONE = 0x01000000U,   /* 输出时每条日志均刷新 */
	LOG_OPT_FILE_APPEND = 0x02000000U       /* 开启文件追加模式 */
} LZH_LOG_OPTION;

/*
 * 创建/释放日志工具
 * 应用层应保证在创建日志工具或者释放日志工具时，程序不应处于并发状态，
 * 且 new/free 应成对出现，否则会造成内存泄漏。
 */
extern LZH_UINT32 lzh_log_new(LZH_LOG *log, const char *name, LZH_BOOL lock);
extern LZH_UINT32 lzh_log_free(LZH_LOG log);

/* 创建临时缓冲区(单位：byte，不调用该函数时，默认大小是 1024) */
extern LZH_UINT32 lzh_log_new_buff(LZH_LOG log, LZH_UINT32 len);

/* 设置日志级别 */
extern LZH_UINT32 lzh_log_set_level(LZH_LOG log, LZH_LOG_LEVEL level);

/* 设置输出方式 */
extern LZH_UINT32 lzh_log_set_output_type(LZH_LOG log, LZH_OUTPUT_TYPE type);

/* 设置日志选项 */
extern LZH_UINT32 lzh_log_set_opt(LZH_LOG log, LZH_LOG_OPTION opt);

/* 设置日志文件保存路径 */
extern LZH_UINT32 lzh_log_set_file_path(LZH_LOG log, const char *path);

/* 输出未格式化信息 */
extern LZH_UINT32 lzh_log_trace(LZH_LOG log, const char *info, ...);

/* 输出二进制信息 */
extern LZH_UINT32 lzh_log_trace_bin(
	LZH_LOG log, const char *name, const LZH_UINT8 *data, LZH_UINT32 size);

/*
 * 输出格式化信息
 *
 * 完整版格式化信息的形式为：
 * [process-id thread-id name info-typename date]: info-string file:xxx/xxxx/ func:xxxxxx line:
 */
extern LZH_UINT32 lzh_log_trace_details(
	LZH_LOG	     log,
	LZH_LOG_TYPE type,	/* 日志类型 */
	LZH_UINT32	  line,	/* 行数 */
	const char	 *file,	/* 所属文件 */
	const char	 *func,	/* 所属函数 */
	const char	 *info,	/* 日志信息 */
	...);

/* 以下是专门为调用者提供的日志工具快速定义模板 */

/* 本地使用的日志工具 */
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
 * 本地使用的日志工具，调用者应提供唯一的前缀(prefix)、日志模块名称(name)
 *
 * 举例说明，用户可用宏定义这样的功能:
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
