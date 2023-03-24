#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        int zeros = 0;
        int maxNum = 0;
        for (int i = 0; i < n; i++)
        {
            int num;
            cin >> num;
            if (num == 0)
                zeros++;
            else
                maxNum = max(maxNum, num);
        }
        if (zeros - 1 > n - zeros)
            cout << (maxNum == 1 ? 2 : 1) << '\n';
        else
            cout << "0\n";
    }
}