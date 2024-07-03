#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <map>
#include <vector>
using namespace std;

class HuffmanTreeNode
{
public:
    char ch;
    int freq;
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;
    HuffmanTreeNode(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};

struct Compare
{
    bool operator()(HuffmanTreeNode *a, HuffmanTreeNode *b)
    {
        return a->freq > b->freq;
    }
};

void printCodes(HuffmanTreeNode *root, string str, map<char, string> &huffmanCodes) // BFS
{
    if (root == NULL)
        return;
    if (root->ch != '$')
        huffmanCodes[root->ch] = str;
    printCodes(root->left, str + "0", huffmanCodes);
    printCodes(root->right, str + "1", huffmanCodes);
}

int main()
{
    string s;
    getline(cin, s);
    map<char, int> freq;

    for (int i = 0; i < s.length(); i++) // count frequency of each character
    {
        freq[s[i]]++;
    }
    priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, Compare> minHeap;
    map<char, string> huffmanCodes;
    for (auto pair : freq)
    {
        minHeap.push(new HuffmanTreeNode(pair.first, pair.second));
    }

    while (minHeap.size() != 1) // generate Huffman Tree
    {
        HuffmanTreeNode *left = minHeap.top();
        minHeap.pop();
        HuffmanTreeNode *right = minHeap.top();
        minHeap.pop();
        HuffmanTreeNode *top = new HuffmanTreeNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    printCodes(minHeap.top(), "", huffmanCodes);
    for (auto pair : huffmanCodes)
    {
        cout << pair.first << " " << pair.second << endl;
    }

    system("pause");
    return 0;
}