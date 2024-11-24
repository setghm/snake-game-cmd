#ifndef SNAKE_GAME_MENU_POPUP_H
#define SNAKE_GAME_MENU_POPUP_H

#include <core.h>
#include "../types/types.h"
#include "helpers.h"
#include "menu_options.h"
#include <math.h>

/* Popup Menu */

PopupMenu* Menu_PopupCreate(Game *parent, int title_string_id, bool title_translatable, Vec2 limits);
void Menu_PopupDestroy(PopupMenu* menu);

void Menu_PopupSetOptions(PopupMenu* menu, MenuOptions* options);
void Menu_PopupSetTitle(PopupMenu* menu, int title_string_id);

void Menu_PopupDraw(PopupMenu* menu, Console* screen);
void Menu_PopupUpdate(PopupMenu* menu);

#endif //SNAKE_GAME_MENU_POPUP_H
