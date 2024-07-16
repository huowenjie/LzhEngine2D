#include <lzh_mem.h>

#include "lzh_core_text.h"
#include "lzh_core_camera.h"

/*===========================================================================*/

static void lzh_text_draw(LZH_BASE *base, void *args);
static void lzh_text_remove(LZH_COMPONENT *cpnt);

static void init_vertex(LZH_TEXT *text);
static void quit_vertex(LZH_TEXT *text);

/*===========================================================================*/

LZH_TEXT *lzh_text_create(LZH_ENGINE *engine, LZH_OBJECT *object)
{
    LZH_TEXT *text = NULL;
    LZH_COMPONENT *base = NULL;

    if (!engine || !object) {
        return NULL;
    }

    text = LZH_MALLOC(sizeof(LZH_TEXT));
    if (!text) {
        return NULL;
    }
    memset(text, 0, sizeof(LZH_TEXT));

    base = &text->base;
    lzh_cpnt_init(base, LZH_CPNT_TEXT, object);

    base->base.engine = engine;
    base->base.draw = lzh_text_draw;
    base->remove_component = lzh_text_remove;

    text->text_face = NULL;
    text->text_char = NULL;

    init_vertex(text);
    return text;
}

void lzh_text_destroy(LZH_TEXT *text)
{
    lzh_cpnt_destroy((LZH_COMPONENT *)text);
}

LZH_BOOL lzh_text_load_font(LZH_TEXT *text, const char *font)
{
    FT_Face face = NULL;
    LZH_ENGINE *engine = NULL;

    if (!text || !font || !*font) {
        return LZH_FALSE;
    }

    engine = text->base.base.engine;
    if (!engine) {
        return LZH_FALSE;
    }

    if (text->text_face) {
        if (FT_Done_Face(text->text_face)) {
            return LZH_FALSE;
        }
        text->text_face = NULL;
    }

    if (FT_New_Face(engine->ft_lib, font, 0, &face)) {
        return LZH_FALSE;
    }

    text->text_face = face;
    return LZH_TRUE;
}

void lzh_text_set_font_size(LZH_TEXT *text, int pw, int ph)
{
    FT_Face face = NULL;
    
    if (!text) {
        return;
    }

    face = text->text_face;
    if (!face) {
        return;
    }

    FT_Set_Pixel_Sizes(face, pw, ph);  
}

void lzh_text_set_font_color(
    LZH_TEXT *text, float r, float g, float b, float a)
{
    
}

void lzh_text_set_content(LZH_TEXT *text, const char *content)
{
    if (text && text->text_face) {
        LZH_CHARACTER *character = NULL;
        FT_Face face = text->text_face;
        FT_GlyphSlot slot = face->glyph;
        FT_Bitmap *bitmap = NULL;

        FT_ULong charcode = 0x5B89;
        FT_UInt index = FT_Get_Char_Index(face, charcode);

        LZH_DATA buffer = { 0 };

        printf("index = %d -- charcode = %ld\n", index, charcode);

        if (FT_Load_Glyph(text->text_face, index, FT_LOAD_DEFAULT)) {
            return;
        }

        if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL)) {
            return;
        }

        bitmap = &slot->bitmap;
        if (!bitmap) {
            return;
        }

        buffer.value = bitmap->buffer;
        buffer.size = bitmap->width * bitmap->rows;

        // render
        character = lzh_character_create(
            &buffer, bitmap->width, bitmap->rows,
            slot->bitmap_left, slot->bitmap_top, slot->advance.x);
        if (character) {
            text->text_char = character;
        }
    }
}

void lzh_text_set_offset(LZH_TEXT *text, float x, float y, float z)
{

}

/*===========================================================================*/

static void update_text_vertex(
    LZH_SHADER *shader, LZH_CAMERA *camera, LZH_TRANSFORM *transform, LZH_TEXT *text)
{
    LZH_MAT4X4F proj = lzh_mat4x4f_unit();
    
    if (!shader || !camera || !transform || !text) {
        return;
    }

    proj = lzh_mat4x4f_ortho2d(0.0f, camera->view_port_h, camera->view_port_w, 0.0f);

    if (text->vao) {
        LZH_CHARACTER *character = text->text_char;
        if (!character) {
            return;
        }

        GLfloat xpos = 0.0f + character->bearing_x;
        //GLfloat ypos = 0.0f - (character->height - character->bearing_y);
        GLfloat ypos = 0.0f;

        GLfloat w = character->width;
        GLfloat h = character->height;

        float vertices[] = {
            xpos + w, ypos,     1.0f, 1.0f,
            xpos + w, ypos + h, 1.0f, 0.0f,
            xpos,     ypos + h, 0.0f, 0.0f,
            xpos,     ypos,     0.0f, 1.0f
        };

        glBindBuffer(GL_ARRAY_BUFFER, text->vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 

        lzh_shader_bind(shader);
        lzh_shader_set_mat4x4f(shader, "projection", &proj);

        glBindVertexArray(text->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}

static void update_text_texture(LZH_ENGINE *engine, LZH_TEXT *text)
{
    LZH_SHADER *shader = NULL;
    LZH_CHARACTER *character = NULL;
    LZH_VEC3F textcolor = lzh_vec3f_xyz(1.0f, 0.0f, 0.0f);

    if (!engine || !text) {
        return;
    }

    shader = engine->text_shader;
    if (!shader) {
        return;
    }

    character = text->text_char;
    if (!character) {
        return;
    }

    lzh_shader_bind(shader);
    lzh_shader_set_vec3f(shader, "textColor", &textcolor);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, character->texid);
}

void lzh_text_draw(LZH_BASE *base, void *args)
{
    LZH_TEXT *text = NULL;
    LZH_OBJECT *object = NULL;
    LZH_ENGINE *engine = NULL;
    LZH_TRANSFORM *transform = NULL;
    LZH_OBJECT *camera = NULL;
    LZH_CAMERA *camera_cpnt = NULL;
    LZH_SCENE *scene = NULL;

    if (!base) {
        return;
    }

    text = (LZH_TEXT *)base;

    object = text->base.object;
    if (!object) {
        return;
    }

    engine = object->base.engine;
    if (!engine) {
        return;
    }

    scene = lzh_sm_get_active_scene(engine->scene_manager);
    if (!scene) {
        return;
    }

    camera = scene->main_camera;
    if (!camera) {
        return;
    }

    camera_cpnt = (LZH_CAMERA *)lzh_cpnt_get_type(
        camera->components, LZH_CPNT_CAMERA);
    if (!camera_cpnt) {
        return;
    }

    transform = object->transform;
    if (!transform) {
        return;
    }

    update_text_texture(engine, text);
    update_text_vertex(engine->text_shader, camera_cpnt, transform, text);
}

void lzh_text_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_TEXT *text = (LZH_TEXT *)cpnt;

        quit_vertex(text);

        if (text->text_char) {
            lzh_character_destroy(text->text_char);
            text->text_char = NULL;
        }

        if (text->text_face) {
            FT_Face face = text->text_face;
            FT_Done_Face(face);
            text->text_face = NULL;
        }

        lzh_cpnt_quit(cpnt);
        LZH_FREE(text);
    }
}

void init_vertex(LZH_TEXT *text)
{
    int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;

    if (!text) {
        return;
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    text->vao = vao;
    text->vbo = vbo;
    text->ebo = ebo;
}

void quit_vertex(LZH_TEXT *text)
{
    if (text) {
        if (text->ebo) {
            glDeleteBuffers(1, &text->ebo);
        }

        if (text->vbo) {
            glDeleteBuffers(1, &text->vbo);
        }

        if (text->vao) {
            glDeleteBuffers(1, &text->vao);
        }
    }
}

/*===========================================================================*/
