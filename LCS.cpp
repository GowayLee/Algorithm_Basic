#include <iostream>
#include <string>

using namespace std;

void lcs(string a, string b)
{
    int m = a.length();
    int n = b.length();
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    cout << "Length of LCS is " << dp[m][n] << endl;

    char lcs[dp[m][n]];
    int index = dp[m][n];

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (a[i - 1] == b[j - 1])
        {
            lcs[index - 1] = a[i - 1];
            i--;
            j--;
            index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
    cout << "LCS is " << lcs << endl;
}

int main()
{
    string a, b;
    cin >> a >> b;
    lcs(a, b);

    system("pause");
    return 0;
}