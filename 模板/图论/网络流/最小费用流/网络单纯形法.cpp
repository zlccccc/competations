// Author:  HolyK
// Created: Thu Apr 27 12:05:36 2023
#include "bits/stdc++.h"
template <class F, class C> struct MCMF {
    static const int N = 5005, M = 50005;
    struct Edge {
        int v, ne;
        F w;
        C c;
    } e[M * 2];
    int head[N], tot, fa[N], fe[N], mark[N], buf[M], ti, nc;
    C pi[N];
    MCMF() { memset(head, -1, sizeof head); }
    void add(int x, int y, F f, C c) {
        e[tot] = {y, head[x], f, c}, head[x] = tot++;
        e[tot] = {x, head[y], 0, -c}, head[y] = tot++;
    }
    void dfs(int x) {
        nc++, mark[x] = 1;
        for (int i = head[x]; ~i; i = e[i].ne) {
            int y = e[i].v;
            if (!mark[y] && e[i].w) {
                fa[y] = x, fe[y] = i, dfs(y);
            }
        }
    }
    C phi(int x) {
        if (mark[x] == ti)
            return pi[x];
        return mark[x] = ti, pi[x] = phi(fa[x]) - e[fe[x]].c;
    }
    void pushFlow(int id, C &cost) {
        int u = e[id ^ 1].v, v = e[id].v, l = nc, r = nc;
        ti++;
        while (u)
            buf[++r] = fe[u], mark[u] = ti, u = fa[u];
        while (mark[v] != ti)
            buf[--l] = fe[v] ^ 1, mark[v] = ti, v = fa[v];
        buf[nc] = id;
        int t = l;
        for (int i = l; buf[i] != fe[v]; i++) {
            if (e[buf[t]].w > e[buf[i]].w)
                t = i;
        }
        F f = e[buf[t]].w;
        for (int i = l; buf[i] != fe[v]; i++) {
            e[buf[i]].w -= f, e[buf[i] ^ 1].w += f;
            cost += e[buf[i]].c * f;
        }
        if (t == nc)
            return;
        int x = id ^ (t < nc), y = e[x].v, z = e[x ^ 1].v;
        while (x != (buf[t] ^ (t < nc))) {
            x ^= 1;
            pi[z] = pi[y] - e[x].c;
            std::swap(x, fe[z]);
            std::swap(y, fa[z]);
            std::swap(y, z);
        }
    }
    std::pair<F, C> flow(int s, int t) {
        int hs = head[s], ht = head[t];
        C minval = std::numeric_limits<C>::max();
        for (int i = 0; i < tot; i++)
            minval = std::min(minval, e[i].c);
        minval = (minval - 1) * N;
        add(t, s, std::numeric_limits<F>::max() / 2, minval);
        memset(fe, -1, sizeof fe);
        C cost = 0;
        nc = fa[t] = 0;
        dfs(t);
        mark[t] = ti = 2;
        for (int i = 0, pre = tot - 1; i != pre; i = i + 1 == tot ? 0 : i + 1) {
            if (e[i].w && e[i].c < phi(e[i ^ 1].v) - phi(e[i].v)) {
                pushFlow(pre = i, cost);
            }
        }
        F flow = e[tot - 1].w;
        head[t] = ht, head[s] = hs, tot -= 2;
        return {flow, cost - flow * minval};
    }
};
MCMF<int, int> g;
void solve() {
    int n, m, s, t;
    std::cin >> n >> m;
    s = 1, t = n;
    while (m--) {
        int x, y, z, w;
        std::cin >> x >> y >> z >> w;
        g.add(x, y, z, w);
    }
    auto [f, c] = g.flow(s, t);
    std::cout << f << " " << c << "\n";
}
int main() {
    // freopen("t.in", "r", stdin);
    // freopen("t.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    // std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}