#include<stdbool.h>
#include"board.h"
#include "evaluate_point.h"
#include"role.h"
#include "shape.h"
#include "struction.h"

#define MAX 2147483647 // 正无穷
#define MIN -2147483648 // 负无穷
#define LIMITS 20 //每个节点下子节点搜索限制
//保存得分最高点的坐标
int X; 
int Y;


int minMax(int board[SIZE][SIZE], int depth, int role, int alpha, int beta, int step);//极大值极小值搜索
bool hasNeighbor(int board[SIZE][SIZE], int x, int y, int n);//判断一个点周围是否有落子
bool isNeighbor(pPoints currentSteps, int x, int y);
int fixScore(int score); //局面得分修正
int score(int role, int board[SIZE][SIZE], int n);//对局面进行打分
pPoints gen(int role, int onlyThree);//启发式搜索以减少搜索量，提高效率




