#include <iostream>
using namespace std;
#define NUMPLACE 5

// =================================Arrange Basical ADTs=================================
class node
{
public:
  int place;
  int weight;
  node *next;

  node(int inputPlace, int inputWeight)
  {
    place = inputPlace;
    weight = inputWeight;
    next = NULL;
  }
};

class list
{
public:
  list() { head = NULL; };
  void insertNode(int inputPlace, int inputWeight)
  {
    node *newNode;
    newNode = new node(inputPlace, inputWeight);
    if (head == NULL)
    {
      head = newNode;
    }
    else
    {
      node *ptr = head;
      while (ptr->next)
      {
        ptr = ptr->next;
      }
      ptr->next = newNode;
      newNode->next = NULL;
    }
  }

private:
  node *head;
  friend class graph;
};

// =================================Arrange Graphic=================================
class graph
{
public:
  graph(int inputPlace[NUMPLACE])
  {
    for (int i = 0; i < NUMPLACE; i++)
    {
      place[i] = inputPlace[i];
    }
  };
  void createEdge(int p1, int p2, int inputWeight);
  void showVisiting(int a) { cout << a << " "; };
  int findIndex(int inputPlace)
  {
    for (size_t i = 0; i < NUMPLACE; i++)
    {
      if (inputPlace == place[i])
      {
        return i;
      }
      if (i == NUMPLACE - 1)
      {
        cout << "No such place" << endl;
        return -1;
      }
    }
    return -1;
  }
  void BellmanFord(int start);
  void Dijikstra(int start);

private:
  int place[NUMPLACE];
  list edge[NUMPLACE];
  int visited[NUMPLACE] = {0};
};

bool isAllTrue(bool a[NUMPLACE])
{
  for (size_t i = 0; i < NUMPLACE; i++)
  {
    if (!a[i])
    {
      return false;
    }
  }
  return true;
}
void graph::Dijikstra(int start)
{
  // Initiallize
  int distance[NUMPLACE];
  bool isVisited[NUMPLACE];
  for (size_t i = 0; i < NUMPLACE; i++)
  {
    isVisited[i] = false;
    distance[i] = 10000;
  }
  distance[findIndex(start)] = 0;

  while (!isAllTrue(isVisited))
  {
    // find index of the unvisited vertice with the minimal Distance
    int min = 10000;
    int minIndex = 0;
    for (size_t i = 0; i < NUMPLACE; i++)
    {
      if (!isVisited[i])
      {
        if (distance[i] <= min)
        {
          min = distance[i];
          minIndex = i;
        }
      }
    }

    // relax Process
    node *ptr = edge[minIndex].head;
    while (ptr)
    {
      int curDistance = distance[minIndex] + ptr->weight;
      if (curDistance < distance[findIndex(ptr->place)])
      {
        distance[findIndex(ptr->place)] = curDistance;
      }
      ptr = ptr->next;
    }
    isVisited[minIndex] = true;
  }

  // display
  for (size_t i = 0; i < NUMPLACE; i++)
  {
    cout << start << " to " << place[i] << " is " << distance[findIndex(place[i])] << endl;
  }
}

void graph::BellmanFord(int start)
{
  // Initiallize
  int distance[NUMPLACE];
  bool isAccessible[NUMPLACE];
  for (size_t i = 0; i < NUMPLACE; i++)
  {
    isAccessible[i] = false;
  }
  isAccessible[findIndex(start)] = true;
  distance[findIndex(start)] = 0;

  // relax Process
  for (size_t i = 0; i < NUMPLACE - 1; i++)
  {
    // traverse each vertice
    for (size_t j = 0; j < NUMPLACE; j++)
    {
      // relax every edge on the vertice
      node *ptr = edge[j].head;
      while (ptr)
      {
        int curDistance = distance[j] + ptr->weight;
        if (curDistance < distance[findIndex(ptr->place)] || isAccessible[findIndex(ptr->place)] == false)
        {
          distance[findIndex(ptr->place)] = curDistance;
          isAccessible[findIndex(ptr->place)] = true;
        }
        ptr = ptr->next;
      }
    }
  }

  // determine the Negative-weight Edge
  bool isNegative = false;
  // traverse each vertice
  for (size_t j = 0; j < NUMPLACE; j++)
  {
    // relax every edge on the vertice
    node *ptr = edge[j].head;
    while (ptr)
    {
      int curDistance = distance[j] + ptr->weight;
      if (curDistance < distance[findIndex(ptr->place)])
      {
        isNegative = true;
      }
      ptr = ptr->next;
    }
  }

  // display
  cout << "Negative-weight Edge exist? " << isNegative << endl;
  for (size_t i = 0; i < NUMPLACE; i++)
  {
    if (isAccessible[findIndex(place[i])])
    {
      cout << start << " to " << place[i] << " is " << distance[findIndex(place[i])] << endl;
    }
    else
    {
      cout << start << " to " << place[i] << " is " << "not accessible!" << endl;
    }
  }
}

void graph::createEdge(int p1, int p2, int inputWeight)
{
  if (p1 == p2)
  {
    cout << "No edge between " << p1 << " and " << p2 << endl;
    return;
  }
  // Find the index of the p1
  int i;
  for (i = 0; i < NUMPLACE; i++)
  {
    if (place[i] == p1)
    {
      break;
    }
  }
  edge[i].insertNode(p2, inputWeight);
}

int main()
{
  int place[NUMPLACE] = {'1', '2', '3', '4', '5'};
  // Arrange the Undirected Graphic
  graph g(place);
  g.createEdge('1', '3', 6);
  g.createEdge('1', '4', 3);
  g.createEdge('2', '1', 3);
  g.createEdge('3', '4', 2);
  g.createEdge('4', '2', 1);
  g.createEdge('4', '3', 1);
  g.createEdge('5', '2', 4);
  g.createEdge('5', '4', 2);

  // g.createEdge('3', '5', 5);

  g.BellmanFord('3');
  cout << "==========================\n\n";
  g.Dijikstra('3');
  system("pause");
  return 0;
}