#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

// 출발지에 대한 모든 노드의 최단 경로를 구함
vector<int> dijkstra(vector<vector<int>>& nEdge, int start)
{
	vector<int> dis(nEdge.size(), INT_MAX);
	dis[start] = 0;

	priority_queue<pair<int, int>> pQ;

	pQ.push(make_pair(0, start));
	while (!pQ.empty())
	{
		int cost = pQ.top().first;
		int src = pQ.top().second;
		pQ.pop();
		if (dis[src] < cost) continue;
		for (int i = 0; i < nEdge[src].size(); i++)
		{
			int dst = nEdge[src][i];
			if (dis[dst] > cost + 1)
			{
				dis[dst] = cost + 1;
				pQ.push(make_pair(cost + 1, dst));
			}
		}
	}
	return dis;
}

vector<int> solution(int N, vector<vector<int>> edge)
{
	vector<int> answer;

	vector<vector<int>> nEdge(N, vector<int>());	// 정뱡향 길
	vector<vector<int>> rEdge(N, vector<int>());	// 역방향 길

	for (int i = 0; i < edge.size(); i++)
	{
		nEdge[edge[i][0] - 1].push_back(edge[i][1] - 1);
		rEdge[edge[i][1] - 1].push_back(edge[i][0] - 1);
	}

	vector<int> startDis = dijkstra(nEdge, 0);	// 1 -> 전체 노드 거리
	vector<int> dstDis = dijkstra(rEdge, N - 1); // N <- 전체 노드 거리

	int minCost = startDis[N - 1];	// 1 -> N 까지의 최단거리

	for (int i = 0; i < N; i++)
	{
		// [1 -> i] 거리 + [i -> N] 거리의 결과가 1->N의 최단거리면 i를 경유해도 됨
		if (startDis[i] + dstDis[i] == minCost) answer.push_back(i + 1);
	}
	sort(answer.begin(), answer.end());	// 오름차순으로 정렬

	return answer;
}

int main()
{
	vector<vector<int>> answers;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int N, M;
		cin >> N >> M;

		vector<vector<int>> edge(M, vector<int>(2, 0));
		for (int j = 0; j < M; j++)
		{
			cin >> edge[j][0] >> edge[j][1];
		}
		answers.push_back(solution(N, edge));
	}

	for (int i = 0; i < answers.size(); i++)
	{
		for (int j = 0; j < answers[i].size(); j++)
		{
			cout << answers[i][j];
			if (j != answers[i].size() - 1) cout << " ";
		}
		cout << endl;
	}
	return 0;
}