#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <lzh_systool.h>
#include <SDL2/SDL.h>

#include "lzh_log.h"

/*===========================================================================*/

#define LOG_STR_INFO_FLG		"Info"
#define LOG_STR_WARNING_FLG		"Warning"
#define LOG_STR_ERROR_FLG		"Error"

#define LOG_LEVEL_MASK			0x0000000FU
#define LOG_OUTPUT_MASK			0x000000F0U
#define LOG_TYPE_MASK			0x0000FF00U
#define LOG_OPT_MASK			0xFF000000U

#define LOG_NAME_BUFLEN			32					/* 定义日志模块名称缓冲区长度 */
#define LOG_FORMAT_RESERVE_LEN	64					/* 定义格式化日志信息预留长度 */
#define LOG_LOCAL_BUFLEN_WEIGHT	0x01				/* 本地默认编码缓冲区长度权重 */
#define LOG_CHENC_BUFLEN_WEIGHT	0x02				/* 字符编码转换默认缓冲长度权重	*/
#define LOG_FILE_INPLZH_WRITE	"wb"				/* 文件模式数据输入模式 */
#define LOG_FILE_INPLZH_APPEND	"ab"

#define LOG_BUFF_SIZE			1024				/* 日志信息缓冲区默认大小(byte) */ 
#define LOG_BUFF_MIN_SIZE		512					/* 日志信息缓冲区最小长度 */ 
#define LOG_BUFF_MAX_SIZE		2048				/* 日志信息缓冲区最大长度 */

#define LZH_LOG_SUCCESS 0
#define LZH_LOG_FAILED -1

/* 永久阻塞式加锁快捷方式 */
#define SYS_LOCK_NOTIME(m)      SDL_LockMutex((m))
#define SYS_UNLOCK(m)		    SDL_UnlockMutex((m))

/* 日志信息对象 */
typedef struct lzh_log_info_st
{
	LZH_UINT32 len;								/* 日志结构长度 */

	/* 
	 * 0~4   位为日志级别；
	 * 4~8   位为日志输出方式；
	 * 8~16  位为日志类型；
	 * 剩下的为保留位。
	 */
	LZH_UINT32		flag;							/* 日志类型参数 */
	char			log_name[LOG_NAME_BUFLEN];		/* 日志模块名称 */
	FILE			*log_file;						/* 文件指针 */
	SDL_mutex		*mutex;							/* 互斥锁 */
	LZH_DATA		path_buf;						/* 日志文件路径 */
	LZH_DATA		log_buf;						/* 日志缓冲区 */
} LZH_LOG_INFO;

/* 日志输出 */
static LZH_UINT32 log_output(LZH_LOG_INFO *log, const char *info);

/* 标准输出 */
static LZH_UINT32 log_output_std(LZH_LOG_INFO *log, const char *info);

/* 文件输出 */
static LZH_UINT32 log_output_file(LZH_LOG_INFO *log, const char *info);

/* 系统日志输出 */
static LZH_UINT32 log_output_sys(LZH_LOG_INFO *log, const char *info);

/* 打开文件 */
static FILE *log_open_file(LZH_LOG_INFO *log, const char *path);

LZH_UINT32 lzh_log_new(LZH_LOG *log, const char *name, LZH_BOOL lock)
{
	LZH_LOG_INFO *lgst = NULL;
	LZH_UINT32 flag = 0;
	LZH_UINT32 ret = LZH_LOG_SUCCESS;
	SDL_mutex *mutex = NULL;

	if (!log || !name || !name[0])
	{
		return LZH_LOG_FAILED;
	}

	lgst = (LZH_LOG_INFO *)malloc(sizeof(LZH_LOG_INFO));
	if (!lgst)
	{
		return LZH_LOG_FAILED;
	}
	memset(lgst, 0, sizeof(LZH_LOG_INFO));

	/* 设置长度，用于校验 */
	lgst->len = sizeof(LZH_LOG_INFO);

	/* 创建互斥锁 */
	if (lock)
	{
		mutex = SDL_CreateMutex();
		if (!mutex)
		{
			ret = LZH_LOG_FAILED;
			goto err;
		}
	}

	/* 设置默认的输出级别、输出类型、等属性 */
	flag  = LOG_LEVEL_NORMAL;
	flag |= LOG_OUTPUT_STD;
	flag |= LOG_LEVEL_FULL_DEBUG;

	lgst->flag = flag;
	strncpy(lgst->log_name, name, LOG_NAME_BUFLEN);
	lgst->log_name[LOG_NAME_BUFLEN - 1] = '\0';

	/* 首先设置两个缓冲区长度的权重，然后申请内存 */
	lgst->log_buf.value = (LZH_UINT8 *)malloc(LOG_BUFF_SIZE);
	lgst->log_buf.size  = LOG_BUFF_SIZE;

	if (!lgst->log_buf.value)
	{
		ret = LZH_LOG_FAILED;
		goto err;
	}

	lgst->mutex = mutex;
	memset(lgst->log_buf.value, 0, LOG_BUFF_SIZE);
	*log = (LZH_LOG)lgst;

err:
	if (ret != LZH_LOG_SUCCESS)
	{
		if (mutex)
		{
			SDL_DestroyMutex(mutex);
		}

		free(lgst);
	}

	return ret;
}

LZH_UINT32 lzh_log_free(LZH_LOG log)
{
	LZH_LOG_INFO *lgst = NULL;

	if (!log)
	{
		return LZH_LOG_FAILED;
	}

	lgst = (LZH_LOG_INFO *)log;

	if (lgst->len != sizeof(LZH_LOG_INFO))
	{
		return LZH_LOG_FAILED;
	}

	/* 释放文件路径缓冲区 */
	if (lgst->path_buf.value)
	{
		free(lgst->path_buf.value);
		lgst->path_buf.value = NULL;
		lgst->path_buf.size = 0;
	}

	/* 释放缓冲区 */
	if (lgst->log_buf.value)
	{
		free(lgst->log_buf.value);
		lgst->log_buf.value = NULL;
		lgst->log_buf.size = 0;
	}

	/* 释放文件指针 */
	if (lgst->log_file)
	{
		fflush(lgst->log_file);
		fclose(lgst->log_file);
		lgst->log_file = NULL;
	}

	/* 释放互斥锁 */
	if (lgst->mutex)
	{
		SDL_DestroyMutex(lgst->mutex);
		lgst->mutex = NULL;
	}

	free(lgst);
	return LZH_LOG_SUCCESS;
}

LZH_UINT32 lzh_log_new_buff(LZH_LOG log, LZH_UINT32 len)
{
	LZH_LOG_INFO *lgst = NULL;
	LZH_UINT8 *tmp = NULL;
	LZH_UINT32 ret = LZH_LOG_SUCCESS;
	LZH_UINT32 buf_len = 0;

	if (!log)
	{
		return LZH_LOG_FAILED;
	}

	if (len < LOG_BUFF_MIN_SIZE || len > LOG_BUFF_MAX_SIZE)
	{
		return LZH_LOG_FAILED;
	}

	lgst = (LZH_LOG_INFO *)log;

	if (lgst->len != sizeof(LZH_LOG_INFO))
	{
		return LZH_LOG_FAILED;
	}

	SYS_LOCK_NOTIME(lgst->mutex);

	if (!lgst->log_buf.value)
	{
		tmp = malloc(len * sizeof(LZH_UINT8));
		if (!tmp)
		{
			ret = LZH_LOG_FAILED;
			goto end;
		}

		lgst->log_buf.value = tmp;
		lgst->log_buf.size  = len;
	}
	else if ((buf_len = lgst->log_buf.size) < len)
	{
		tmp = (LZH_UINT8 *)realloc(lgst->log_buf.value, len);
		if (!tmp)
		{
			ret = LZH_LOG_FAILED;
			goto end;
		}

		memset(tmp + buf_len, 0, len - buf_len);

		lgst->log_buf.value = tmp;
		lgst->log_buf.size = len;
	}
	else
	{
		/* 不需要重新分配内存，只需要调整‘大小’即可 */
		lgst->log_buf.size = len;
	}

end:
	SYS_UNLOCK(lgst->mutex);
	return ret;
}

LZH_UINT32 lzh_log_set_level(LZH_LOG log, LZH_LOG_LEVEL level)
{
	LZH_LOG_INFO *lgst = NULL;

	if (!log || !level)
	{
		return LZH_LOG_FAILED;
	}

	lgst = (LZH_LOG_INFO *)log;

	if (lgst->len != sizeof(LZH_LOG_INFO))
	{
		return LZH_LOG_FAILED;
	}

	SYS_LOCK_NOTIME(lgst->mutex);
	lgst->flag = (lgst->flag & (~LOG_LEVEL_MASK)) | level;
	SYS_UNLOCK(lgst->mutex);

	return LZH_LOG_SUCCESS;
}

LZH_UINT32 lzh_log_set_output_type(LZH_LOG log, LZH_OUTPUT_TYPE type)
{
	LZH_LOG_INFO *lgst = NULL;

	if (!log || !type)
	{
		return LZH_LOG_FAILED;
	}

	lgst = (LZH_LOG_INFO *)log;

	if (lgst->len != sizeof(LZH_LOG_INFO))
	{
		return LZH_LOG_FAILED;
	}

	SYS_LOCK_NOTIME(lgst->mutex);
	lgst->flag = (lgst->flag & (~LOG_OUTPUT_MASK)) | type;
	SYS_UNLOCK(lgst->mutex);

	return LZH_LOG_SUCCESS;
}

LZH_UINT32 lzh_log_set_opt(LZH_LOG log, LZH_LOG_OPTION opt)
{
	LZH_LOG_INFO *lgst = NULL;

	if (!log)
	{
		return LZH_LOG_FAILED;
	}

	lgst = (LZH_LOG_INFO *)log;
	if (lgst->len != sizeof(LZH_LOG_INFO))
	{
		return LZH_LOG_FAILED;
	}

	SYS_LOCK_NOTIME(lgst->mutex);

	lgst->flag = (opt != LOG_OPT_SHOW_DEF_OPT) ?
		(lgst->flag | (opt & LOG_OPT_MASK)) : (lgst->flag & (~LOG_OPT_MASK));

	SYS_UNLOCK(lgst->mutex);

	return LZH_LOG_SUCCESS;
}

LZH_UINT32 lzh_log_set_file_path(LZH_LOG log, const char *path)
{
	LZH_LOG_INFO *lgst = NULL;
	LZH_UINT32 ret = LZH_LOG_SUCCESS;
	LZH_UINT32 plen = 0;
	LZH_UINT8  *tmp = NULL;
	FILE *pfile = NULL;

	if (!log || !path || !path[0])
	{
		return LZH_LOG_FAILED;
	}

	lgst = (LZH_LOG_INFO *)log;

	if (lgst->len != sizeof(LZH_LOG_INFO))
	{
		return LZH_LOG_FAILED;
	}

	SYS_LOCK_NOTIME(lgst->mutex);

	tmp  = lgst->path_buf.value;
	plen = (LZH_UINT32)strlen(path) + 1;

	if (!tmp)
	{
		tmp = (LZH_UINT8 *)malloc(plen * sizeof(LZH_UINT8));
		if (!tmp)
		{
			ret = LZH_LOG_FAILED;
			goto end;
		}

		lgst->path_buf.value = tmp;
		lgst->path_buf.size  = plen;
	}
	else if (lgst->path_buf.size < plen)
	{
		tmp = (LZH_UINT8 *)realloc(lgst->path_buf.value, plen);
		if (!tmp)
		{
			ret = LZH_LOG_FAILED;
			goto end;
		}

		lgst->path_buf.value = tmp;
		lgst->path_buf.size  = plen;
	}

	if (lgst->log_file)
	{
		fflush(lgst->log_file);
		fclose(lgst->log_file);
	}

	/* 打开文件 */
	pfile = log_open_file(lgst, path);
	if (!pfile)
	{
		ret = LZH_LOG_FAILED;
		goto end;
	}

	strcpy((char *)tmp, path);
	lgst->log_file = pfile;

end:
	SYS_UNLOCK(lgst->mutex);
	return ret;
}

LZH_UINT32 lzh_log_trace(LZH_LOG log, const char *info, ...)
{
	int num = 0;
	int buflen = 0;

	char *large = NULL;
	char *buf = NULL;

	LZH_LOG_INFO *lgst = NULL;
	LZH_UINT32 ret = LZH_LOG_SUCCESS;
	va_list arg_list;

	if (!log)
	{
		return LZH_LOG_FAILED;
	}

	if (!info || !info[0])
	{
		return LZH_LOG_FAILED;
	}

	lgst = (LZH_LOG_INFO *)log;
	buflen = lgst->log_buf.size;

	if (lgst->len != sizeof(LZH_LOG_INFO))
	{
		return LZH_LOG_FAILED;
	}

	SYS_LOCK_NOTIME(lgst->mutex);

	va_start(arg_list, info);
	num = vsnprintf(NULL, 0, info, arg_list);
	va_end(arg_list);

	if (num < 0)
	{
		ret = LZH_LOG_FAILED;
		goto end;
	}

	if (num >= buflen)
	{
		large = malloc(num);
		if (!large)
		{
			exit(0);
		}
		memset(large, 0, num);

		buf = large;
		buflen = num;
	}
	else
	{
		buf = (char *)lgst->log_buf.value;
	}

	va_start(arg_list, info);
	num = vsnprintf(buf, buflen, info, arg_list);
	va_end(arg_list);

	if (num < 0)
	{
		ret = LZH_LOG_FAILED;
	}

	ret = log_output(lgst, buf);

end:
	if (large)
	{
		free(large);
	}
	SYS_UNLOCK(lgst->mutex);
	return ret;
}

LZH_UINT32 lzh_log_trace_bin(
	LZH_LOG			log, 
	const char		*name, 
	const LZH_UINT8 *data, 
	LZH_UINT32		size)
{
	LZH_LOG_INFO *lgst = NULL;
	LZH_UINT32	   ret  = LZH_LOG_SUCCESS;
	LZH_UINT8	  *bptr = NULL;
	LZH_UINT32	   blen = 0;

	char		tmp[4] = { 0 };
	const char *sline  = NULL;
	size_t		llen   = 0;
	size_t		offset = 0;
	size_t		nlen   = 0;

	LZH_UINT32	i,j = 0;

	if (!log || !data)
	{
		return LZH_LOG_FAILED;
	}

	if (!size)
	{
		return LZH_LOG_FAILED;
	}

	lgst = (LZH_LOG_INFO *)log;

	if (lgst->len != sizeof(LZH_LOG_INFO))
	{
		return LZH_LOG_FAILED;
	}

	SYS_LOCK_NOTIME(lgst->mutex);

	sline = "------------------------+------------------------\n";
	llen  = strlen(sline);

	bptr = lgst->log_buf.value;
	blen = lgst->log_buf.size - LOG_FORMAT_RESERVE_LEN;

	if (!name || !*name)
	{
		name = "BinInfo";
	}

	nlen = strlen(name);

	if (nlen > (size_t)blen)
	{
		nlen = blen;
	}

	strncpy((char *)bptr, name, blen);
	bptr[blen - 1] = '\0';

	ret = log_output(lgst, (const char *)bptr);
	if (ret != LZH_LOG_SUCCESS) {
		return ret;
	}

	sprintf((char *)bptr, "(%d bytes):\n%s", size, sline);

	offset += strlen((const char *)bptr);
	j = 0;
	i = 0;

	while (i < size)
	{
		if (i > 0)
		{
			if (i % 16 == 0)
			{
				strcat((char *)bptr, "\n");
				offset += 1;
				if (++j % 8 == 0)
				{
					strcat((char *)bptr, sline);
					offset += llen;
				}
			}
			else if (i % 8 == 0)
			{
				strcat((char *)bptr, "| ");
				offset += 2;
			}
		}

		if ((i + 1) % 16 == 0)
		{
			sprintf(tmp, "%02x", data[i]);
			offset += 2;
		}
		else
		{
			sprintf(tmp, "%02x ", data[i]);
			offset += 3;
		}

		strcat((char *)bptr, tmp);

		/* 这里预留 64 字节的安全距离，防止越界，同时也是给最后的
		   结尾部分留出空间 */
		if (offset >= blen)
		{
			ret = log_output(lgst, (const char *)bptr);
			offset = 0;

			memset(bptr, 0, lgst->log_buf.size);
		}

		i++;
	}

	strcat((char *)bptr, "\n");
	strcat((char *)bptr, sline);

	ret = log_output(lgst, (const char *)bptr);
	SYS_UNLOCK(lgst->mutex);
	return ret;
}

LZH_UINT32 lzh_log_trace_details(
	LZH_LOG      log,
	LZH_LOG_TYPE type,	/* 日志类型 */
	LZH_UINT32	  line,	/* 行数 */
	const char   *file,	/* 所属文件 */
	const char   *func,	/* 所属函数 */
	const char   *info,	/* 日志信息 */
	...)
{
	int num = 0;
	LZH_LOG_INFO *lgst = NULL;
	LZH_UINT32	ret = LZH_LOG_SUCCESS;
	LZH_UINT32 level = 0;

	char buf[64] = { 0 };
	char *large = NULL;
	size_t lsize = 0;

	LZH_UINT8 *tmp	= NULL;
	size_t tmplen = 0;
	size_t offset = 0;
	va_list arg_list;

	if (!log)
	{
		return LZH_LOG_FAILED;
	}

	if (!info || !info[0] ||
		!file || !file[0] ||
		!func || !func[0])
	{
		return LZH_LOG_FAILED;
	}

	lgst = (LZH_LOG_INFO *)log;

	if (lgst->len != sizeof(LZH_LOG_INFO))
	{
		return LZH_LOG_FAILED;
	}

	level = lgst->flag & LOG_LEVEL_MASK;

	/* 日志等级限制 */
	if (level == LOG_LEVEL_NORMAL)
	{
		if (type == LOG_TYPE_INFO || type == LOG_TYPE_WARNING)
		{
			return LZH_LOG_SUCCESS;
		}
	}
	else if (level == LOG_LEVEL_LOW_DBG)
	{
		if (type == LOG_TYPE_INFO)
		{
			return LZH_LOG_SUCCESS;
		}
	}
	else if (level != LOG_LEVEL_FULL_DEBUG)
	{
		return LZH_LOG_FAILED;
	}

	SYS_LOCK_NOTIME(lgst->mutex);

	tmp = lgst->log_buf.value;
	tmplen = lgst->log_buf.size - LOG_FORMAT_RESERVE_LEN;

	strcpy((char *)tmp, "[");
	offset++;

	/* 显示进程 ID */
	if (lgst->flag & LOG_OPT_SHOW_PROCESS_ID)
	{
		if (sizeof(SDL_threadID) <= 4)
		{
			/* 32 位机 */
			sprintf(buf, "0x%08X ", (unsigned int)lzh_getpid());
		}
		else
		{
			/* 64 位机 */
			sprintf(buf, "0x%llX ", (unsigned long long)lzh_getpid());
		}

		strcat((char *)(tmp + offset), buf);
		offset += strlen(buf);
	}

	/* 显示线程 ID */
	if (lgst->flag & LOG_OPT_SHOW_THREAD_ID)
	{
		if (sizeof(SDL_threadID) <= 4)
		{
			/* 32 位机 */
			sprintf(buf, "0x%08X ", (unsigned int)SDL_ThreadID());
		}
		else
		{
			/* 64 位机 */
			sprintf(buf, "0x%llX ", (unsigned long long)SDL_ThreadID());
		}

		strcat((char*)(tmp + offset), buf);
		offset += strlen(buf);
	}

	if (lgst->log_name[0])
	{
		strcpy((char *)(tmp + offset), lgst->log_name);
		offset += strlen(lgst->log_name);
		strcpy((char *)(tmp + offset), " ");
		offset++;
	}

	switch (type)
	{
	case LOG_TYPE_ERROR:
		strcpy((char *)(tmp + offset), LOG_STR_ERROR_FLG);
		offset += (sizeof(LOG_STR_ERROR_FLG) - 1);
		break;
	case LOG_TYPE_WARNING:
		strcpy((char *)(tmp + offset), LOG_STR_WARNING_FLG);
		offset += (sizeof(LOG_STR_WARNING_FLG) - 1);
		break;
	case LOG_TYPE_INFO:
	default:
		strcpy((char *)(tmp + offset), LOG_STR_INFO_FLG);
		offset += (sizeof(LOG_STR_INFO_FLG) - 1);
	}

	if ((ret = lzh_get_curtime(" %Y-%m-%d %H:%M:%S]:", buf, sizeof(buf))) != LZH_LOG_SUCCESS)
	{
		goto end;
	}
	strcpy((char*)(tmp + offset), buf);
	offset += strlen(buf);

	if (offset >= tmplen)
	{
		goto end;
	}

	tmplen = tmplen - offset;

	/* 数据量过大则单独申请一块内存来输出 */
	va_start(arg_list, info);
	num = vsnprintf(NULL, 0, info, arg_list);
	va_end(arg_list);

	if (num < 0) 
	{
		goto end;
	}

	if (num >= (int)tmplen)
	{
		lsize = offset + num + LOG_FORMAT_RESERVE_LEN;
		large = malloc(lsize);
		if (!large)
		{
			exit(0);
		}
		memset(large, 0, lsize);
		strcpy(large, (const char *)tmp);

		tmp = (LZH_UINT8 *)large;
		tmplen = lsize - offset;
	}

	va_start(arg_list, info);
	num = vsnprintf((char *)(tmp + offset), tmplen, info, arg_list);
	va_end(arg_list);

	if (num < 0) 
	{
		goto end;
	}

	offset += num;

	if (lgst->flag & LOG_OPT_SHOW_FILE_PATH)
	{
		strcpy((char *)(tmp + offset), " file:");
		offset += 6;
		strcpy((char *)(tmp + offset), file);
		offset += strlen(file);
	}

	if (lgst->flag & LOG_OPT_SHOW_FUNC_LINE)
	{
		strcpy((char *)(tmp + offset), " func:");
		offset += 6;
		strcpy((char *)(tmp + offset), func);
		offset += strlen(func);
		strcpy((char *)(tmp + offset), " line:");
		offset += 6;
		sprintf(buf, "%d ", line);
		strcpy((char *)(tmp + offset), buf);
		offset += strlen(buf);
	}

	strcpy((char *)(tmp + offset), "\n");
	ret = log_output(lgst, (const char *)tmp);

end:
	if (large)
	{
		free(large);
	}
	SYS_UNLOCK(lgst->mutex);
	return ret;
}

/* ========================================================================= */

LZH_UINT32 log_output(LZH_LOG_INFO *log, const char *info)
{
	LZH_UINT32 ret = LZH_LOG_SUCCESS;

	if (!log)
	{
		return LZH_LOG_FAILED;
	}

	switch (log->flag & LOG_OUTPUT_MASK)
	{
	case LOG_OUTPUT_FILE:
		ret = log_output_file(log, info);
		break;

	case LOG_OUTPUT_SYS:
		ret = log_output_sys(log, info);
		break;

	case LOG_OUTPUT_STD:
	default:
		ret = log_output_std(log, info);
	}

	return ret;
}

LZH_UINT32 log_output_std(LZH_LOG_INFO *log, const char *info)
{
	LZH_UINT32 ret = LZH_LOG_SUCCESS;

	if (!log)
	{
		return LZH_LOG_FAILED;
	}

	if (!info || !*info)
	{
		return LZH_LOG_FAILED;
	}

	printf("%s", info);

	if (log->flag & LOG_OPT_FLUSH_EVERYONE)
	{
		fflush(stdout);
	}

	return ret;
}

LZH_UINT32 log_output_file(LZH_LOG_INFO *log, const char *info)
{
	LZH_UINT32	ret    = LZH_LOG_SUCCESS;
	const char *str	   = NULL;
	FILE		**fptr = &log->log_file;

	if (!log)
	{
		return LZH_LOG_FAILED;
	}

	if (!info || !*info)
	{
		return LZH_LOG_FAILED;
	}

	if (!(*fptr))
	{
		if (!log->path_buf.value || !log->path_buf.value[0])
		{
			return LZH_LOG_FAILED;
		}

		/* 打开文件 */
		*fptr = log_open_file(log, (const char *)log->path_buf.value);

		if (!(*fptr))
		{
			return LZH_LOG_FAILED;
		}
	}

	str = info;
	fwrite((const char*)str, sizeof(const char), strlen(str), *fptr);

	if (log->flag & LOG_OPT_FLUSH_EVERYONE)
	{
		fflush(*fptr);
	}

	return ret;
}

LZH_UINT32 log_output_sys(LZH_LOG_INFO *log, const char *info)
{
	LZH_UINT32 ret = LZH_LOG_SUCCESS;

	printf(info);
	return ret;
}

FILE *log_open_file(LZH_LOG_INFO *log, const char *path)
{
	FILE *file = NULL;

	if (!log)
	{
		return NULL;
	}

	if (!path || !*path)
	{
		return NULL;
	}

	/* 判断是否文件是否属于追加模式 */
	if ((log->flag & LOG_OPT_FILE_APPEND) == LOG_OPT_FILE_APPEND)
	{
		file = fopen(path, LOG_FILE_INPLZH_APPEND);
	}
	else
	{
		file = fopen(path, LOG_FILE_INPLZH_WRITE);
	}

	return file;
}

/*===========================================================================*/
