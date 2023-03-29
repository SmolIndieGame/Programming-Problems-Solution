#include <bits/stdc++.h>

using namespace std;

int solve(string s)
{
    if (s.length() <= 1)
        return s.length();
    vector<int> arr(128, -1);
    arr[s[0]] = 0;
    int i = 0, ans = 1;
    for (int j = 1; j < s.length(); j++)
    {
        if (arr[s[j]] >= i)
            i = arr[s[j]] + 1;
        arr[s[j]] = j;
        ans = max(ans, j - i + 1);
    }
    return ans;
}

int main()
{
    string s;
    getline(cin, s);
    cout << solve(s);
}