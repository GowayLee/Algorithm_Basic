#include <iostream>
using namespace std;
#define VERTICECOUNT 7

class Node
{
public:
	int placeIndex;
	Node *next;

	Node(int inputPlaceIndex)
	{
		placeIndex = inputPlaceIndex;
		next = NULL;
	}
};

class List
{
public:
	List() { head = NULL; };
	void insertNode(int inputPlaceIndex)
	{
		Node *newNode;
		newNode = new Node(inputPlaceIndex);
		if (head == NULL)
		{
			head = newNode;
		}
		else
		{
			Node *ptr = head;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
			}
			ptr->next = newNode;
			newNode->next = NULL;
		}
	}

protected:
	Node *head;
	friend class Graph;
};

class Stack : public List
{
public:
	Stack() { head = NULL; };
	void push(int inputPlaceIndex) { insertNode(inputPlaceIndex); };
	bool isEmpty() { return head == NULL; }
	int pop()
	{
		if (isEmpty())
		{
			cout << "Stack is empty" << endl;
			return -1;
		}
		int temp;
		Node *ptr = head;
		head = head->next;
		temp = ptr->placeIndex;
		delete ptr;
		return temp;
	}
};

class Queue : public List
{
public:
	Queue() { head = NULL; };
	void enqueue(int inputPlaceIndex) { insertNode(inputPlaceIndex); };
	bool isEmpty() { return head == NULL; };
	int dequeue()
	{
		if (isEmpty())
		{
			cout << "Queue is empty" << endl;
			return -1;
		}
		int temp;
		Node *ptr = head;
		head = head->next;
		temp = ptr->placeIndex;
		delete ptr;
		return temp;
	};
};

class Graph
{
public:
	Graph(char inputPlace[VERTICECOUNT])
	{
		for (int i = 0; i < VERTICECOUNT; i++)
		{
			place[i] = inputPlace[i];
		}
	};
	void createEdge(char p1, char p2);
	void showVisiting(int index) { cout << place[index] << " "; };
	void DFS(char start);
	void BFS(char start);
    int findIndex(char inputPlace)
    {
        for (size_t i = 0; i < VERTICECOUNT; i++)
        {
            if (inputPlace == place[i])
                return i;
        }
        return -1;
    }

private:
	char place[VERTICECOUNT];
	List edge[VERTICECOUNT];
	void goDeeper(int now, int visited[]);
};

void Graph::createEdge(char p1, char p2)
{
    if (p1 == p2) return;
    int i = findIndex(p1);
    int j = findIndex(p2);
    if (i == -1 || j == -1) return;
    edge[i].insertNode(j);
    edge[j].insertNode(i);
}

void Graph::BFS(char start)
{
	Queue q;
	Node *ptr = NULL;
	int visited[VERTICECOUNT] = {0};
	
	int now = findIndex(start);
	if (now == -1)
	{
		cout << "Start Place is not exist" << endl;
		return;
	}
	
	visited[now] = 1;
	showVisiting(now);
	q.enqueue(now);
	while (!q.isEmpty())
	{
		now = q.head->placeIndex;
		ptr = edge[now].head;
		while (ptr)
		{
			if (visited[ptr->placeIndex] == 0)
			{
				q.enqueue(ptr->placeIndex);
				visited[ptr->placeIndex] = 1;
				showVisiting(ptr->placeIndex);
			}
			ptr = ptr->next;
		}
		q.dequeue();
	}
	return;
}

void Graph::goDeeper(int now, int visited[])
{
	Node *ptr = edge[now].head;
	visited[now] = 1;
	showVisiting(now);
	while (ptr)
	{
		if (visited[ptr->placeIndex] == 0)
		{
			goDeeper(ptr->placeIndex, visited);
		}
		ptr = ptr->next;
	}
	return;
}
void Graph::DFS(char start)
{
	int visited[VERTICECOUNT] = {0};
	int now = findIndex(start);
	if (now == -1)
	{
		cout << "Start Place is not exist" << endl;
		return;
	}
	goDeeper(now, visited);
	return;
}

int main()
{
	char place[VERTICECOUNT] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	// Arrange the Undirected Graphic
	Graph g(place);
	g.createEdge('A', 'B');
	g.createEdge('A', 'E');
	g.createEdge('A', 'D');
	g.createEdge('B', 'G');
	g.createEdge('D', 'E');
	g.createEdge('E', 'F');
	g.createEdge('C', 'F');

	// DFS
	cout << "DFS Result: ";
	g.DFS('A');

	// BFS
	cout << "\nBFS Result: ";
	g.BFS('A');

	system("pause");
	return 0;
}