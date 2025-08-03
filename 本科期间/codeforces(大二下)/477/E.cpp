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
const LL maxn=1e5+7;
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

int n;
vector<int> limit[maxn];
int SIZE=300;
int A[maxn],Del[maxn];
int BID[maxn],L[maxn],R[maxn],p[maxn];//p:偏置
void rebuild(int x){
//    printf("rebuild:%d\n",x);
    int i;
    limit[x].clear();
    FOR(i,L[x],R[x]) if (!Del[i])
        limit[x].push_back(A[i]);
    sort(limit[x].begin(),limit[x].end());
//    FOR(i,1,n) printf("%d ",A[i]);puts("<- A");
}
void change(int l,int r,int val){
//    dbg(l);dbg(r);dbgln(val);
    int i;
    if (BID[l]==BID[r]){
        FOR(i,l,r) A[i]+=val;
        rebuild(BID[l]);
    }else{
        FOR(i,l,R[BID[l]]) A[i]+=val; rebuild(BID[l]);
        FOR(i,L[BID[r]],r) A[i]+=val; rebuild(BID[r]);
        FOR(i,BID[l]+1,BID[r]-1) p[i]+=val;
    }
}
int query(){
    int ret=0,i;
//    FOR(i,0,BID[n]){
//        printf("%d :(p=%d)  ",i,p[i]);for (int v:limit[i]) printf("%d ",v); puts(" ");
//    }
    FOR(i,0,BID[n])
        ret+=lower_bound(limit[i].begin(),limit[i].end(),-p[i])-limit[i].begin();
    return ret;
}

vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],dep[maxn];
int id[maxn],tot;
void dfs1(int u,int depth){
    int mx=-1;
    sz[u]=1;dep[u]=depth;son[u]=0;
    for (int v:edge[u]){
        dfs1(v,depth+1);
        sz[u]+=sz[v];
        if (sz[v]>mx) mx=sz[v],son[u]=v;
    }
}
void dfs2(int u,int x){
    int i;
    top[u]=x;id[u]=++tot;
    if (son[u]) dfs2(son[u],x);
    for (int v:edge[u])
        if (v!=son[u]) dfs2(v,v);
}
void update(int x,int val){
    if (val==-1) Del[id[x]]=1;
    else Del[id[x]]=0;
    while (x){
        change(id[top[x]],id[x],val);
        x=fa[top[x]];
    }
}
int m;
int B[maxn];
int main() {
    int i,j;
    scanf("%d%d",&n,&m);
    FOR(i,2,n){
        scanf("%d",&fa[i]);
        edge[fa[i]].push_back(i);
    }FOR(i,1,n) scanf("%d",&B[i]);
    dfs1(1,0);
    dfs2(1,1);
    FOR(i,1,n) A[id[i]]=B[i];
    SIZE=sqrt(n)*0.7;
    if (SIZE==0) SIZE=1;
//    SIZE=300;
    FOR(i,1,n) {
        BID[i]=i/SIZE; R[BID[i]]=i;
        if (!L[BID[i]]) L[BID[i]]=i;
    }FOR(i,0,BID[n]) rebuild(i);
//    FOR(i,1,n) printf("%d ",id[i]);puts("");
//    FOR(i,1,n) printf("%d ",A[i]);puts("");
    REP(i,m){
        int x;
        scanf("%d",&x);
        if (x>0) update(x,-1);
        else update(-x,1);
        printf("%d\n",query());
    }
    return 0;
}
/*
*/
