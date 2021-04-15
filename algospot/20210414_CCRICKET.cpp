#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <set>
using namespace std;


bool dfs(vector<bool>& visited, map<int, vector<int>>& mM, vector<int>& A, vector<int>& B, int a)
{
	visited[a] = true; //방문 표시
	for (int i = 0; i < mM[a].size(); i++)
	{
		int b = mM[a][i]; // 연결 가능한 목적지
		// 목적지에 연결된 간선이 없거나
		// 목적지에 연결한 이전 출발지를 다른 목적지를 선택하도록 바꿀 수 있는 경우(이번 차수 미방문 출발지) 
		// 목적지에 연결된 간선 갱신 후 선택 성공 리턴
		if (B[b] == -1 || !visited[B[b]] && dfs(visited, mM, A, B, B[b]))
		{
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	// 선택 실패
	return false;
}

int solution(vector<vector<int>> board, int P1, int P2)
{
	int result = 0;

	map<int, vector<int>> mM;

	// 차수별 방문 표시용 bool형 벡터
	vector<bool> visited(board.size() * board[0].size(), false);
	// 출발지에 연결된 목적지 표시
	vector<int> A(board.size() * board[0].size(), -1);
	// 목적지에 연결된 출발지 표시
	vector<int> B(board.size() * board[0].size(), -1);

	int totalFlow = 0;	// 2개 블록을 선택 가능한 경우의 수
	int targetCount = 0;	// 수리해야하는 타일 수 
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == 0)
			{
				targetCount++;

				// 이분 매칭은 출발지 그룹간 간선이 없어야 하며, 목적지 그룹 간 간선이 없어야 함
				// 격자 타일 내 출발지는 i%2 == j%2, 목적지는 i%2 != j%2 성질을 만족시키면 위 조건이 만족
				if (i % 2 == j % 2)
				{
					if (i > 0 && board[i - 1][j] == 0)
					{
						if (mM.find(i * board[0].size() + j) == mM.end()) mM[i * board[0].size() + j] = vector<int>();
						mM[i * board[0].size() + j].push_back((i - 1) * board[0].size() + j);
					}
					if (j > 0 && board[i][j - 1] == 0)
					{
						if (mM.find(i * board[0].size() + j) == mM.end()) mM[i * board[0].size() + j] = vector<int>();
						mM[i * board[0].size() + j].push_back(i * board[0].size() + (j - 1));
					}
					if (i < board.size() - 1 && board[i + 1][j] == 0)
					{
						if (mM.find(i * board[0].size() + j) == mM.end()) mM[i * board[0].size() + j] = vector<int>();
						mM[i * board[0].size() + j].push_back((i + 1) * board[0].size() + j);
					}
					if (j < board[0].size() - 1 && board[i][j + 1] == 0)
					{
						if (mM.find(i * board[0].size() + j) == mM.end()) mM[i * board[0].size() + j] = vector<int>();
						mM[i * board[0].size() + j].push_back(i * board[0].size() + (j + 1));
					}
				}
			}
		}
	}
	for (map<int, vector<int>>::iterator iter = mM.begin(); iter != mM.end(); iter++)
	{
		if (A[iter->first] == -1) // 아직 선택 안된 출발지 일 경우 탐색
		{
			vector<bool> nVisited = visited;	// 이번 차수 방문 체크 초기화
			if (dfs(nVisited, mM, A, B, iter->first)) totalFlow++;	// 간선 추가 선택 가능한 경우 2타일 수량 +1
		}
	}
	if (2 * P1 <= P2) result = targetCount * P1;	// P1이 더 싸면 그냥 P1으로 채우면 됨
	else result = totalFlow * P2 + (targetCount - 2 * totalFlow) * P1;

	return result;
}

int main()
{
	int T;
	vector<int> answer;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int N, M, P1, P2;
		cin >> N >> M >> P1 >> P2;
		vector<vector<int>> board(N, vector<int>(M, 0));
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				char a;
				cin >> a;
				if (a == '0') board[j][k] = 0;
				else board[j][k] = 1;
			}
		}
		answer.push_back(solution(board, P1, P2));
	}
	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;

	return 0;
}