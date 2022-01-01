#pragma once
#include <malloc.h>
typedef struct leaf {
	int score;
	int Alpha;
	int Beta;
	int X;
	int Y;
} Leaf;

typedef struct point {
	int x;
	int y;
	int role;
	int scoreHum;
	int scoreCom;
	int score;
} Point, * Points;

typedef struct ppoints {
	Points points;
	int length;
} pPoint, * pPoints;
pPoints creatpPoints(int n);
void pushPoint(pPoints points, Point  point);
void insertPoint(pPoints points, Point point);
pPoints joinPoints(pPoints to, pPoints from);
void remoPoint(pPoints points);
void sortPoint(pPoints points);