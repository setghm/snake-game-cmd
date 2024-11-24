#include "strings.h"
#include <stdio.h>

bool Strings_Load(int id, int language, wchar_t* buffer, int buffer_length) {
    // Get the string of the desired language.
    // The strings of each language are identified by multiples of 100.
    int str_id = id + language * 100;

    //char message[100] = { 0 };
    //sprintf(message, "Loading string: %d, language: %d", id, language);
    //MessageBox(0, message, "Strings_Load", 0);

    int result = LoadStringW(GetModuleHandle(NULL),
                             str_id,
                             buffer,
                             buffer_length);

    if (result < 0) {
        // Copy an empty string to the target _buffer.
        wcsncpy_s(buffer, 2, L" \0", 2);
        fputs("Cannot load that string", stderr);
        return false;
    }

    return true;
}
