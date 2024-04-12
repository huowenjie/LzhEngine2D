#ifndef __LZH_SHADER_H__
#define __LZH_SHADER_H__

#include "lzh_opengl.h"

/*===========================================================================*/
/* 着色器 */
/*===========================================================================*/

typedef struct LZH_SHADER {
    GLuint program;
} LZH_SHADER;

/* 根据文件创建着色器 */
LZH_SHADER *lzh_shader_create(const char *vert_file, const char *frag_file);

/* 根据内容创建着色器 */
LZH_SHADER *lzh_shader_new(const char *vert_shader, const char *frag_shader);

/* 通用精灵着色器 */
LZH_SHADER *lzh_shader_sprite();

/* 销毁着色器 */
void lzh_shader_destroy(LZH_SHADER *shader);

/* 绑定着色程序 */
void lzh_shader_bind(LZH_SHADER *shader);

/* 取消绑定着色程序 */
void lzh_shader_unbind(LZH_SHADER *shader);

/*===========================================================================*/

#endif /* __LZH_SHADER_H__ */
