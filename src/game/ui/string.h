#ifndef SNAKE_GAME_STRING_H
#define SNAKE_GAME_STRING_H

#include "../types/types.h"
#include <core.h>

String* String_New(Game* parent, int string_id);
String* String_NewTranslatable(Game* parent, int string_id);
void String_Draw(String* string, Console* screen);
void String_Destroy(String* string);

#endif //SNAKE_GAME_STRING_H
