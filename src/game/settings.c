#include "settings.h"
#include "ui/ui.h"
#include <strings.h>
#include <core.h>

Settings *SettingsCreate(Game *parent) {
    STRUCT_CREATE(Settings, config);

    config->parent = parent;

    // Load the saved configuration if exists.
    if (!Storage_GetSettings(&config->sound, &config->language)) {
        // Set the default settings.
        config->language = GAME_LANG_EN;
        config->sound = true;
    }

    /* Create the main settings options menu. */
    MenuOptions* options = Menu_OptionsCreate(parent, true, 3, IDS_SETTINGS_LANG, IDS_SETTINGS_SOUND, IDS_OK);
    config->menu = Menu_PopupCreate(parent, IDS_SETTINGS, true, parent->screen_size);
    Menu_PopupSetOptions(config->menu, options);

    /* Create the languages' menu. */
    MenuOptions* languages_options = Menu_OptionsCreate(
        parent, false, 11,
        IDS_LANGUAGE, IDS_AF_LANGUAGE, IDS_AR_LANGUAGE, IDS_ZH_LANGUAGE, IDS_FR_LANGUAGE, IDS_JA_LANGUAGE,
        IDS_KO_LANGUAGE, IDS_PT_LANGUAGE, IDS_RU_LANGUAGE, IDS_ES_LANGUAGE, IDS_TR_LANGUAGE);
    config->languages_menu = Menu_PopupCreate(parent, IDS_LANG_SELECT, true, parent->screen_size);
    Menu_PopupSetOptions(config->languages_menu, languages_options);

    // Create the sound config menu.
    MenuOptions* sound_options = Menu_OptionsCreate(parent, true, 2, IDS_ENABLE, IDS_DISABLE);
    config->sound_menu = Menu_PopupCreate(parent, IDS_SETTINGS_SOUND, true, parent->screen_size);
    Menu_PopupSetOptions(config->sound_menu, sound_options);

    return config;
}

void SettingsShow(Settings *config) {
    if (config->parent->active_scene == SCENE_PLAY) {
        config->menu->limits = config->parent->gameplay->canvas_size;
    } else {
        config->menu->limits = config->parent->screen_size;
    }

    config->parent->show_config = true;
}

void SettingsInput(Settings *config) {
    if (KEY_PRESSED(VK_RETURN)) {
        // Handle the options of the languages menu.
        if (config->show_languages_menu) {
            // Change the game language.
            config->language = (Language)config->languages_menu->options->selected;

            // Save the current configuration.
            Storage_SaveSettings(config->sound, config->language);

            // Return to the settings menu.
            config->show_languages_menu = false;
        }
        // Handle the options of the sound menu.
        else if (config->show_sound_menu) {
            // Enable/disable game sound.
            config->sound = config->sound_menu->options->selected == 0;

            // Save the current configuration.
            Storage_SaveSettings(config->sound, config->language);

            // Return to the settings menu.
            config->show_sound_menu = false;
        }
        // Handle the options of the menu.
        else {
            switch (config->menu->options->selected) {
                // Option language selected.
                case 0:
                    config->show_languages_menu = true;
                    break;
                // Option sound selected.
                case 1:
                    config->show_sound_menu = true;
                    break;
                // Option exit selected.
                case 2:
                    config->parent->show_config = false;
                    break;
            }
        }
    }
}

void SettingsUpdate(Settings *config) {
    if (config->show_languages_menu) {
        Menu_PopupUpdate(config->languages_menu);
        Menu_PopupDraw(config->languages_menu, config->parent->console);
    } else if (config->show_sound_menu) {
        Menu_PopupUpdate(config->sound_menu);
        Menu_PopupDraw(config->sound_menu, config->parent->console);
    } else {
        // First update, then draw.
        Menu_PopupUpdate(config->menu);
        Menu_PopupDraw(config->menu, config->parent->console);
    }
}

void SettingsDestroy(Settings *config) {
    Menu_PopupDestroy(config->languages_menu);
    Menu_PopupDestroy(config->sound_menu);
    Menu_PopupDestroy(config->menu);
    free(config);
}
