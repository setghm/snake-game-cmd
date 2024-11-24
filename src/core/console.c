#include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

void MinimumRect(SMALL_RECT* smrc) {
	smrc->Left = 0;
	smrc->Top = 0;
	smrc->Right = 1;
	smrc->Bottom = 1;
}
void SizeRect(SMALL_RECT* smrc, COORD brsize) {
	smrc->Left = 0;
	smrc->Top = 0;
	smrc->Right = brsize.X - 1;
	smrc->Bottom = brsize.Y - 1;
}

Console* CreateConsole(COORD size) {
	Console *con = (Console*) malloc(sizeof(Console));
	memset(con, 0, sizeof(Console));
	
	con->restore = GetStdHandle(STD_OUTPUT_HANDLE);
	con->handle = CreateConsoleScreenBuffer(
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	con->cr_size = size;
	con->area = size.X * size.Y;
	
	// Set desired size
	MinimumRect(&con->rcWinCon);
	SetConsoleWindowInfo(con->handle, TRUE, &con->rcWinCon);
	
	SetConsoleScreenBufferSize(con->handle, size);
	
	SizeRect(&con->rcWinCon, size);
	SetConsoleWindowInfo(con->handle, TRUE, &con->rcWinCon);
	
	// Hide the console cursor
	CONSOLE_CURSOR_INFO ccinf;
	ccinf.dwSize = 100;
	ccinf.bVisible = FALSE;
	SetConsoleCursorInfo(con->handle, &ccinf);
	
	// Create new char info _buffer
	con->buffer = (CHAR_INFO*) calloc(con->area, sizeof(CHAR_INFO));
	
	return con;
}

void ConsoleCleanup(Console* con) {
	// Restore original console handle
	SetConsoleActiveScreenBuffer(con->restore);
	
	CloseHandle(con->handle);
	free(con->buffer);
	
	free(con);
	con = NULL;
}

void ConsoleShow(Console *con) {
    // Activate the new handle
    SetConsoleActiveScreenBuffer(con->handle);
}

void ConsoleClearColor(Console* con, DWORD color) {
	con->cColor = color;
}

void FillScreen(Console* con, wchar_t ch, DWORD color) {
	for (int i=0; i < con->area; i++) {
		con->buffer[i].Char.UnicodeChar = ch;
		con->buffer[i].Attributes = color;
	}
}

void DrawChar(Console* con, COORD pos, wchar_t ch, DWORD color) {
	UINT index = pos.X + (pos.Y * con->cr_size.X);
	
	// Draw altough the position is outside the screen
//	while(index > console->area) index -= console->area;

	if (index >= 0 && index < con->area) {
		
		con->buffer[index].Char.UnicodeChar = ch;
		con->buffer[index].Attributes = color;
		
	}
}

void DrawString(Console* con, COORD pos, wchar_t* str, DWORD color) {
	unsigned int len = wcslen(str);
	
	for (int i=0; i<len; i++) {
		DrawChar(con, pos, str[i], color);
        pos.X++;
	}
}

void DrawColorArray(Console *con, COORD pos, const byte *colors, size_t rows, size_t cols) {
    for (int y=0; y<rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (y < con->cr_size.Y && x < con->cr_size.X) {
                con->buffer[y * con->cr_size.X + x].Attributes = colors[y * con->cr_size.X + x];
            }
        }
    }
}

void DrawColorPattern(Console *con, COORD pos, const byte *pat, size_t len, size_t times) {
    int start = pos.Y * con->cr_size.X + pos.X;
    for (int i=start; i < start+times && i < con->area; i += len) {
        for (int j=0; j<len; j++) {
            con->buffer[i + j].Attributes = pat[j];
        }
    }
}

void PresentScreen(Console* con) {
	WriteConsoleOutputW(
		con->handle,
		con->buffer,
		con->cr_size,
		(COORD){0, 0},
		&con->rcWinCon
	);
}

void ClearScreen(Console* con) {
	FillScreen(con, L' ', con->cColor);
}

/*
 *	End Of File
 */