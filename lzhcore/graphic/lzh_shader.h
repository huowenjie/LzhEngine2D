#ifndef __LZH_SHADER_H__
#define __LZH_SHADER_H__

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

/* ������ɫ�� */
void lzh_shader_destroy(LZH_SHADER *shader);

/* ����ɫ���� */
void lzh_shader_bind(LZH_SHADER *shader);

/* ȡ������ɫ���� */
void lzh_shader_unbind(LZH_SHADER *shader);

/*===========================================================================*/

#endif /* __LZH_SHADER_H__ */
