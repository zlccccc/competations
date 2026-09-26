#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
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
const LL maxn=(1<<20)+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int f[maxn][20],a[maxn];
int h[maxn],H[maxn];
vector<int> edge[maxn];
void dfs(int x,int fa){
    H[x]=H[fa]+1;int FA=fa,i;
//    printf("  FA %d=%d,H=%d\n",x,FA,H[x]);
    rREP(i,20) if (f[FA][i]&&a[f[FA][i]]<=a[x]) FA=f[FA][i];
    if (a[FA]<=a[x]) FA=f[FA][0];
    f[x][0]=FA;h[x]=h[FA]+1;
//    printf(" fa %d=%d,h=%d\n",x,FA,h[x]);
    rep(i,1,20) f[x][i]=f[f[x][i-1]][i-1];
    for (int v:edge[x]) if (v!=fa) dfs(v,x);
}int n,q;
int i,j,k;
int main(){
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%d",&a[i]);
    FOR(i,1,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }dfs(1,0);
    FOR(i,1,q){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        rREP(j,20) if (f[u][j]&&a[f[u][j]]<=c) u=f[u][j];
        if (a[u]<=c) u=f[u][0];
//        printf("Q :  %d\n",u);
        int ans=h[u];u=u;
        rREP(j,20) if (H[f[u][j]]>=H[v]) u=f[u][j];
        if (H[u]>=H[v]) u=f[u][0];
//        printf("HH :  %d %d\n",h[u],u);
        ans-=h[u];
        printf("%d\n",ans);
    }
}
/*
*/
