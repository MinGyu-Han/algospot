#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double calcul(vector<double>& numbers, double x)
{
	double result = 0;
	for (int i = 0; i < numbers.size(); i++)
	{
		result += pow(x, numbers.size() - 1 - i) * numbers[i];
	}
	return result;
}

vector<double> solution(vector<double> numbers)
{
	vector<double> answer;

	if (numbers.size() == 1) return answer;

	vector<double> differential(numbers.size() - 1, 0);
	//미분 수행
	for (int i = 0; i < numbers.size() - 1; i++)
	{
		differential[i] = numbers[i] * (numbers.size() - 1 - i);
	}

	// 극점을 얻어냄
	vector<double> poles = solution(differential);

	// 앞뒤로 -10, 10을 추가
	poles.insert(poles.begin(), -10);
	poles.push_back(10);

	double checkV = pow(10, -8);
	// 이분법을 이용하여 구간별 해를 구함
	for (int i = 0; i < poles.size() - 1; i++)
	{
		if (poles[i] == poles[i + 1]) continue;

		double minX = poles[i];
		double maxX = poles[i + 1];

		//f(minX) * f(maxX) < 0 이면 해당 구간에 해가 있음
		while (calcul(numbers, minX) * calcul(numbers, maxX) < 0)
		{
			double midX = (minX + maxX) / 2;

			// 답에 충분히 가까워졌으므로 midX를 답으로 저장
			if (abs(calcul(numbers, midX)) <= checkV / 10)
			{
				answer.push_back(midX);
				break;
			}
			else if (calcul(numbers, minX) * calcul(numbers, midX) < 0)
			{	// minX, midX 구간 안에 답이 있으므로 minX, midX 구간 탐색
				maxX = midX;
			}
			else
			{	// midX, maxX 구간 안에 답이 있으므로 midX, maxX 구간 탐색
				minX = midX;
			}
		}
	}
	return answer;
}

int main()
{
	int C;
	vector<vector<double>> answers;

	cin >> C;

	for (int i = 0; i < C; i++)
	{
		int n;
		cin >> n;
		vector<double> numbers(n + 1, 0);
		for (int j = 0; j < n + 1; j++) cin >> numbers[j];

		answers.push_back(solution(numbers));
	}

	for (vector<double> answer : answers)
	{
		for (int i = 0; i < answer.size(); i++)
		{
			cout << fixed;
			cout.precision(12);
			cout << round(answer[i] * pow(10, 8)) / pow(10, 8);
			if (i != answer.size() - 1) cout << " ";
		}
		cout << endl;
	}
	return 0;
}