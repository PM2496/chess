#include<stdbool.h>
#include"board.h"
#include "evaluate_point.h"
#include"role.h"
#include "shape.h"
#include "struction.h"

#define MAX 2147483647 // 正无穷
#define MIN -2147483648 // 负无穷
#define LIMITS 20

int X;
int Y;


int minMax(int board[SIZE][SIZE], int depth, int role, int alpha, int beta, int step);
bool hasNeighbor(int board[SIZE][SIZE], int x, int y, int n);
int fixScore(int score);
int score(int role, int board[SIZE][SIZE], int n);
pPoints gen(int role, int onlyThree);




