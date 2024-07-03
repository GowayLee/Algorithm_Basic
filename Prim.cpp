#include <iostream>
#include <vector>
#include <queue>
#include <climits> // 用于INT_MAX
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
    void createUndirectedEdge(char p1, char p2, int inputWeight);
    void Prim(char src);

private:
    char place[VERTICECOUNT];
    Adj_list edge[VERTICECOUNT];
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> min_heap; // {weight, {v1, v2}}
    int findIndex(char inputPlace)
    {
        for (size_t i = 0; i < VERTICECOUNT; i++)
        {
            if (inputPlace == place[i])
                return i;
        }
        return -1;
    }
};

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
    min_heap.push(make_pair(inputWeight, make_pair(i, j)));
}

void Graph::Prim(char src)
{
    vector<bool> inMST(VERTICECOUNT, false);
    bool isAllIn = false;
    inMST[findIndex(src)] = true;
    vector<pair<int, pair<int, int>>> MSTedges;
    vector<pair<int, pair<int, int>>> tempEdges;
    
    while (!isAllIn)
    {
        isAllIn = true;
        tempEdges.clear();

        while (true) // pick the shortest suitable edge
        {
            if (min_heap.size() <= 0)
            {
                cout << "Error: There is no MST" << endl;
                return;
            }

            pair<int, pair<int, int>> temp = min_heap.top();
            min_heap.pop();
            int v1 = temp.second.first;
            int v2 = temp.second.second;

            if (inMST[v1] && !inMST[v2])
            {
                MSTedges.push_back(temp);
                inMST[v2] = true;
                break;
            }
            if (!inMST[v1] && inMST[v2])
            {
                MSTedges.push_back(temp);
                inMST[v1] = true;
                break;
            }
            {
                tempEdges.push_back(temp);
            }
        }

        for (auto i : tempEdges)
        {
            min_heap.push(i);
        }

        for (bool i : inMST)
        {
            if (i == false)
            {
                isAllIn = false;
                break;
            }
        }
    }
    
    for (auto i : MSTedges)
    {
        cout << place[i.second.first] << " - " << place[i.second.second] << " : " << i.first << endl;
    }
}

int main()
{

    char place[VERTICECOUNT] = {'1', '2', '3', '4', '5', '6'};
    // Arrange the Directed Graphic
    Graph g(place);
    g.createUndirectedEdge('1', '2', 1);
    g.createUndirectedEdge('1', '3', 2);
    g.createUndirectedEdge('2', '3', 6);
    g.createUndirectedEdge('2', '4', 11);
    g.createUndirectedEdge('3', '5', 13);
    g.createUndirectedEdge('3', '4', 9);
    g.createUndirectedEdge('4', '5', 7);
    g.createUndirectedEdge('4', '6', 3);
    g.createUndirectedEdge('5', '6', 4);

    g.Prim('1');

    system("pause");
    return 0;
}