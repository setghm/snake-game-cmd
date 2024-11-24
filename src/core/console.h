#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <Windows.h>
#include <stdio.h>

typedef struct _Console {
	HANDLE handle;
	HANDLE restore;
	SMALL_RECT rcWinCon;
	COORD cr_size;
	UINT area;
	CHAR_INFO* buffer;
	DWORD cColor;
} Console;

typedef unsigned char byte;

Console* CreateConsole(COORD size);
void ConsoleCleanup(Console* con);

void ConsoleShow(Console *con);
void ConsoleClearColor(Console* con, DWORD color);
void FillScreen(Console* con, wchar_t ch, DWORD color);

void DrawChar(Console* con, COORD pos, wchar_t ch, DWORD color);
void DrawString(Console* con, COORD pos, wchar_t* str, DWORD color);
void DrawColorArray(Console *con, COORD pos, const byte *colors, size_t rows, size_t cols);
void DrawColorPattern(Console *con, COORD pos, const byte *pat, size_t len, size_t times);

void PresentScreen(Console* con);
void ClearScreen(Console* con);

#endif
/*
 *	End Of File
 */