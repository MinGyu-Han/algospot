#include <iostream>
#include <vector>
#include <climits>
#include <map>
#include <set>
using namespace std;


bool dfs(vector<bool>& visited, map<int, vector<int>>& mM, vector<int>& A, vector<int>& B, int a)
{
	visited[a] = true; //�湮 ǥ��
	for (int i = 0; i < mM[a].size(); i++)
	{
		int b = mM[a][i]; // ���� ������ ������
		// �������� ����� ������ ���ų�
		// �������� ������ ���� ������� �ٸ� �������� �����ϵ��� �ٲ� �� �ִ� ���(�̹� ���� �̹湮 �����) 
		// �������� ����� ���� ���� �� ���� ���� ����
		if (B[b] == -1 || !visited[B[b]] && dfs(visited, mM, A, B, B[b]))
		{
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	// ���� ����
	return false;
}

int solution(vector<vector<int>> board, int P1, int P2)
{
	int result = 0;

	map<int, vector<int>> mM;

	// ������ �湮 ǥ�ÿ� bool�� ����
	vector<bool> visited(board.size() * board[0].size(), false);
	// ������� ����� ������ ǥ��
	vector<int> A(board.size() * board[0].size(), -1);
	// �������� ����� ����� ǥ��
	vector<int> B(board.size() * board[0].size(), -1);

	int totalFlow = 0;	// 2�� ����� ���� ������ ����� ��
	int targetCount = 0;	// �����ؾ��ϴ� Ÿ�� �� 
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			if (board[i][j] == 0)
			{
				targetCount++;

				// �̺� ��Ī�� ����� �׷찣 ������ ����� �ϸ�, ������ �׷� �� ������ ����� ��
				// ���� Ÿ�� �� ������� i%2 == j%2, �������� i%2 != j%2 ������ ������Ű�� �� ������ ����
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
		if (A[iter->first] == -1) // ���� ���� �ȵ� ����� �� ��� Ž��
		{
			vector<bool> nVisited = visited;	// �̹� ���� �湮 üũ �ʱ�ȭ
			if (dfs(nVisited, mM, A, B, iter->first)) totalFlow++;	// ���� �߰� ���� ������ ��� 2Ÿ�� ���� +1
		}
	}
	if (2 * P1 <= P2) result = targetCount * P1;	// P1�� �� �θ� �׳� P1���� ä��� ��
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