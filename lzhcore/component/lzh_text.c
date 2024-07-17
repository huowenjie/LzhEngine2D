#include <lzh_mem.h>

#include "lzh_core_text.h"
#include "lzh_core_camera.h"

/*===========================================================================*/

RBTREE_IMPLEMENT(LZH_TEXT, lzh_text, int, LZH_CHARACTER *)

/*===========================================================================*/

static int lzh_text_tree_comp(const void *a, const void *b);
static void lzh_text_rb_visit(const LZH_TEXT_RB_NODE *node, void *args);

static void lzh_text_draw(LZH_BASE *base, void *args);
static void lzh_text_remove(LZH_COMPONENT *cpnt);

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
    text->characters = lzh_text_rb_create(lzh_text_tree_comp);
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

        FT_ULong charcode = 0x65;
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
            slot->bitmap_left, slot->bitmap_top, slot->advance.x, charcode);
        if (character) {
            text->text_char = character;
        }
    }
}

void lzh_text_set_offset(LZH_TEXT *text, float x, float y, float z)
{

}

/*===========================================================================*/

int lzh_text_tree_comp(const void *a, const void *b)
{
    int i1 = *((int *)a);
    int i2 = *((int *)b);

    if (i1 < i2) {
        return -1;
    } else if (i1 > i2) {
        return 1;
    }

    return 0;
}

void lzh_text_rb_visit(const LZH_TEXT_RB_NODE *node, void *args)
{
    LZH_CHARACTER *ch = NULL;

    if (!node) {
        return;
    }

    ch = node->value;
    if (!ch) {
        return;
    }

    lzh_character_destroy(ch);
}

static void update_text_vertex(
    LZH_TEXT_VERTEX *vertex,
    LZH_SHADER *shader,
    LZH_CAMERA *camera,
    LZH_TRANSFORM *transform,
    LZH_TEXT *text)
{
    LZH_MAT4X4F proj = lzh_mat4x4f_unit();
    LZH_VEC3F textcolor = lzh_vec3f_xyz(1.0f, 0.0f, 0.0f);

    if (!vertex || !shader || !camera || !transform || !text) {
        return;
    }

    proj = lzh_mat4x4f_ortho2d(0.0f, camera->view_port_h, camera->view_port_w, 0.0f);

    LZH_CHARACTER *character = text->text_char;
    if (!character) {
        return;
    }

    GLfloat xpos = 0.0f + character->bearing_x;
    //GLfloat ypos = 0.0f - (character->height - character->bearing_y);
    GLfloat ypos = 0.0f;

    GLfloat w = character->base.width;
    GLfloat h = character->base.height;

    lzh_shader_bind(shader);
    lzh_shader_set_vec3f(shader, "textColor", &textcolor);
    lzh_texture_active((LZH_TEXTURE *)character);

    lzh_vertex_text_data(vertex, xpos, ypos, w, h);
    lzh_shader_bind(shader);
    lzh_shader_set_mat4x4f(shader, "projection", &proj);
    lzh_vertex_text_draw(vertex);
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

    update_text_vertex(
        engine->text_vertex, engine->text_shader, camera_cpnt, transform, text);
}

void lzh_text_remove(LZH_COMPONENT *cpnt)
{
    if (cpnt) {
        LZH_TEXT *text = (LZH_TEXT *)cpnt;

        if (text->characters) {
            lzh_text_rb_destroy(text->characters, lzh_text_rb_visit, NULL);
        }

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

/*===========================================================================*/
