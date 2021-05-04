#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

class Online {
private:
	unsigned int A;
public:
	Online() {
		A = 1983;
	}
	// ���� A[i]�� A[i+1]�� ���� ��, A[i]%10000 + 1�� ���� ����
	unsigned int getNext() {
		unsigned int result = A;
		A = (A * 214013u) + 2531011u;
		return result % 10000 + 1;
	}
};
int main()
{
	int C;
	vector<int> answers;
	cin >> C;

	for (int i = 0; i < C; i++)
	{
		int K, N;
		cin >> K >> N;

		Online online;
		queue<int> mQ;
		int sum = 0;
		int answer = 0;

		for (int j = 0; j < N; j++)
		{
			// A[j]%10000 + 1 ���� mQ �� sum�� ����
			int lastV = online.getNext();
			mQ.push(lastV);
			sum += lastV;

			// sum <= K �� ������ ���� �� �� ���� ����
			while (sum > K)
			{
				sum -= mQ.front();
				mQ.pop();
			}

			// sum == K �� ���, �� ���� + 1
			if (sum == K) answer++;
		}
		answers.push_back(answer);
	}

	for (int answer : answers) cout << answer << endl;

	return 0;
}