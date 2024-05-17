#include <stddef.h>
#include <stdio.h>
#include <lzh_engine.h>

#include "globalres.h"
#include "tank.h"
#include "camera.h"
#include "scene.h"

/*===========================================================================*/

class Game
{
public:
    Game();
    ~Game();
    
public:
    void Run();

private:
    LZH_ENGINE *engine;
};

int main(int argc, char *argv[])
{
    Game game;
    game.Run();
    return 0;
}

/*===========================================================================*/

Game::Game()
{
    lzh_init();
    init_global_res();
}

Game::~Game()
{
    lzh_engine_destroy(engine);
    lzh_quit();
}

void Game::Run()
{
    engine = lzh_engine_create("Tank", 800, 600);
    if (!engine) {
        return;
    }

    Scene scene(engine, "tutorial level");
    Tank player(engine);
    Camera camera(engine);

    scene.AddObjectToScene(&player);
    scene.AddObjectToScene(&camera);
    scene.SetMainCamera(&camera);
    scene.LoadScene();
    //level_load_scenes(engine);

    lzh_engine_update(engine);
}

/*===========================================================================*/
