#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>

#include "globalres.h"
#include "player.h"
#include "camera.h"
#include "scene.h"
#include "bullet.h"
#include "explode.h"

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
    Tank tank(engine, &scene);
    Player player(engine, &scene);
    Camera camera(engine, &scene);

    tank.SetName("target");
    player.SetName("player");

    tank.SetPosition(0.0f, 4.0f);
    scene.SetMainCamera(&camera);

    scene.LoadScene();

    lzh_engine_update(engine);
}

/*===========================================================================*/
