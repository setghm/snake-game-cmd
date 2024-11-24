#include "scenes.h"
#include "../ui/ui.h"
#include "../settings.h"
#include <strings.h>

CREATE_SCENE_DEFINITION(SceneMenu)

static const unsigned char background_pattern_1[4] = {0x22, 0x22, 0x00, 0x00};
static const unsigned char background_pattern_2[4] = {0x00, 0x00, 0x22, 0x22};
static int pattern_repeat_x;
static int pattern_repeat_y;

// Internal functions.
void SceneMenuStopMusic(SceneMenu* scene) {
    PlaySound(NULL, NULL, 0);
}

void SceneMenuUpdateMusic(SceneMenu* scene) {
    if (scene->background_music_playing != scene->parent->config->sound) {
        // Stop/play the background music.
        if (scene->parent->config->sound) {
            PlaySound(MAKEINTRESOURCE(MUSIC_RETRO), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
        } else {
            SceneMenuStopMusic(scene);
        }

        // Update the state of this field.
        scene->background_music_playing = scene->parent->config->sound;
    }
}

void SceneMenuStartGame(SceneMenu* scene) {
    if (scene->parent->config->sound) {
        PlaySound(MAKEINTRESOURCE(SOUND_START), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
    }
}

void SceneMenuInit(SceneMenu* scene) {
    MenuOptions *options = Menu_OptionsCreate(scene->parent, true, 3, IDS_PLAY, IDS_SETTINGS, IDS_EXIT);
	scene->menu = Menu_PopupCreate(scene->parent, IDS_APP_NAME, false, scene->parent->screen_size);
	Menu_PopupSetOptions(scene->menu, options);

    pattern_repeat_x = (int) scene->parent->console->cr_size.X;
    pattern_repeat_y = scene->parent->console->cr_size.Y;
}

void SceneMenuDestroy(SceneMenu* scene) {
    Menu_PopupDestroy(scene->menu);
    free(scene);
    scene = NULL;
}

void SceneMenuUpdate(SceneMenu* scene) {
    // Update the background music.
    SceneMenuUpdateMusic(scene);

    /* Draw the scene background */
    for (SHORT i=0; i < pattern_repeat_y; i++) {
        DrawColorPattern(scene->parent->console,
                         (COORD) {0, i},
                         i%2==0 ? background_pattern_1 : background_pattern_2,
                         4,
                         pattern_repeat_x);
    }

    // Draw the menu itself only if the settings menu is not showing.
    if (!scene->parent->show_config) {
        Menu_PopupDraw(scene->menu, scene->parent->console);
    }
}

void SceneMenuInput(SceneMenu* scene) {
    // Handle the menu input events only if the settings menu is not showing.
    if (scene->parent->show_config) {
        return; // Exit.
    }

	Menu_PopupUpdate(scene->menu);
	
    if (KEY_PRESSED(VK_RETURN)) {
        switch (scene->menu->options->selected) {
            // Option play was pressed.
            case 0:
                SceneMenuStartGame(scene);
                scene->parent->active_scene = SCENE_PLAY;
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

/*
 *	End Of File
 */