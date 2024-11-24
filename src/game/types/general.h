#ifndef SNAKE_GAME_GENERAL_H
#define SNAKE_GAME_GENERAL_H

#include "../../core/console.h"
#include "../../core/timer.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define STRUCT_CREATE(type, name) \
	type* name = (type*) malloc(sizeof(type)); \
	memset(name, 0, sizeof(type))

#define KEY_PRESSED(k) GetAsyncKeyState(k) & 0x01
#define V2COORD(v) ((COORD) {v.x, v.y})

typedef struct TagGame Game;

/* Utility definitions */

typedef struct TagVec2 {
    unsigned int x;
    unsigned int y;
} Vec2;

typedef enum TagLanguage {
    GAME_LANG_EN,
    GAME_LANG_AF,
    GAME_LANG_AR,
    GAME_LANG_ZH,
    GAME_LANG_FR,
    GAME_LANG_JA,
    GAME_LANG_KO,
    GAME_LANG_PT,
    GAME_LANG_RU,
    GAME_LANG_ES,
    GAME_LANG_TR,
} Language;

// String type definition.
typedef struct tagString {
    // Public properties.
    int string_id;
    int length;

    // Internal properties.
    Game* _parent;
    int _last_string_id;
    Language _last_language;
    bool _translatable;
    wchar_t *_buffer;

    // Display properties.
    unsigned short int color;
    Vec2 position;
} String;

#endif //SNAKE_GAME_GENERAL_H
