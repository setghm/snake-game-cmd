#ifndef SNAKE_GAME_GAME_DEFINITIONS_H
#define SNAKE_GAME_GAME_DEFINITIONS_H

/* Game definition */

typedef struct TagGame {
    Console* console;
    bool running;
    Vec2 screen_size;

    Scene active_scene;
    ScenePlay* gameplay;
    SceneMenu* mainmenu;

    // Settings
    Settings* config;
    bool show_config;

    Time* time;
} Game;


#endif //SNAKE_GAME_GAME_DEFINITIONS_H
