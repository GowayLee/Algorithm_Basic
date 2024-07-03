#include <iostream>
#include <climits>
#include <vector>
#define VERTICECOUNT 6

using namespace std;


class Adj_node
{
public:
	int placeIndex;
	int weight;
	Adj_node *next;

	Adj_node(int inputPlace, int inputWeight)
	{
		placeIndex = inputPlace;
		weight = inputWeight;
		next = NULL;
	}
};

class Adj_list
{
public:
	Adj_list() { head = NULL; };
	void insertNode(int inputPlace, int inputWeight)
	{
		Adj_node *newNode;
		newNode = new Adj_node(inputPlace, inputWeight);
		if (head == NULL)
		{
			head = newNode;
		}
		else
		{
			Adj_node *ptr = head;
			while (ptr->next)
			{
				ptr = ptr->next;
			}
			ptr->next = newNode;
			newNode->next = NULL;
		}
	}

private:
	Adj_node *head;
	friend class Graph;
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
	void createDirectedEdge(char p1, char p2, int inputWeight);
	void createUndirectedEdge(char p1, char p2, int inputWeight);
	void showVisiting(int a) { cout << a << " "; };
	int findIndex(char inputPlace)
	{
		for (size_t i = 0; i < VERTICECOUNT; i++)
		{
			if (inputPlace == place[i])
				return i;
		}
		return -1;
	}
	void BellmanFord(char src);

private:
	char place[VERTICECOUNT];
	Adj_list edge[VERTICECOUNT];
};

void Graph::createDirectedEdge(char p1, char p2, int inputWeight)
{
	if (p1 == p2)
		return;
	int i = findIndex(p1);
	int j = findIndex(p2);
	if (i == -1 || j == -1)
		return;
	edge[i].insertNode(j, inputWeight);
}

void Graph::createUndirectedEdge(char p1, char p2, int inputWeight)
{
	if (p1 == p2)
		return;
	int i = findIndex(p1);
	int j = findIndex(p2);
	if (i == -1 || j == -1)
		return;
	edge[i].insertNode(j, inputWeight);
	edge[j].insertNode(i, inputWeight);
}

void Graph::BellmanFord(char src)
{
	// Initiallize
	vector<int> dist(VERTICECOUNT, INT_MAX);

	dist[findIndex(src)] = 0;

	// relax Process
	for (size_t i = 0; i < VERTICECOUNT - 1; i++)
	{
		// traverse each vertice
		for (size_t j = 0; j < VERTICECOUNT; j++)
		{
			// relax every edge on the vertice
			Adj_node *ptr = edge[j].head;
			while (ptr)
			{
				int curDistance = dist[j] + ptr->weight;
				if (curDistance < dist[ptr->placeIndex])
				{
					dist[ptr->placeIndex] = curDistance;
				}
				ptr = ptr->next;
			}
		}
	}

	// determine the Negative-weight Edge
	int isNegative = 0;
	// traverse each vertice
	for (size_t j = 0; j < VERTICECOUNT; j++)
	{
		// relax every edge on the vertice
		Adj_node *ptr = edge[j].head;
		while (ptr)
		{
			int curDistance = dist[j] + ptr->weight;
			if (curDistance < dist[ptr->placeIndex])
			{
				isNegative++;
			}
			ptr = ptr->next;
		}
	}

	// display
	cout << "Negative-weight Edge exist? " << isNegative << endl;
	for (size_t i = 0; i < VERTICECOUNT; i++)
	{
		if (dist[i] != INT_MAX)
		{
			cout << src << " to " << place[i] << " is " << dist[i] << endl;
		}
		else
		{
			cout << src << " to " << place[i] << " is " << "not accessible!" << endl;
		}
	}
}

int main()
{
	char place[VERTICECOUNT] = {'a', 'b', 'c', 'd', 'e', 'f'};
	// Arrange the Directed Graphic
	Graph g(place);
	g.createDirectedEdge('a', 'c', 7);
	g.createDirectedEdge('a', 'b', 9);
	g.createDirectedEdge('b', 'e', 3);
	g.createDirectedEdge('b', 'f', -1);
	g.createDirectedEdge('b', 'd', 1);
	g.createDirectedEdge('c', 'b', -2);
	g.createDirectedEdge('c', 'd', 2);
	g.createDirectedEdge('d', 'f', 1);
	g.createDirectedEdge('f', 'e', 1);

	g.BellmanFord('a');

	system("pause");
	return 0;
}