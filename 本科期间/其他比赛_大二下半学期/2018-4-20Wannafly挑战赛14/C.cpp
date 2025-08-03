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

struct Edge {
    int to,next;
    Edge(int _to=0,int _next=-1):to(_to),next(_next) {};
} edge[maxn*2];
int head[maxn],etot;
inline void addedge(int u,int v) {
    edge[++etot]=Edge(v,head[u]);
    head[u]=etot;
}
vector<int> nodes[maxn];
int cnt;
int dfn[maxn],low[maxn],tot;
bool vis[maxn];//instack
int S[maxn],top;
int id[maxn];
void tarjan(int x) {
    low[x]=dfn[x]=++tot;
    S[++top]=x;
    vis[x]=1;
    for(int i=head[x]; ~i; i=edge[i].next) {
        int v=edge[i].to;
        if(!dfn[v]) {
            tarjan(v);
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
			nodes[cnt].push_back(now);
            if(now==x) break;
        }
    }
}
vector<int> ans;
int F[maxn];
int d[maxn];
int main() {
    int i,j;
    int T;
    int n,m;
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u,v);
    }FOR(i,1,n) if (!dfn[i]) tarjan(i);
    FOR(i,1,n)
        for (int v=head[i];~v;v=edge[v].next)
            if (id[i]!=id[edge[v].to]) d[id[edge[v].to]]++;
    FOR(i,1,cnt) F[i]=INF;
    FOR(i,1,n) F[id[i]]=min(F[id[i]],i);
    FOR(i,1,cnt) if (!d[i]) ans.push_back(F[i]);
    sort(ans.begin(),ans.end());
    printf("%d\n",ans.size());
    REP(i,ans.size()) printf("%d%c",ans[i]," \n"[i==ans.size()-1]);
    return 0;
}
/*
2 2 3 3
+-++++
*/
