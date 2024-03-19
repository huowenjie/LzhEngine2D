#include <lzh_keyboard.h>
#include <SDL2/SDL_keyboard.h>

/*===========================================================================*/

LZH_BOOL lzh_get_key_status(LZH_KEYCODE code)
{
    LZH_BOOL ret = LZH_FALSE;
    const Uint8 *status = SDL_GetKeyboardState(NULL);

    /* SDL °´¼üÓ³Éä  */
    switch (code) {
    case KEY_CODE_0: ret = (LZH_BOOL)status[SDL_SCANCODE_0]; break;
    case KEY_CODE_1: ret = (LZH_BOOL)status[SDL_SCANCODE_1]; break;
    case KEY_CODE_2: ret = (LZH_BOOL)status[SDL_SCANCODE_2]; break;
    case KEY_CODE_3: ret = (LZH_BOOL)status[SDL_SCANCODE_3]; break;
    case KEY_CODE_4: ret = (LZH_BOOL)status[SDL_SCANCODE_4]; break;
    case KEY_CODE_5: ret = (LZH_BOOL)status[SDL_SCANCODE_5]; break;
    case KEY_CODE_6: ret = (LZH_BOOL)status[SDL_SCANCODE_6]; break;
    case KEY_CODE_7: ret = (LZH_BOOL)status[SDL_SCANCODE_7]; break;
    case KEY_CODE_8: ret = (LZH_BOOL)status[SDL_SCANCODE_8]; break;
    case KEY_CODE_9: ret = (LZH_BOOL)status[SDL_SCANCODE_9]; break;
    case KEY_CODE_A: ret = (LZH_BOOL)status[SDL_SCANCODE_A]; break;
    case KEY_CODE_B: ret = (LZH_BOOL)status[SDL_SCANCODE_B]; break;
    case KEY_CODE_C: ret = (LZH_BOOL)status[SDL_SCANCODE_C]; break;
    case KEY_CODE_D: ret = (LZH_BOOL)status[SDL_SCANCODE_D]; break;
    case KEY_CODE_E: ret = (LZH_BOOL)status[SDL_SCANCODE_E]; break;
    case KEY_CODE_F: ret = (LZH_BOOL)status[SDL_SCANCODE_F]; break;
    case KEY_CODE_G: ret = (LZH_BOOL)status[SDL_SCANCODE_G]; break;
    case KEY_CODE_H: ret = (LZH_BOOL)status[SDL_SCANCODE_H]; break;
    case KEY_CODE_I: ret = (LZH_BOOL)status[SDL_SCANCODE_I]; break;
    case KEY_CODE_J: ret = (LZH_BOOL)status[SDL_SCANCODE_J]; break;
    case KEY_CODE_K: ret = (LZH_BOOL)status[SDL_SCANCODE_K]; break;
    case KEY_CODE_L: ret = (LZH_BOOL)status[SDL_SCANCODE_L]; break;
    case KEY_CODE_M: ret = (LZH_BOOL)status[SDL_SCANCODE_M]; break;
    case KEY_CODE_N: ret = (LZH_BOOL)status[SDL_SCANCODE_N]; break;
    case KEY_CODE_O: ret = (LZH_BOOL)status[SDL_SCANCODE_O]; break;
    case KEY_CODE_P: ret = (LZH_BOOL)status[SDL_SCANCODE_P]; break;
    case KEY_CODE_Q: ret = (LZH_BOOL)status[SDL_SCANCODE_Q]; break;
    case KEY_CODE_R: ret = (LZH_BOOL)status[SDL_SCANCODE_R]; break;
    case KEY_CODE_S: ret = (LZH_BOOL)status[SDL_SCANCODE_S]; break;
    case KEY_CODE_T: ret = (LZH_BOOL)status[SDL_SCANCODE_T]; break;
    case KEY_CODE_U: ret = (LZH_BOOL)status[SDL_SCANCODE_U]; break;
    case KEY_CODE_V: ret = (LZH_BOOL)status[SDL_SCANCODE_V]; break;
    case KEY_CODE_W: ret = (LZH_BOOL)status[SDL_SCANCODE_W]; break;
    case KEY_CODE_X: ret = (LZH_BOOL)status[SDL_SCANCODE_X]; break;
    case KEY_CODE_Y: ret = (LZH_BOOL)status[SDL_SCANCODE_Y]; break;
    case KEY_CODE_Z: ret = (LZH_BOOL)status[SDL_SCANCODE_Z]; break;
    case KEY_CODE_SPACE: ret = (LZH_BOOL)status[SDL_SCANCODE_SPACE]; break;
    }

    return ret;
}

LZH_BOOL lzh_get_key_down(LZH_KEYCODE code)
{
    LZH_BOOL ret = LZH_FALSE;
    return ret;
}

/*===========================================================================*/
