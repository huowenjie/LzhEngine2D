#include <lzh_mem.h>
#include <lzh_systool.h>

#include "lzh_shader.h"
#include "../log/lzh_tracer.h"

/*===========================================================================*/

static char infobuffer[1024] = { 0 };

static LZH_BOOL lzh_shader_compile_check(GLuint shader);
static LZH_BOOL lzh_program_link_check(GLuint shader);
static void lzh_shader_show_err(GLuint shader);
static void lzh_program_show_err(GLuint shader);

/*===========================================================================*/

LZH_SHADER *lzh_shader_create(const char *vert_file, const char *frag_file)
{
    LZH_DATA vdata;
    LZH_DATA fdata;
    LZH_SHADER *shader = NULL;

    if (!vert_file || !*vert_file) {
        return NULL;
    }

    if (!frag_file || !*frag_file) {
        return NULL;
    }

    LZH_DATA_INIT(&vdata);
    LZH_DATA_INIT(&fdata);

    vdata.size = lzh_get_file_size(vert_file);
    fdata.size = lzh_get_file_size(frag_file);

    if (!vdata.size || !fdata.size) {
        return NULL;
    }

    LZH_DATA_MALLOC(&vdata, vdata.size);
    LZH_DATA_MALLOC(&fdata, fdata.size);

    if (!lzh_read_file(vert_file, &vdata) || !lzh_read_file(frag_file, &fdata)) {
        goto end;
    }

    shader = lzh_shader_new((const char *)vdata.value, (const char *)fdata.value);
end:
    LZH_DATA_FREE(&vdata);
    LZH_DATA_FREE(&fdata);
    return shader;
}

LZH_SHADER *lzh_shader_new(const char *vert_shader, const char *frag_shader)
{
    LZH_SHADER *shader = NULL;
    GLuint program = 0;
    GLuint vshader = 0;
    GLuint fshader = 0;

    LZH_BOOL success = LZH_TRUE;

    if (!vert_shader || !*vert_shader) {
        return NULL;
    }

    if (!frag_shader || !*frag_shader) {
        return NULL;
    }

    shader = LZH_MALLOC(sizeof(LZH_SHADER));
    if (!shader) {
        return NULL;
    }
    memset(shader, 0, sizeof(LZH_SHADER));

    vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vert_shader, NULL);
    glCompileShader(vshader);

    if (!lzh_shader_compile_check(vshader)) {
        lzh_shader_show_err(vshader);
        success = LZH_FALSE;
        goto end;
    }

    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &frag_shader, NULL);
    glCompileShader(fshader);

    if (!lzh_shader_compile_check(fshader)) {
        lzh_shader_show_err(fshader);
        success = LZH_FALSE;
        goto end;
    }

    program = glCreateProgram();
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);
    glLinkProgram(program);

    if (!lzh_program_link_check(program)) {
        lzh_program_show_err(program);
        success = LZH_FALSE;
        goto end;
    }

    shader->program = program;

end:
    if (vshader) {
        glDeleteShader(vshader);
    }

    if (fshader) {
        glDeleteShader(fshader);
    }

    if (!success) {
        if (program) {
            glDeleteProgram(program);
        }

        if (shader) {
            LZH_FREE(shader);
            shader = NULL;
        }
    }
    
    return shader;
}

LZH_SHADER *lzh_shader_sprite()
{
    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 inPos;\n"
        "layout (location = 1) in vec4 inColor;\n"
        "layout (location = 2) in vec2 inTexCoord;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "out vec4 outColor;\n"
        "out vec2 outTexture;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * model * vec4(inPos, 1.0);\n"
        "   outColor = inColor;\n"
        "   outTexture = inTexCoord;\n"
        "}\n\0";

    const char *fragmentShaderSource = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 outColor;\n"
        "in vec2 outTexture;\n"
        "uniform sampler2D texture1;\n"
        "void main()\n"
        "{\n"
        "   FragColor = texture(texture1, outTexture);\n"
        "}\n\0";

    return lzh_shader_new(vertexShaderSource, fragmentShaderSource);
}

LZH_SHADER *lzh_shader_text()
{
    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 inPos;\n"
        "layout (location = 1) in vec2 inTexCoord;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "out vec2 outTexture;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * model * vec4(inPos, 1.0);\n"
        "   outTexture = inTexCoord;\n"
        "}\n\0";

    const char *fragmentShaderSource = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 outTexture;\n"
        "uniform sampler2D texture1;\n"
        "uniform vec4 textColor;\n"
        "void main()\n"
        "{\n"
        "   vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture1, outTexture).r);\n"
        "   FragColor = textColor * sampled;\n"
        "}\n\0";

    return lzh_shader_new(vertexShaderSource, fragmentShaderSource);
}

void lzh_shader_destroy(LZH_SHADER *shader)
{
    if (shader) {
        if (shader->program) {
            glDeleteProgram(shader->program);
        }
        LZH_FREE(shader);
    }
}

void lzh_shader_bind(LZH_SHADER *shader)
{
    if (shader && shader->program) {
        glUseProgram(shader->program);
    }
}

void lzh_shader_unbind(LZH_SHADER *shader)
{
    if (shader && shader->program) {
        glUseProgram(0);
    }
}

void lzh_shader_set_int(LZH_SHADER *shader, const char *name, int value)
{
    GLint location = 0;

    if (!name || !*name) {
        return;
    }

    if (!shader || !shader->program) {
        return;
    }

    location = glGetUniformLocation(shader->program, name);
    glUniform1i(location, value);
}

void lzh_shader_set_float(LZH_SHADER *shader, const char *name, float value)
{
    GLint location = 0;

    if (!name || !*name) {
        return;
    }

    if (!shader || !shader->program) {
        return;
    }

    location = glGetUniformLocation(shader->program, name);
    glUniform1f(location, value);
}

void lzh_shader_set_vec2f(
    LZH_SHADER *shader, const char *name, const LZH_VEC2F *vec)
{
    GLint location = 0;

    if (!name || !*name || !vec) {
        return;
    }

    if (!shader || !shader->program) {
        return;
    }

    location = glGetUniformLocation(shader->program, name);
    glUniform2f(location, vec->x, vec->y);
}

void lzh_shader_set_vec3f(
    LZH_SHADER *shader, const char *name, const LZH_VEC3F *vec)
{
    GLint location = 0;

    if (!name || !*name || !vec) {
        return;
    }

    if (!shader || !shader->program) {
        return;
    }

    location = glGetUniformLocation(shader->program, name);
    glUniform3f(location, vec->x, vec->y, vec->z);
}

void lzh_shader_set_vec4f(
    LZH_SHADER *shader, const char *name, const LZH_VEC4F *vec)
{
    GLint location = 0;

    if (!name || !*name || !vec) {
        return;
    }

    if (!shader || !shader->program) {
        return;
    }

    location = glGetUniformLocation(shader->program, name);
    glUniform4f(location, vec->x, vec->y, vec->z, vec->w);
}

void lzh_shader_set_mat2x2f(
    LZH_SHADER *shader, const char *name, const LZH_MAT2X2F *mat)
{
    GLint location = 0;

    if (!name || !*name || !mat) {
        return;
    }

    if (!shader || !shader->program) {
        return;
    }

    location = glGetUniformLocation(shader->program, name);
    glUniformMatrix2fv(location, 1, GL_TRUE, mat->mat);
}

void lzh_shader_set_mat3x3f(
    LZH_SHADER *shader, const char *name, const LZH_MAT3X3F *mat)
{
    GLint location = 0;

    if (!name || !*name || !mat) {
        return;
    }

    if (!shader || !shader->program) {
        return;
    }

    location = glGetUniformLocation(shader->program, name);
    glUniformMatrix3fv(location, 1, GL_TRUE, mat->mat);
}

void lzh_shader_set_mat4x4f(
    LZH_SHADER *shader, const char *name, const LZH_MAT4X4F *mat)
{
    GLint location = 0;

    if (!name || !*name || !mat) {
        return;
    }

    if (!shader || !shader->program) {
        return;
    }

    location = glGetUniformLocation(shader->program, name);
    glUniformMatrix4fv(location, 1, GL_TRUE, mat->mat);
}

/*===========================================================================*/

LZH_BOOL lzh_shader_compile_check(GLuint shader)
{
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    return success ? LZH_TRUE : LZH_FALSE;
}

LZH_BOOL lzh_program_link_check(GLuint program)
{
    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    return success ? LZH_TRUE : LZH_FALSE;
}

void lzh_shader_show_err(GLuint shader)
{
    glGetShaderInfoLog(shader, sizeof(infobuffer), NULL, infobuffer);
    LZH_TRACE(infobuffer);
}

void lzh_program_show_err(GLuint program)
{
    glGetProgramInfoLog(program, sizeof(infobuffer), NULL, infobuffer);
    LZH_TRACE(infobuffer);
}

/*===========================================================================*/
