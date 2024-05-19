#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>

#include "globalres.h"
#include "tank.h"
#include "camera.h"
#include "scene.h"
#include "bullet.h"

/*===========================================================================*/

void Run(LZH_ENGINE *engine);

/*===========================================================================*/

int main(int argc, char *argv[])
{
    LZH_ENGINE *engine = NULL;

    lzh_init();
    init_global_res();

    engine = lzh_engine_create("Tank", 800, 600);
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
    Scene scene(engine, "tutorial level");
    Tank player(engine);
    Camera camera(engine);

    player.SetCurrentScene(&scene);
    scene.AddObjectToScene(&player);
    scene.AddObjectToScene(&camera);
    scene.SetMainCamera(&camera);

    scene.LoadScene();

    lzh_engine_update(engine);
}

/*===========================================================================*/
