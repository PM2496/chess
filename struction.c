#include "struction.h"

pPoints creatpPoints(int n) {
	pPoints ppoints = (pPoints)malloc(sizeof(pPoint));
	ppoints->points = (Points)malloc(sizeof(Point) * n);
	ppoints->length = 0;
	return ppoints;
}
void pushPoint(pPoints ppoints, Point  point) {
	Points points = ppoints->points;
	int length = ppoints->length;
	points[length].x = point.x;
	points[length].y = point.y;
	points[length].scoreCom = point.scoreCom;
	points[length].scoreHum = point.scoreHum;
	points[length].score = point.score;
	points[length].role = point.role;
	ppoints->length++;
}
pPoints joinPoints(pPoints pto, pPoints pfrom) {

	pPoints newppoints = creatpPoints(pto->length + pfrom->length);
	Points newPoints = newppoints->points;
	for (int i = 0; i < pto->length; i++) {
		int length = newppoints->length;
		Points to = pto->points;
		newPoints[length].x = to[i].x;
		newPoints[length].y = to[i].y;
		newPoints[length].scoreHum = to[i].scoreHum;
		newPoints[length].scoreCom = to[i].scoreCom;
		newPoints[length].score = to[i].score;
		newPoints[length].role = to[i].role;
		newppoints->length++;
	}
	for (int i = 0; i < pfrom->length; i++) {
		int length = newppoints->length;
		Points from = pfrom->points;
		newPoints[length].x = from[i].x;
		newPoints[length].y =from[i].y;
		newPoints[length].scoreHum = from[i].scoreHum;
		newPoints[length].scoreCom = from[i].scoreCom;
		newPoints[length].score = from[i].score;
		newPoints[length].role = from[i].role;
		newppoints->length++;
	}
	return newppoints;
}

void remoPoint(pPoints ppoints) {
	ppoints->length--;
}

void sortPoint(pPoints ppoints) {
	Points points = ppoints->points;
	for (int i = 0; i < ppoints->length; i++) {
		for (int j = 0; j < ppoints->length - i-1; j++) {
			Point point;
			if (points[j].score < points[j + 1].score) {
				point.x = points[j].x;
				point.y = points[j].y;
				point.score = points[j].score;
				point.scoreCom = points[j].scoreCom;
				point.scoreHum = points[j].scoreHum;
				point.role = points[j].role;

				points[j].x = points[j + 1].x;
				points[j].y = points[j + 1].y;
				points[j].score = points[j + 1].score;
				points[j].scoreCom = points[j + 1].scoreCom;
				points[j].scoreHum = points[j + 1].scoreHum;
				points[j].role = points[j + 1].role;

				points[j+1].x = point.x;
				points[j+1].y = point.y;
				points[j+1].score = point.score;
				points[j+1].scoreCom = point.scoreCom;
				points[j+1].scoreHum = point.scoreHum;
				points[j+1].role = point.role;

			}
		}
	}
}