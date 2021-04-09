#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

bool compare(vector<int> a, vector<int> b)
{
	return a[1] > b[1];
}

int solution(vector<vector<vector<int>>> bookStores)
{
	int answer = INT_MAX;

	for (int i = 0; i < bookStores.size(); i++)
	{
		// �� ������ ����Ʈ �������� ����
		sort(bookStores[i].begin(), bookStores[i].end(), compare);

		int tmpAnswer = 0;
		int tmpBonus = 0;
		for (int j = 0; j < bookStores[i].size(); j++)
		{
			// å���� ��� �ݾ׿� ����
			tmpAnswer += bookStores[i][j][0];
			// min(�������ִ�����Ʈ, å��) ��ŭ ��� �ݾ׿��� ��
			tmpAnswer -= min(tmpBonus, bookStores[i][j][0]);
			// ����Ʈ�� ����� ��ŭ ��
			tmpBonus -= min(tmpBonus, bookStores[i][j][0]);
			// å ���� �� ����Ʈ ����
			tmpBonus += bookStores[i][j][1];
		}
		answer = min(answer, tmpAnswer); // �ּ� �ݾ� ��� ����
	}
	return answer;
}

int main()
{
	vector<int> answer;
	int C;
	cin >> C;
	for (int i = 0; i < C; i++)
	{
		int N, M;
		cin >> N >> M;
		vector<vector<vector<int>>> bookStores(M, vector<vector<int>>(N, vector<int>(2, 0)));

		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				cin >> bookStores[k][j][0] >> bookStores[k][j][1];
			}
		}
		answer.push_back(solution(bookStores));
	}
	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;
	return 0;
}