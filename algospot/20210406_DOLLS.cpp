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

	// dolls�� ���� ������������ �����ϱ� ���� idx�� �߰� ����
	vector<vector<int>> nDolls(dolls.size(), vector<int>(2, 0));
	for (int i = 0; i < dolls.size(); i++)
	{
		nDolls[i][0] = dolls[i];
		nDolls[i][1] = i;
	}
	// ���� ��������, idx �������� ����
	sort(nDolls.begin(), nDolls.end(), compare);

	int remainM = m;
	int choice = m / nDolls.size();
	int remainDoll = nDolls.size();


	// �߰��� �̾ƾ� �� ������ ������ ���� dolls�� ���������� ũ�� �ݺ��� ����
	int j = 0;
	while (remainDoll < remainM)
	{
		for (int i = j; i < nDolls.size(); i++)
		{
			if (nDolls[i][0] == 0) continue; // �ش� ������ ������ �н�
			if (nDolls[i][0] <= choice)	// �������� ��ȹ�� ������ ������ �۰ų� ������
			{
				remainM -= nDolls[i][0];	// �ִ� ��ŭ �� ����
				answer[nDolls[i][1]] += nDolls[i][0];
				nDolls[i][0] = 0;
				remainDoll--;	// ���� ������ ������ ����
				j++;
			}
			else
			{
				remainM -= choice;	// ������ ��ȹ�� ��ŭ ����
				answer[nDolls[i][1]] += choice;
				nDolls[i][0] -= choice;
			}
		}
		choice = remainM / remainDoll;	// ���� ��ȹ
	}
	int i = 0;

	// ���� ���� ���� ����
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