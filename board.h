#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"struction.h"
#define SIZE 16

int Board[SIZE][SIZE];
int comScore[SIZE][SIZE];
int humScore[SIZE][SIZE];
pPoints currentSteps;
void gotoxy(int x, int y);//落子定位

void setBoard(int board[SIZE][SIZE]);//初始化棋盘

void play(int x, int y, int role);//落子

void remo(int x, int y);//移除落子

void location(int x, int y);//定位光标

void clearLocation(int x, int y);//清除定位光标

void control(int* p, int role);//控制落子顺序与棋局的结束

