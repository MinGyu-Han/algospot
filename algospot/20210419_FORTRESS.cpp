#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

// Ʈ�� ���ۿ� ����ü
struct Node
{
	vector<int> data;
	vector<Node*> childs;
	Node* parent;
};

// ������ ������ ���� ���� �� �Լ�
bool compare(vector<int> a, vector<int> b)
{
	return a[2] > b[2];
}

// �� ���� �ٸ� �� �ȿ� �ִ��� �Ǻ�
bool check(vector<int> a, vector<int> b)
{
	int dis = sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]));

	return (a[2] >= dis || b[2] >= dis);
}


// Ʈ�� �ۼ�
void makeTree(Node* node, Node* curNode)
{
	// �� ���� �ٸ� �� �ȿ� �ִ� ���°� �ƴϸ� �ٷ� ����
	// �̹� ������ ������ ���� �����Ƿ� curNode�� node���� ���� ���� �� ����
	if (!check(node->data, curNode->data)) return;

	bool tCheck = false;

	for (int i = 0; i < node->childs.size(); i++)
	{
		// node�� �ڽ� ���� curNode�� �� ���� �ٸ� �� �ȿ� �ִ� ���¸� ��� ȣ��
		if (check(node->childs[i]->data, curNode->data))
		{
			makeTree(node->childs[i], curNode);
			tCheck = true;
			break;
		}
	}
	// node�� �ڽ� ���� ������ ���� ��� ���ο� �ڽ� ���� �߰�
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

		// �����͸� Node ���·� �ٲ� ��, Ʈ���� ����
		vector<Node> nodes(N);
		for (int j = 0; j < N; j++)
		{
			nodes[j].data = info[j];
			if (j != 0)
			{
				makeTree(&nodes[0], &nodes[j]);
			}
		}

		// ù��° ���� ��� Ž��(BFS)
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

		// �ι�° ���� ��� Ž��(BFS)
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