#include <iostream>
#include <vector>
using namespace std;

int findAnswer(vector<int>& coins, vector<vector<int>>& dp, int remainM, int idx)
{
	if (remainM == 0) return 1;	// 환전에 성공했으면 1 리턴
	if (idx > coins.size() - 1) return 0; // 범위 초과시(환전 미성공) 0 리턴
	if (dp[idx][remainM] != -1) return dp[idx][remainM]; // 이미 계산된 값 있으면 해당 값 리턴

	dp[idx][remainM] = 0;
	int i = 0;
	while (coins[idx] * i <= remainM)
	{
		// 남은 돈(remainM)에 대해서 다음 동전부터 경우의 수 구하여 합산
		dp[idx][remainM] = (dp[idx][remainM] + findAnswer(coins, dp, remainM - coins[idx] * i, idx + 1)) % 1000000007;
		i++;
	}
	return dp[idx][remainM];

}

int solution(vector<int> coins, int M)
{
	int result = 0;

	vector<vector<int>> dp(coins.size(), vector<int>(M + 1, -1));

	result = findAnswer(coins, dp, M, 0);

	return result;
}

int main()
{
	vector<int> answer;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int M, C;
		cin >> M >> C;
		vector<int> coins(C, 0);
		for (int j = 0; j < C; j++)
		{
			cin >> coins[j];
		}
		answer.push_back(solution(coins, M));
	}
	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;
	return 0;
}