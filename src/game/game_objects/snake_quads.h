#ifndef __SNAKE_QUADS_H__
#define __SNAKE_QUADS_H__

#include "../types/types.h"

QuadList* NewQuadList(void);
Quad* NewQuad(Vec2* position, Dir direction);

void QuadListDestroy(QuadList* list);
void QuadDestroy(Quad* quad);

void PushQuad(QuadList* list, Quad* quad);

#endif//__SNAKE_QUADS_H__
/*
 *	End Of File
 */