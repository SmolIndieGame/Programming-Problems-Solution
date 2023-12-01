#include <bits/stdc++.h>

using namespace std;

int rCnt[26], cnt[26];

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        string s;
        cin >> n >> s;
        if (n % 2 == 1)
        {
            cout << -1 << '\n';
            continue;
        }

        int rCount = 0;
        memset(rCnt, 0, sizeof(rCnt));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n / 2; i++)
        {
            cnt[s[i] - 'a']++;
            cnt[s[n - i - 1] - 'a']++;
            if (s[i] != s[n - i - 1])
                continue;

            rCount++;
            rCnt[s[i] - 'a']++;
        }

        int maxRCnt = 0, maxCnt = 0;
        for (int i = 0; i < 26; i++)
        {
            maxRCnt = max(maxRCnt, rCnt[i]);
            maxCnt = max(maxCnt, cnt[i]);
        }
        if (maxCnt > n / 2)
        {
            cout << -1 << '\n';
            continue;
        }
        if (maxRCnt <= rCount / 2)
        {
            cout << rCount / 2 + rCount % 2 << '\n';
            continue;
        }
        cout << maxRCnt << '\n';
    }
}