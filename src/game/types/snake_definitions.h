#ifndef SNAKE_GAME_SNAKE_DEFINITIONS_H
#define SNAKE_GAME_SNAKE_DEFINITIONS_H

/* Snake List Definitions */

typedef enum TagDir {
    UP, DOWN, LEFT, RIGHT
} Dir;

typedef enum TagQuadPart {
    HEAD, BODY, TAIL
} QuadPart;

typedef struct TagQuad {
    struct TagQuad* next;
    struct TagQuad* prev;

    QuadPart part;
    Vec2 position;
    Dir direction;

} Quad;

typedef struct TagQuadList {
    Quad *head;
    Quad *tail;
} QuadList;

#endif //SNAKE_GAME_SNAKE_DEFINITIONS_H
