#include "game.h"
#include "scenes/scenes.h"
#include "settings.h"
#include <resource.h>
#include <core.h>

Vec2 canvas = {72, 23};

void GameInput(Game* game);

Game* GameCreate(char* name) {
	STRUCT_CREATE(Game, game);
	if (!game) return NULL;
	
	/* Screen Initialization */
	game->screen_size = canvas;

	game->console = CreateConsole((COORD){(short)canvas.x, (short)canvas.y});
	SetConsoleTitle(name);
	ConsoleClearColor(game->console, 0x00);
	if (!game->console) return NULL;

    // Show the game screen
    ConsoleShow(game->console);

    /* Settings creation. */
    game->config = SettingsCreate(game);

	/* Game Scenes Creation */
    game->mainmenu = SceneMenuCreate(game);
    game->gameplay = ScenePlayCreate(game, (Vec2) {canvas.x, canvas.y - 1});
	game->active_scene = SCENE_MENU;

	/* Game Time Initialization and Run */
	game->time = InitTime(0.20f);
	game->running = true;

	return game;
}

void GameCleanup(Game* game) {
	if (!game) return;
	
	ScenePlayDestroy(game->gameplay);
	SceneMenuDestroy(game->mainmenu);
    SettingsDestroy(game->config);

	ConsoleCleanup(game->console);
	free(game);
	
	game = NULL;
}

void GameInput(Game* game) {
    // Check if the settings are showing and only handle its input events.
    // Handling only this input events avoids controlling the other scenes accidentally.
    if (game->show_config) {
        SettingsInput(game->config);
    } else {
        switch (game->active_scene) {
            case SCENE_MENU:
                SceneMenuInput(game->mainmenu);
                break;
            case SCENE_PLAY:
                ScenePlayInput(game->gameplay);
                break;
        }
    }

}

void GameUpdate(Game* game) {
    UpdateTime(game->time);
    GameInput(game);

    if (!game->time->waiting) {
        ClearScreen(game->console);

        switch (game->active_scene) {
            case SCENE_MENU:
                SceneMenuUpdate(game->mainmenu);
                break;
            case SCENE_PLAY:
                ScenePlayUpdate(game->gameplay);
                break;
        }

        // Draw last to always be at the top of everything.
        if (game->show_config) {
            SettingsUpdate(game->config);
        }

        PresentScreen(game->console);
    }
}

/*
 *	End Of File
 */