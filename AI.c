
#include "ai.h"

int minMax(int board[SIZE][SIZE], int depth, int role, int alpha, int beta) {
	int i, j;
	int cache[SIZE][SIZE];
	int minmax;
	int b;
	int n = 1;
	Tree tree;
	tree.data = MIN;
	tree.Alpha = MIN;
	tree.Beta = MAX;
	tree.X = 0;
	tree.Y = 0;
	b = (role == 1 ? 2 : 1);
	if (depth > 0)
	{
		for (i = 0; i < SIZE; i++)
			for (j = 0; j < SIZE; j++)
			{
				if (board[i][j] == 0 && hasNeighbor(board, i, j, 1) && tree.Alpha < tree.Beta)
				{
					memcpy(cache, board, sizeof(int) * SIZE * SIZE);
					cache[i][j] = role;
					minmax = minMax(cache, depth - 1, b, tree.Alpha, tree.Beta);
					if (depth % 2 == 0)
					{
						if (n == 1)
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Alpha < minmax)
						{
							tree.Alpha = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
					else
					{
						if (n == 1)
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Beta > minmax)
						{
							tree.Beta = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
				}
			}
		/*for (i = 0; i < 20; i++)
			for (j = 0; j < 20; j++)
			{
				if (board[i][j] == 0 && hasNeighbor(board, i, j, 2) && tree.Alpha < tree.Beta)
				{
					memcpy(cache, board, sizeof(int) * SIZE * SIZE);
					cache[i][j] = role;
					minmax = minMax(cache, depth - 1, b, tree.Alpha, tree.Beta);
					if (depth % 2 == 0)
					{
						if (tree.Alpha < minmax)
						{
							tree.Alpha = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
					else
					{
						if (tree.Beta > minmax)
						{
							tree.Beta = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
				}
			}*/
		X = tree.X;
		Y = tree.Y;
		//printf("%d", tree.data);
		return tree.data;
	}
	else
	{
		return score(role, board, 1);
	}
}
bool hasNeighbor(int board[SIZE][SIZE], int x, int y, int n) {
	int i, j;

	for (i = x - n; i < x + n + 1; i++) {
		for (j = y - n; j < y + n + 1; j++) {
			if (i > 0 && j > 0 && i < SIZE && j < SIZE && board[i][j] != 0) {
				return true;
			}
		}
	}

	return false;
}

int score(int role, int board[SIZE][SIZE], int n) {
	int i, j, k, l;
	int sum = 0, su = 0;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (board[i][j] == role) {
				sum += fixScore(score_point(board, i, j, role));
			}
		}
	}
	if (n == 1 && role == 1)
		return sum - score(2, board, 2);
	else if (n == 1 && role == 2)
		return sum - score(1, board, 2);
	else if (n == 2)
		return sum;
}
int fixScore(int score) {
	if (score < FOUR && score >= BLOCKED_FOUR) {
		if (score < BLOCKED_FOUR + THREE) {
			return THREE;
		}
		else if (score >= BLOCKED_FOUR + THREE && score < BLOCKED_FOUR * 2) {
			return FOUR;
		}
		else
		{
			return FOUR * 2;
		}
	}
	return score;
}

