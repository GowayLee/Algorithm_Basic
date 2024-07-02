#include <iostream>
using namespace std;
#define NUMPLACE 7

// =================================Arrange Basical ADTs=================================
class node
{
public:
  char place;
  node *next;

  node(char inputPlace)
  {
    place = inputPlace;
    next = NULL;
  }
};

class list
{
public:
  list() { head = NULL; };
  void insertNode(char inputPlace)
  {
    node *newNode;
    newNode = new node(inputPlace);
    if (head == NULL)
    {
      head = newNode;
    }
    else
    {
      node *ptr = head;
      while (ptr->next != NULL)
      {
        ptr = ptr->next;
      }
      ptr->next = newNode;
      newNode->next = NULL;
    }
  }

private:
  node *head;
  friend class stack;
  friend class graph;
  friend class queue;
};

class stack : public list
{
public:
  stack() { head = NULL; };
  void push(char inputPlace) { insertNode(inputPlace); };
  bool isEmpty() { return head == NULL; }
  char pop()
  {
    if (isEmpty())
    {
      cout << "Stack is empty" << endl;
      return -1;
    }
    char temp;
    node *ptr = head;
    head = head->next;
    temp = ptr->place;
    delete ptr;
    return temp;
  }
};

class queue : public list
{
public:
  queue() { head = NULL; };
  void enqueue(char inputPlace) { insertNode(inputPlace); };
  bool isEmpty() { return head == NULL; };
  char dequeue()
  {
    if (isEmpty())
    {
      cout << "Queue is empty" << endl;
      return -1;
    }
    char temp;
    node *ptr = head;
    head = head->next;
    temp = ptr->place;
    delete ptr;
    return temp;
  };
};

// =================================Arrange Graphic=================================
class graph
{
public:
  graph(char inputPlace[NUMPLACE])
  {
    for (int i = 0; i < NUMPLACE; i++)
    {
      place[i] = inputPlace[i];
    }
  };
  void createEdge(char p1, char p2);
  void showVisiting(char a) { cout << a << " "; };
  void DFS(char start);
  void BFS(char start);
  int findIndex(char inputPlace)
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

private:
  char place[NUMPLACE];
  list edge[NUMPLACE];
  int visited[NUMPLACE] = {0};
  void goDeeper(char now, int visited[NUMPLACE]);
};

void graph::createEdge(char p1, char p2)
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
  edge[i].insertNode(p2);
  // Find the index of the p2
  for (i = 0; i < NUMPLACE; i++)
  {
    if (place[i] == p2)
    {
      break;
    }
  }
  edge[i].insertNode(p1);
}

void graph::BFS(char start)
{
  queue q;
  node *ptr = NULL;
  int visited[NUMPLACE] = {0};
  // Enqueue the Start Place
  char now = start;
  visited[findIndex(now)] = 1;
  showVisiting(now);
  q.enqueue(now);
  while (q.isEmpty() == false)
  {
    now = q.head->place;
    ptr = edge[findIndex(now)].head;
    while (ptr)
    {
      if (visited[findIndex(ptr->place)] == 0)
      {
        q.enqueue(ptr->place);
        visited[findIndex(ptr->place)] = 1;
        showVisiting(ptr->place);
      }
      ptr = ptr->next;
    }
    q.dequeue();
  }
  return;
}

void graph::goDeeper(char now, int visited[NUMPLACE])
{
  node *ptr = edge[findIndex(now)].head;
  visited[findIndex(now)] = 1;
  showVisiting(now);
  while (ptr)
  {
    if (visited[findIndex(ptr->place)] == 0)
    {
      goDeeper(ptr->place, visited);
    }
    ptr = ptr->next;
  }
  return;
}
void graph::DFS(char start)
{
  int visited[NUMPLACE] = {0};
  char now = start;
  goDeeper(now, visited);
  return;
}
int main()
{
  char place[NUMPLACE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  // Arrange the Undirected Graphic
  graph g(place);
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