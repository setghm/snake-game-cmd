#include "snake.h"
#include "snake_quads.h"
#include <stdio.h>
#include <wchar.h>

Snake* SnakeCreate(Game* parent, unsigned int len, Vec2 pos) {
	STRUCT_CREATE(Snake, snake);
	
	snake->parent = parent;
	
	snake->color.live = 0xa0;
	snake->color.dead = 0x4f;
	
	snake->initial.position = pos;
	snake->initial.direction = UP;
	snake->initial.length = len;
	
	SnakeRestart(snake);
	
	return snake;
}

void SnakeDestroy(Snake* snake) {
	QuadListDestroy(snake->body);
	free(snake);
	snake = NULL;
}

void SnakeRestart(Snake* snake) {
	if (snake->body) {
		QuadListDestroy(snake->body);
	}
    snake->body = NewQuadList();
	
	for (int i=0; i < snake->initial.length; i++) {
		SnakeGrow(snake);
	}
	
	snake->state = SNAKE_LIVE;
}

void SnakeDraw(Snake* snake, Console* screen) {
	Quad* quad = snake->body->head;
	int drawColor = (snake->state == SNAKE_LIVE) ?
		snake->color.live:
		snake->color.dead;
	
	while (quad) {
		
		wchar_t *content = L"  ";
		
		if (quad->part == HEAD) {
			switch (quad->direction) {
				case UP:	content = L"˙˙"; break;
				case DOWN:	content = L".."; break;
				case LEFT:	content = L": "; break;
				case RIGHT:	content = L" :"; break;
			}
		}
		
		DrawString(
			screen,
			(COORD) {
				quad->position.x,
				quad->position.y},
			content,
			drawColor
		);
		
		quad = quad->next;
	}
	
}

void SnakeUpdate(Snake* snake, Time* time) {
	if (snake->state == SNAKE_DEATH) return;
	
	/* Update Positions */
	Quad* quad = snake->body->tail;
	
	while (quad) {
		
		if (quad->part == HEAD) {
			switch (quad->direction) {
				case UP:	quad->position.y -= 1; break;
				case DOWN:	quad->position.y += 1; break;
				case LEFT:	quad->position.x -= 2; break;
				case RIGHT:	quad->position.x += 2; break;
			}
		} else {
			quad->position = quad->prev->position;
		}
		
		quad = quad->prev;
	}
	
}

void SnakeKeyEvent(Snake* snake, Dir direction) {
    if (snake->state == SNAKE_DEATH) return;

	Dir headDir = snake->body->head->direction;
	
	switch (direction) {
		case UP: if (headDir == DOWN) return; break;
		case DOWN: if (headDir == UP) return; break;
		case LEFT: if (headDir == RIGHT) return; break;
		case RIGHT: if (headDir == LEFT) return; break;
	}
	
	snake->body->head->direction = direction;
}

void SnakeGrow(Snake* snake) {
	
	if (snake->body->tail == NULL) {
		// If there aren't any quads added to body yet
		
		Quad* quad = NewQuad(&snake->initial.position,
			snake->initial.direction);
		
		PushQuad(snake->body, quad);
	}
	else {
		// If there are one or more quads added already
		
		Dir direction = snake->body->tail->direction;
		Vec2 position = snake->body->tail->position;
		
		Quad* quad = NewQuad(&position, direction);
		PushQuad(snake->body, quad);
	}
	
}

void SnakeDie(Snake* snake) {
	snake->state = SNAKE_DEATH;
}

/* Collision Detection Functions */

#define EQUAL_V2(a, b) (a.x == b.x) && (a.y == b.y)
#define RANGE_V2(v, l, u) ((v.x > l.x) && (v.x < u.x)) && ((v.y > l.y) && (v.y < u.y))

bool SnakeFruitCollision(Snake* snake, Fruit* fruit) {
	return EQUAL_V2(snake->body->head->position, fruit->position);
}

bool SnakeSelfCollide(Snake* snake) {
	Quad* quad = snake->body->head;
	Vec2 headPos = quad->position;
	
	while (quad) {
		if (quad->part != HEAD) {
			if (EQUAL_V2(quad->position, headPos)) {
				return true;
			}
		}
		quad = quad->next;
	}
	
	return false;
}

bool SnakeOutOfBounds(Snake* snake, Vec2 limits) {
	Vec2 headPos = snake->body->head->position;
	Vec2 zero = {0, 0};
	
	limits.x -= 2;
	limits.y -= 1;
	
	if (RANGE_V2(headPos, zero, limits)) {
		return false;
	}
	
	return true;
}

bool SnakeDeadlyCollisions(Snake* snake, Vec2 limits) {
    return SnakeSelfCollide(snake) || SnakeOutOfBounds(snake, limits);
}

bool SnakeBodyCollision(Snake* snake, Vec2 pos) {
	Quad* quad = snake->body->head;
	
	while (quad) {
		if (EQUAL_V2(quad->position, pos)) {
			return true;
		}
		quad = quad->next;
	}
	
	return false;
}

/*
 *	End Of File
 */