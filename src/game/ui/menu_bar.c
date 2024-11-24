#include "menu_bar.h"
#include "string.h"

/*
 *  Menu Bar function definitions
 * */

MenuBar *Menu_BarCreate(Game *parent) {
    STRUCT_CREATE(MenuBar, menu);
    return menu;
}

void Menu_BarSetLeftText(MenuBar* menu, wchar_t* text) {
    if (menu->text.left) {
        free(menu->text.left);
    }

    menu->text.left = wcsdup(text);
}

void Menu_BarSetRightText(MenuBar* menu, wchar_t* text) {
    if (menu->text.right) {
        free(menu->text.right);
    }
    menu->text.right = wcsdup(text);
}

void Menu_BarDestroy(MenuBar* menu) {
    if (menu->text.left) {
        free(menu->text.left);
    }
    if (menu->text.right) {
        free(menu->text.right);
    }

    free(menu->text.left);
    free(menu->text.right);

    free(menu);
    menu = NULL;
}

void Menu_BarDraw(MenuBar* menu, Console* screen, Vec2 pos, unsigned int cols) {

    for (int i=0; i<cols; i++) {
        DrawChar(screen, (COORD) {(short)(pos.x + i), (short)pos.y}, L' ', menu->color);
    }

    if (menu->text.left) {
        DrawString(screen, (COORD){1, pos.y}, menu->text.left, menu->color);
    }
    if (menu->text.right) {
        unsigned int rightX = cols - wcslen(menu->text.right) - 1;
        DrawString(screen, (COORD){rightX, pos.y}, menu->text.right, menu->color);
    }
}

/*
 *  End Of File
 * */