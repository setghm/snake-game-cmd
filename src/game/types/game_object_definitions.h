#ifndef SNAKE_GAME_GAME_OBJECT_DEFINITIONS_H
#define SNAKE_GAME_GAME_OBJECT_DEFINITIONS_H

/* Other game object member Definitions */

typedef enum TagFruitKind {
    APPLE, BLUEBERRY, PINEAPPLE, GRAPE
} FruitKind;

typedef enum TagSnakeState {
    SNAKE_LIVE, SNAKE_DEATH
} SnakeState;

/* Game object definitions */

typedef struct TagSnake {

    Game* parent;

    /* Stores an initial state for the player */
    struct {
        Vec2 position;
        Dir direction;
        unsigned int length;
    } initial;

    QuadList* body;

    struct {
        unsigned short live;
        unsigned short dead;
    } color;

    SnakeState state;

} Snake;

typedef struct TagFruit {
    Game* parent;
    Vec2 limits;

    Vec2 position;
    FruitKind kind;
} Fruit;

#endif //SNAKE_GAME_GAME_OBJECT_DEFINITIONS_H
