#pragma once
#include "role.h"
#include"board.h"

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void setBoard(int board[SIZE][SIZE]) {
	int i, j;
	gotoxy(0, 0); puts("©³ ©¥");
	gotoxy(0, 34); puts("©» ©¥");
	gotoxy(68, 0); puts("©·");
	gotoxy(68, 34); puts("©¿");
	for (i = 1; i < 17; i++)
		for (j = 1; j < 17; j++)
		{
			gotoxy(j * 4, 2 * i - 1); puts("©§");
			gotoxy(j * 4, i * 2); puts("©ï ©¥");
		}
	for (i = 1; i < 18; i++)
	{
		gotoxy(0, i * 2 - 1); puts("©§");
		gotoxy(68, i * 2 - 1); puts("©§");
	}
	for (i = 1; i < 17; i++)
	{
		gotoxy(i * 4, 0); puts("©× ©¥");
		gotoxy(i * 4, 34); puts("©ß ©¥");
		gotoxy(i * 4, 33); puts("©§");
		gotoxy(2, i * 2); puts("©¥");
		gotoxy(0, i * 2); puts("©Ç");
		gotoxy(68, i * 2); puts("©Ï");
	}
	for (i = 0; i < 16; i++)
		for (j = 0; j < 16; j++)
			board[i][j] = 0;
	
	currentSteps = creatpPoints(SIZE*SIZE);
	currentSteps->length = 0;
}

void play(int x, int y, int role) {
	if (role == AI && Board[x][y] == 0)
	{
		gotoxy((y + 1) * 4, (x + 1) * 2); puts("¡ñ");
		Board[x][y] = AI;
		
	}
	else if (role == HUM && Board[x][y] == 0)
	{
		gotoxy((y + 1) * 4, (x + 1) * 2); puts("¡ð");
		Board[x][y] = HUM;
	}
	if (Board[x][y] != 0) {
		Points points = currentSteps->points;
		points[currentSteps->length].x = x;
		points[currentSteps->length].y = y;
		points[currentSteps->length].role = role;
		currentSteps->length++;
	}
	
}

void remo(int x, int y) {
	Board[x][y] = EMPTY;
	currentSteps->length--;
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

