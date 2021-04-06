#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(vector<int> a, vector<int> b)
{
	if (a[0] < b[0]) return true;
	else if (a[0] > b[0]) return false;

	return a[1] < b[1];
}

vector<int> solution(vector<int> dolls, int m)
{
	vector<int> answer(dolls.size(), 0);

	// dolls를 개수 오름차순으로 정렬하기 위해 idx값 추가 저장
	vector<vector<int>> nDolls(dolls.size(), vector<int>(2, 0));
	for (int i = 0; i < dolls.size(); i++)
	{
		nDolls[i][0] = dolls[i];
		nDolls[i][1] = i;
	}
	// 개수 오름차순, idx 오름차순 정렬
	sort(nDolls.begin(), nDolls.end(), compare);

	int remainM = m;
	int choice = m / nDolls.size();
	int remainDoll = nDolls.size();


	// 추가로 뽑아야 할 인형의 개수가 남은 dolls의 가지수보다 크면 반복문 수행
	int j = 0;
	while (remainDoll < remainM)
	{
		for (int i = j; i < nDolls.size(); i++)
		{
			if (nDolls[i][0] == 0) continue; // 해당 인형이 없으면 패스
			if (nDolls[i][0] <= choice)	// 뽑으려고 계획한 수보다 인형이 작거나 같으면
			{
				remainM -= nDolls[i][0];	// 있는 만큼 다 뽑음
				answer[nDolls[i][1]] += nDolls[i][0];
				nDolls[i][0] = 0;
				remainDoll--;	// 남은 인형의 가지수 감소
				j++;
			}
			else
			{
				remainM -= choice;	// 인형을 계획한 만큼 뽑음
				answer[nDolls[i][1]] += choice;
				nDolls[i][0] -= choice;
			}
		}
		choice = remainM / remainDoll;	// 새로 계획
	}
	int i = 0;

	// 남은 인형 마저 뽑음
	while (remainM > 0)
	{
		if (answer[i] < dolls[i])
		{
			answer[i]++;
			remainM--;
		}
		i++;
	}

	return answer;
}

int main()
{
	vector<vector<int>> answer;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int n, m;
		cin >> n >> m;
		vector<int> dolls(n, 0);

		for (int j = 0; j < n; j++)
		{
			cin >> dolls[j];
		}
		answer.push_back(solution(dolls, m));

	}
	for (int i = 0; i < answer.size(); i++)
	{
		for (int j = 0; j < answer[i].size(); j++)
		{
			cout << answer[i][j];
			if (j != answer[i].size() - 1) cout << " ";
		}
		cout << endl;
	}
	return 0;
}