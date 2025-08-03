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

vector<int> edge[maxn];
int in[maxn],out[maxn],dep[maxn],tot;
int fa[maxn],top[maxn],sz[maxn],son[maxn];
void dfs1(int x,int f,int depth) {
	int mx=-1; sz[x]=1;
	fa[x]=f; dep[x]=depth; son[x]=0;
	for (int v:edge[x]) if (v!=f) {
			dfs1(v,x,depth+1);
			sz[x]+=sz[v];
			if (sz[v]>mx) mx=sz[v],son[x]=v;
		}
}
void dfs2(int u,int x) {
	top[u]=x; in[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	for (int v:edge[u]) {
		if (v==son[u]||v==fa[u]) continue;
		dfs2(v,v);
	} out[u]=tot;
}
int lca(int x,int y) {
	while (top[x]!=top[y]) {
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	return x;
}

int n;
inline int lowbit(int x) {return x&-x;}
int F[maxn];
void update(int x,int val) {
	for (; x<=n; x+=lowbit(x)) F[x]+=val;
}
void update(int l,int r,int val) {
	update(l,val); update(r+1,-val);
}
int query(int x) {
	int ret=0;
	for (; x; x-=lowbit(x)) ret+=F[x];
	return ret;
}
const int maxp=1e6+7;
struct node {
	int pos,cnt,id,inv;
	node(int _p=0,int _c=0,int _id=0,int _inv=0):pos(_p),cnt(_c),id(_id),inv(_inv) {}
};
vector<node> queries[maxp];
bool mark[(int)1e7+7];
int p[maxp],pn;
int ans[maxn];
int main() {
	int q;
	int i,j;
	FOR(i,2,10000000) {
		if (!mark[i]) p[pn++]=i;
		REP(j,pn) {
			if (i*p[j]>10000000) break;
			mark[i*p[j]]=1;
			if (i*p[j]==0) break;
		}
	} debug("pn=%d\n",pn);
	scanf("%d",&n);
	FOR(i,2,n) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs1(1,0,1); dfs2(1,1);
	FOR(i,1,n) {
		int x;
		scanf("%d",&x);
		REP(j,pn) {
			if (p[j]*p[j]>x) break;
			if (x%p[j]==0) {
				int cnt=0;
				while (x%p[j]==0) {
					x/=p[j],cnt++;
					queries[j].push_back(node(i,cnt,0,0));
				}
			}
		} if (x!=1) {
			j=lower_bound(p,p+pn,x)-p;
			queries[j].push_back(node(i,1,0,0));
		}
	}
	scanf("%d",&q);
	FOR(i,1,q) {
		ans[i]=1;
		int u,v,x,f,F;
		scanf("%d%d%d",&u,&v,&x);
		f=lca(u,v); F=fa[f];
		REP(j,pn) {
			if (p[j]*p[j]>x) break;
			if (x%p[j]==0) {
				int cnt=0;
				while (x%p[j]==0) x/=p[j],cnt++;
				if (cnt) {
					queries[j].push_back(node(u,cnt,i,0));
					queries[j].push_back(node(v,cnt,i,0));
					queries[j].push_back(node(f,cnt,i,1));
					if (F) queries[j].push_back(node(F,cnt,i,1));
				}
			}
		} if (x!=1) {
			j=lower_bound(p,p+pn,x)-p;
			queries[j].push_back(node(u,1,i,0));
			queries[j].push_back(node(v,1,i,0));
			queries[j].push_back(node(f,1,i,1));
			if (F) queries[j].push_back(node(F,1,i,1));
		}
	}

	REP(i,pn) if (queries[i].size()) {
		debug("query %d :\n",p[i]);
		sort(queries[i].begin(), queries[i].end(),[](node &A,node &B) {
			if (A.cnt==B.cnt) return A.id<B.id;
			else return A.cnt<B.cnt;
		});
		for (auto now:queries[i]) {
			if (now.id) {
				debug("query : %d (in=%d) (%d)\n",now.pos,in[now.pos],now.cnt);
				int cnt=query(in[now.pos]);
				int base=p[i];
				if (now.inv) base=powMM((LL)base,M-2);
				ans[now.id]=(LL)ans[now.id]*powMM(base,cnt)%M;
			} else {
				debug("update : %d (%d-%d) (%d)\n",now.pos,in[now.pos],out[now.pos],now.cnt);
				update(in[now.pos],out[now.pos],1);
			}
		}
		for (auto now:queries[i]) {
			if (!now.id) update(in[now.pos],out[now.pos],-1);
		}
	}
	FOR(i,1,q) printf("%d\n",ans[i]);
	return 0;
}
/*
*/
