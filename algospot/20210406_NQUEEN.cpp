#include<iostream>
#include<vector>
using namespace std;


int solution(int idx, vector<int>& chess, int& N)
{
	// ������ ���� �� �������� 1 ����
	if (idx > N - 1) return 1;

	int result = 0;

	for (int i = 0; i < N; i++)
	{
		int check = true;
		for (int j = 0; j < idx; j++)	// idx ���� ��������� ��
		{
			// �̹� ���� ���̰ų�, ���Ⱑ 1(�밢������ ���� ����)�̸�
			// ���� �� ����
			if (i == chess[j] || abs(idx - j) == abs(i - chess[j]))
			{
				check = false;
				break;
			}
		}
		if (check)	// ���� �� ���� ��� dfs ����
		{
			chess[idx] = i;
			result += solution(idx + 1, chess, N);
		}
	}

	return result;
}

int main()
{
	int C;
	cin >> C;
	vector<int> answer;

	for (int i = 0; i < C; i++)
	{
		int N;
		cin >> N;
		vector<int> chess(N, 0);
		answer.push_back(solution(0, chess, N));
	}
	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;


	return 0;
}