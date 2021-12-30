#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"struction.h"
#define SIZE 20

int Board[SIZE][SIZE];
int comScore[SIZE][SIZE];
int humScore[SIZE][SIZE];
pPoints currentSteps;
void gotoxy(int x, int y);

void setBoard(int board[SIZE][SIZE]);

void play(int x, int y, int role);

void remo(int x, int y);

void location(int x, int y);

void clearLocation(int x, int y);

void control(int* p, int role);

