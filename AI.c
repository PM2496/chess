
#include "AI.h"

int minMax(int board[SIZE][SIZE], int depth, int role, int alpha, int beta, int step) {
	Leaf leaf; //保存并更新节点信息
	leaf.score = MIN;//节点当前得分
	leaf.Alpha = MIN;
	leaf.Beta = MAX;
	//节点坐标
	leaf.X = 0;
	leaf.Y = 0;
	if(depth <= 0)//深度小于等于零直接返回得分，停止递归
	{
		return score(role, board, 1);
	}
	else
	{
		//通过启发式搜索函数获取当前节点下得分较高的节点集合（这些节点个数不超过20）
		pPoints ppoints = gen(role, currentSteps->length  > 10 ? step > 1:step > 3);
		if (!ppoints->length) return score(role, board, 1);

		int length = ppoints->length;
		for (int i = 0; i < length; i++)
		{
			Points points = ppoints->points;
			int x = points[i].x;
			int y = points[i].y;
			//进行剪枝操作
			if (leaf.Alpha < leaf.Beta)
			{
				Board[x][y] = role;//落子
				pushPoint(currentSteps, points[i]);//更新落子信息
				int reverserole = role == AI ? HUM : AI;
				int minmax = minMax(Board, depth - 1, reverserole, leaf.Alpha, leaf.Beta, step++);//开始递归
				Board[x][y] = EMPTY;//去掉刚才的落子
				remoPoint(currentSteps);//更新落子信息
				if (depth % 2 == 0)//极大层，更新Alpha的值
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
				else//极小层，更新Beta的值
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
		//保存目前得分最高的点
		X = leaf.X;
		Y = leaf.Y;
		return leaf.score;
	}
}
bool hasNeighbor(int board[SIZE][SIZE], int x, int y, int n) {//n来控制点周围多大范围内有落子
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

bool isNeighbor(pPoints currentSteps, int x, int y) {//判断当前节点是否在最后三个落子的周围(n=3)
	int length = currentSteps->length;
	for (int i = 1; length - i >= 0 && i <= 3; i++) {
		int x1 = currentSteps->points[length - i].x;
		int y1 = currentSteps->points[length - i].y;
		if (x - x1 <= 1 && x - x1 >= -1 && y - y1 <= 1 && y - y1 >= -1) {
			return true;
		}
	}
	return false;
}

int score(int role, int board[SIZE][SIZE], int n) {//n是用来标记是否结束递归的
	int i, j, k, l;
	int sum = 0, su = 0;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (board[i][j] == role || board[i][j] == EMPTY) {
				sum += fixScore(score_point(board, i, j, role));//对棋盘上己方所有点打分并修正
			}
		}
	}
	//己方得分减去对方得分即为最终得分
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
			return THREE;//单独冲四无法获胜，分数降低为活三
		}
		else if (score >= BLOCKED_FOUR + THREE && score < BLOCKED_FOUR * 2) {
			return FOUR;//冲四活三为杀棋， 分数提高为活四
		}
		else
		{
			return FOUR * 2;//两个冲四，必胜棋，得分翻倍
		}
	}
	return score;
}

pPoints gen(int role, int onlyThree) {
	pPoints ppoints = creatpPoints(SIZE * SIZE);
	ppoints->length = 0;
    Points points = ppoints->points;
	//如果当前无落子，那就落在棋盘中间
	if (currentSteps->length <= 0) {
		points[ppoints->length].x = 9;
		points[ppoints->length].y = 9;
		ppoints->length++;
		return ppoints;
	}
	//不同得分点的集合
	pPoints fives = creatpPoints(10);
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
				//棋盘落子个数少于6个，落子点少且当前点周围n=1的范围内仍没有落子，不考虑
				if (currentSteps->length < 6) {
					if (!hasNeighbor(Board, i, j, 1))
						continue;
				}
				//落子点较多时就要考虑n更大的范围内是否有落子
				else if (!hasNeighbor(Board, i, j, 2))
				{
					continue;
				}
				int scoreHum = score_point(Board, i, j, HUM);
				int scoreCom = score_point(Board, i, j, AI);
				int maxScore = scoreHum > scoreCom ? scoreHum : scoreCom;
				//only Three用来控制是否只返回分数大于等于活三的点
				if (onlyThree && maxScore < THREE)
					continue;
				//储存节点信息
				Point p;
				p.x = i;
				p.y = j;
				p.scoreHum = scoreHum;
				p.scoreCom = scoreCom;
				p.score = maxScore;
				p.role = role;
				bool isneighbor = isNeighbor(currentSteps, i, j);
				//根据得分从高到低将节点存入相应集合
				if (scoreCom >= FIVE || scoreHum >= FIVE) {
					pushPoint(fives, p);
				}
				else if (scoreHum >= FIVE)
				{
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
					if (isneighbor) 
						insertPoint(comtwothrees, p);//最后落子周围的节点分数往往比较高
					else
						pushPoint(comtwothrees, p);
				}
				else if (scoreHum >= 2 * THREE) {
					if (isneighbor) 
						insertPoint(humtwothrees, p);
					else
						pushPoint(humtwothrees, p);
				}
				else if (scoreCom >= THREE) {
					if (isneighbor) 
						insertPoint(comthrees, p);
					else
						pushPoint(comthrees, p);
				}
				else if (scoreHum >= THREE) {
					if (isneighbor) 
						insertPoint(humthrees, p);
					else
						pushPoint(humthrees, p);
				}
				else if (scoreCom >= TWO) {
					if (isneighbor) 
						insertPoint(comtwos, p);
					else
						pushPoint(comtwos, p);
				}
				else if (scoreHum >= TWO) {
					if (isneighbor) 
						insertPoint(humtwos, p);
					else
						pushPoint(humtwos, p);
				}
				else pushPoint(neighbors, p);
			}
		}
	}

	//如果成五，是必杀棋，直接返回
	if (fives->length) return fives;

	// 己方能活四，则直接活四，不考虑冲四
	if (role == AI && comfours->length) return comfours;
	if (role == HUM && humfours->length) return humfours;

	// 对方有活四冲四，而自己没有，则只考虑对面活四 

	if (role == AI && humfours->length && !comblockedfours->length) return humfours;
	if (role == HUM && comfours->length && !humblockedfours->length) return comfours;

	// 对面有活四自己有冲四，都进行考虑
	pPoints fours = role == AI ? joinPoints(comfours, humfours) : joinPoints(humfours, comfours);
	pPoints blockedfours = role == AI ? joinPoints(comblockedfours, humblockedfours) : joinPoints(humblockedfours, comblockedfours);
	if (fours->length) return joinPoints(fours, blockedfours);
	//将这些不同点集按分数高低整合在一起
	pPoints result;
	if (role == AI) {
		result = joinPoints(joinPoints(joinPoints(joinPoints(joinPoints(comtwothrees, humtwothrees), comblockedfours), humblockedfours), comthrees), humthrees);
	}
	if (role == HUM) {
		result = joinPoints(joinPoints(joinPoints(joinPoints(joinPoints(humtwothrees, comtwothrees), humblockedfours), comblockedfours), humthrees), comthrees);
	}

	//sortPoint(result);

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

	//sortPoint(twos);

	result = twos->length ? joinPoints(result, twos) : joinPoints(result, neighbors);

	//分数低的只考虑前LIMITS(20)个
	if (result->length > LIMITS) {
		result->length = LIMITS;
		return result;
	}

	return result;
}
			