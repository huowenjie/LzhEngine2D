#include <lzh_mem.h>
#include "lzh_vertex.h"

/*===========================================================================*/

LZH_SPRITE_VERTEX *lzh_vertex_sprite()
{
    float vertices[] = {
         /* positions          colors                texture coords */
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f
    };

    int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    LZH_SPRITE_VERTEX *vertex = LZH_MALLOC(sizeof(LZH_SPRITE_VERTEX));

    if (!vertex) {
        return vertex;
    }
    memset(vertex, 0, sizeof(LZH_SPRITE_VERTEX));

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    vertex->vao = vao;
    vertex->vbo = vbo;
    vertex->ebo = ebo;
    vertex->count = 6;
    return vertex;
}

LZH_TEXT_VERTEX *lzh_vertex_text()
{
    int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    LZH_TEXT_VERTEX *vertex = LZH_MALLOC(sizeof(LZH_TEXT_VERTEX));

    if (!vertex) {
        return vertex;
    }
    memset(vertex, 0, sizeof(LZH_TEXT_VERTEX));

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 5 * 4, NULL, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    vertex->vao = vao;
    vertex->vbo = vbo;
    vertex->ebo = ebo;
    vertex->count = 6;
    return vertex;
}

void lzh_vertex_text_data(
    LZH_TEXT_VERTEX *vertex, float x, float y, float w, float h)
{
    if (vertex) {
        float vertices[] = {
            x + w, y,     0.0f, 1.0f, 1.0f,   /* 纹理右上角 */
            x + w, y + h, 0.0f, 1.0f, 0.0f,   /* 纹理右下角 */
            x,     y + h, 0.0f, 0.0f, 0.0f,   /* 纹理左下角 */
            x,     y,     0.0f, 0.0f, 1.0f    /* 纹理左上角 */
        };
        glBindBuffer(GL_ARRAY_BUFFER, vertex->vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
    }
}

void lzh_vertex_destroy(LZH_VERTEX *vertex)
{
    if (vertex) {
        if (vertex->ebo) {
            glDeleteBuffers(1, &vertex->ebo);
        }

        if (vertex->vbo) {
            glDeleteBuffers(1, &vertex->vbo);
        }

        if (vertex->vao) {
            glDeleteBuffers(1, &vertex->vao);
        }

        LZH_FREE(vertex);
    }
}

void lzh_vertex_draw(LZH_VERTEX *vertex)
{
    if (vertex) {
        glBindVertexArray(vertex->vao);
        glDrawElements(GL_TRIANGLES, vertex->count, GL_UNSIGNED_INT, 0);
    }
}

void lzh_vertex_sprite_draw(LZH_SPRITE_VERTEX *vertex)
{
    lzh_vertex_draw(vertex);
}

void lzh_vertex_text_draw(LZH_TEXT_VERTEX *vertex)
{
    lzh_vertex_draw(vertex);
}

/*===========================================================================*/
