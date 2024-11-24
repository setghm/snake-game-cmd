#ifndef SNAKE_GAME_MENU_OPTIONS_H
#define SNAKE_GAME_MENU_OPTIONS_H

#include <core.h>
#include "../types/types.h"
#include <stdarg.h>
#include "menu_option.h"
#include "helpers.h"

/* Menu Options */

/// Create a new menu options object.
/// @param count Number of strings passed
MenuOptions* Menu_OptionsCreate(Game* parent, bool translatable, int count, ...);

/// Delete a created menu options object
void Menu_OptionsDestroy(MenuOptions* menu);

void Menu_OptionsChange(MenuOptions* menu, MenuMove movement);
void Menu_OptionsDraw(MenuOptions* menu, Console* screen, Vec2 pos, unsigned short bgColor);


#endif //SNAKE_GAME_MENU_OPTIONS_H
