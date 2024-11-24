#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "../types/types.h"

Snake* SnakeCreate(Game* game, unsigned int len, Vec2 pos);
void SnakeDestroy(Snake* snake);
void SnakeRestart(Snake* snake);

void SnakeDraw(Snake* snake, Console* screen);
void SnakeUpdate(Snake* snake, Time* time);
void SnakeKeyEvent(Snake* snake, Dir direction);

void SnakeGrow(Snake* snake);
void SnakeDie(Snake* snake);

bool SnakeFruitCollision(Snake* snake, Fruit* fruit);
bool SnakeBodyCollision(Snake* snake, Vec2 pos);
bool SnakeDeadlyCollisions(Snake* snake, Vec2 limits);

#endif//__SNAKE_H__
/*
 *	End Of File
 */