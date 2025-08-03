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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
 
int fa[maxn][21];
int dep[maxn],tot;
vector<int> edge[maxn];
int ans;
void dfs(int x,int f,int depth){
    int i;
    fa[x][0]=f;dep[x]=depth;
    rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int v:edge[x]){
        if (v==f) continue;
        dfs(v,x,depth+1);
    }
}
int lca(int x,int y){
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int dis(int x,int y){
    return dep[x]+dep[y]-2*dep[lca(x,y)];
}
vector<int> S;
int main(){
    int n,i;
    scanf("%d",&n);
    REP(i,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }
    int q;
    scanf("%d",&q);
    dfs(1,0,1);
    while (q--){
        int u,v,m;
        scanf("%d",&m);
        v=0;
        REP(i,m){
            scanf("%d",&u);
            S.push_back(u);
            if (dep[u]>dep[v]) v=u;
        }
        ans=0;
        for (int u:S) ans=max(ans,dis(u,v));
        S.clear();
        printf("%d\n",(ans+1)/2);
    }
    return 0;
}
/*
*/
