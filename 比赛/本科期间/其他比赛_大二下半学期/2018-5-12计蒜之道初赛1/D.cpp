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
const LL maxn=4e6+7;
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
} edge[maxn];
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
    }if(low[x]==dfn[x]) {
        cnt++;
        while(1) {
            int now=S[top--];
            vis[now]=0;
            id[now]=cnt;
            if(now==x) break;
        }
    }
}
int val[maxn],timetot,fid[maxn];
void build(int x,int L,int R){
    val[x]=++timetot;
    if (L==R){
        fid[L]=val[x];
        return;
    }int mid=(L+R)/2;
    build(x<<1,L,mid);
    build(x<<1|1,mid+1,R);
    addedge(val[x],val[x<<1]);
    addedge(val[x],val[x<<1|1]);
}
void update(int x,int pos,int L,int R){
    val[x]=++timetot;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    if (mid<pos) update(x<<1|1,pos,mid+1,R);
    addedge(val[x],val[x<<1]);
    addedge(val[x],val[x<<1|1]);
}
vector<int> pre,now;
void query(int x,int l,int r,int L,int R){
    if (l<=L&&R<=r){
        now.push_back(val[x]);
        return;
    }int mid=(L+R)/2;
    if (l<=mid) query(x<<1,l,r,L,mid);
    if (mid<r) query(x<<1|1,l,r,mid+1,R);
}
LL A[maxn],B[maxn];
int main() {
    int i,n,m,T;
    scanf("%d",&n);int N=n;
    FOR(i,1,n*40) head[i]=-1;
    FOR(i,1,n) scanf("%lld",&A[i]);
    build(1,1,n);
    scanf("%d",&m);
    while(m--){
        int op;
        scanf("%d",&op);
        if (op==1){
            int x,l,r;
            scanf("%d%d%d",&x,&l,&r);
            pre.clear();now.clear();
            query(1,x,x,1,N);swap(pre,now);
            query(1,l,r,1,N);
            for (int u:pre) for (int v:now)
                addedge(u,v);
        }else{
            int x;LL val;
            scanf("%d%lld",&x,&A[++n]);
            update(1,x,1,N);
            now.clear();
            query(1,x,x,1,N);
            fid[n]=now[0];
        }
    }FOR(i,1,timetot) if (!dfn[i]) tarjan(i,0);
    LL ans=INFF;
    FOR(i,1,n) B[id[fid[i]]]+=A[i];
    FOR(i,1,timetot)
        for (int v=head[i];~v;v=edge[v].next)
            if (id[edge[v].to]!=id[i]) B[id[i]]=INFF;
    FOR(i,1,cnt) ans=min(ans,B[i]);
    printf("%lld\n",ans);
}
/*
*/
