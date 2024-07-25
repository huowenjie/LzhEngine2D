#ifndef __LZH_SHADER_H__
#define __LZH_SHADER_H__

#include "../math/lzh_mat2x2f.h"
#include "../math/lzh_mat3x3f.h"
#include "../math/lzh_mat4x4f.h"
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

/* 通用文本着色器 */
LZH_SHADER *lzh_shader_text();

/* 销毁着色器 */
void lzh_shader_destroy(LZH_SHADER *shader);

/* 绑定着色程序 */
void lzh_shader_bind(LZH_SHADER *shader);

/* 取消绑定着色程序 */
void lzh_shader_unbind(LZH_SHADER *shader);

/* 设置着色器数据 */
void lzh_shader_set_int(LZH_SHADER *shader, const char *name, int value);
void lzh_shader_set_float(LZH_SHADER *shader, const char *name, float value);
void lzh_shader_set_vec2f(LZH_SHADER *shader, const char *name, const LZH_VEC2F *vec);
void lzh_shader_set_vec3f(LZH_SHADER *shader, const char *name, const LZH_VEC3F *vec);
void lzh_shader_set_vec4f(LZH_SHADER *shader, const char *name, const LZH_VEC4F *vec);
void lzh_shader_set_mat2x2f(LZH_SHADER *shader, const char *name, const LZH_MAT2X2F *mat);
void lzh_shader_set_mat3x3f(LZH_SHADER *shader, const char *name, const LZH_MAT3X3F *mat);
void lzh_shader_set_mat4x4f(LZH_SHADER *shader, const char *name, const LZH_MAT4X4F *mat);

/*===========================================================================*/

#endif /* __LZH_SHADER_H__ */
