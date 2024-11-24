#include "string.h"

// Internal method.
void String_LoadResource(String* string);

String* String_New(Game* parent, int string_id) {
    STRUCT_CREATE(String, string);

    string->string_id = string_id;
    string->_last_string_id = string_id;
    string->_last_language = -1;
    string->_parent = parent;

    // Load the string in order to get the string length.
    String_LoadResource(string);

    return string;
}

String* String_NewTranslatable(Game* parent, int string_id) {
    String* string = String_New(parent, string_id);
    string->_translatable = true;

    return string;
}

void String_Draw(String* string, Console* screen) {
    // Check if the language was updated.
    if (string->_translatable && string->_last_language != string->_parent->config->language) {
        // Get current language id.
        // Load the current string each time the language is changed.
        String_LoadResource(string);
    }

    // Check if the string was updated.
    if (string->_last_string_id != string->string_id) {
        String_LoadResource(string);
    }

    // Draw the string.
    DrawString(screen, V2COORD(string->position), string->_buffer, string->color);
}

void String_Destroy(String* string) {
    if (string->_buffer != NULL) {
        free(string->_buffer);
        string->_buffer = NULL;
    }
    free(string);
}

// Internal methods.
void String_LoadResource(String* string) {
    // Update the string language.
    if (string->_translatable) {
        string->_last_language = string->_parent->config->language;
    }

    // Update the string resource if it was changed.
    string->_last_string_id = string->string_id;

    // Free the last _buffer.
    if (string->_buffer != NULL) {
        free(string->_buffer);
        string->_buffer = NULL;
    }

    // Load the string from the resources.
    wchar_t buffer[50] = { 0 };
    Strings_Load(string->string_id,
                 string->_translatable ? (int)string->_last_language : 0,
                 buffer,
                 50);

    // Duplicate the current _buffer into the owned by this structure.
    string->_buffer = wcsdup(buffer);

    string->length = (int)wcslen(string->_buffer);
}
