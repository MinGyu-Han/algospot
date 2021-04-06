#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<int> solution(vector<double>& B, vector<vector<double>>& T, vector<vector<double>>& M, vector<int>& nWords)
{
	vector<int> answer;

	vector <pair<double, vector<int>>> dp;
	for (int i = 0; i < B.size(); i++)
	{	// 초기 확률 계산(확률 0은 제외) 후, i번째 단어를 첫단어로 넣음
		if (M[i][nWords[0]] * B[i] == 0) continue;
		dp.push_back(make_pair(M[i][nWords[0]] * B[i], vector<int>({ i })));
	}

	for (int i = 1; i < nWords.size(); i++)
	{
		vector <pair<double, vector<int>>> nDp;

		// i+1번째 단어가 k인 경우 중, 가장 확률이 큰 값만 저장
		for (int k = 0; k < B.size(); k++)
		{
			double maxPerCnt = 0;
			vector<int> tmp;
			for (int j = 0; j < dp.size(); j++)
			{	// 앞 단어가 dp[j].second[dp[j].second.size() - 1]
				// 인식된 단어가 nWords[i] 일때, 확률 계산 후
				// 가장 확률이 큰 경우만 저장
				int lastWord = dp[j].second[dp[j].second.size() - 1];
				double perCnt = dp[j].first;
				vector<int> resultWords = dp[j].second;

				if (perCnt * M[k][nWords[i]] * T[lastWord][k] <= maxPerCnt) continue;

				maxPerCnt = perCnt * M[k][nWords[i]] * T[lastWord][k];
				resultWords.push_back(k);
				tmp = resultWords;
			}
			// 확률이 0이면 제외
			if (maxPerCnt != 0) nDp.push_back(make_pair(maxPerCnt, tmp));
		}
		dp.clear();
		dp = nDp;
	}
	double perCnt = 0;
	// 마지막 글자에 대한 dp 값 중 가장 확률이 큰 값을 답으로 함
	for (int i = 0; i < dp.size(); i++)
	{
		if (dp[i].first > perCnt)
		{
			perCnt = dp[i].first;
			answer = dp[i].second;
		}
	}

	return answer;
}

int main()
{
	vector<vector<int>> answer;
	int m, q;
	cin >> m >> q;

	vector<string> words(m, "");
	for (int i = 0; i < m; i++)
	{
		cin >> words[i];
	}

	map<string, int> mM;
	for (int i = 0; i < words.size(); i++) mM[words[i]] = i;

	vector<double> B(m, 0);
	for (int i = 0; i < m; i++)
	{
		cin >> B[i];
	}

	vector<vector<double>> T(m, vector<double>(m, 0));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> T[i][j];
		}
	}

	vector<vector<double>> M(m, vector<double>(m, 0));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> M[i][j];
		}
	}

	for (int i = 0; i < q; i++)
	{
		int n;
		cin >> n;
		vector<string> qWords(n, "");
		for (int j = 0; j < n; j++)
		{
			cin >> qWords[j];
		}
		vector<int> nWords(n, 0);
		for (int j = 0; j < qWords.size(); j++)
		{
			nWords[j] = mM[qWords[j]];
		}

		answer.push_back(solution(B, T, M, nWords));
	}

	for (int i = 0; i < answer.size(); i++)
	{
		for (int j = 0; j < answer[i].size(); j++)
		{
			cout << words[answer[i][j]];
			if (j != answer[i].size() - 1) cout << " ";
		}
		cout << endl;
	}

	return 0;
}
