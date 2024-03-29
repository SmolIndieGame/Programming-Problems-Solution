## **Problem**

https://codeforces.com/problemset/problem/1822/E

給定一個字串 $s$，長度爲 $n$，可以任意交換其中的兩個字符 $k$ 次，求最小的 $k$ 使得交換後，$s$ 變爲反迴文。（如果無法變成反迴文，輸出 $-1$）

$s$ 是反迴文 iff $\forall i, s_i \neq s_{n - i}$

## **Observation**

如果 $n$ 是奇數，直接輸出 $-1$。

定義 $cnt(c)$ 爲字符 $c$ 在 $s$ 中出現的次數。

如果 $\exist c\in s, cnt(c)\gt \frac n2$，那麼 $s$ 不可能會變成反迴文。
因爲如果 $s$ 能變成迴文，那麼 $s$ 中的所有字符都能組成一對，使得每一對字符中的兩個字符都不相等。

定義集合 $S=\\{ i:s_i=s_{n-i}\\}$

如果 $a'$ 裏沒有 0， $x$ 就會是最小的。所有在 $a$ 裏的數都會被使用兩次，除了 $a_1$ 和 $a_n$。

定義 $z$ 爲這 $n$ 個數中 0 的個數， $n-z$ 爲大於 0 的數的個數。\
定義序列 $\\{b_{n-z}\\}$ 爲這 $n$ 個數中所有大於 0 的數。

如果 $z-1\le n-z$，\
那我們把 0 和非 0 間隔的放： $[0,b_1,0,b_2,0,\dotsc,0,b_{z-1},0,b_z,b_{z+1}\dotsc,b_{n-z}]$，\
那麼相加後的數組便沒有 0，即 $x=0$。

如果 $z-1>n-z$（沒有足夠的非 0 數），\
我們令 $b_1$ 等於最大的數，
* 如果 $b_1>1$，\
  那我們把 0 放在一起，非 0 放在一起： $[0,\dotsc,0,b_1,\dotsc,b_{n-z}]$\
  在相加後的數組中，所有的數值都等於 0 或大於 1，即 $x=1$。
* 如果 $b_1=1$（ $\forall i~b_i=1$），\
  那我們把 0 和非 0 間隔的放： $[0,b_1,0,b_2,\dotsc,0,b_{n-z},0,\dotsc,0]$\
  在相加後的數組中，所有的數值都等於 0 或 1，即 $x=2$。

$x$ 只能是 0，1 或 2，只要分 3 種情況判斷即可。

## **Solution**

由 Observation 中可以看出，我們只要知道這 $n$ 個數裏 0 的數量和他們的最大值即可。
```cpp
int zeros = 0;
int maxNum = 0;
```
其中 `zeros` 代表 0 的數量， `maxNum` 代表最大值。
```cpp
int num;
cin >> num;
if (num == 0)
    zeros++;
else
    maxNum = max(maxNum, num);
```
我在讀數據的時候同時計算 `zeros` 和 `maxNum`，這樣就不需要把數據存到數組裏。
```cpp
if (zeros - 1 > n - zeros)
    cout << (maxNum == 1 ? 2 : 1) << '\n';
else
    cout << "0\n";
```
`zeros - 1 > n - zeros` 不成立是就是 Observation 裏的第一種情況。\
`maxNum == 1` 成立時是第三種情況。\
`maxNum > 1` 成立時是第二種情況。\
\* `maxNum` 可以爲 0，這時代表這 $n$ 個數全是 0，輸出 1 即可。