#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// 시간 순으로 정렬용
bool compare(vector<unsigned int> a, vector<unsigned int> b)
{
	return a[0] < b[0];
}
// 인덱스 순으로 정렬용
bool compare2(vector<unsigned int> a, vector<unsigned int> b)
{
	return a[3] < b[3];
}

vector<unsigned int> solution(vector<vector<unsigned int>> timeTable, int N)
{
	vector<unsigned int> answer;
	sort(timeTable.begin(), timeTable.end(), compare);	// 시간 순으로 정렬

	map<unsigned int, unsigned int> mM;
	// 각 인원이 가장 마지막에 나온 시간 저장
	for (int i = 0; i < timeTable.size(); i++) mM[timeTable[i][1]] = timeTable[i][0];
	vector<unsigned int> peoples;
	for (map<unsigned int, unsigned int>::iterator iter = mM.begin(); iter != mM.end(); iter++)
	{
		peoples.push_back(iter->second);
	}
	sort(peoples.begin(), peoples.end());	// 인원에 대한 시간도 시간순으로 정렬

	int i = 0;
	int unknownCount = N - peoples.size();	// 한번도 대화를 치지 않은 안읽은 후보들
	int lastAnswer = 0;
	for (int j = 0; j < timeTable.size(); j++)
	{
		while (timeTable[j][0] > peoples[i])
		{
			unknownCount++;
			i++;
		}
		// 해당 시간을 포함하여 이후까지 채팅을 안친 사람들과
		// 안읽은 사람의 수가 같다면, 추론 가능
		if (unknownCount == timeTable[j][2])
		{
			timeTable[j][4] = unknownCount;
			lastAnswer = unknownCount;
		}
		// 아니라면 이전에 추론했던 사람들 만큼만 추론 가능
		else timeTable[j][4] = lastAnswer;
	}
	// 다시 인덱스 순으로 정렬
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