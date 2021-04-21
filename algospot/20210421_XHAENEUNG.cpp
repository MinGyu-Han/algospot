#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// �������� ���ڿ��� �и��� split �Լ� �ۼ�
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

	// �� ���� ���ڿ��� ��� ������ ��츦 map�� ����
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

	// ���� ����
	cin.ignore();
	for (int i = 0; i < T; i++)
	{
		string s;
		getline(cin, s);
		vector<string> nS = split(s, ' ');

		// map�� �̿��� ���ڷ� ��ȯ�Ͽ� ��� ���
		int first = mM[nS[0]];
		int second = mM[nS[2]];
		int result = 0;
		if (nS[1] == "+") result = first + second;
		else if (nS[1] == "-") result = first - second;
		else if (nS[1] == "*") result = first * second;

		// ������ ������� ��ġ�ϸ� Yes, �ƴϸ� No ���
		if (mM.find(nS[4]) != mM.end() && mM[nS[4]] == result) answers.push_back("Yes");
		else answers.push_back("No");
	}
	for (int i = 0; i < answers.size(); i++) cout << answers[i] << endl;

	return 0;
}