#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

int fa[maxn][20];
vector<pair<int,LL> > edge[maxn];
LL beauty[maxn],cnt[maxn];
void dfs(int x,int f){
    int i;fa[x][0]=f;
    rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    beauty[x]=cnt[x]=0;
    for (auto v:edge[x]) if (v.first!=f){
        dfs(v.first,x);
        beauty[x]+=cnt[v.first]*v.second;
        beauty[x]+=beauty[v.first];
        cnt[x]+=cnt[v.first];
    }cnt[x]++;
}
int n,m;
int main() {
    int i,j;
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        FOR(i,1,n) edge[i].clear(),beauty[i]=cnt[i]=0;
        FOR(i,1,n-1){
            int u,v;LL d;
            scanf("%d%d%lld",&u,&v,&d);
            edge[u].push_back(make_pair(v,d));
            edge[v].push_back(make_pair(u,d));
        }
        dfs(1,0);
        LL ans=-1;
//        FOR(i,1,n) printf("%lld ",beauty[i]);puts("");
        FOR(i,1,n){
            int f=i;
            rREP(j,20)
                if (fa[f][j]&&beauty[fa[f][j]]-beauty[i]<=m)
                    f=fa[f][j];
            if (i!=f) ans=max(ans,(LL)(beauty[f]-beauty[i]));
        }printf("%lld\n",ans);
    }
    return 0;
}
/*
10
3 4
1 2 1
1 3 2
3 4
1 2 3
1 3 2
4 6
1 2 2
2 3 5
3 4 2
2 0
1 2 1
*/
