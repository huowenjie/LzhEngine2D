#ifndef __LZH_SHADER_H__
#define __LZH_SHADER_H__

#include "../math/lzh_mat2x2f.h"
#include "../math/lzh_mat3x3f.h"
#include "../math/lzh_mat4x4f.h"
#include "lzh_opengl.h"

/*===========================================================================*/
/* ��ɫ�� */
/*===========================================================================*/

typedef struct LZH_SHADER {
    GLuint program;
} LZH_SHADER;

/* �����ļ�������ɫ�� */
LZH_SHADER *lzh_shader_create(const char *vert_file, const char *frag_file);

/* �������ݴ�����ɫ�� */
LZH_SHADER *lzh_shader_new(const char *vert_shader, const char *frag_shader);

/* ͨ�þ�����ɫ�� */
LZH_SHADER *lzh_shader_sprite();

/* ͨ���ı���ɫ�� */
LZH_SHADER *lzh_shader_text();

/* ������ɫ�� */
void lzh_shader_destroy(LZH_SHADER *shader);

/* ����ɫ���� */
void lzh_shader_bind(LZH_SHADER *shader);

/* ȡ������ɫ���� */
void lzh_shader_unbind(LZH_SHADER *shader);

/* ������ɫ������ */
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
