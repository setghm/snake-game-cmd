#include "scenes.h"
#include "../game_objects/game_objects.h"
#include "../settings.h"
#include "../ui/ui.h"
#include <strings.h>

// Internal functions.
void RestartGameSound(ScenePlay* scene) {
    if (scene->parent->config->sound) {
        PlaySound(MAKEINTRESOURCE(SOUND_START), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
    }
}

void RestartFruit(ScenePlay* scene) {
	do {
		FruitRandom(scene->target);
	} while (
		SnakeBodyCollision(scene->player, scene->target->position)
	);
}

void UpdateBottomBarByFruit(ScenePlay* scene) {
	wchar_t right_text[100] = { 0 }, left_text[100] = { 0 }, fruit_str[50] = { 0 };

    // Load a message string randomly.
    bool load_msg_1 = ((int)rand() % 10) >= 5;
    wchar_t msg_str[50] = { 0 };

    Strings_Load(load_msg_1 ? IDS_FRUIT_MSG_1 : IDS_FRUIT_MSG_2,
                 scene->parent->config->language,
                 msg_str, 50);

    // Load score string from resources.
    wchar_t score_str[50] = { 0 };
    Strings_Load(IDS_SCORE, scene->parent->config->language, score_str, 50);

    swprintf(right_text, 99, L"%ls: %d", score_str, scene->score);

	switch (scene->target->kind) {
		case APPLE:
            Strings_Load(IDS_FRUIT_1, scene->parent->config->language, fruit_str, 50);
			scene->bar->color = 0xcF;
			break;
		case BLUEBERRY:
            Strings_Load(IDS_FRUIT_2, scene->parent->config->language, fruit_str, 50);
			scene->bar->color = 0x9F;
			break;
		case PINEAPPLE:
            Strings_Load(IDS_FRUIT_3, scene->parent->config->language, fruit_str, 50);
			scene->bar->color = 0xe0;
			break;
		case GRAPE:
            Strings_Load(IDS_FRUIT_4, scene->parent->config->language, fruit_str, 50);
			scene->bar->color = 0x5F;
			break;
	}
    swprintf_s(left_text, 99, L"%ls %ls!", msg_str, fruit_str);

	Menu_BarSetLeftText(scene->bar, left_text);
	Menu_BarSetRightText(scene->bar, right_text);
}

void UpdateBottomBarByGameOver(ScenePlay* scene) {
    // Load strings from resources.
    wchar_t play_again_str[50] = { 0 };
    wchar_t last_score_str[50] = { 0 };
    Strings_Load(IDS_PLAY_AGAIN, scene->parent->config->language, play_again_str, 50);
    Strings_Load(IDS_LAST_SCORE, scene->parent->config->language, last_score_str, 50);

    Menu_PopupSetTitle(scene->menu, IDS_GAMEOVER);

    scene->bar->color = 0xF0;
    Menu_BarSetLeftText(scene->bar, play_again_str);

    wchar_t rightText[100] = { 0 };
    swprintf(rightText, 99, L"%ls: %u", last_score_str, scene->score);
    Menu_BarSetRightText(scene->bar, rightText);
}

ScenePlay* ScenePlayCreate(Game* parent, Vec2 drawableZone) {
    STRUCT_CREATE(ScenePlay, scene);
    scene->parent = parent;
    scene->canvas_size = drawableZone;
    ScenePlayInit(scene);
    return scene;
}

void ScenePlayDestroy(ScenePlay* scene) {
	SnakeDestroy(scene->player);
	FruitDestroy(scene->target);
	Menu_PopupDestroy(scene->menu);
	Menu_BarDestroy(scene->bar);
	free(scene);
	scene = NULL;
}

void ScenePlayInit(ScenePlay* scene) {
	scene->player = SnakeCreate(scene->parent, 5, (Vec2){10, 10});
	scene->target = FruitCreate(scene->parent, scene->canvas_size);

    // Create the options menu.
    MenuOptions* options = Menu_OptionsCreate(scene->parent, true, 3, IDS_PLAY, IDS_SETTINGS, IDS_LEAVE_GAME);
    scene->menu = Menu_PopupCreate(scene->parent, IDS_SETTINGS, true, scene->canvas_size);
	Menu_PopupSetOptions(scene->menu, options);
	
	scene->bar = Menu_BarCreate(scene->parent);
	
	ScenePlayNewGame(scene);
}

void ScenePlayNewGame(ScenePlay* scene) {
	RestartFruit(scene);
	SnakeRestart(scene->player);

    // Load span string randomly.
    int span_string_id = IDS_SPAN_1 + (rand() % 3);

    wchar_t span_str[50] = { 0 };
    Strings_Load(span_string_id, scene->parent->config->language, span_str, 50);
    Menu_PopupSetTitle(scene->menu, IDS_PAUSE);
	
	scene->bar->color = 0xF0;
	Menu_BarSetLeftText(scene->bar, span_str);
	
	scene->score = 0;
	scene->state = PLAY_STATE_PLAYING;
}

void ScenePlayUpdate(ScenePlay* scene) {
	Time* time = scene->parent->time;

	switch (scene->state) {
        case PLAY_STATE_PLAYING: {
            // Update the snake.
            SnakeUpdate(scene->player, time);
            // Check if the player is dead.
            if (SnakeDeadlyCollisions(scene->player, scene->canvas_size)) {
                // Play the game over sound effect.
                if (scene->parent->config->sound) {
                    PlaySound(MAKEINTRESOURCE(SOUND_GAME_OVER_1), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
                }

                SnakeDie(scene->player);
                scene->state = PLAY_STATE_END;
                UpdateBottomBarByGameOver(scene);
                break;
            }
            // Check if the snake just collide with a fruit.
            if (SnakeFruitCollision(scene->player, scene->target)) {
                if (scene->parent->config->sound) {
                    PlaySound(MAKEINTRESOURCE(SOUND_POWER_UP), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
                }

                SnakeGrow(scene->player);
				scene->score++;
                UpdateBottomBarByFruit(scene);
                RestartFruit(scene);
                break;
            }
        }
        default: {
            // Update the options menu if the settings menu is not showing.
            if (!scene->parent->show_config) {
                Menu_PopupUpdate(scene->menu);
            }
        }
	}

	FruitDraw(scene->target, scene->parent->console);
	SnakeDraw(scene->player, scene->parent->console);
	
	Menu_BarDraw(
        scene->bar,
        scene->parent->console,
        (Vec2) {0, scene->parent->screen_size.y - 1},
        scene->parent->screen_size.x
    );

    // Draw the options menu if the settings menu is not showing.
	if (scene->state != PLAY_STATE_PLAYING && !scene->parent->show_config) {
        Menu_PopupDraw(scene->menu, scene->parent->console);
    }
}

void ScenePlayInput(ScenePlay* scene) {
    if (scene->state == PLAY_STATE_PLAYING) {
        // Handle the movements of the player.
        if (KEY_PRESSED(VK_UP))
            SnakeKeyEvent(scene->player, UP);
        if (KEY_PRESSED(VK_DOWN))
            SnakeKeyEvent(scene->player, DOWN);
        if (KEY_PRESSED(VK_LEFT))
            SnakeKeyEvent(scene->player, LEFT);
        if (KEY_PRESSED(VK_RIGHT))
            SnakeKeyEvent(scene->player, RIGHT);
    }

    if (KEY_PRESSED(VK_ESCAPE)) {
        if (scene->state == PLAY_STATE_PLAYING)
			scene->state = PLAY_STATE_PAUSED;
    }
	
	if (KEY_PRESSED(VK_RETURN)) {
        // Handle the input events of the pause/(game over) menu.
		if (scene->state != PLAY_STATE_PLAYING) {
            switch (scene->menu->options->selected) {
                // Option play was pressed.
                case 0:
                    switch (scene->state) {
                        case PLAY_STATE_PLAYING:
                            // Selecting the option "Play" while playing :/
                            // This case shouldn't be reached.
                            break;
                        case PLAY_STATE_PAUSED:
                            scene->state = PLAY_STATE_PLAYING;
                            break;
                        case PLAY_STATE_END:
                            RestartGameSound(scene);
                            ScenePlayNewGame(scene);
                            break;
                    }
                    break;
                // Option settings was pressed.
                case 1:
                    SettingsShow(scene->parent->config);
                    break;
                // Option exit was pressed.
                case 2:
                    scene->parent->running = false;
                    break;
            }
		}
	}
}

/*
 *	End Of File
 */