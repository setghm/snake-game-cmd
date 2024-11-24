#ifndef SNAKE_GAME_UI_DEFINITIONS_H
#define SNAKE_GAME_UI_DEFINITIONS_H

/* Menu GUI definitions */

typedef enum TagMenuMove {
    OPTION_FORWARD, OPTION_BACKWARD
} MenuMove;

typedef struct TagOption {
    struct TagOption* next;
    struct TagOption* prev;
    //wchar_t *content;
    //int string_id;
    String* string;
    unsigned int id;
} Option;

typedef struct TagMenuOptions {
    unsigned int len;
    unsigned int ch_size;
    unsigned int selected;
    Option *first;
    Option *last;
} MenuOptions;

typedef struct TagPopupMenu {
    Vec2 position;
    Vec2 limits;

    //wchar_t *label;
    //int title_string_id;
    String* title;
    MenuOptions* options;

    struct {
        unsigned int cols;
        unsigned int rows;
    } size;
} PopupMenu;

typedef struct TagMenuBar {
    unsigned short color;
    struct {
        wchar_t *left;
        wchar_t *right;
    } text;
} MenuBar;

#endif //SNAKE_GAME_UI_DEFINITIONS_H
