#ifndef SNAKE_GAME_STORAGE_H
#define SNAKE_GAME_STORAGE_H

#include <stdbool.h>
#include "../game/types/types.h"

bool Storage_SaveSettings(bool enable_sound, Language language);
bool Storage_GetSettings(__out bool* enable_sound, __out Language* language);

#endif //SNAKE_GAME_STORAGE_H
