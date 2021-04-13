#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

bool compare(vector<int> a, vector<int> b)
{
	if (a[0] < b[0]) return true;
	else if (a[0] > b[0]) return false;
	return a[1] < b[1];
}

int solution(vector<vector<int>> cloud, int K)
{
	int result = INT_MAX;
	sort(cloud.begin(), cloud.end(), compare);

	// dp[i][j] = k�� ���� j���� ������ ���ִ� �ּ����� ���
	vector<vector<int>> dp(K + 1, vector<int>(cloud.size() + 1, INT_MAX));

	dp[0][0] = 0;
	for (int i = 1; i <= K; i++)
	{
		for (int j = 0; j < cloud.size(); j++)
		{
			if (dp[i - 1][j] != INT_MAX)
			{
				// j��°���� �������Ƿ� j+1��° ������ �������� ����
				int count = 0;
				int start = cloud[j][0];
				int end = cloud[j][1];

				for (int k = j; k < cloud.size(); k++)
				{
					// start�� ���� ������ left�� ������ �и��ؼ� ���� �� �����Ƿ� count�� +1
					if (start == cloud[k][0]) count++;
					else
					{
						// start�� �ٸ� ������ left�� �ٸ��� �и��ؼ� ���� �� �����Ƿ�,
						// ���������� �ּҺ���� start���� �ʴ����� ��
						dp[i][j + count] = min(dp[i][j + count], dp[i - 1][j] + start * count);
						// start�� �ű�
						start = cloud[k][0];
						// ���� end�� �� �۴ٸ�, ����
						if (end > cloud[k][1]) end = cloud[k][1];
						count++;
					}
					// ������ �����̰ų�, ���� ������ k��° ������ �Բ� ���� �� ���� ���
					if (k == cloud.size() - 1 || end < cloud[k + 1][0])
					{
						// ���� ����� start �������� ���� ��
						dp[i][j + count] = min(dp[i][j + count], dp[i - 1][j] + start * count);
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i <= K; i++)
	{
		result = min(result, dp[i][cloud.size()]);
	}
	return result;
}

int main()
{
	int T;
	cin >> T;
	vector<int> answer;
	for (int i = 0; i < T; i++)
	{
		int N, K;
		cin >> N >> K;
		vector<vector<int>> cloud(N, vector<int>(2, 0));
		for (int j = 0; j < N; j++)
		{
			cin >> cloud[j][0] >> cloud[j][1];
		}
		answer.push_back(solution(cloud, K));
	}
	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;
	return 0;
}