#include <bits/stdc++.h>
#define N 200005

using namespace std;

vector<int> adjList[N];
int highestSubTreeHeight[N], secondHighestSubTreeHeight[N];

int n;
long long k, c;
long long maxCost;

// Calculate the highestSubTreeHeight and the secondHighestSubTreeHeight.
int dfs_pre(int u, int depth, int parent)
{
    int maxHeight = -1, secondMaxHeight = -1;
    for (int i = 0; i < adjList[u].size(); i++)
    {
        if (adjList[u][i] == parent)
            continue;
        int sh = dfs_pre(adjList[u][i], depth + 1, u);
        if (sh > maxHeight)
        {
            secondMaxHeight = maxHeight;
            maxHeight = sh;
        }
        else if (sh > secondMaxHeight)
            secondMaxHeight = sh;
    }
    highestSubTreeHeight[u] = maxHeight;
    secondHighestSubTreeHeight[u] = secondMaxHeight;
    return maxHeight + 1;
}

void dfs_solve(int u, int depth, int parent, int heightOfParent)
{
    maxCost = max(maxCost, k * max(highestSubTreeHeight[u] + 1, heightOfParent + 1) - c * depth);
    for (int i = 0; i < adjList[u].size(); i++)
    {
        int v = adjList[u][i];
        if (v == parent)
            continue;

        int newSubTreeHeight = highestSubTreeHeight[u];
        if (newSubTreeHeight == highestSubTreeHeight[v] + 1)
            newSubTreeHeight = secondHighestSubTreeHeight[u];
        int newHeightOfNodeU = max(heightOfParent, newSubTreeHeight) + 1;
        dfs_solve(v, depth + 1, u, newHeightOfNodeU);
    }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        maxCost = 0;
        cin >> n >> k >> c;
        for (int i = 0; i <= n; i++)
        {
            adjList[i].clear();
            highestSubTreeHeight[i] = 0;
            secondHighestSubTreeHeight[i] = 0;
        }
        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        dfs_pre(1, 0, -1);
        dfs_solve(1, 0, -1, -1);
        cout << maxCost << '\n';
    }
}