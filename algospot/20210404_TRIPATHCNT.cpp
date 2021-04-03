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
			// 경우의 수를 저장하기 위해 확장
			nTri[i][j][0] = triangle[i][j];
			nTri[i][j][1] = 0;
		}
	}
	// 0, 0은 경우의 수1
	nTri[0][0][1] = 1;

	for (int i = 1; i < nTri.size(); i++)
	{
		// 맨 왼쪽 값은 위에서 내려올 수밖에 없으므로 미리 계산
		nTri[i][0][0] += nTri[i - 1][0][0];
		nTri[i][0][1] = nTri[i - 1][0][1];

		for (int j = 1; j <= i; j++)
		{
			// 맨 오른쪽 값이거나 위왼 값이 위 값보다 크면 
			// i-1, j-1에서 내려옴
			if (j == i || nTri[i - 1][j - 1][0] > nTri[i - 1][j][0])
			{
				nTri[i][j][0] += nTri[i - 1][j - 1][0];
				nTri[i][j][1] = nTri[i - 1][j - 1][1];
			}
			// 위왼 값이 위 값보다 작으면
			// i-1, j에서 내려옴
			else if (nTri[i - 1][j - 1][0] < nTri[i - 1][j][0])
			{
				nTri[i][j][0] += nTri[i - 1][j][0];
				nTri[i][j][1] = nTri[i - 1][j][1];
			}
			// 위왼 값과 위 값이 같을 경우
			// (i-1, j-1), (i-1, j) 둘 다 max 값이므로 둘다 내려옴(경우의 수 더함)
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
		// max값이 갱신될 경우 경우의 수 갱신
		if (max < nTri[nTri.size() - 1][i][0])
		{
			answer = nTri[nTri.size() - 1][i][1];
			max = nTri[nTri.size() - 1][i][0];
		}
		// 동일한 max값일 경우 경우의 수 더함
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