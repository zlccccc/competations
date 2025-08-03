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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=250000+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

vector<int> edge[maxn];
int val[307];
int n,m;
int dfs(int x,int y,int id){
    val[x]=id;val[y]=n/2+id;
    if (id==n/2-1){
        for (int v:edge[x])
            for (int u:edge[y])
                if (val[v]==0&&val[u]==n/2) return 1;
        return 0;
    }
    for (int v:edge[x]) if (val[v]==-1)
        for (int u:edge[y]) if (val[u]==-1)
            for (int k:edge[v]) if (k==u)
                return dfs(v,u,id+1);
    return 0;
}
int solve(){
    for (int v:edge[0]){
        int i;
        REP(i,n) val[i]=-1;
        if (dfs(0,v,0)) return 1;
    }return 0;
}int T;
int V[307];
int E[207][207];
int Solve(){
    int i,j;
    REP(i,n) if (edge[i].size()!=3) return 0*puts("-1");
    if (n<6) return 0*puts("-1");
    if (solve()){
        REP(i,n) V[val[i]]=i;
        REP(i,n/2){
            assert(E[V[i]][V[(i+1)%(n/2)]]);
            assert(E[V[i+n/2]][V[n/2+(i+1)%(n/2)]]);
            assert(E[V[i]][V[i+n/2]]);
        }
        REP(i,n) printf("%d ",V[i]);
        return 0*puts("");
    }return 0*puts("-1");
}
int main(){
    scanf("%d",&T);
	while (T--){
        int i,j;
        scanf("%d%d",&n,&m);
        REP(i,n) edge[i].clear();
        REP(i,n) REP(j,m) E[i][j]=0;
        FOR(i,1,m){
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
            E[u][v]=1;E[v][u]=1;
        }Solve();
	}
}
/*
3
6 9
0 1
1 2
2 0
3 4
4 5
3 5
0 3
1 4
2 5
8 12
0 1
0 2
0 3
4 5
4 6
4 7
1 5
1 6
2 6
2 7
3 7
3 5
6 9
0 1
0 2
0 3
0 4
0 5
1 2
1 3
1 4
1 5
*/
