#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

bool checkEnable(const vector<vector<int>>& vMap, const vector<int>& tmp)
{
	return tmp[1] >= 0 && tmp[2] >= 0 && tmp[2] < vMap[0].size() && tmp[1] < vMap.size() && vMap[tmp[1]][tmp[2]] != 1;
}


int solution(vector<vector<int>> vMap)
{
	int result = 0;

	vector<int> cur({ 0, (int)vMap.size() - 1, 0 });
	set<vector<int>> mS;
	queue<vector<int>> mQ;

	mQ.push(vector<int>({ 0, (int)vMap.size() - 1, 0 }));
	// 상태는 0:땅에 있는 상태, 1:1점프 중, 2:하락 중(1점프), 3:2점프 중, 4:하락 중(2점프)

	while (!mQ.empty())
	{
		result++;
		int qSize = mQ.size();
		for (int i = 0; i < qSize; i++)
		{
			vector<int> cur = mQ.front();

			mQ.pop();
			if (mS.find(cur) != mS.end()) continue;
			if (cur[0] == 3 || cur[1] == 4)
			{
				if (mS.find(vector<int>({ cur[0] - 2, cur[1], cur[2] })) != mS.end()) continue;
			}
			mS.insert(cur);

			vector<int> tmp;
			if (cur[0] == 0) // 땅에 있는 상태
			{
				// 그대로 전진
				tmp = cur;
				tmp[2]++;
				if (checkEnable(vMap, tmp)) mQ.push(tmp);
				// 점프
				tmp = cur;
				tmp[2]++;
				tmp[1]--;
				tmp[0] = 1;
				if (checkEnable(vMap, tmp)) mQ.push(tmp);
			}
			else if (cur[0] == 1 || cur[0] == 3) // 1, 3점프 중
			{
				if (cur[1] > 0) // 천장에 안닿은 상태
				{
					tmp = cur;
					tmp[1]--;
					tmp[2]++;
					if (checkEnable(vMap, tmp)) mQ.push(tmp);
				}
				else // 천장에 닿은 상태
				{
					tmp = cur;
					tmp[1]++;
					tmp[2]++;
					if (cur[0] == 1) tmp[0] = 2;
					else tmp[0] = 4;
					if (checkEnable(vMap, tmp)) mQ.push(tmp);
				}
			}
			else if (cur[0] == 2 || cur[0] == 4) // 하락 중(1점프)
			{
				// 바닥에 닿은 경우
				if (cur[1] == vMap.size() - 1)
				{
					tmp = cur;
					// 그대로 전진
					tmp[0] = 0;
					tmp[2]++;
					if (checkEnable(vMap, tmp)) mQ.push(tmp);
					// 점프
					tmp = cur;
					tmp[0] = 1;
					tmp[1]--;
					tmp[2]++;
					if (checkEnable(vMap, tmp)) mQ.push(tmp);
				}
				else
				{
					// 그대로 하락
					tmp = cur;
					tmp[1]++;
					tmp[2]++;
					if (checkEnable(vMap, tmp)) mQ.push(tmp);

					// 2단 점프
					if (cur[0] != 4)
					{
						tmp = cur;
						tmp[0] = 3;
						tmp[1]--;
						tmp[2]++;
						if (checkEnable(vMap, tmp)) mQ.push(tmp);
					}
				}
			}
		}
	}

	return result;
}

int main()
{
	int M;
	cin >> M;

	vector<int> answer;

	for (int i = 0; i < M; i++)
	{
		int W, H;
		cin >> W >> H;
		vector<vector<int>> vMap(H, vector<int>(W, 0));

		for (int j = 0; j < H; j++)
		{
			for (int k = 0; k < W; k++)
			{
				char c;
				cin >> c;
				if (c == '#') vMap[j][k] = 1;
			}
		}
		answer.push_back(solution(vMap));
	}

	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;
	return 0;
}