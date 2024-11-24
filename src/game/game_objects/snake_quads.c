#include "snake_quads.h"
#include <stdlib.h>
#include <string.h>

QuadList* NewQuadList(void) {
	QuadList* list = (QuadList*) malloc(sizeof(QuadList));
	memset(list, 0, sizeof(QuadList));
	return list;
}

Quad* NewQuad(Vec2* position, Dir direction) {
	Quad* quad = (Quad*) malloc(sizeof(Quad));
	memset(quad, 0, sizeof(Quad));
	
	quad->position.x = position->x;
	quad->position.y = position->y;
	quad->direction = direction;
	quad->part = BODY;
	
	return quad;
}

void QuadListDestroy(QuadList* list) {
	QuadDestroy(list->head);
	free(list);
	list = NULL;
}

void QuadDestroy(Quad* quad) {
	if (quad->next) {
		QuadDestroy(quad->next);
	}
	free(quad);
	quad = NULL;
}

void PushQuad(QuadList* list, Quad* quad) {
	if (!list->head) {
		list->head = quad;
		quad->part = HEAD;
	}
	if (list->tail) {
		list->tail->next = quad;
		quad->prev = list->tail;
		if (list->tail->part == TAIL)
			list->tail->part = BODY;
	}
	
	if (quad->part == BODY)
		quad->part = TAIL;
	
	list->tail = quad;
}

/*
 *	End Of File
 */