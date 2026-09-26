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
#include <bitset>
#include <utility>
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
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

typedef pair<int,int> pii;
vector<pii> edge[3007];
bitset<200> f[3007][107],g[3007][107];
void dfsup(int x,int fa){
    int i;
    FOR(i,1,100) f[x][i][0]=1;
    for (auto now:edge[x]) if (now.first!=fa){
        int v=now.first;
        dfsup(v,x);
        FOR(i,1,100){
            g[v][i]|=f[x][i]<<(now.second%i);
            f[x][i]|=f[v][i]<<(now.second%i);
            f[x][i]|=f[x][i]>>i;
            g[v][i]|=g[v][i]>>i;
        }
    }reverse(edge[x].begin(),edge[x].end());
}void dfsdown(int x,int fa){
    int i;
    for (auto now:edge[x]) if (now.first!=fa){
        int v=now.first;
        FOR(i,1,100){
            g[v][i]|=g[x][i]<<(now.second%i);
            g[v][i]|=g[v][i]>>i;
            f[v][i]|=g[v][i];
        }dfsdown(v,x);
    }
}
int n,q;
int i,j,k;
int main(){
    while (~scanf("%lld",&n)){
        FOR(i,1,n) edge[i].clear();
        REP(i,n-1){
            int u,v,l;
            scanf("%d%d%d",&u,&v,&l);
            edge[u].push_back(make_pair(v,l));
            edge[v].push_back(make_pair(u,l));
        }dfsup(1,0);
        FOR(i,1,n) FOR(j,1,100) f[i][j].reset();//dfs_right
        dfsup(1,0);
        dfsdown(1,0);
        scanf("%d",&q);
        while (q--){
            int u,k;
            scanf("%d%d",&u,&k);
            for (i=k-1;f[u][k][i]==0;i--);
            printf("%d\n",i);
        }FOR(i,1,n) FOR(j,1,100) g[i][j].reset(),f[i][j].reset();
    }
}
/*
3
1 2 7
1 3 6
5
1 9
1 7
3 2
3 15
2 7
*/
