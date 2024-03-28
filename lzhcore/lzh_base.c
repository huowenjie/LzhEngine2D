#include <lzh_mem.h>
#include <string.h>
#include <lzh_systool.h>

#include "lzh_base.h"

/*===========================================================================*/

void lzh_base_init(LZH_BASE *base)
{
    if (base) {
        memset(base, 0, sizeof(LZH_BASE));
    }
}

void lzh_base_quit(LZH_BASE *base)
{
    if (base) {
        if (base->name) {
            LZH_FREE(base->name);
            base->name = NULL;
        }
        memset(base, 0, sizeof(LZH_BASE));
    }
}

void lzh_base_set_name(LZH_BASE *base, const char *name)
{
    char *buf = NULL;
    size_t size = 0;

    if (!base) {
        return;   
    }

    if (!name || !*name) {
        return;
    }

    size = strlen(name) + 1;
    buf = LZH_MALLOC(size);
    if (!buf) {
        return;
    }
    memset(buf, 0, size);
    strcpy(buf, name);

    if (base->name) {
        LZH_FREE(base->name);
    }

    base->name = buf;
    base->hash = lzh_gen_hash_code(buf);
}

/*===========================================================================*/
