#include <sstream>
#include <fstream>
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

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

vector<int> nodes,edge[maxn];
vector<pair<int,int> > edges;
int dep[maxn],dfn[maxn],tot,fa[maxn];
void dfs(int x,int father,int depth) {
	dep[x]=depth; dfn[x]=++tot;
	for (int v:edge[x]) if (v!=father){
		if (dep[v]) {
			if (x<v){
				nodes.push_back(v);
				nodes.push_back(x);
				edges.push_back(make_pair(x,v));
			}
		} else dfs(v,x,depth+1),fa[v]=x;
	}
}
inline int lca(int x,int y) {
	if (dep[x]<dep[y]) swap(x,y);
	while (dep[x]!=dep[y]) x=fa[x];
	while (x!=y) x=fa[x],y=fa[y];
	return x;
}
namespace vtree {
	int S[maxn],top;
	int pid[maxn],mark[maxn];
	int vid[maxn],vfa[maxn];
	inline void addedge(int u,int v) {vfa[v]=u;}
	int m;
	void vbuild(int n) {
		int i; m=0;
		sort(pid+1,pid+1+n,[](int x,int y) {
			return dfn[x]<dfn[y];
		});	S[top=1]=pid[1];
		mark[pid[1]]=1;
		FOR(i,2,n) {
			int f=lca(pid[i-1],pid[i]);
			while (top&&dep[S[top]]>dep[f]) {
				int v; vid[++m]=v=S[top--];
				if (top&&dep[S[top]]>dep[f]) addedge(S[top],v);
				else addedge(f,v);
			} if (!top||S[top]!=f) S[++top]=f;
			S[++top]=pid[i]; mark[pid[i]]=1;
		} while (top-1) addedge(S[top-1],S[top]),vid[++m]=S[top--];
		vid[++m]=S[1];
		reverse(vid+1,vid+m+1);
	}
}
bool mask[maxn];
int d[maxn],Fa[maxn];
inline int getfa(int x) {
	if (Fa[x]==x) return x;
	return Fa[x]=getfa(Fa[x]);
}
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs(1,0,1); int t=0;
	sort(nodes.begin(), nodes.end());
	nodes.erase(unique(nodes.begin(), nodes.end()),nodes.end());
	for (int v:nodes) vtree::pid[++t]=v;
	vtree::vbuild(t);
	// for (auto now:edges) {printf(" %d-%d\n",now.first,now.second);}
	// FOR(i,1,vtree::m) printf("%d ",vtree::vid[i]); puts("");
	// FOR(i,1,vtree::m) printf("%d ",vtree::vfa[vtree::vid[i]]); puts("");
	nodes.clear();
	FOR(i,1,vtree::m) nodes.push_back(vtree::vid[i]);
	int sta,ans=0;
	n=edges.size(); m=1<<n;
	rep(sta,1,m) {
		bool okay=1;
		for (int v:nodes) mask[v]=0,d[v]=0,Fa[v]=v;
		REP(i,n) if ((sta>>i)&1) {
			for (int t=edges[i].first; t; t=vtree::vfa[t]) mask[t]^=1;
			for (int t=edges[i].second; t; t=vtree::vfa[t]) mask[t]^=1;
			int x=getfa(edges[i].first),y=getfa(edges[i].second);
			d[edges[i].first]++; d[edges[i].second]++;
			if (x==y) continue; else Fa[x]=y;
		} for (int v:nodes) {
			if (vtree::vfa[v]&&mask[v]) {
				int x=getfa(vtree::vfa[v]),y=getfa(v);
				d[v]++; d[vtree::vfa[v]]++;
				if (x==y) continue; else Fa[x]=y;
			}
		} int f=0;
		for (int x:nodes) if (Fa[x]!=x) f=getfa(x);
		for (int x:nodes) if (Fa[x]!=x&&getfa(x)!=f) okay=0;
		for (int x:nodes) if (d[x]!=0&&d[x]!=2) okay=0;
		ans+=okay;
	}
	printf("%d\n",ans);
}
/*
*/
