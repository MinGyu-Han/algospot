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
	// 현재 A[i]를 A[i+1]로 변경 및, A[i]%10000 + 1의 값을 리턴
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
			// A[j]%10000 + 1 값을 mQ 및 sum에 더함
			int lastV = online.getNext();
			mQ.push(lastV);
			sum += lastV;

			// sum <= K 일 때까지 구간 맨 앞 값을 제거
			while (sum > K)
			{
				sum -= mQ.front();
				mQ.pop();
			}

			// sum == K 인 경우, 답 개수 + 1
			if (sum == K) answer++;
		}
		answers.push_back(answer);
	}

	for (int answer : answers) cout << answer << endl;

	return 0;
}