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

int sum[maxn*4];
void pushup(int x){
    sum[x]=sum[x<<1]+sum[x<<1|1];
}
void build(int x,int l,int r){
	if (l==r){
        sum[x]=1;
		return;
	}int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void update(int x,int l,int r,int L,int R){//negative
    if (!sum[x]) return;
	if (l<=L&&R<=r){
        sum[x]=0;
		return;
	}int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,L,mid);
	if (r>mid) update(x<<1|1,l,r,mid+1,R);
	pushup(x);
}
int query(int x,int l,int r,int L,int R){
    if (!sum[x]) return 0;
	if (l<=L&&R<=r) return sum[x];
	int mid=(L+R)/2,ret=0;
	if (mid>=l) ret+=query(x<<1,l,r,L,mid);
	if (r>mid) ret+=query(x<<1|1,l,r,mid+1,R);
	pushup(x);
	return ret;
}
vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int tot;
void dfs1(int u,int from,int depth){
	int v,i,mx=-1;
	sz[u]=1;fa[u]=from;dep[u]=depth;son[u]=0;
	REP(i,(int)edge[u].size()){
		v=edge[u][i];
		if (v==from) continue;
		dfs1(v,u,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x){
	int v,i;
	top[u]=x;id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	REP(i,(int)edge[u].size()){
		v=edge[u][i];
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
inline void Update(int x,int y){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,id[top[x]],id[x],1,tot);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	update(1,id[x],id[y],1,tot);
}
inline int Query(int x,int y){
	int ret=0;
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		ret+=query(1,id[top[x]],id[x],1,tot);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	ret+=query(1,id[x],id[y],1,tot);
	return ret;
}
vector<int> ans;
int main() {
    int n,k,i;
    scanf("%d%d",&n,&k);
    FOR(i,1,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        if (u>v) swap(u,v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }dfs1(1,0,0);
    dfs2(1,1);
    build(1,1,n);
    int now=n;
    rFOR(i,1,n){
        int len=Query(i,n);
//        printf("%d:len=%d\n",i,len);
        if (now-len>=k){
            now-=len;
            Update(i,n);
        }else ans.push_back(i);
    }reverse(ans.begin(),ans.end());
    for (int v:ans) printf("%d ",v);
    return 0;
}
/*
*/
