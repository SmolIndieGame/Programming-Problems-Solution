## **Problem**

https://codeforces.com/contest/1822/problem/F

給定一棵樹和其 root，這棵樹每一條邊的長度是 $k$，定義這棵樹的價值爲由 root 到離 root 最遠的點的距離乘以 $k$。\
現在可以把 root 移到任意位置，但樹的價值就會減少原 root 到新 root 的距離乘以 $c$，問這棵樹的最大可能價值是多少？

## **Observation**

我的想法是每一個點遍歷一次，把那個點設爲 root，然後用 $O(1)$ 的時間計算樹的價值，最後輸出最大的價值即可。

由於由 root 到離 root 最遠的點的距離等於這棵樹的高度。\
而一棵樹的高度就是所有以它的孩子爲頂點的子樹中最高的子樹的高度加上一。

先計算出所有子樹的高度。

然後用 dfs 由 root 開始遍歷每個點：\
定義 $v=$ dfs 準備進入的點， $u=$ dfs 的點。\
如果這棵樹的 root 由 $u$ 變成 $v$：\
那麼由 $u$ 爲頂點的樹就會變成 $v$ 的子樹，這棵子樹的高度就是所有除了 $v$ 以外，以它原本的孩子爲頂點的子樹中最高的子樹的高度，而其它子樹的高度不會變。\
那麼樹的價值就是 由 $u$ 爲頂點的子樹的高度 和 所有以 $v$ 的孩子爲頂點的子樹（不包含 $u$）中最高的子樹的高度 的最大值 加上一的和乘以 $k$ 減去 dfs 的深度乘以 c$。

！[Alt text](figure%201.png "figure")

在上圖中，每個點右下角的數字代表以這個點爲頂點的子樹的高度，由 $u$ 爲 root 變爲由 $v$ 爲 root 時，只有標了紅色的子樹的高度可能會改變。

\* 由於其它子樹的高度不會變，要在 $O(1)$ 時間內得到所有除了 $v$ 以外，以 $u$ 原本的孩子爲頂點的子樹中最高的子樹的高度，只需先計算最高和第二高的子樹並儲存下來。\
如果 $v$ 的高度等於最高子樹的高度，那麼就用第二高的子樹的高度。

## **Solution**

[Code](solution.cpp)

`highestSubTreeHeight[i]` 爲以點 $i$ 的孩子爲頂點的子樹中最高的子樹的高度
`secondHighestSubTreeHeight[i]` 爲以點 $i$ 的孩子爲頂點的子樹中最二高的子樹的高度

`dfs_pre` 計算所有子樹的最高子樹和第二高子樹的高度。

在 `dfs_solve` 中，更新 `maxCost` 的公式：
```cpp
k * max(highestSubTreeHeight[u] + 1, heightOfParent + 1) - c * depth
```
`heightOfParent` 是當 dfs 中的上一個點成爲了 $u$ 子樹時，它的高度。

計算 `heightOfParent`：
```cpp
int newSubTreeHeight = highestSubTreeHeight[u];
if (newSubTreeHeight == highestSubTreeHeight[v] + 1)
    newSubTreeHeight = secondHighestSubTreeHeight[u];
```
`newSubTreeHeight` 是所有除了 $v$ 以外，以 $u$ 原本的孩子爲頂點的子樹中最高的子樹的高度。
如果 $v$ 的高度等於最高子樹的高度，那麼就用第二高的子樹的高度。

最後 pass 給下一個 dfs 的 `heightOfParent` 要把 $u$ 的 `heightOfParent` 也算進出，因爲那個子樹的高度更新了：
```cpp
int newHeightOfNodeU = max(heightOfParent, newSubTreeHeight) + 1;
```
