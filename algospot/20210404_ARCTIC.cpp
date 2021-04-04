#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

double solution(vector<vector<double>>& loc)
{
	double answer = -1;

	// �湮���� Ȯ�ο� base
	vector<bool> visited(loc.size(), true);

	// �̺�Ž�� ����
	double minV = 0;	// �ּҰ�
	double maxV = 1000 * sqrt(2);	// �ִ밪(��ǥ�� 0~1000 ������..)

	while (minV <= maxV)
	{
		double midV = (maxV + minV) / 2;

		// BFS�� ���� Ž�� 
		vector<bool> curVisited = visited;

		queue<int> mQ;
		// ����(index 0) ó�� �湮
		mQ.push(0);
		int count = 0;

		while (!mQ.empty())
		{
			int idx = mQ.front();
			mQ.pop();

			// �̹� �湮�� ������ ����
			if (curVisited[idx] != true) continue;
			count++;	// �湮 ������ ī��Ʈ
			curVisited[idx] = false;	// �湮���� ǥ��

			for (int i = 0; i < loc.size(); i++)
			{
				// �̹� �湮�� ������ ����
				if (curVisited[i] == false) continue;

				double a = abs(loc[idx][0] - loc[i][0]);
				double b = abs(loc[idx][1] - loc[i][1]);
				if (sqrt(a * a + b * b) <= midV)
				{	// idx, i ������ �Ÿ��� midV ���ϸ� ť�� ����
					mQ.push(i);
				}
			}
		}

		// ���̰� �������� ��� ������ ���� Ž��
		if (count < loc.size()) minV = midV + 0.00001;
		else
		{	// ���̰� ������� ���(��� ���� �湮�� ���) ���� ���� Ž��
			// answer �ּҰ� ����
			if (answer == -1 || answer > midV) answer = midV;
			maxV = midV - 0.00001;
		}
	}
	// ���� ���ǿ� ���� �ݿø�(�Ҽ��� ��°�ڸ� �ݿø�)
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