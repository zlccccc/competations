#include<bits/stdc++.h>

const int N = 16;
const int moder = (int) 1e9 + 7;

std::map <int, int> fa;
int mult[1 << N];
int dp[1 << N];
bool containmin[1 << N];
std::vector <int> transfer[1 << N];

int find(int u){
    return u == fa[u] ? u : (fa[u] = find(fa[u]));
}

void unite(int u, int v){
    u = find(u), v = find(v);
    if (u == v) return;
    fa[u] = v;
}

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

const int inv9 = powermod(9, moder - 2);

int calc(int n, bool equal){
    int ret = 1ll * (powermod(10, n) - 1) * inv9 % moder;
    if (equal){
        ++ ret;
        ret -= ret >= moder ? moder : 0;
    }
    return ret;
}

int main(){
    //int begin = clock();
    //srand((unsigned) time(NULL));
    int n, q;
    scanf("%d%d", &n, &q);
    //n = 1e9;
    //q = 15;
    for (int i = 0, l, r; i < q; ++ i){
        scanf("%d%d", &l, &r);
        //l = rand() % n + 1, r = rand() % n + 1;
        //if (l > r) std::swap(l, r);
        -- l;
        if (!fa.count(l)) fa[l] = l;
        if (!fa.count(r)) fa[r] = r;
        unite(l, r);
    }
    std::map <int, std::vector <int>> map;
    std::vector <int> point;
    for (auto u : fa){
        point.push_back(u.first);
    }
    int sz = point.size();
    int ans = powermod(10, n - point.back());
    for (int i = 0; i < sz; ++ i){
        if (i == 0 && point[i] == 0) continue;
        ans = 1ll * ans * calc(point[i] - (i ? point[i - 1] : 0), false) % moder;
    }
    for (auto u : point){
        map[find(u)].push_back(u);
    }
    std::vector <std::vector <int>> vec;
    int bit = 0;
    for (auto u : map){
        vec.push_back(u.second);
        ++ bit;
    }
    dp[0] = 1;
    for (int i = 0; i < 1 << bit; ++ i){
        std::vector <int> totvec;
        for (int j = 0; j < bit; ++ j){
            if (i >> j & 1){
                for (auto u : vec[j]){
                    totvec.push_back(u);
                }
            }
        }
        std::sort(totvec.begin(), totvec.end());
        mult[i] = 1;
        for (int j = 0, tsz = totvec.size(); j < tsz - 1; ++ j){
            int sit = std::lower_bound(point.begin(), point.end(), totvec[j]) - point.begin();
            if (point[sit + 1] == totvec[j + 1]){
                int dis = point[sit + 1] - point[sit];
                mult[i] = 1ll * mult[i] * calc(dis, true) % moder * powermod(calc(dis, false), moder - 2) % moder;
            }
        }
        containmin[i] = !totvec.empty() && totvec[0] == point[0];
    }
    int dis = point[0];
    int coe0 = 1ll * calc(dis, true) * powermod(calc(dis, false), moder - 2) % moder;
    for (int i = 0; i < (1 << bit) - 1; ++ i){
        std::vector <int> bits;
        int x = i ^ ((1 << bit) - 1);
        while (x){
            bits.push_back(x & -x);
            x ^= x & -x;
        }
        for (int j = 1, bsz = bits.size(); j < 1 << bsz; ++ j) {
            int mask = 0;
            for (int u = 0; u < bsz; ++u) {
                if (j >> u & 1) {
                    mask |= bits[u];
                }
            }
            transfer[i].push_back(mask);
        }
    }
    for (int i = 0; i < 9; ++ i){
        for (int j = (1 << bit) - 1; j >= 0; -- j){
            for (auto mask : transfer[j]){
                if (i != 0 && containmin[mask] && point[0] == 0){
                    continue;
                }
                int &u = dp[j | mask];
                int x = i == 0 && containmin[mask] && point[0] != 0 ? coe0 : 1;
                u = (u + 1ll * dp[j] * mult[mask] % moder * x) % moder;
            }
        }  
        for (int j = 0; j <=(1 << bit) - 1; j++) printf("%lld ",1ll*ans * dp[j] % moder); puts("");
        printf("%lld\n",1ll*ans * dp[(1 << bit) - 1] % moder);
    }
    ans = 1ll * ans * dp[(1 << bit) - 1] % moder;
    printf("%d\n", ans);
    //printf("%.15f\n", 1.0 * (clock() - begin) / CLOCKS_PER_SEC);
    return 0;
}