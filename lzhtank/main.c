#include <stddef.h>
#include <lzh_engine.h>

/*===========================================================================*/

static LZH_UINT32 update(LZH_ENGINE *eg, void *args);

/*===========================================================================*/

int main(int argc, char* argv[])
{
    LZH_ENGINE *engine = NULL;
    
    lzh_init();

    engine = lzh_engine_create("Tank", 800, 600);
    if (!engine) {
        return 0;
    }

    lzh_engine_set_update(engine, update, NULL);
    lzh_engine_render(engine);
    lzh_engine_destroy(engine);

    lzh_quit();
    return 0;
}

/*===========================================================================*/

LZH_UINT32 update(LZH_ENGINE *eg, void *args)
{
    return 0;
}

/*===========================================================================*/
