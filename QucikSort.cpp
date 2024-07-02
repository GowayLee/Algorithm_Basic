#include <iostream>

using namespace std;

const int N = 20;
int q[N];

void quick_sort(int q[], int l, int r)
{
    if (l >= r)
        return;

    int i = l - 1, j = r + 1, x = q[l + r >> 1];
    while (i < j)
    {
        do
            i++;
        while (q[i] < x);
        do
            j--;
        while (q[j] > x);
        if (i < j)
            swap(q[i], q[j]);
    }
    quick_sort(q, l, j), quick_sort(q, j + 1, r);
}

int main()
{
    for (size_t i = 0; i < N; i++)
        q[i] = rand() % 100;
    quick_sort(q, 0, N - 1);
    for (size_t i = 0; i < N; i++)
        printf("%d ", q[i]);

    system("pause");
    return 0;
}