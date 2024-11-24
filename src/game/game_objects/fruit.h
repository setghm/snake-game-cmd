#ifndef __FRUIT_H__
#define __FRUIT_H__

#include "../types/types.h"

Fruit* FruitCreate(Game* parent, Vec2 limits);
void FruitDestroy(Fruit* fruit);

void FruitDraw(Fruit* fruit, Console* screen);
void FruitRandom(Fruit* fruit);

#endif
/*
 *	End Of File
 */