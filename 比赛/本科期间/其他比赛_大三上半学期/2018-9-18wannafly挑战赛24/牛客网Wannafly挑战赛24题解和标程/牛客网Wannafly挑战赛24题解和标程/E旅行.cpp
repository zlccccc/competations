#include <bits/stdc++.h>

const int Mod = 998244353;

const int MAXN = 2e5 + 5;
const int MAXK = 50 + 5;

int n, k, w[MAXN];
std::vector<int> G[MAXN];

int size[MAXN], maxson[MAXN], root, total;

bool vis[MAXN];

void Focus(int now, int fa) {
    size[now] = 1;
    maxson[now] = 0;
    for (int to: G[now]) {
        if (to == fa || vis[to]) continue;
        Focus(to, now);
        size[now] += size[to];
        maxson[now] = std::max(maxson[now], size[to]);
    }
    maxson[now] = std::max(maxson[now], total - size[now]);
    if (maxson[now] < maxson[root]) root = now;
}

namespace HLDecomp {
    std::vector<int> G2[MAXN];
    int fa[MAXN];
    int son[MAXN], depth[MAXN], top[MAXN];
    
    int DFS(int now) {
        int res = 1, tmp, maxson = 0;
        for (int to: G2[now]) {
            depth[to] = depth[now] + 1;
            tmp = DFS(to);
            res += tmp;
            if (tmp > maxson) {
                maxson = tmp; son[now] = to;
            }
        }
        return res;
    }
    
    void DFS2(int now, int tp) {
        top[now] = tp;
        if (son[now]) DFS2(son[now], tp);
        for (int to: G2[now]) {
            if (to == son[now]) continue;
            DFS2(to, to);
        }
    }
    
    void Init(int rt) {
        DFS(rt);
        DFS2(rt, rt);
    }
    
    int LCA(int u, int v) {
        while (top[u] != top[v]) {
            if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
            u = fa[top[u]];
        }
        return depth[u] < depth[v] ? u : v;
    }
}

void Build(int now) {
    vis[now] = 1;
    for (int to: G[now]) if (!vis[to]) {
        total = size[to];
        root = 0;
        Focus(to, now);
        
        HLDecomp::G2[now].push_back(root);
        HLDecomp::fa[root] = now;
        Build(root);
    }
}

struct Query {
    int u, v, id;
    
    Query() = default;
    Query(int _u, int _v, int _id): u(_u), v(_v), id(_id) {}
}; std::vector<Query> qrys[MAXN];

int ans[MAXN];

int cnt[MAXN][MAXK];

void Calc(int now, int fa) {
    for (int i = 0; i < k; ++i)
        cnt[now][(i + w[now]) % k] = (cnt[fa][i] + cnt[fa][(i + w[now]) % k]) % Mod;
    for (int to: G[now]) {
        if (to == fa || vis[to]) continue;
        Calc(to, now);
    }
}

void Del(int now, int fa) {
    memset(cnt[now], 0, sizeof cnt[now]);
    for (int to: G[now]) {
        if (to == fa || vis[to]) continue;
        Del(to, now);
    }
}

void DAC(int now) {
    vis[now] = 1;
    
    cnt[now][0] = 1;
    for (int to: G[now]) if (!vis[to]) {
        Calc(to, now);
    }
    
    for (auto e: qrys[now]) {
        if (e.u == now || e.v == now) {
            int x = e.u + e.v - now;
            ans[e.id] = (cnt[x][(k - w[now]) % k] + cnt[x][0]) % Mod;
        } else {
            for (int i = 0; i < k; ++i)
                ans[e.id] = (ans[e.id] + 1LL * cnt[e.u][i] * cnt[e.v][(2 * k - i - w[now]) % k] + 1LL * cnt[e.u][i] * cnt[e.v][(k - i) % k]) % Mod;
        }
    }
    for (int to: G[now]) if (!vis[to]) {
        Del(to, now);
    }
    for (int to: G[now]) if (!vis[to]) {
        total = size[to];
        root = 0;
        Focus(to, now);
        
        DAC(root);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; ++i) {
        static int u, v;
        
        scanf("%d%d", &u, &v);
        
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", w + i); w[i] %= k;
    }
    
    total = n;
    maxson[root = 0] = 0x3f3f3f3f;
    Focus(1, 0);
    
    int rt = root;
    
    Build(root);
    
    HLDecomp::Init(rt);
    
    int q; scanf("%d", &q);
    for (int i = 1; i <= q; ++i) {
        static int u, v;
        
        scanf("%d%d", &u, &v);
        int lca = HLDecomp::LCA(u, v);
        qrys[lca].emplace_back(u, v, i);
    }
    
    memset(vis, 0, sizeof vis);
    
    total = n;
    root = 0;
    Focus(1, 0);
    
    DAC(root);
    
    for (int i = 1; i <= q; ++i)
        printf("%d\n", ans[i]);
    
    return 0;
}
