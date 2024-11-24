#ifndef SNAKE_GAME_MENU_OPTION_H
#define SNAKE_GAME_MENU_OPTION_H

#include <console.h>
#include "../types/types.h"

//Option* Menu_OptionNew(wchar_t* content, unsigned int id);
//Option* Menu_OptionNew(int string_id, unsigned int id);
Option* Menu_OptionNew(String* string, unsigned int id);
void Menu_OptionFree(Option* option);


#endif //SNAKE_GAME_MENU_OPTION_H
