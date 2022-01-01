#include "AI.h"

bool gameOver(int x, int y, int role) {
	return (score_point(Board, x, y, role) >= FIVE);
}

int* compu(int depth) {
	int i, j;
	int* p = (int*)malloc(2 * sizeof(int));
	static int n = 0;
	if (n == 0) {
		//如果电脑先下，第一个子落子棋盘中央
		if (Board[7][7] == EMPTY) {
			p[0] = 7;
			p[1] = 7;
			return p;
		}
		else
		{
			n++;
		}
	}

	minMax(Board, depth, AI, MIN, MAX, 1);
	p[0] = X;
	p[1] = Y;

	return p;
}
int* human()
{
	static int X = 7, Y = 7;
	char h;
	int* p = (int*)malloc(2 * sizeof(int));
	location(X, Y);
	while (1)
	{
		if (kbhit() != 0)
		{
			h = getch();
			clearLocation(X, Y);
			switch (h)
			{
			case 72://上
				if (X > 0)
					X--;
				break;
			case 80://下
				if (X < 19)
					X++;
				break;
			case 75://左
				if (Y > 0)
					Y--;
				break;
			case 77://右
				if (Y < 19)
					Y++;
				break;
			case 32://空格
				if (Board[X][Y] == 0)
				{
					p[0] = X;
					p[1] = Y;
					return p;
				}
				break;
			}
			location(X, Y);
		}
	}
}

void control(int* p, int role) {
	static int x, y;
	play(p[0], p[1], role);
	location(p[0], p[1]);
	clearLocation(x, y);
	x = p[0];
	y = p[1];
	if (gameOver(p[0], p[1], role))
	{
		gotoxy(0,38);
		puts("\n游戏结束\n");
		exit(0);
	}
}