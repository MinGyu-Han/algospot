#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ǥ���� ���� ��ġ ���� �������� ����
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

		// �̺� Ž�� ����. max ���� �������� �־���
		int minV = 0;
		int maxV = 8030000;

		while (minV <= maxV)
		{
			int midV = (minV + maxV) / 2;
			int count = 0; // midV ������ ǥ���� ����

			for (int j = 0; j < data.size(); j++)
			{
				// ǥ���� ���� ��ġ
				int start = data[j][0] - data[j][1];
				// ǥ���� ���� ��ġ�� midV ���ĸ� �ݺ��� ����
				if (start > midV) break;
				// ���� ��ġ�� midV���� �� ��� midV������ ��
				int last = min(data[j][0], midV);
				// ǥ���� ���� ��ġ���� ǥ������ �־��ؼ� +1 ó��
				count += (last - start) / data[j][2] + 1;
			}
			// ǥ���� ������ �����ϸ� ������ ���� Ž��
			if (count < K) minV = midV + 1;
			// ����ϸ� ���� ���� Ž��
			else maxV = midV - 1;
		}

		answer.push_back(minV);
	}
	for (int ans : answer) cout << ans << endl;

	return 0;
}