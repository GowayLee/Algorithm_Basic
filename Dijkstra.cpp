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
    void dijkstra(char src);

private:
    char place[VERTICECOUNT];
    Adj_list edge[VERTICECOUNT];
    int visited[VERTICECOUNT] = {0};
};

void Graph::createDirectedEdge(char p1, char p2, int inputWeight)
{
    if (p1 == p2) return;
    int i = findIndex(p1);
    int j = findIndex(p2);
    if (i == -1 || j == -1) return;
    edge[i].insertNode(j, inputWeight);
}

void Graph::createUndirectedEdge(char p1, char p2, int inputWeight)
{
    if (p1 == p2) return;
    int i = findIndex(p1);
    int j = findIndex(p2);
    if (i == -1 || j == -1) return;
    edge[i].insertNode(j, inputWeight);
    edge[j].insertNode(i, inputWeight);
}

void Graph::dijkstra(char src)
{
    vector<int> dist(VERTICECOUNT, INT_MAX);                                            // 从源点到所有点的距离，初始化为无穷大
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // {距离, 节点}
    int srcIndex = findIndex(src);                                                       
    if (srcIndex == -1)
    {
        cout << "The source place is not exist!" << endl;
        return;
    }                                                    
    dist[srcIndex] = 0;
    pq.push({0, srcIndex});

    while (!pq.empty())
    {
        int u = pq.top().second; // 取出距离最小的节点
        pq.pop();
        
        Adj_node *ptr = edge[u].head;
        // 遍历所有与u相连的边
        while (ptr)
        {
            int v = ptr->placeIndex;
            int weight = ptr->weight;
            // 如果找到更短的路径，则更新距离并加入优先队列
            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
            ptr = ptr->next;
        }
    }

    for (int i = 0; i < VERTICECOUNT; ++i)
    {
        if (dist[i] == INT_MAX)
            cout << "There is no path from " << src << " to " << place[i] << endl;
        else
            cout << "The shortest path from " << src << " to " << place[i] << " is " << dist[i] << endl;
    }
}

int main()
{

    char place[VERTICECOUNT] = {'1', '2', '3', '4', '5', '6'};
    // Arrange the Directed Graphic
    Graph g(place);
    g.createDirectedEdge('1', '2', 1);
    g.createDirectedEdge('1', '3', 12);
    g.createDirectedEdge('2', '3', 9);
    g.createDirectedEdge('2', '4', 3);
    g.createDirectedEdge('3', '5', 5);
    g.createDirectedEdge('4', '3', 4);
    g.createDirectedEdge('4', '5', 13);
    g.createDirectedEdge('4', '6', 15);
    g.createDirectedEdge('5', '6', 4);

    g.dijkstra('1');

    system("pause");
    return 0;
}