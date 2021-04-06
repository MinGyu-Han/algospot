#include<iostream>
#include<vector>
using namespace std;


int solution(int idx, vector<int>& chess, int& N)
{
	// 끝까지 퀸을 다 놓았으면 1 리턴
	if (idx > N - 1) return 1;

	int result = 0;

	for (int i = 0; i < N; i++)
	{
		int check = true;
		for (int j = 0; j < idx; j++)	// idx 위의 결과까지만 비교
		{
			// 이미 놓인 열이거나, 기울기가 1(대각선으로 공격 가능)이면
			// 놓을 수 없음
			if (i == chess[j] || abs(idx - j) == abs(i - chess[j]))
			{
				check = false;
				break;
			}
		}
		if (check)	// 놓을 수 있을 경우 dfs 수행
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