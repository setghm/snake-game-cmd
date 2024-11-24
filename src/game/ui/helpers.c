#include "helpers.h"

void DisplayPadding(Console* screen, Vec2 *pos, int len) {
    for (int i=0; i<len; i++) {
        DrawChar(screen, (COORD) {(short)pos->x, (short)pos->y}, L' ', 0x00);
        pos->x++;
    }
}
