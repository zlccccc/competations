#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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

#define DEBUG1
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
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


set<int> Q[maxn];
int A[maxn];
vector<int> edge[maxn],nodes[maxn];
int dep[maxn],in[maxn],out[maxn],tot,sz[maxn];
int top[maxn],son[maxn],fa[maxn],id[maxn];
int n;
int cnt[maxn];
inline int lowbit(int x){return x&-x;}
void update(int x,int val){
    debug("  up %d(%d) %d\n",x,id[x],val);
    for (;x<=n;x+=lowbit(x)) cnt[x]+=val;
}
void tozero(int x){
    for (;x<=n;x+=lowbit(x)) cnt[x]=0;
}
int query(int x){
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=cnt[x];
    return ret;
}
int query(int l,int r){
    return query(r)-query(l-1);
}
void dfs1(int x,int depth){
    int mx=-1;son[x]=0;
    dep[x]=depth;sz[x]=1;
    for (int v:edge[x]) {
        dfs1(v,depth+1); sz[x]+=sz[v];
        if (sz[v]>mx) mx=sz[v],son[x]=v;
    }
}
void dfs2(int u,int x){
    top[u]=x;in[u]=++tot;id[tot]=u;
    if (son[u]) dfs2(son[u],x);
    for (int v:edge[u]){
        if (v==son[u]) continue;
        dfs2(v,v);
    }out[u]=tot;
}
int lca(int x,int y){
    while (top[x]!=top[y]){
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }if (dep[x]>dep[y]) swap(x,y);
    return x;
}
int ans[maxn];
struct qwq{
    int l,r,dep,k,id;
    qwq(int _l=0,int _r=0,int _dep=0,int _k=0,int _i=0):l(_l),r(_r),dep(_dep),k(_k),id(_i){};
};
vector<qwq> queries[maxn*4];
qwq l_l[maxn];
vector<int> clr;
void solve(int x,int l,int r){
    debug("\nquery : %d %d %d\n",x,l,r);
    if (l==r){
        for (auto now:queries[x]) ans[now.id]=l;
        return;
    }int mid=(l+r)/2,tot=0,i;
    FOR(i,l,mid) for (int v:nodes[i])
        l_l[tot++]=qwq(v,0,dep[v],0,0);//careful!!!
    for (auto now:queries[x]) l_l[tot++]=now;
    vector<qwq>().swap(queries[x]);
    clr.clear();
    sort(l_l,l_l+tot,[](qwq &A,qwq &B){
        if (A.dep==B.dep) return A.r<B.r;
        return A.dep<B.dep;
    });
    REP(i,tot){
        auto now=l_l[i];
        if (now.id){
            int number=query(now.l,now.r);
            debug("Q:%d %d %d (%d) -> %d(have %d)\n",now.l,now.r,now.dep,now.k,now.id,number);
            if (number<now.k){
                now.k-=number;
                queries[x<<1|1].push_back(now);
            }else queries[x<<1].push_back(now);
        }else {
            update(in[now.l],1);clr.push_back(now.l);
            int pre=0,suf=0;
            Q[A[now.l]].insert(in[now.l]);
            auto it=Q[A[now.l]].lower_bound(in[now.l]);
            if (it!=Q[A[now.l]].begin()){it--;pre=*it;it++;}
            if ((++it)!=Q[A[now.l]].end()){suf=*it;}
            debug("A:%d %d;\n",now.l,now.dep); debug("pre=%d suf=%d\n",pre,suf);
            debug("?  %d %d\n",A[now.l],in[now.l]);
            if (pre) update(in[lca(now.l,id[pre])],-1),clr.push_back(lca(now.l,id[pre]));
            if (suf) update(in[lca(now.l,id[suf])],-1),clr.push_back(lca(now.l,id[suf]));
            if (pre&&suf) update(in[lca(id[pre],id[suf])],1),clr.push_back(lca(id[pre],id[suf]));
        }
    }for (int v:clr) tozero(in[v]),Q[A[v]].clear();
    solve(x<<1,l,mid);
    solve(x<<1|1,mid+1,r);
}
int main() {
    int i,j,q;
    scanf("%d%d",&n,&q);
    FOR(i,2,n) scanf("%d",&fa[i]),edge[fa[i]].push_back(i);
    FOR(i,1,n) scanf("%d",&A[i]),nodes[A[i]].push_back(i);
    dfs1(1,1);dfs2(1,1);
    FOR(i,1,n) debug("%d ",in[i]);debug("\n");
    FOR(i,1,n) debug("%d ",out[i]);debug("\n");
    FOR(i,1,n) debug("%d ",id[i]);debug("\n");
    FOR(i,1,q){
        int x,y,k;
        scanf("%d%d%d",&x,&y,&k);
        queries[1].push_back(qwq(in[x],out[x],min(n,dep[x]+y),k,i));
    }solve(1,1,n+1);
    FOR(i,1,q) printf("%d\n",ans[i]==n+1?-1:ans[i]);
    return 0;
}
/*
5 3
1 1 2 2
1 2 1 3 2
1 1 2
1 2 3
2 1 2
*/
