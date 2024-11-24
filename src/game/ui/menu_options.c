#include "menu_options.h"
#include "string.h"

// Internal functions.
void Menu_OptionsPush(MenuOptions* menu, Option* option);
//Option* Menu_OptionsGet(MenuOptions* menu, unsigned int target_id);

/*
 *  Menu Options function definitions
 * */

/// @param count The number of elements specified in the variable arguments, be careful, this can raise in an exception.
MenuOptions* Menu_OptionsCreate(Game* parent, bool translatable, int count, ...) {
    STRUCT_CREATE(MenuOptions, menu);

    menu->len = count;
    menu->selected = 0;

    // Start the iteration over the variable arguments.
    va_list content_list;
    va_start(content_list, count);
    int string_id = 0;

    for (int i=0; i < menu->len; i++) {
        string_id = va_arg(content_list, int);

        String* string = String_New(parent, string_id);
        string->_translatable = translatable;

        Option* option = Menu_OptionNew(string, i);
        Menu_OptionsPush(menu, option);
    }

    va_end(content_list);
    return menu;
}

void Menu_OptionsPush(MenuOptions* menu, Option* option) {
    if (menu->first == NULL) {
        menu->first = option;
    }
    if (menu->last != NULL) {
        menu->last->next = option;
        option->prev = menu->last;
    }

    menu->last = option;
}

void Menu_OptionsDestroy(MenuOptions* menu) {
    Menu_OptionFree(menu->first);
    free(menu);
    menu = NULL;
}

void Menu_OptionsChange(MenuOptions* menu, MenuMove movement) {
    switch(movement) {
        case OPTION_BACKWARD:
            if (menu->selected == menu->first->id)
                menu->selected = menu->last->id;
            else menu->selected--;
            break;
        case OPTION_FORWARD:
            if (menu->selected == menu->last->id)
                menu->selected = menu->first->id;
            else menu->selected++;
            break;
    }
}

void Menu_OptionsDraw(MenuOptions* menu, Console* screen, Vec2 pos, unsigned short bgColor) {
    int padding, string_length, color;
    Option* option = menu->first;

    while (option) {
        Vec2 position = {pos.x, pos.y};
        string_length = option->string->length;

        padding = (int)((menu->ch_size - string_length) / 2);

        if (option->id == menu->selected) {
            color = bgColor | 0x0E;

            DrawChar(screen, V2COORD(position), L'[', color);
            position.x++;

            option->string->color = color;
            option->string->position = position;
            String_Draw(option->string, screen);
            position.x += string_length;

            DrawChar(screen, V2COORD(position), L']', color);
        }
        else {
            color = bgColor | 0x07;

            option->string->color = color;
            option->string->position = position;
            String_Draw(option->string, screen);
            position.x += string_length;
        }

        pos.y++;
        option = option->next;
    }

}
