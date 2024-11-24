#ifndef SNAKE_GAME_SETTINGS_DEFINITIONS_H
#define SNAKE_GAME_SETTINGS_DEFINITIONS_H

/* Settings definitions */

typedef struct TagSettings {
    Game *parent;

    // Menus.
    PopupMenu *menu;
    PopupMenu *languages_menu;
    PopupMenu *sound_menu;

    // Menus flags.
    bool show_languages_menu;
    bool show_sound_menu;

    // Stores the possible configurations
    Language language;
    bool sound;
} Settings;

#endif //SNAKE_GAME_SETTINGS_DEFINITIONS_H
