#include "menu_option.h"
#include "string.h"

//Option* Menu_OptionNew(wchar_t* content, unsigned int id) {
//Option* Menu_OptionNew(int string_id, unsigned int id) {
Option* Menu_OptionNew(String* string, unsigned int id) {
    STRUCT_CREATE(Option, option);
    option->id = id;
    //option->content = wcsdup(content);
    //option->string_id = string_id;
    option->string = string;
    return option;
}


void Menu_OptionFree(Option* option) {
    if (option->next) {
        Menu_OptionFree(option->next);
    }
    //free(option->content);
    String_Destroy(option->string);
    free(option);
    option = NULL;
}
