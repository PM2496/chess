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
void gotoxy(int x, int y);//���Ӷ�λ

void setBoard(int board[SIZE][SIZE]);//��ʼ������

void play(int x, int y, int role);//����

void remo(int x, int y);//�Ƴ�����

void location(int x, int y);//��λ���

void clearLocation(int x, int y);//�����λ���

void control(int* p, int role);//��������˳������ֵĽ���

