#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>
#include <lzh_scene.h>

#include "tank.h"
#include "globalres.h"
#include "level.h"

/*===========================================================================*/

int main(int argc, char *argv[])
{
    LZH_ENGINE *engine = NULL;

    lzh_init();
    init_global_res();

    engine = lzh_engine_create("Tank", 800, 600);
    if (!engine) {
        return 0;
    }

    level_load_scenes(engine);

    lzh_engine_update(engine);
    lzh_engine_destroy(engine);
    lzh_quit();
    return 0;
}

/*===========================================================================*/
