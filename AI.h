#include<stdbool.h>
#include"board.h"
#include "evaluate_point.h"
#include"role.h"
#include "shape.h"
#include "struction.h"

#define MAX 2147483647 // ������
#define MIN -2147483648 // ������
#define LIMITS 20 //ÿ���ڵ����ӽڵ���������
//����÷���ߵ������
int X; 
int Y;


int minMax(int board[SIZE][SIZE], int depth, int role, int alpha, int beta, int step);//����ֵ��Сֵ����
bool hasNeighbor(int board[SIZE][SIZE], int x, int y, int n);//�ж�һ������Χ�Ƿ�������
bool isNeighbor(pPoints currentSteps, int x, int y);
int fixScore(int score); //����÷�����
int score(int role, int board[SIZE][SIZE], int n);//�Ծ�����д��
pPoints gen(int role, int onlyThree);//����ʽ�����Լ��������������Ч��




