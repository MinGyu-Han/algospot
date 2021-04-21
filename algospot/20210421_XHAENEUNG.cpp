#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// 공백으로 문자열을 분리할 split 함수 작성
vector<string> split(string s, char c)
{
	vector<string> answer;
	stringstream ss(s);
	string tmp;
	while (getline(ss, tmp, c)) {
		answer.push_back(tmp);
	}
	return answer;
}

int main()
{
	int T;
	cin >> T;

	vector<string> answers;

	map<string, int> mM;
	vector<string> numbers = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten" };

	// 각 숫자 문자열별 모든 조합의 경우를 map에 저장
	for (int i = 0; i < numbers.size(); i++)
	{
		vector<int> v;
		for (int j = 0; j < numbers[i].size(); j++) v.push_back(j);

		do {
			string a = "";
			for (int j = 0; j < v.size(); j++)
			{
				a += numbers[i][v[j]];
			}
			mM[a] = i;
		} while (next_permutation(v.begin(), v.end()));
	}

	// 공백 제거
	cin.ignore();
	for (int i = 0; i < T; i++)
	{
		string s;
		getline(cin, s);
		vector<string> nS = split(s, ' ');

		// map을 이용해 숫자로 변환하여 결과 계산
		int first = mM[nS[0]];
		int second = mM[nS[2]];
		int result = 0;
		if (nS[1] == "+") result = first + second;
		else if (nS[1] == "-") result = first - second;
		else if (nS[1] == "*") result = first * second;

		// 정답이 계산결과와 일치하면 Yes, 아니면 No 출력
		if (mM.find(nS[4]) != mM.end() && mM[nS[4]] == result) answers.push_back("Yes");
		else answers.push_back("No");
	}
	for (int i = 0; i < answers.size(); i++) cout << answers[i] << endl;

	return 0;
}