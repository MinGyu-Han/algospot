#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

void preOrderCamp(vector<vector<int>>& range, vector<vector<int>>& peoples, int idx, int& count)
{
	range[idx][0] = count++;

	for (int i = 0; i < peoples[idx].size(); i++)
	{
		preOrderCamp(range, peoples, peoples[idx][i], count);
	}
	range[idx][1] = count - 1;
}

int init(int start, int end, int node, vector<int>& tree, vector<int>& checkRange)
{
	if (start == end) return tree[node] = checkRange[start];
	int mid = (start + end) / 2;

	return tree[node] = init(start, mid, node * 2, tree, checkRange) + init(mid + 1, end, node * 2 + 1, tree, checkRange);
}

int sum(int start, int end, int node, int left, int right, vector<int>& tree)
{
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	return sum(start, mid, node * 2, left, right, tree) + sum(mid + 1, end, node * 2 + 1, left, right, tree);
}

void update(int start, int end, int node, int idx, int newValue, vector<int>& tree)
{
	if (idx < start || idx > end) return;

	if (newValue == 0) tree[node]--;
	else tree[node]++;

	if (start == end) return;
	int mid = (start + end) / 2;
	update(start, mid, node * 2, idx, newValue, tree);
	update(mid + 1, end, node * 2 + 1, idx, newValue, tree);
}


int main()
{
	int T;
	cin >> T;
	vector<string> answer;

	for (int i = 0; i < T; i++)
	{
		int N, Q;

		cin >> N >> Q;

		vector<vector<int>> peoples(N + 1, vector<int>());
		vector<int> camp(N + 1, 0);

		for (int j = 0; j < N - 2; j++)
		{
			int a, b;
			cin >> a >> b;
			peoples[a].push_back(b);

		}

		vector<vector<int>> range(N + 1, vector<int>(2, 0));
		vector<int> checkRange(N, 0);
		vector<int> tree(N * 4, 0);

		int count = 0;
		preOrderCamp(range, peoples, 1, count);

		checkRange[count] = 1;
		preOrderCamp(range, peoples, 2, count);

		init(0, checkRange.size() - 1, 1, tree, checkRange);
		for (int j = 0; j < Q; j++)
		{
			char c;
			int a, b;
			cin >> c;
			if (c == 'T')
			{
				cin >> a;

				checkRange[range[a][0]] = (checkRange[range[a][0]] + 1) % 2;
				update(0, checkRange.size() - 1, 1, range[a][0], checkRange[range[a][0]], tree);

				if (range[a][1] < checkRange.size() - 1)
				{
					checkRange[range[a][1] + 1] = (checkRange[range[a][1] + 1] + 1) % 2;
					update(0, checkRange.size() - 1, 1, range[a][1] + 1, checkRange[range[a][1] + 1], tree);
				}
			}
			else
			{
				cin >> a >> b;

				int left = 0;
				int tmp1 = sum(0, checkRange.size() - 1, 1, 0, range[a][0], tree);
				int tmp2 = sum(0, checkRange.size() - 1, 1, 0, range[b][0], tree);
				if (tmp1 % 2 == tmp2 % 2) answer.push_back("Ally");
				else answer.push_back("Enemy");
			}
		}
	}

	for (int i = 0; i < answer.size(); i++)
	{
		cout << answer[i];
		if (i != answer.size() - 1) cout << endl;
	}
	return 0;
}