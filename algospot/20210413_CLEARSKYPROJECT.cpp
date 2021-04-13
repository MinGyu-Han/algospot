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

	// dp[i][j] = k번 쏴서 j개의 구름을 없애는 최소한의 비용
	vector<vector<int>> dp(K + 1, vector<int>(cloud.size() + 1, INT_MAX));

	dp[0][0] = 0;
	for (int i = 1; i <= K; i++)
	{
		for (int j = 0; j < cloud.size(); j++)
		{
			if (dp[i - 1][j] != INT_MAX)
			{
				// j번째까지 없앴으므로 j+1번째 구름을 기준으로 시작
				int count = 0;
				int start = cloud[j][0];
				int end = cloud[j][1];

				for (int k = j; k < cloud.size(); k++)
				{
					// start와 다음 구름의 left가 같으면 분리해서 없앨 수 없으므로 count만 +1
					if (start == cloud[k][0]) count++;
					else
					{
						// start와 다름 구름의 left가 다르면 분리해서 없앨 수 있으므로,
						// 이전까지의 최소비용인 start에서 너덜포를 쏨
						dp[i][j + count] = min(dp[i][j + count], dp[i - 1][j] + start * count);
						// start를 옮김
						start = cloud[k][0];
						// 만일 end가 더 작다면, 갱신
						if (end > cloud[k][1]) end = cloud[k][1];
						count++;
					}
					// 마지막 구름이거나, 다음 구름은 k번째 총으로 함께 없앨 수 없을 경우
					if (k == cloud.size() - 1 || end < cloud[k + 1][0])
					{
						// 현재 저장된 start 기준으로 총을 쏨
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