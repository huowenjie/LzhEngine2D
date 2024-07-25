#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>

#include "globalres.h"
#include "player.h"
#include "camera.h"
#include "scene.h"
#include "bullet.h"
#include "enemy.h"
#include "fontobj.h"

/*===========================================================================*/

void Run(LZH_ENGINE *engine);

/*===========================================================================*/

int main(int argc, char *argv[])
{
    LZH_ENGINE *engine = NULL;

    lzh_init();
    InitGlobalRes();

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
    Camera *camera = new Camera(engine, &scene);
    Enemy *enemy = new Enemy(engine, &scene);
    Player *player = new Player(engine, &scene);
    FontObj *font = new FontObj(engine, &scene);

    player->SetName("player");
    enemy->SetName("enemey");
    font->SetName("FlagText");
    enemy->SetPosition(8.0f, 0.0f);

    float height = font->GetTextHeight();
    font->SetPosition(-40.0f, 20.0f - height);

    scene.AddObject(camera);
    scene.AddObject(enemy);
    scene.AddObject(player);
    scene.AddObject(font);

    scene.SetMainCamera(camera);
    scene.LoadScene();

    lzh_engine_update(engine);
}

/*===========================================================================*/
