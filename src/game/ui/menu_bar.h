#ifndef SNAKE_GAME_MENU_BAR_H
#define SNAKE_GAME_MENU_BAR_H

#include <console.h>
#include "../types/types.h"

/* Menu Bar */

MenuBar *Menu_BarCreate(Game *parent);
void Menu_BarDestroy(MenuBar* menu);

void Menu_BarSetLeftText(MenuBar* menu, wchar_t* text);
void Menu_BarSetRightText(MenuBar* menu, wchar_t* text);

void Menu_BarDraw(MenuBar* menu, Console* screen, Vec2 pos, unsigned int cols);

#endif //SNAKE_GAME_MENU_BAR_H
