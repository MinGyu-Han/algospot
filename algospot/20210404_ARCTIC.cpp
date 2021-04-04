#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

double solution(vector<vector<double>>& loc)
{
	double answer = -1;

	// 방문여부 확인용 base
	vector<bool> visited(loc.size(), true);

	// 이분탐색 범위
	double minV = 0;	// 최소값
	double maxV = 1000 * sqrt(2);	// 최대값(좌표가 0~1000 범위라..)

	while (minV <= maxV)
	{
		double midV = (maxV + minV) / 2;

		// BFS로 기지 탐색 
		vector<bool> curVisited = visited;

		queue<int> mQ;
		// 본부(index 0) 처음 방문
		mQ.push(0);
		int count = 0;

		while (!mQ.empty())
		{
			int idx = mQ.front();
			mQ.pop();

			// 이미 방문한 기지면 무시
			if (curVisited[idx] != true) continue;
			count++;	// 방문 기지수 카운트
			curVisited[idx] = false;	// 방문여부 표시

			for (int i = 0; i < loc.size(); i++)
			{
				// 이미 방문한 기지면 무시
				if (curVisited[i] == false) continue;

				double a = abs(loc[idx][0] - loc[i][0]);
				double b = abs(loc[idx][1] - loc[i][1]);
				if (sqrt(a * a + b * b) <= midV)
				{	// idx, i 기지간 거리가 midV 이하면 큐에 넣음
					mQ.push(i);
				}
			}
		}

		// 길이가 부족했을 경우 오른쪽 범위 탐색
		if (count < loc.size()) minV = midV + 0.00001;
		else
		{	// 길이가 충분했을 경우(모든 기지 방문된 경우) 왼쪽 범위 탐색
			// answer 최소값 갱신
			if (answer == -1 || answer > midV) answer = midV;
			maxV = midV - 0.00001;
		}
	}
	// 문제 조건에 따라 반올림(소수점 셋째자리 반올림)
	answer = round(answer * 100) / 100;
	return answer;
}

int main()
{
	int C;
	cin >> C;

	vector<double> answer;

	for (int i = 0; i < C; i++)
	{
		int N;
		cin >> N;

		vector<vector<double>> loc(N, vector<double>(2, 0));

		for (int j = 0; j < N; j++)
		{
			cin >> loc[j][0] >> loc[j][1];
		}

		answer.push_back(solution(loc));
	}

	for (int i = 0; i < answer.size(); i++) printf("%.2lf\n", answer[i]);
	return 0;
}