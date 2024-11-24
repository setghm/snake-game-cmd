#include "menu_popup.h"
#include "string.h"

/*
 *  Popup Menu function definitions
 * */

PopupMenu* Menu_PopupCreate(Game* parent, int title_string_id, bool title_translatable, Vec2 limits) {
    STRUCT_CREATE(PopupMenu, menu);

    // Create the title.
    menu->title = String_New(parent, title_string_id);
    menu->title->_translatable = title_translatable;

    // Set the limits.
    menu->limits = limits;

    return menu;
}

void Menu_PopupSetOptions(PopupMenu* menu, MenuOptions* options) {
    menu->options = options;

    // Make size calculation to center the menu in the screen.
    menu->size.rows = options->len + 2;

    if (menu->size.cols < options->ch_size) {
        menu->size.cols = options->ch_size;
    }

    menu->position.x = (menu->limits.x / 2) - (menu->size.cols / 2) - 2;
    menu->position.y = (menu->limits.y / 2) - (menu->size.rows / 2);
}

void Menu_PopupSetTitle(PopupMenu* menu, int title_string_id) {
    // Free the previous string.
    menu->title->string_id = title_string_id;
}

void Menu_PopupDestroy(PopupMenu* menu) {
    if (menu->options) {
        Menu_OptionsDestroy(menu->options);
    }
    //free(menu->label);
    String_Destroy(menu->title);
    free(menu);
    menu = NULL;
}

void Menu_PopupDraw(PopupMenu* menu, Console* screen) {
    Vec2 pos = menu->position;

    int title_length = menu->title->length;
    int title_padding = (int) truncf((float)(menu->size.cols - title_length) / 2) + 2;
    int row_size = (int)menu->size.cols + 4;

    DisplayPadding(screen, &pos, title_padding);

    menu->title->color = 0x0F;
    menu->title->position = pos;
    String_Draw(menu->title, screen);

    pos.x += title_length;
    DisplayPadding(screen, &pos, title_padding);

    pos.y++;
    pos.x = menu->position.x;
    DisplayPadding(screen, &pos, row_size);

    pos.y++;
    pos.x = menu->position.x;
    Menu_OptionsDraw(menu->options, screen, pos, 0x00);
}

void Menu_PopupUpdate(PopupMenu* menu) {
    if (KEY_PRESSED(VK_UP)) {
        Menu_OptionsChange(menu->options, OPTION_BACKWARD);
    } else if (KEY_PRESSED(VK_DOWN)) {
        Menu_OptionsChange(menu->options, OPTION_FORWARD);
    }
}

