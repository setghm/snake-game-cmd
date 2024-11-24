#ifndef SNAKE_GAME_SETTINGS_H
#define SNAKE_GAME_SETTINGS_H

#include "types/types.h"

Settings *SettingsCreate(Game *parent);
void SettingsShow(Settings *config);
void SettingsInput(Settings *config);
void SettingsUpdate(Settings *config);
void SettingsDestroy(Settings *config);

#endif //SNAKE_GAME_SETTINGS_H
/*
 *  End Of File
 */
