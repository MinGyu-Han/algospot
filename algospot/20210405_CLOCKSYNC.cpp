#include <iostream>
#include <vector>

using namespace std;

void solution(vector<int>& clocks, vector<vector<int>>& connect, int idx, int count, int& tmpAnswer)
{
	// 이미 있는 답보다 스위치 조작 횟수가 많으면 종료
	if (tmpAnswer != -1 && count >= tmpAnswer) return;

	bool check = true;
	for (int i = 0; i < clocks.size(); i++)
	{
		if (clocks[i] != 0)
		{
			check = false;
			break;
		}
	}
	if (check)	// 모두 12시를 가리키면 답 저장
	{
		tmpAnswer = count;
		return;
	}
	if (idx > connect.size() - 1) return;	//범위 초과시 종료


	// 0번 눌렀을 때
	solution(clocks, connect, idx + 1, count, tmpAnswer);

	// 1번 눌렀을 때
	for (int i = 0; i < connect[idx].size(); i++)
	{
		clocks[connect[idx][i]] = (clocks[connect[idx][i]] + 1) % 4;
	}
	solution(clocks, connect, idx + 1, count + 1, tmpAnswer);

	// 2번 눌렀을 때
	for (int i = 0; i < connect[idx].size(); i++)
	{
		clocks[connect[idx][i]] = (clocks[connect[idx][i]] + 1) % 4;
	}
	solution(clocks, connect, idx + 1, count + 2, tmpAnswer);

	// 3번 눌렀을 때
	for (int i = 0; i < connect[idx].size(); i++)
	{
		clocks[connect[idx][i]] = (clocks[connect[idx][i]] + 1) % 4;
	}
	solution(clocks, connect, idx + 1, count + 3, tmpAnswer);

	// 원래대로 돌림
	for (int i = 0; i < connect[idx].size(); i++)
	{
		clocks[connect[idx][i]] = (clocks[connect[idx][i]] + 1) % 4;
	}
}

int main()
{
	int C;

	vector<int> answer;

	cin >> C;

	for (int i = 0; i < C; i++)
	{
		vector<int> clocks(16, 0);
		for (int j = 0; j < 16; j++)
		{
			int tmp;
			cin >> tmp;

			tmp /= 3;
			clocks[j] = tmp % 4;

		}

		vector<vector<int>> connect;
		connect.push_back(vector<int>({ 0, 1, 2 }));
		connect.push_back(vector<int>({ 3, 7, 9, 11 }));
		connect.push_back(vector<int>({ 4, 10, 14, 15 }));
		connect.push_back(vector<int>({ 0, 4, 5, 6, 7 }));
		connect.push_back(vector<int>({ 6, 7, 8, 10, 12 }));
		connect.push_back(vector<int>({ 0, 2, 14, 15 }));
		connect.push_back(vector<int>({ 3, 14, 15 }));
		connect.push_back(vector<int>({ 4, 5, 7, 14, 15 }));
		connect.push_back(vector<int>({ 1, 2, 3, 4, 5 }));
		connect.push_back(vector<int>({ 3, 4, 5, 9, 13 }));

		int tmpAnswer = -1;
		solution(clocks, connect, 0, 0, tmpAnswer);

		answer.push_back(tmpAnswer);
	}

	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;

	return 0;
}