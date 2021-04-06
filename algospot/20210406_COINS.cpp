#include <iostream>
#include <vector>
using namespace std;

int findAnswer(vector<int>& coins, vector<vector<int>>& dp, int remainM, int idx)
{
	if (remainM == 0) return 1;	// ȯ���� ���������� 1 ����
	if (idx > coins.size() - 1) return 0; // ���� �ʰ���(ȯ�� �̼���) 0 ����
	if (dp[idx][remainM] != -1) return dp[idx][remainM]; // �̹� ���� �� ������ �ش� �� ����

	dp[idx][remainM] = 0;
	int i = 0;
	while (coins[idx] * i <= remainM)
	{
		// ���� ��(remainM)�� ���ؼ� ���� �������� ����� �� ���Ͽ� �ջ�
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