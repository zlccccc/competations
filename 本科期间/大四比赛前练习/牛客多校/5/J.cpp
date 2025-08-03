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
const LL M=998244353;
const LL maxn=2e5+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace tree {
	typedef pair<int,int> pii;
	int fa[maxn][20],dep[maxn];
	vector<int> edge[maxn];
	pii maxlen[maxn][3],d[maxn];
	void dfs1(int x,int father) {
		int i=0; dep[x]=dep[father]+1; fa[x][0]=father;
		rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
		REP(i,3) maxlen[x][i]=make_pair(0,x);
		for (int v:edge[x]) if (v!=father) {
				dfs1(v,x);
				pii now=maxlen[v][0]; now.first++;
				REP(i,3) if (maxlen[x][i]<now) swap(now,maxlen[x][i]);
			}
	}
	void dfs2(int x,int father) {
		int i; pii now=d[x];
		REP(i,3) if (maxlen[x][i]<now) swap(now,maxlen[x][i]);
		now=make_pair(1,x);
		for (int v:edge[x]) if (v!=father) {
				d[v]=max(d[v],now);
				pii nxt=maxlen[v][0]; nxt.first+=2;
				now=max(now,nxt);
			} reverse(edge[x].begin(), edge[x].end());
		now=d[x]; now.first++;
		for (int v:edge[x]) if (v!=father) {
				d[v]=max(d[v],now);
				pii nxt=maxlen[v][0]; nxt.first+=2;
				now=max(now,nxt);
			}
		for (int v:edge[x]) if (v!=father) dfs2(v,x);
	}
	int lca(int x,int y) {
		int i;
		if (dep[x]<dep[y]) swap(x,y);
		rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
		if (x==y) return x;
		rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	int kthfa(int x,int k) {
		int i;
		rREP(i,20) if ((k>>i)&1) x=fa[x][i];
		return x;
	}
	int walk(int x,int y,int d) {
		int f=lca(x,y);
		if (dep[x]-dep[f]>=d) return kthfa(x,d);
		return kthfa(y,dep[x]+dep[y]-2*dep[f]-d);
	}
};
void getlen(int n) {
	int i,o;
	FOR(i,1,n) {
		REP(o,3) printf("(%d %d) ",tree::maxlen[i][o].first,tree::maxlen[i][o].second);
		printf(" d(%d %d) <- %d\n",tree::d[i].first,tree::d[i].second,i);
	}
}
int Ans[maxn][3];
typedef pair<pii,int> P3;
vector<P3> Ins[maxn];//pos; val; rootid
vector<pair<P3,P3> > Q[maxn];//i; j,k,id; 012
pii Max[maxn];//bit
inline int lowbit(int x) {
	return x&-x;
}
void update(int x,pii val,int n) {
	x=n-x;
	for (; x<=n; x+=lowbit(x)) Max[x]=max(Max[x],val);
}
pii query(int x,int n) {
	pii ret=make_pair(0,0); x=n-x;
	for (; x; x-=lowbit(x)) ret=max(ret,Max[x]);
	return ret;
}
P3 make_p3(int x,int y,int z) {
	return make_pair(make_pair(x,y),z);
}
int main() {
	int n,q,i;
	scanf("%d",&n);
	FOR(i,1,n-1) {
		int u,v;
		scanf("%d%d",&u,&v); u++; v++;
		tree::edge[u].push_back(v);
		tree::edge[v].push_back(u);
	} tree::dfs1(1,0);
	tree::dfs2(1,0);
	FOR(i,1,n) {
		Ins[tree::maxlen[i][0].first].push_back(make_p3(tree::maxlen[i][1].first,tree::maxlen[i][2].first,i));
	}
	scanf("%d",&q);
	FOR(i,1,q) {
		int a,b,c; scanf("%d%d%d",&a,&b,&c);
		pii now[3]; int sum=a+b+c;
		if (sum&1) continue;
		if (sum<max(max(a,b),c)*2) continue;//no
		now[0]=make_pair(sum/2-c,0);
		now[1]=make_pair(sum/2-b,1);
		now[2]=make_pair(sum/2-a,2);
		sort(now,now+3);
		reverse(now,now+3);
		Q[now[0].first].push_back(make_pair(make_p3(now[1].first,now[2].first,i),
		                                    make_p3(now[0].second,now[1].second,now[2].second)));
	}
	rFOR(i,0,n-1) {
		for (P3 p:Ins[i]) {
			// printf("Upd: %d %d %d\n",i,p.first.first,p.first.second);
			update(p.first.first,make_pair(p.first.second,p.second),n);
		}
		for (pair<P3,P3> q:Q[i]) {
			P3 p=q.first,pos=q.second;
			pii nowans=query(p.first.first,n);
			// printf("Q: %d %d %d (id=%d)\n",i,p.first.first,p.first.second,p.second);
			// printf("A: %d %d\n",nowans.first,nowans.second);
			if (nowans.first<p.first.second) continue;
			int f=nowans.second;
			Ans[p.second][pos.first.first]=tree::walk(f,tree::maxlen[f][0].second,i);
			Ans[p.second][pos.first.second]=tree::walk(f,tree::maxlen[f][1].second,p.first.first);
			Ans[p.second][pos.second]=tree::walk(f,tree::maxlen[f][2].second,p.first.second);
		}
	}
	FOR(i,1,q) {
		if (Ans[i][0]==0) puts("-1");
		else printf("%d %d %d\n",Ans[i][0]-1,Ans[i][1]-1,Ans[i][2]-1);
	}
}
/*
1
2 2
10 10
*/