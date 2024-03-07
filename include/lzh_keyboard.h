#ifndef __LZH_KEYBOARD_H__
#define __LZH_KEYBOARD_H__

#include "lzh_type.h"

/*===========================================================================*/
/* 键盘事件 */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/* 键盘按键码 */
typedef enum
{
    KEY_CODE_0 = 0x00,
    KEY_CODE_1 = 0x01,
    KEY_CODE_2 = 0x02,
    KEY_CODE_3 = 0x03,
    KEY_CODE_4 = 0x04,
    KEY_CODE_5 = 0x05,
    KEY_CODE_6 = 0x06,
    KEY_CODE_7 = 0x07,
    KEY_CODE_8 = 0x08,
    KEY_CODE_9 = 0x09,

    KEY_CODE_A = 0x0A,
    KEY_CODE_B = 0x0B,
    KEY_CODE_C = 0x0C,
    KEY_CODE_D = 0x0D,
    KEY_CODE_E = 0x0E,
    KEY_CODE_F = 0x0F,
    KEY_CODE_G = 0x10,
    KEY_CODE_H = 0x11,
    KEY_CODE_I = 0x12,
    KEY_CODE_J = 0x13,
    KEY_CODE_K = 0x14,
    KEY_CODE_L = 0x15,
    KEY_CODE_M = 0x16,
    KEY_CODE_N = 0x17,
    KEY_CODE_O = 0x18,
    KEY_CODE_P = 0x19,
    KEY_CODE_Q = 0x1A,
    KEY_CODE_R = 0x1B,
    KEY_CODE_S = 0x1C,
    KEY_CODE_T = 0x1D,
    KEY_CODE_U = 0x1E,
    KEY_CODE_V = 0x1F,
    KEY_CODE_W = 0x20,
    KEY_CODE_X = 0x21,
    KEY_CODE_Y = 0x22,
    KEY_CODE_Z = 0x23,

    KEY_CODE_SPACE = 0x024
} LZH_KEYCODE;

/* 检测键盘按键否按下，（逐帧检测），按下返回 LZH_TRUE，未按下返回 LZH_FALSE */
LZH_API LZH_BOOL lzh_get_key_status(LZH_KEYCODE code);

#ifdef __cplusplus
}
#endif

/*===========================================================================*/

#endif /* __LZH_KEYBOARD_H__ */
