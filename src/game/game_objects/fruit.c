#include "fruit.h"
#include <time.h>

Fruit* FruitCreate(Game* parent, Vec2 limits) {
    STRUCT_CREATE(Fruit, fruit);
	
	fruit->parent = parent;
	fruit->limits = limits;
	
	srand(time(NULL));
	
	FruitRandom(fruit);
}

void FruitDestroy(Fruit* fruit) {
	if (fruit == NULL) return;
	free(fruit);
	fruit = NULL;
}

void FruitDraw(Fruit* fruit, Console* screen) {
	int color;
	wchar_t *content = L"  ";
	
	switch (fruit->kind) {
		case APPLE:		color = 0xc0; break;
		case BLUEBERRY:	color = 0x90; break;
		case PINEAPPLE:	color = 0xe0; break;
		case GRAPE:		color = 0x50; break;
	}
	
	DrawString(
		screen,
		(COORD) {
			fruit->position.x,
			fruit->position.y
		},
		content,
		color
	);
}

void FruitRandom(Fruit* fruit) {
	
	do {
		fruit->position.x = rand() % fruit->limits.x;
	} while (fruit->position.x % 2 != 0);
	
	if (fruit->position.x == fruit->limits.x - 2) {
		fruit->position.x -= 2;
	}
	else if (fruit->position.x == 0) {
		fruit->position.x = 2;
	}
	
	fruit->position.y = rand() % fruit->limits.y;
	if (fruit->position.y == fruit->limits.y - 1) {
		fruit->position.y -= 1;
	}
	else if (fruit->position.y == 0) {
		fruit->position.y = 1;
	}
	
	fruit->kind = rand() % 4;
}

/*
 *	End Of File
 */