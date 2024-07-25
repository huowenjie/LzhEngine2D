#include <lzh_mem.h>
#include <lzh_type.h>

#include "../tool/lzh_stb_image.h"
#include "lzh_texture.h"

/*===========================================================================*/

static GLint get_png_format(int channels);

/*===========================================================================*/

LZH_TEXTURE *lzh_texture_create(const char *path)
{
    LZH_TEXTURE *texture = NULL;
    GLuint texid = 0;
    int width = 0;
    int height = 0;
    int channels = 0;

    LZH_UINT8 *imgdata = NULL;

    if (!path || !*path) {
        return NULL;
    }

    texture = LZH_MALLOC(sizeof(LZH_TEXTURE));
    if (!texture) {
        return NULL;
    }
    memset(texture, 0, sizeof(LZH_TEXTURE));

    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* ͼƬ�� y �ᷭתչʾ */
    stbi_set_flip_vertically_on_load(1);
    imgdata = stbi_load(path, &width, &height, &channels, 0);
    if (imgdata) {
        GLint format = get_png_format(channels);

        if (format == GL_NONE) {
            stbi_image_free(imgdata);
            glDeleteTextures(1, &texid);
            LZH_FREE(texture);
            return NULL;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imgdata);
        glGenerateMipmap(GL_TEXTURE_2D);

        texture->channels = channels;
        texture->width = width;
        texture->height = height;
        texture->texid = texid;

        stbi_image_free(imgdata);
    } else {
        if (texid) {
            glDeleteTextures(1, &texid);
        }

        LZH_FREE(texture);
        texture = NULL;
    }

    return texture;
}

void lzh_texture_destroy(LZH_TEXTURE *texture)
{
    if (texture) {
        glDeleteTextures(1, &texture->texid);
        LZH_FREE(texture);
    }
}

void lzh_texture_active(LZH_TEXTURE *texture)
{
    if (texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->texid);
    }
}

/*===========================================================================*/

LZH_CHARACTER *lzh_character_create(
    const LZH_DATA *bitmap, int w, int h, int bx, int by, int advance, int unicode)
{
    LZH_CHARACTER *character = NULL;
    GLuint texid = 0;

    if (!bitmap || !bitmap->value) {
        return NULL;
    }

    character = LZH_MALLOC(sizeof(LZH_CHARACTER));
    if (!character) {
        return NULL;
    }
    memset(character, 0, sizeof(LZH_CHARACTER));

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap->value);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    character->base.texid = texid;
    character->base.width = w;
    character->base.height = h;
    character->advance = advance;
    character->bearing_x = bx;
    character->bearing_y = by;
    character->unicode = unicode;
    return character;
}

void lzh_character_destroy(LZH_CHARACTER *character)
{
    if (character) {
        glDeleteTextures(1, &character->base.texid);
        LZH_FREE(character);
    }
}

/*===========================================================================*/

GLint get_png_format(int channels)
{
    GLint format = GL_NONE;

    switch (channels) {
        case 3:
            format = GL_RGB;
            break;

        case 4:
            format = GL_RGBA;
            break;
    }

    return format;
}

/*===========================================================================*/
