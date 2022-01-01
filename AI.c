
#include "AI.h"

int minMax(int board[SIZE][SIZE], int depth, int role, int alpha, int beta, int step) {
	Leaf leaf; //���沢���½ڵ���Ϣ
	leaf.score = MIN;//�ڵ㵱ǰ�÷�
	leaf.Alpha = MIN;
	leaf.Beta = MAX;
	//�ڵ�����
	leaf.X = 0;
	leaf.Y = 0;
	if(depth <= 0)//���С�ڵ�����ֱ�ӷ��ص÷֣�ֹͣ�ݹ�
	{
		return score(role, board, 1);
	}
	else
	{
		//ͨ������ʽ����������ȡ��ǰ�ڵ��µ÷ֽϸߵĽڵ㼯�ϣ���Щ�ڵ����������20��
		pPoints ppoints = gen(role, currentSteps->length  > 10 ? step > 1:step > 3);
		if (!ppoints->length) return score(role, board, 1);

		int length = ppoints->length;
		for (int i = 0; i < length; i++)
		{
			Points points = ppoints->points;
			int x = points[i].x;
			int y = points[i].y;
			//���м�֦����
			if (leaf.Alpha < leaf.Beta)
			{
				Board[x][y] = role;//����
				pushPoint(currentSteps, points[i]);//����������Ϣ
				int reverserole = role == AI ? HUM : AI;
				int minmax = minMax(Board, depth - 1, reverserole, leaf.Alpha, leaf.Beta, step++);//��ʼ�ݹ�
				Board[x][y] = EMPTY;//ȥ���ղŵ�����
				remoPoint(currentSteps);//����������Ϣ
				if (depth % 2 == 0)//����㣬����Alpha��ֵ
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
				else//��С�㣬����Beta��ֵ
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
		//����Ŀǰ�÷���ߵĵ�
		X = leaf.X;
		Y = leaf.Y;
		return leaf.score;
	}
}
bool hasNeighbor(int board[SIZE][SIZE], int x, int y, int n) {//n�����Ƶ���Χ���Χ��������
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

bool isNeighbor(pPoints currentSteps, int x, int y) {//�жϵ�ǰ�ڵ��Ƿ�������������ӵ���Χ(n=3)
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

int score(int role, int board[SIZE][SIZE], int n) {//n����������Ƿ�����ݹ��
	int i, j, k, l;
	int sum = 0, su = 0;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (board[i][j] == role || board[i][j] == EMPTY) {
				sum += fixScore(score_point(board, i, j, role));//�������ϼ������е��ֲ�����
			}
		}
	}
	//�����÷ּ�ȥ�Է��÷ּ�Ϊ���յ÷�
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
			return THREE;//���������޷���ʤ����������Ϊ����
		}
		else if (score >= BLOCKED_FOUR + THREE && score < BLOCKED_FOUR * 2) {
			return FOUR;//���Ļ���Ϊɱ�壬 �������Ϊ����
		}
		else
		{
			return FOUR * 2;//�������ģ���ʤ�壬�÷ַ���
		}
	}
	return score;
}

pPoints gen(int role, int onlyThree) {
	pPoints ppoints = creatpPoints(SIZE * SIZE);
	ppoints->length = 0;
    Points points = ppoints->points;
	//�����ǰ�����ӣ��Ǿ����������м�
	if (currentSteps->length <= 0) {
		points[ppoints->length].x = 9;
		points[ppoints->length].y = 9;
		ppoints->length++;
		return ppoints;
	}
	//��ͬ�÷ֵ�ļ���
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
				//�������Ӹ�������6�������ӵ����ҵ�ǰ����Χn=1�ķ�Χ����û�����ӣ�������
				if (currentSteps->length < 6) {
					if (!hasNeighbor(Board, i, j, 1))
						continue;
				}
				//���ӵ�϶�ʱ��Ҫ����n����ķ�Χ���Ƿ�������
				else if (!hasNeighbor(Board, i, j, 2))
				{
					continue;
				}
				int scoreHum = score_point(Board, i, j, HUM);
				int scoreCom = score_point(Board, i, j, AI);
				int maxScore = scoreHum > scoreCom ? scoreHum : scoreCom;
				//only Three���������Ƿ�ֻ���ط������ڵ��ڻ����ĵ�
				if (onlyThree && maxScore < THREE)
					continue;
				//����ڵ���Ϣ
				Point p;
				p.x = i;
				p.y = j;
				p.scoreHum = scoreHum;
				p.scoreCom = scoreCom;
				p.score = maxScore;
				p.role = role;
				bool isneighbor = isNeighbor(currentSteps, i, j);
				//���ݵ÷ִӸߵ��ͽ��ڵ������Ӧ����
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
						insertPoint(comtwothrees, p);//���������Χ�Ľڵ���������Ƚϸ�
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

	//������壬�Ǳ�ɱ�壬ֱ�ӷ���
	if (fives->length) return fives;

	// �����ܻ��ģ���ֱ�ӻ��ģ������ǳ���
	if (role == AI && comfours->length) return comfours;
	if (role == HUM && humfours->length) return humfours;

	// �Է��л��ĳ��ģ����Լ�û�У���ֻ���Ƕ������ 

	if (role == AI && humfours->length && !comblockedfours->length) return humfours;
	if (role == HUM && comfours->length && !humblockedfours->length) return comfours;

	// �����л����Լ��г��ģ������п���
	pPoints fours = role == AI ? joinPoints(comfours, humfours) : joinPoints(humfours, comfours);
	pPoints blockedfours = role == AI ? joinPoints(comblockedfours, humblockedfours) : joinPoints(humblockedfours, comblockedfours);
	if (fours->length) return joinPoints(fours, blockedfours);
	//����Щ��ͬ�㼯�������ߵ�������һ��
	pPoints result;
	if (role == AI) {
		result = joinPoints(joinPoints(joinPoints(joinPoints(joinPoints(comtwothrees, humtwothrees), comblockedfours), humblockedfours), comthrees), humthrees);
	}
	if (role == HUM) {
		result = joinPoints(joinPoints(joinPoints(joinPoints(joinPoints(humtwothrees, comtwothrees), humblockedfours), comblockedfours), humthrees), comthrees);
	}

	//sortPoint(result);

	//˫�������⣬��Ϊ���γ�˫���Ĳ�һ����һ������ǿ
	if (comtwothrees->length || humtwothrees->length) {
		return result;
	}


	// ֻ���ش��ڵ��ڻ�������
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

	//�����͵�ֻ����ǰLIMITS(20)��
	if (result->length > LIMITS) {
		result->length = LIMITS;
		return result;
	}

	return result;
}
			