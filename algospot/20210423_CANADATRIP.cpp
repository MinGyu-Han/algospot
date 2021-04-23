#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 표지판 시작 위치 기준 오름차순 정렬
bool compare(vector<int> a, vector<int> b)
{
	return a[0] - a[1] < b[0] - b[1];
}

int main()
{
	vector<int> answer;
	int T;
	cin >> T;

	for (int i = 0; i < T; i++)
	{
		int N, K;
		cin >> N >> K;
		vector<vector<int>> data(N, vector<int>(3, 0));
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < 3; k++) cin >> data[j][k];
		}

		sort(data.begin(), data.end(), compare);

		// 이분 탐색 범위. max 값은 문제에서 주어짐
		int minV = 0;
		int maxV = 8030000;

		while (minV <= maxV)
		{
			int midV = (minV + maxV) / 2;
			int count = 0; // midV 까지의 표지판 개수

			for (int j = 0; j < data.size(); j++)
			{
				// 표지판 시작 위치
				int start = data[j][0] - data[j][1];
				// 표지판 시작 위치가 midV 이후면 반복문 중지
				if (start > midV) break;
				// 도시 위치가 midV보다 먼 경우 midV까지만 샘
				int last = min(data[j][0], midV);
				// 표지판 시작 위치에도 표지판을 둬야해서 +1 처리
				count += (last - start) / data[j][2] + 1;
			}
			// 표지판 개수가 부족하면 오른쪽 범위 탐색
			if (count < K) minV = midV + 1;
			// 충분하면 왼쪽 범위 탐색
			else maxV = midV - 1;
		}

		answer.push_back(minV);
	}
	for (int ans : answer) cout << ans << endl;

	return 0;
}