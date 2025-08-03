#include <bits/stdc++.h>
 
#define M (L+R>>1)
#define kl (k<<1)
#define kr (k<<1|1)
 
using namespace std;
 
int n, pre[200005], T[1 << 19], dp[200005], p[200005], cut[200005];
pair<int, int> b2[200005], b3[200005];
char s[200005];
 
int pickMax(int x, int y) {
    if (x == -1)
        return y;
    if (y == -1)
        return x;
    return dp[x] > dp[y] ? x : y;
}
 
void insert(int k, int L, int R, int pos, int val) {
    if (L == R) {
        T[k] = val;
        return;
    }
    if (pos <= M)
        insert(kl, L, M, pos, val);
    else
        insert(kr, M + 1, R, pos, val);
    T[k] = pickMax(T[kl], T[kr]);
}
 
int query(int k, int L, int R, int l, int r) {
    if (l > r)
        return -1;
    if (l <= L && R <= r)
        return T[k];
    int res = -1;
    if (l <= M)
        res = pickMax(res, query(kl, L, M, l, r));
    if (r > M)
        res = pickMax(res, query(kr, M + 1, R, l, r));
    return res;
}
 
void print(int x) {
    if (x == 0)
        return;
    int g = p[x];
    print(g);
    for (int i = g + 1; i <= x; i++)
        putchar(s[i]);
    puts("");
}
 
int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = n, j; i > 0; i = j) {
        j = i;
        while (j > 0 && s[j] == s[i])
            j--;
        for (int k = j + 1; k <= i; k++)
            pre[k] = j;
    }
    for (int i = 1; i <= n; i++) {
        cut[i] = -1;
        if (pre[i])
            b2[i] = {pre[pre[i]], pre[i] - 1};
        else
            b2[i] = {-1, -1};
        if (b2[i].second != -1 && b2[i].first == b2[i].second) {
            b3[i] = {pre[pre[pre[i]]], b2[i].first - 1};
            if (s[b3[i].second + 1] == s[i]) {
                cut[i] = b2[i].first - (i - b2[i].first - 1);
                if (cut[i] < b3[i].first)
                    cut[i] = -1;
            }
        } else
            b3[i] = {-1, -1};
    }
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
        dp[i] = -1;
    for (int i = 1; i <= n; i++) {
        if (b2[i].second != -1) {
            int t = query(1, 0, n, b2[i].first, b2[i].second);
            if (dp[t] + 1 > dp[i])
                p[i] = t, dp[i] = dp[t] + 1;
        }
        if (b3[i].second != -1) {
            int t;
            if (cut[i] == -1)
                t = query(1, 0, n, b3[i].first, b3[i].second);
            else
                t = pickMax(query(1, 0, n, b3[i].first, cut[i] - 1), query(1, 0, n, cut[i] + 1, b3[i].second));
            if (t != -1 && dp[t] + 1 > dp[i])
                p[i] = t, dp[i] = dp[t] + 1;
        }
        if (dp[i] == 0)
            dp[i] = -1;
        insert(1, 0, n, i, i);
    }
    if (dp[n] == -1) {
        puts("-1");
        return 0;
    }
    printf("%d\n", dp[n]);
    print(n);
    return 0;
}