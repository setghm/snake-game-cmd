#ifndef __GAME_H__
#define __GAME_H__

#include "types/types.h"

Game* GameCreate(char* name);
void GameCleanup(Game* game);
void GameUpdate(Game* game);

#endif
/*
 *	End Of File
 */