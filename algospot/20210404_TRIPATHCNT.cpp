#include <iostream>
#include <vector>
using namespace std;

int solution(vector<vector<int>> triangle)
{
	int answer = 0;

	vector<vector<vector<int>>> nTri(triangle.size(), vector<vector<int>>(triangle.size(), vector<int>(2, 0)));

	for (int i = 0; i < triangle.size(); i++)
	{
		for (int j = 0; j <= i; j++)
		{
			// ����� ���� �����ϱ� ���� Ȯ��
			nTri[i][j][0] = triangle[i][j];
			nTri[i][j][1] = 0;
		}
	}
	// 0, 0�� ����� ��1
	nTri[0][0][1] = 1;

	for (int i = 1; i < nTri.size(); i++)
	{
		// �� ���� ���� ������ ������ ���ۿ� �����Ƿ� �̸� ���
		nTri[i][0][0] += nTri[i - 1][0][0];
		nTri[i][0][1] = nTri[i - 1][0][1];

		for (int j = 1; j <= i; j++)
		{
			// �� ������ ���̰ų� ���� ���� �� ������ ũ�� 
			// i-1, j-1���� ������
			if (j == i || nTri[i - 1][j - 1][0] > nTri[i - 1][j][0])
			{
				nTri[i][j][0] += nTri[i - 1][j - 1][0];
				nTri[i][j][1] = nTri[i - 1][j - 1][1];
			}
			// ���� ���� �� ������ ������
			// i-1, j���� ������
			else if (nTri[i - 1][j - 1][0] < nTri[i - 1][j][0])
			{
				nTri[i][j][0] += nTri[i - 1][j][0];
				nTri[i][j][1] = nTri[i - 1][j][1];
			}
			// ���� ���� �� ���� ���� ���
			// (i-1, j-1), (i-1, j) �� �� max ���̹Ƿ� �Ѵ� ������(����� �� ����)
			else if (nTri[i - 1][j - 1][0] == nTri[i - 1][j][0])
			{
				nTri[i][j][0] += nTri[i - 1][j][0];
				nTri[i][j][1] = nTri[i - 1][j - 1][1] + nTri[i - 1][j][1];
			}
		}
	}
	int max = -1;
	for (int i = 0; i < nTri[nTri.size() - 1].size(); i++)
	{
		// max���� ���ŵ� ��� ����� �� ����
		if (max < nTri[nTri.size() - 1][i][0])
		{
			answer = nTri[nTri.size() - 1][i][1];
			max = nTri[nTri.size() - 1][i][0];
		}
		// ������ max���� ��� ����� �� ����
		else if (max == nTri[nTri.size() - 1][i][0])
		{
			answer += nTri[nTri.size() - 1][i][1];
		}
	}
}
return answer;
}

int main()
{
	int C;
	cin >> C;
	vector<int> answer;

	for (int i = 0; i < C; i++)
	{
		int n;
		cin >> n;
		vector<vector<int>> triangle(n, vector<int>(n, 0));

		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k <= j; k++)
			{
				cin >> triangle[j][k];
			}
		}
		answer.push_back(solution(triangle));
	}

	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;

	return 0;
}