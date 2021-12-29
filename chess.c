#pragma once
#include "AI.h"
#include "control.h"


int main(void) {
	setBoard(Board);
	int depth, n;
	printf("\n\n请输入搜索深度（深度为偶数）：");
	scanf_s("%d", &depth);
	printf("\n先手按1, 后手按2：");
	scanf_s("%d", &n);
	gotoxy(0, 0);
	puts("                                                                 ");
	gotoxy(0, 1);
	puts("                                                    ");
	setBoard(Board);
	while (1)
	{
		if (n == 1) {
			control(human(), HUM);
			control(compu(depth), AI);
		}
		if (n == 2) {
			control(compu(depth), AI);
			control(human(), HUM);
		}
	}
}