#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>
#include <LzhVector2d.h>
#include <LzhVector3d.h>
#include <LzhMatrix4x4.h>

/*===========================================================================*/

void Run(LZH_ENGINE *engine);

/*===========================================================================*/

int main(int argc, char *argv[])
{
    LZH_ENGINE *engine = NULL;

    lzh_init();

    engine = lzh_engine_create("Physics", 800, 600);
    if (!engine) {
        goto end;
    }

    Run(engine);

end:
    lzh_engine_destroy(engine);
    lzh_quit();
    return 0;
}

/*===========================================================================*/

void Run(LZH_ENGINE *engine)
{
    
    lzh_engine_update(engine);
}

/*===========================================================================*/
