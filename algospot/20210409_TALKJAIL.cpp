#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// �ð� ������ ���Ŀ�
bool compare(vector<unsigned int> a, vector<unsigned int> b)
{
	return a[0] < b[0];
}
// �ε��� ������ ���Ŀ�
bool compare2(vector<unsigned int> a, vector<unsigned int> b)
{
	return a[3] < b[3];
}

vector<unsigned int> solution(vector<vector<unsigned int>> timeTable, int N)
{
	vector<unsigned int> answer;
	sort(timeTable.begin(), timeTable.end(), compare);	// �ð� ������ ����

	map<unsigned int, unsigned int> mM;
	// �� �ο��� ���� �������� ���� �ð� ����
	for (int i = 0; i < timeTable.size(); i++) mM[timeTable[i][1]] = timeTable[i][0];
	vector<unsigned int> peoples;
	for (map<unsigned int, unsigned int>::iterator iter = mM.begin(); iter != mM.end(); iter++)
	{
		peoples.push_back(iter->second);
	}
	sort(peoples.begin(), peoples.end());	// �ο��� ���� �ð��� �ð������� ����

	int i = 0;
	int unknownCount = N - peoples.size();	// �ѹ��� ��ȭ�� ġ�� ���� ������ �ĺ���
	int lastAnswer = 0;
	for (int j = 0; j < timeTable.size(); j++)
	{
		while (timeTable[j][0] > peoples[i])
		{
			unknownCount++;
			i++;
		}
		// �ش� �ð��� �����Ͽ� ���ı��� ä���� ��ģ ������
		// ������ ����� ���� ���ٸ�, �߷� ����
		if (unknownCount == timeTable[j][2])
		{
			timeTable[j][4] = unknownCount;
			lastAnswer = unknownCount;
		}
		// �ƴ϶�� ������ �߷��ߴ� ����� ��ŭ�� �߷� ����
		else timeTable[j][4] = lastAnswer;
	}
	// �ٽ� �ε��� ������ ����
	sort(timeTable.begin(), timeTable.end(), compare2);
	for (int i = 0; i < timeTable.size(); i++) answer.push_back(timeTable[i][4]);
	return answer;
}

int main()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int N, M;
		cin >> N >> M;
		vector<vector<unsigned int>> timeTable(M, vector<unsigned int>(5, 0));

		for (int i = 0; i < M; i++)
		{
			cin >> timeTable[i][0] >> timeTable[i][1] >> timeTable[i][2];
			timeTable[i][3] = i;
		}
		vector<unsigned int> a = solution(timeTable, N);
		cout << "#" << i + 1 << endl;
		for (int j = 0; j < a.size(); j++)
		{
			cout << a[j] << endl;
		}
	}
	return 0;
}