#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int solution(vector<int> arr)
{
	int result = INT_MIN;

	vector<int> dp(arr.size(), INT_MIN);
	dp[0] = arr[0];

	for (int i = 1; i < arr.size(); i++)
	{
		dp[i] = max(dp[i - 1] + arr[i], arr[i]);
		result = max(dp[i], result);
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
		int N;
		cin >> N;
		vector<int> arr(N, 0);
		for (int j = 0; j < N; j++) cin >> arr[j];
		answer.push_back(solution(arr));
	}
	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;
	return 0;
}