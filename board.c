#pragma once
#include"board.h"

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void setBoard(int board[SIZE][SIZE]) {
	int i, j;
	gotoxy(0, 0); puts("©³ ©¥");
	gotoxy(0, 42); puts("©» ©¥");
	gotoxy(84, 0); puts("©·");
	gotoxy(84, 42); puts("©¿");
	for (i = 1; i < 21; i++)
		for (j = 1; j < 21; j++)
		{
			gotoxy(j * 4, 2 * i - 1); puts("©§");
			gotoxy(j * 4, i * 2); puts("©ï ©¥");
		}
	for (i = 1; i < 22; i++)
	{
		gotoxy(0, i * 2 - 1); puts("©§");
		gotoxy(84, i * 2 - 1); puts("©§");
	}
	for (i = 1; i < 21; i++)
	{
		gotoxy(i * 4, 0); puts("©× ©¥");
		gotoxy(i * 4, 42); puts("©ß ©¥");
		gotoxy(i * 4, 41); puts("©§");
		gotoxy(2, i * 2); puts("©¥");
		gotoxy(0, i * 2); puts("©Ç");
		gotoxy(84, i * 2); puts("©Ï");
	}
	for (i = 0; i < 20; i++)
		for (j = 0; j < 20; j++)
			board[i][j] = 0;
}

void play(int x, int y, int role) {
	if (role == 1 && Board[x][y] == 0)
	{
		gotoxy((y + 1) * 4, (x + 1) * 2); puts("¡ñ");
		Board[x][y] = 1;
	}
	else if (role == 2 && Board[x][y] == 0)
	{
		gotoxy((y + 1) * 4, (x + 1) * 2); puts("¡ð");
		Board[x][y] = 2;
	}
}

void location(int x, int y) {
	gotoxy((y + 1) * 4 - 2, (x + 1) * 2 - 1); puts("©¿");
	gotoxy((y + 1) * 4 + 2, (x + 1) * 2 - 1); puts("©»");
	gotoxy((y + 1) * 4 - 2, (x + 1) * 2 + 1); puts("©·");
	gotoxy((y + 1) * 4 + 2, (x + 1) * 2 + 1); puts("©³");
}

void clearLocation(int x, int y) {
	gotoxy((y + 1) * 4 - 2, (x + 1) * 2 - 1); puts("  ");
	gotoxy((y + 1) * 4 + 2, (x + 1) * 2 - 1); puts("  ");
	gotoxy((y + 1) * 4 - 2, (x + 1) * 2 + 1); puts("  ");
	gotoxy((y + 1) * 4 + 2, (x + 1) * 2 + 1); puts("  ");
}

