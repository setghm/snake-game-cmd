#ifndef SNAKE_GAME_GAME_SCENES_DEFINITIONS_H
#define SNAKE_GAME_GAME_SCENES_DEFINITIONS_H

/* Game Scenes definition */

typedef enum TagScene {
    SCENE_PLAY, SCENE_MENU
} Scene;

typedef enum TagPlayState {
    PLAY_STATE_PLAYING,
    PLAY_STATE_PAUSED,
    PLAY_STATE_END
} PlayState;

typedef struct TagScenePlay {
    Game* parent;
    PlayState state;

    // Game Objects
    Snake* player;
    Fruit* target;
    PopupMenu* menu;
    MenuBar* bar;

    Vec2 canvas_size;

    unsigned short score;

} ScenePlay;

typedef struct TagSceneMenu {
    Game* parent;
    PopupMenu* menu;

    bool background_music_playing;
} SceneMenu;

#endif //SNAKE_GAME_GAME_SCENES_DEFINITIONS_H
