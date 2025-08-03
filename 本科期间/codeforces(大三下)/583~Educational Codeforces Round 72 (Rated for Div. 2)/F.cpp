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

int ans[maxn],nowans;
struct node {
	int l,r,u,v,id,val;
};
int fa[maxn];
vector<node> edge[27];
vector<pair<int,int> > nodes[27];//changed
inline int getfa(int x,int depth) {
	if (fa[x]==x) return fa[x];
	int y=getfa(fa[x],depth);
	nodes[depth].push_back(make_pair(x,fa[x]));
	if (fa[x]!=y) fa[x]=y;
	return fa[x];
}
int n;
int Q[maxn][3],use[maxn][2];
map<pair<int,int>,int> MP;
void solve(int dep,int l,int r) {
	// int i;
	// FOR(i,1,n) printf("%d ",getfa(i,dep)); printf(" pos=init=%d-%d\n",l,r);
	for (auto e:edge[dep]) {
		if (e.l<=l&&r<=e.r) {
			if (!use[e.id][e.val]) continue;
			// printf("update: %d-%d : %d-%d\n",l,r,e.u,e.v);
			int x=getfa(e.u,dep),y=getfa(e.v,dep);
			if (x!=y) {
				nodes[dep].push_back(make_pair(x,x));
				fa[x]=y;
			}
		}
	}
	if (l==r) {
		int u,v,op,x,y,o;
		op=Q[l][0]; u=Q[l][1]; v=Q[l][2];
		if (op==2) {
			u=(u+nowans-1)%n+1;
			v=(v+nowans-1)%n+1;
			nowans=(getfa(u,dep)==getfa(v,dep));
			// printf(" query %d : (%d,%d): %d\n",l,u,v,nowans);
			printf("%d",nowans);
			ans[l]=nowans;
		} else {//check_should_use_this
			x=(u+nowans-1)%n+1;
			y=(v+nowans-1)%n+1;
			if (x>y) swap(x,y);
			MP[make_pair(x,y)]^=1;
			REP(o,2) {
				x=u; y=v; if (x>y) swap(x,y);
				use[l][0]=MP[make_pair(x,y)];
				x=u%n+1; y=v%n+1; if (x>y) swap(x,y);
				use[l][1]=MP[make_pair(x,y)];
			}
			// printf("%d: (%d %d) %d%d\n",l,u,v,use[l][0],use[l][1]);
			//use or not(2)
		}
	} else {
		for (auto e:edge[dep]) {//save_position
			getfa(e.u,dep); getfa(e.v,dep);
		}
		// for (int x:nodes[dep]) printf("x=%d ",x);
		int mid=(l+r)/2;
		edge[dep+1].clear();
		nodes[dep+1].clear();
		for (auto e:edge[dep]) {
			if (e.l<=l&&r<=e.r) continue;
			if (e.l<=mid) edge[dep+1].push_back(e);
		}
		solve(dep+1,l,mid);
		edge[dep+1].clear();
		nodes[dep+1].clear();
		for (auto e:edge[dep]) {
			if (e.l<=l&&r<=e.r) continue;
			if (mid<e.r) edge[dep+1].push_back(e);
		}
		solve(dep+1,mid+1,r);
	}
	reverse(nodes[dep].begin(), nodes[dep].end());
	for (auto x:nodes[dep]) fa[x.first]=x.second;
	// FOR(i,1,n) printf("%d ",getfa(i,dep)); printf(" pos=back=%d-%d\n",l,r);
}
int main() {
	int m,i,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) fa[i]=i;
	FOR(i,1,m) REP(k,3) scanf("%d",&Q[i][k]);
	rFOR(i,1,m) {
		int u,v,x,y,op,pre;
		op=Q[i][0]; u=Q[i][1]; v=Q[i][2];
		if (op==1) {
			x=u; y=v; if (x>y) swap(x,y);
			pre=MP[make_pair(x,y)]; if (!pre) pre=m;//previous_notadd
			MP[make_pair(x,y)]=i;
			edge[1].push_back(node{i+1,pre,x,y,i,0});
			// printf("  %d-%d: %d %d (%d %d)\n",i+1,pre,x,y,i,0);
			x=u%n+1; y=v%n+1; if (x>y) swap(x,y);
			pre=MP[make_pair(x,y)]; if (!pre) pre=m;
			if (pre==i) continue;//same; previous_add
			MP[make_pair(x,y)]=i;
			edge[1].push_back(node{i+1,pre,x,y,i,1});
			// printf("  %d-%d: %d %d (%d %d)\n",i+1,pre,x,y,i,1);
		} else continue;//在solve里做
	} MP.clear();
	solve(1,1,m);
}
/*
*/