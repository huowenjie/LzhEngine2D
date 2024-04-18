#include "../sdl2/SDL.h"
#include "lzh_opengl.h"

/*===========================================================================*/

void lzh_init_opengl(int major, int minor)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

void lzh_quit_opengl()
{
}

void lzh_load_openglapi()
{
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
}

/*===========================================================================*/
