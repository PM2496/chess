
#include "AI.h"

int minMax(int board[SIZE][SIZE], int depth, int role, int alpha, int beta, int step) {
	Leaf leaf;
	leaf.score = MIN;
	leaf.Alpha = MIN;
	leaf.Beta = MAX;
	leaf.X = 0;
	leaf.Y = 0;
	if(depth <= 0)
	{
		return score(role, board, 1);
	}
	else
	{
		pPoints ppoints = gen(role, currentSteps->length  > 10 ? step > 1:step > 3);
		if (!ppoints->length) return score(role, board, 1);

		int length = ppoints->length;
		for (int i = 0; i < length; i++)
		{
			Points points = ppoints->points;
			int x = points[i].x;
			int y = points[i].y;
			if (leaf.Alpha < leaf.Beta)
			{
				Board[x][y] = role;
				pushPoint(currentSteps, points[i]);
				int reverserole = role == AI ? HUM : AI;
				int minmax = minMax(Board, depth - 1, reverserole, leaf.Alpha, leaf.Beta, step++);
				Board[x][y] = EMPTY;
				remoPoint(currentSteps);
				if (depth % 2 == 0)
				{
					leaf.score = minmax;
					
					if (leaf.Alpha < minmax)
					{
						leaf.Alpha = minmax;
						leaf.score = minmax;
						leaf.X = x;
						leaf.Y = y;
					}
				}
				else
				{
					leaf.score = minmax;
					
					if (leaf.Beta > minmax)
					{
						leaf.Beta = minmax;
						leaf.score = minmax;
						leaf.X = x;
						leaf.Y = y;
					}
				}
			}
		}
		X = leaf.X;
		Y = leaf.Y;
		return leaf.score;
	}
}
bool hasNeighbor(int board[SIZE][SIZE], int x, int y, int n) {
	int i, j;

	for (i = x - n; i < x + n + 1; i++) {
		for (j = y - n; j < y + n + 1; j++) {
			if (i == x && j == y) continue;
			if (i > 0 && j > 0 && i < SIZE && j < SIZE && board[i][j] != EMPTY) {
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
			if (board[i][j] == role || board[i][j] == EMPTY) {
				sum += fixScore(score_point(board, i, j, role));
			}
		}
	}
	if (n == 1 && role == AI)
		return sum - score(HUM, board, 2);
	else if (n == 1 && role == HUM)
		return sum - score(AI, board, 2);
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

pPoints gen(int role, int onlyThree) {
	pPoints ppoints = creatpPoints(SIZE * SIZE);
	ppoints->length = 0;
    Points points = ppoints->points;
	if (currentSteps->length <= 0) {
		points[ppoints->length].x = 9;
		points[ppoints->length].y = 9;
		ppoints->length++;
		return ppoints;
	}

	pPoints fives = creatpPoints(50);
	pPoints comfours = creatpPoints(50);
	pPoints humfours = creatpPoints(50);
	pPoints comblockedfours = creatpPoints(50);
	pPoints humblockedfours = creatpPoints(50);
	pPoints comtwothrees = creatpPoints(50);
	pPoints humtwothrees = creatpPoints(50);
	pPoints comthrees = creatpPoints(50);
	pPoints humthrees = creatpPoints(50);
	pPoints comtwos = creatpPoints(50);
	pPoints humtwos = creatpPoints(50);
	pPoints neighbors = creatpPoints(100);

	int reverseRole = role == HUM ? AI : HUM;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (Board[i][j] == EMPTY) {
				if (currentSteps->length < 6) {
					if (!hasNeighbor(Board, i, j, 1))
						continue;
				}
				else if (!hasNeighbor(Board, i, j, 2))
				{
					continue;
				}
				int scoreHum = score_point(Board, i, j, HUM);
				int scoreCom = score_point(Board, i, j, AI);
				int maxScore = scoreHum > scoreCom ? scoreHum : scoreCom;
				if (onlyThree && maxScore < THREE)
					continue;
				Point p;
				p.x = i;
				p.y = j;
				p.scoreHum = scoreHum;
				p.scoreCom = scoreCom;
				p.score = maxScore;
				p.role = role;

				if (scoreCom >= FIVE || scoreHum >= FIVE) {
					pushPoint(fives, p);
				}
				else if (scoreCom >= FOUR) {
					pushPoint(comfours, p);
				}
				else if (scoreHum >= FOUR) {
					pushPoint(humfours, p);
				}
				else if (scoreCom >= BLOCKED_FOUR) {
					pushPoint(comblockedfours, p);
				}
				else if (scoreHum >= BLOCKED_FOUR) {
					pushPoint(humblockedfours, p);
				}
				else if (scoreCom >= 2 * THREE) {
					//能成双三也行
					pushPoint(comtwothrees, p);
				}
				else if (scoreHum >= 2 * THREE) {
					pushPoint(humtwothrees, p);
				}
				else if (scoreCom >= THREE) {
					pushPoint(comthrees, p);
				}
				else if (scoreHum >= THREE) {
					pushPoint(humthrees, p);
				}
				else if (scoreCom >= TWO) {
					pushPoint(comtwos, p);
				}
				else if (scoreHum >= TWO) {
					pushPoint(humtwos, p);
				}
				else pushPoint(neighbors, p);
			}
		}
	}

	//如果成五，是必杀棋，直接返回
	if (fives->length) return fives;

	// 自己能活四，则直接活四，不考虑冲四
	if (role == AI && comfours->length) return comfours;
	if (role == HUM && humfours->length) return humfours;

	// 对面有活四冲四，自己冲四都没，则只考虑对面活四 （此时对面冲四就不用考虑了)

	if (role == AI && humfours->length && !comblockedfours->length) return humfours;
	if (role == HUM && comfours->length && !humblockedfours->length) return comfours;

	// 对面有活四自己有冲四，则都考虑下
	pPoints fours = role == AI ? joinPoints(comfours, humfours) : joinPoints(humfours, comfours);
	pPoints blockedfours = role == AI ? joinPoints(comblockedfours, humblockedfours) : joinPoints(humblockedfours, comblockedfours);
	if (fours->length) return joinPoints(fours, blockedfours);
	pPoints result;
	if (role == AI) {
		result = joinPoints(joinPoints(joinPoints(joinPoints(joinPoints(comtwothrees, humtwothrees), comblockedfours), humblockedfours), comthrees), humthrees);
	}
	if (role == HUM) {
		result = joinPoints(joinPoints(joinPoints(joinPoints(joinPoints(humtwothrees, comtwothrees), humblockedfours), comblockedfours), humthrees), comthrees);
	}

	// result.sort(function(a, b) { return b.score - a.score })

	//双三很特殊，因为能形成双三的不一定比一个活三强
	if (comtwothrees->length || humtwothrees->length) {
		return result;
	}


	// 只返回大于等于活三的棋
	if (onlyThree) {
	    return result;
	}

	pPoints twos;
	if (role == AI)
		twos = joinPoints(comtwos, humtwos);
	else
		twos = joinPoints(humtwos, comtwos);

	sortPoint(twos);

	result = twos->length ? joinPoints(result, twos) : joinPoints(result, neighbors);

	//这种分数低的，就不用全部计算了
	if (result->length > LIMITS) {
		result->length = LIMITS;
		return result;
	}

	return result;
}
			