#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>

#include "tank.h"
#include "globalres.h"
#include "level.h"

/*===========================================================================*/

int main(int argc, char *argv[])
{
    LZH_ENGINE *engine = NULL;
    LEVEL *level = NULL;

    lzh_init();
    init_global_res();

    engine = lzh_engine_create("Tank", 800, 600);
    if (!engine) {
        return 0;
    }

    level = level_create_level(engine);
    level_start(level);

    lzh_engine_render(engine);

    level_end(level);
    level_destroy_level(level);
    lzh_engine_destroy(engine);
    lzh_quit();
    return 0;
}

/*===========================================================================*/
