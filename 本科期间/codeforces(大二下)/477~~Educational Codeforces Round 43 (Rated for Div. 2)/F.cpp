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
const LL maxn=4000+7;
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



struct node{
    int to,cap,next;
    node(int t=0,int c=0,int n=0):to(t),cap(c),next(n){}
}edge[maxn*5];
int head[maxn];
int tot;
inline int addedge(int from,int to,int cap,int rcap=0){
    edge[tot]=node(to,cap,head[from]);head[from]=tot++;
    edge[tot]=node(from,rcap,head[to]);head[to]=tot++;
    return tot-2;
}
queue<int> Q;
bool vis[4007];
int d[4007];
bool bfs(int s,int t){
    memset(vis,0,sizeof(vis));
    while (Q.size()) Q.pop();
    Q.push(s);
    d[s]=0;vis[s]=1;
    while (Q.size()){
        int x=Q.front();Q.pop();
        for (int i=head[x];~i;i=edge[i].next){
            int v=edge[i].to;
            if (!vis[v]&&edge[i].cap){
                vis[v]=1;d[v]=d[x]+1;
                Q.push(v);
            }
        }
    }return vis[t];
}
int dfs(int x,int t,int flow){
    if (x==t||flow==0) return flow;
    int i,ret=0,f;
    for (i=head[x];~i;i=edge[i].next){
        if (d[x]+1==d[edge[i].to]&&((f=dfs(edge[i].to,t,min(flow,edge[i].cap)))>0)){
            edge[i].cap-=f;
            edge[i^1].cap+=f;
            ret+=f;flow-=f;
            if (flow==0) break;
        }
    }return ret;
}
int sid[maxn],tid[maxn],eid[maxn],d1[maxn],d2[maxn];
vector<int> ans[maxn];
int main() {
    int i,j;
    int n1,n2,m;
    scanf("%d%d%d",&n1,&n2,&m);
    FOR(i,1,n1+n2+2) head[i]=-1;
    int s=n1+n2+1,t=n1+n2+2;
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        d1[u]++;d2[v]++;
        eid[i]=addedge(u,v+n1,1);
    }
    int all=m;
    FOR(i,1,n1) all=min(all,d1[i]);
    FOR(i,1,n2) all=min(all,d2[i]);
    FOR(i,1,n1) sid[i]=addedge(s,i,d1[i]-all);
    FOR(i,1,n2) tid[i]=addedge(i+n1,t,d2[i]-all);
    //去掉多余的边
    rFOR(j,0,all){
        while (bfs(s,t)) dfs(s,t,n1);
        FOR(i,1,m) if (edge[eid[i]].cap) ans[j].push_back(i);
        FOR(i,1,n1) edge[sid[i]].cap++;
        FOR(i,1,n2) edge[tid[i]].cap++;
    }FOR(j,0,all){
        printf("%d",(int)ans[j].size());
        for (int v:ans[j]) printf(" %d",v);
        puts("");
    }
    return 0;
}
/*
*/
