#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

// 트리 제작용 구조체
struct Node
{
	vector<int> data;
	vector<Node*> childs;
	Node* parent;
};

// 반지름 순으로 정렬 위한 비교 함수
bool compare(vector<int> a, vector<int> b)
{
	return a[2] > b[2];
}

// 한 원이 다른 원 안에 있는지 판별
bool check(vector<int> a, vector<int> b)
{
	int dis = sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]));

	return (a[2] >= dis || b[2] >= dis);
}


// 트리 작성
void makeTree(Node* node, Node* curNode)
{
	// 한 원이 다른 원 안에 있는 형태가 아니면 바로 끝냄
	// 이미 반지름 순으로 정렬 했으므로 curNode는 node보다 밖의 원일 순 없음
	if (!check(node->data, curNode->data)) return;

	bool tCheck = false;

	for (int i = 0; i < node->childs.size(); i++)
	{
		// node의 자식 노드와 curNode가 한 원이 다른 원 안에 있는 형태면 재귀 호출
		if (check(node->childs[i]->data, curNode->data))
		{
			makeTree(node->childs[i], curNode);
			tCheck = true;
			break;
		}
	}
	// node의 자식 노드와 연관이 없을 경우 새로운 자식 노드로 추가
	if (tCheck == false)
	{
		curNode->parent = node;
		curNode->childs = vector<Node*>();

		node->childs.push_back(curNode);
	}
}


int main()
{
	vector<int> answer;
	int C;
	cin >> C;
	for (int i = 0; i < C; i++)
	{
		int N;
		cin >> N;
		vector<vector<int>> info(N, vector<int>(3, 0));
		for (int j = 0; j < N; j++)
		{
			cin >> info[j][0] >> info[j][1] >> info[j][2];
		}
		sort(info.begin(), info.end(), compare);

		// 데이터를 Node 형태로 바꾼 후, 트리로 만듦
		vector<Node> nodes(N);
		for (int j = 0; j < N; j++)
		{
			nodes[j].data = info[j];
			if (j != 0)
			{
				makeTree(&nodes[0], &nodes[j]);
			}
		}

		// 첫번째 지름 노드 탐색(BFS)
		queue<Node> mQ;
		mQ.push(nodes[0]);
		Node lastNode;
		while (!mQ.empty())
		{
			int qSize = mQ.size();

			for (int j = 0; j < qSize; j++)
			{
				lastNode = mQ.front();
				mQ.pop();

				for (int k = 0; k < lastNode.childs.size(); k++)
				{
					mQ.push(*lastNode.childs[k]);
				}
			}
		}

		set<vector<int>> mS;
		mS.insert(lastNode.data);

		int count = 0;
		mQ.push(lastNode);

		// 두번째 지름 노드 탐색(BFS)
		while (!mQ.empty())
		{
			int qSize = mQ.size();

			for (int j = 0; j < qSize; j++)
			{
				Node node = mQ.front();
				mQ.pop();

				for (int k = 0; k < node.childs.size(); k++)
				{
					if (mS.find(node.childs[k]->data) == mS.end())
					{
						mQ.push(*node.childs[k]);
						mS.insert(node.childs[k]->data);
					}
				}
				if (node.parent != NULL && mS.find(node.parent->data) == mS.end())
				{
					mQ.push(*node.parent);
					mS.insert(node.parent->data);
				}
			}
			if (!mQ.empty()) count++;
		}

		answer.push_back(count);
	}

	for (int i = 0; i < answer.size(); i++) cout << answer[i] << endl;
	return 0;
}