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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5e5+7;
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

struct Edge {
    int to,next;
    Edge(int _to=0,int _next=-1):to(_to),next(_next) {};
} edge[maxn*2];
int head[maxn],etot;
inline void addedge(int u,int v) {
    edge[++etot]=Edge(v,head[u]);
    head[u]=etot;
}
int cnt;
int dfn[maxn],low[maxn],tot;
bool vis[maxn];//instack
int S[maxn],top;
int id[maxn];
void tarjan(int x,int fa) {
    low[x]=dfn[x]=++tot;
    S[++top]=x;
    vis[x]=1;
    for(int i=head[x]; ~i; i=edge[i].next) {
        int v=edge[i].to;
        if(v==fa) continue;
        if(!dfn[v]) {
            tarjan(v,x);
            low[x]=min(low[x],low[v]);
        } else if(vis[v])
            low[x]=min(low[x],dfn[v]);
    }
    if(low[x]==dfn[x]) {
        cnt++;
        while(1) {
            int now=S[top--];
            vis[now]=0;
            id[now]=cnt;
            if(now==x) break;
        }
    }
}
int fid[maxn];
LL A[maxn],B[maxn];
int main() {
    int i,n,m,T;LL p,s;
    scanf("%d",&n);
    FOR(i,1,n) head[i]=-1;
    FOR(i,1,n) scanf("%lld",&A[i]),fid[i]=i;
    scanf("%d",&m);
    while(m--){
        int op;
        scanf("%d",&op);
        if (op==1){
            int x,l,r;
            scanf("%d%d%d",&x,&l,&r);
            FOR(i,l,r) addedge(fid[x],fid[i]);
        }else{
            int x;LL val;
            scanf("%d%lld",&x,&A[++n]);
            fid[x]=n;head[n]=-1;
        }
    }FOR(i,1,n) if (!dfn[i]) tarjan(i,0);
    LL ans=INFF;
    FOR(i,1,n) B[id[i]]+=A[i];
    FOR(i,1,n) {
        for (int v=head[i];~v;v=edge[v].next)
            if (id[edge[v].to]!=id[i]) B[id[i]]=INFF;
    }
    FOR(i,1,cnt) ans=min(ans,B[i]);
//    FOR(i,1,cnt) printf("%lld ",B[i]);
    printf("%lld\n",ans);
}
/*
*/
