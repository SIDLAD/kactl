/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: When doing DP on intervals: $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$,
 *  one can solve intervals in increasing order of length, and search $k = p[i][j]$ for $a[i][j]$ only between $p[i][j-1]$ and $p[i+1][j]$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 *  Consider also: LineContainer (ch. Data structures), monotone queues, ternary search.
 * Time: O(N^2)
 */
#pragma once

for(int i = n - 2;i>=0;i--) for(int j = i + 1;j<n;j++) {
    int mn = INF, cost = costF(i, j);
    for(int k = max(i, opt[i][j - 1]);k<=min(j - 1, opt[i + 1][j]);k++) if(mn > dp[i][k] + dp[k][j] + cost)
    {opt[i][j] = k; mn = dp[i][k] + dp[k][j] + cost;}
    dp[i][j] = mn;
}