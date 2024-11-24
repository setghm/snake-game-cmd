#ifndef STRINGS_H__
#define STRINGS_H__

#include <Windows.h>
#include <resource.h>
#include <stdbool.h>

bool Strings_Load(int id, int language, __out wchar_t* buffer, int buffer_length);

#endif //STRINGS_H__
/*
 * End Of File
 */