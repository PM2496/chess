#pragma once
#include "board.h"
#include "evaluate_point.h"
#include "role.h"
#include "shape.h"
int score_point(int board[SIZE][SIZE], int x, int y, int role) {
	int result = 0;
	int empty = -1, count = 1, block = 0, secondCount = 0;
	int len = SIZE;
	//横向棋形, empty数值表示空位在棋形中的位置序数
	for (int i = y + 1; true; i++) {
		if (i >= len) {
			block++;
			break;
		}
		int t = board[x][i];
		if (t == EMPTY) {
			if (empty == -1 && i < len - 1 && board[x][i + 1] == role) {
				empty = count;
				continue;
			}
			else
			{
				break;
			}
		}
		if (t == role) {
			count++;
			continue;
		}
		else
		{
			block++;
			break;
		}
	}

	for (int i = y - 1; true; i--) {
		if (i < 0) {
			block++;
			break;
		}
		int t = board[x][i];
		if (t == EMPTY) {
			if (empty == -1 && i > 0 && board[x][i - 1] == role) {
				empty = 0; //empty序数是相对于棋形最左边棋子而言的
				continue;
			}
			else
			{
				break;
			}
		}
		if (t == role) {
			secondCount++;
			empty != -1 && empty++;
			continue;
		}
		else
		{
			block++;
			break;
		}
	}
	count += secondCount;
	result += cal_score(count, block, empty);

	empty = -1;
	count = 1;
	block = 0;
	secondCount = 0;
	//纵向棋形
	for (int i = x + 1; true; i++) {
		if (i >= len) {
			block++;
			break;
		}
		int t = board[i][y];
		if (t == EMPTY) {
			if (empty == -1 && i < len - 1 && board[i + 1][y] == role) {
				empty = count;
				continue;
			}
			else
			{
				break;
			}
		}
		if (t == role) {
			count++;
			continue;
		}
		else
		{
			block++;
			break;
		}
	}

	for (int i = x - 1; true; i--) {
		if (i < 0) {
			block++;
			break;
		}
		int t = board[i][y];
		if (t == EMPTY) {
			if (empty == -1 && i > 0 && board[i - 1][y] == role) {
				empty = 0;
				continue;
			}
			else
			{
				break;
			}
		}
		if (t == role) {
			secondCount++;
			empty != -1 && empty++;
			continue;
		}
		else
		{
			block++;
			break;
		}
	}
	count += secondCount;
	result += cal_score(count, block, empty);

	empty = -1;
	count = 1;
	block = 0;
	secondCount = 0;

	//"\"棋形
	for (int i = 1; true; i++) {
		int px = x + i, py = y + i;
		if (px >= len || py >= len) {
			block++;
			break;
		}
		int t = board[px][py];
		if (t == EMPTY) {
			if (empty == -1 && (px < len - 1 && py < len - 1) && board[px + 1][py + 1] == role) {
				empty = count;
				continue;
			}
			else
			{
				break;
			}
		}
		if (t == role) {
			count++;
			continue;
		}
		else
		{
			block++;
			break;
		}
	}

	for (int i = 1; true; i++) {
		int px = x - i, py = y - i;
		if (px < 0 || py < 0) {
			block++;
			break;
		}
		int t = board[px][py];
		if (t == EMPTY) {
			if (empty == -1 && (px > 0 && py > 0) && board[x - 1][y - 1] == role) {
				empty = 0;
				continue;
			}
			else
			{
				break;
			}
		}
		if (t == role) {
			secondCount++;
			empty != -1 && empty++;
			continue;
		}
		else
		{
			block++;
			break;
		}
	}
	count += secondCount;
	result += cal_score(count, block, empty);

	empty = -1;
	count = 1;
	block = 0;
	secondCount = 0;

	//"/"棋形
	for (int i = 1; true; i++) {
		int px = x + i, py = y - i;
		if (px >= len || py < 0) {
			block++;
			break;
		}
		int t = board[px][py];
		if (t == EMPTY) {
			if (empty == -1 && (px < len - 1 && py > 0) && board[px + 1][py - 1] == role) {
				empty = count;
				continue;
			}
			else
			{
				break;
			}
		}
		if (t == role) {
			count++;
			continue;
		}
		else
		{
			block++;
			break;
		}
	}

	for (int i = 1; true; i++) {
		int px = x - i, py = y + i;
		if (px < 0 || py >= len) {
			block++;
			break;
		}
		int t = board[px][py];
		if (t == EMPTY) {
			if (empty == -1 && (px > 0 && py < len - 1) && board[px - 1][py + 1] == role) {
				empty = 0;
				continue;
			}
			else
			{
				break;
			}
		}
		if (t == role) {
			secondCount++;
			empty != -1 && empty++;
			continue;
		}
		else
		{
			block++;
			break;
		}
	}
	count += secondCount;
	result += cal_score(count, block, empty);

	return result;
}

int cal_score(int count, int block, int empty) {
	if (empty <= 0) {
		if (count >= 5) return FIVE;
		if (block == 0) {
			switch (count) {
			case 1: return ONE;
			case 2: return TWO;
			case 3: return THREE;
			case 4: return FOUR;
			}
		}
		if (block == 1) {
			switch (count) {
			case 1: return BLOCKED_ONE;
			case 2: return BLOCKED_TWO;
			case 3: return BLOCKED_THREE;
			case 4: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 1 || empty == count - 1) {
		//第一个是空位
		if (count >= 6) return FIVE;
		if (block == 0) {
			switch (count) {
			case 2: return TWO / 2;
			case 3: return THREE;
			case 4: return BLOCKED_FOUR;
			case 5: return FOUR;
			}
		}
		if (block == 1) {
			switch (count) {
			case 2: return BLOCKED_TWO;
			case 3: return BLOCKED_THREE;
			case 4: return BLOCKED_FOUR;
			case 5: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 2 || empty == count - 2) {
		//第二个是空位
		if (count >= 7) {
			return FIVE;
		}
		if (block == 0) {
			switch (count) {
			case 3: return THREE;
			case 4:
			case 5: return BLOCKED_FOUR;
			case 6: return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
			case 3: return BLOCKED_THREE;
			case 4: return BLOCKED_FOUR;
			case 5: return BLOCKED_FOUR;
			case 6: return FOUR;
			}
		}

		if (block == 2) {
			switch (count) {
			case 4:
			case 5:
			case 6: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 3 || empty == count - 3) {
		//第三个是空位
		if (count >= 8) {
			return FIVE;
		}
		if (block == 0) {
			switch (count) {
			case 4:
			case 5: return THREE;
			case 6: return BLOCKED_FOUR;
			case 7: return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
			case 4:
			case 5:
			case 6: return BLOCKED_FOUR;
			case 7: return FOUR;
			}
		}

		if (block == 2) {
			switch (count) {
			case 4:
			case 5:
			case 6:
			case 7: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 4 || empty == count - 4) {
	//第四个是空位
		if (count >= 9) {
			return FIVE;
		}
		if (block == 0) {
			switch (count) {
			case 5:
			case 6:
			case 7:
			case 8: return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
			case 4:
			case 5:
			case 6:
			case 7: return BLOCKED_FOUR;
			case 8: return FOUR;
			}
		}

		if (block == 2) {
			switch (count) {
			case 5:
			case 6:
			case 7:
			case 8: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 5 || empty == count - 5) {
		return FIVE;
	}

	return 0;
}