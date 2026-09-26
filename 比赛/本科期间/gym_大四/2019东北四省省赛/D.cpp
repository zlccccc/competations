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
const LL maxn=5e5+107;
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

vector<int> edge[maxn],vt[maxn],kp;
bool key[maxn];
int vdep[maxn],vfa[maxn],dep[maxn];
int build(int x,int fa) {
	// printf("build %d %d\n",x,fa);
	vector<int> ch;
	for (auto v:edge[x]) {
		if (v==fa) continue;
		int w=build(v,x);
		if (w) ch.push_back(w);
	} if (ch.size()>=2) key[x]=1;
	if (key[x]) {
		kp.push_back(x);
		for (auto v:ch) {
			vt[x].push_back(v);
			vt[v].push_back(x);
			vfa[v]=x;
		} return x;
	} if (ch.size()) return ch[0];
	return 0;
}
inline void dfs(int x,int fa,int dep,int realdep) {
	if (key[x]) dep++; realdep++;
	vdep[x]=dep; ::dep[x]=realdep;
	for (int v:edge[x]) if (v!=fa) dfs(v,x,dep,realdep);
}
struct QAQ{
	int op,u,v,k;
}Q[maxn];
ll val[maxn],nval[maxn];//nval:count=1
void solve(const QAQ &Q) {
	int u=Q.u,v=Q.v,op=Q.op,k=Q.k;
	ll ans=0;
	ll MAX=-INFF,MIN=INFF;
	// printf("solve: %d to %d\n",u,v);
	while (1) {
		if (vdep[u]<vdep[v]) swap(u,v);
		ll l=dep[u]-dep[vfa[u]]-1;
		if (l&&(u!=v)) {
			// printf("%d to %d: length=%lld; value=%d\n",u,vfa[u],l,val[u]);
			if (op==1) val[u]+=k;
			if (op==2) val[u]^=k;
			if (op==3&&val[u]>=k) val[u]-=k;
			if (op==4) ans+=l*val[u];
			if (op==5&&(l&1)) ans^=val[u];
			if (op==6) MAX=max(MAX,val[u]),MIN=min(MIN,val[u]);
			if (op==7) MIN=min(MIN,abs(val[u]-k));
		} {
			// printf("point %d: value=%d\n",u,val[u]);
			if (op==1) nval[u]+=k;
			if (op==2) nval[u]^=k;
			if (op==3&&nval[u]>=k) nval[u]-=k;
			if (op==4) ans+=nval[u];
			if (op==5) ans^=nval[u];
			if (op==6) MAX=max(MAX,nval[u]),MIN=min(MIN,nval[u]);
			if (op==7) MIN=min(MIN,abs(nval[u]-k));
		}
		if (u==v) break;
		u=vfa[u];
	} if (op==6) ans=MAX-MIN;
	if (op==7) ans=MIN;
	if (op>=4) printf("%lld\n",ans);
}
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int n,q,i;
		scanf("%d%d",&n,&q);
		FOR(i,1,n) {
			edge[i].clear(); key[i]=0; val[i]=nval[i]=0;
			vt[i].clear(); dep[i]=vdep[i]=vfa[i]=0;
		} kp.clear();
		FOR(i,1,n-1) {
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		} key[1]=1;
		FOR(i,1,q) {
			scanf("%d%d%d",&Q[i].op,&Q[i].u,&Q[i].v);
			key[Q[i].u]=key[Q[i].v]=1;
			if (Q[i].op<=3||Q[i].op==7) scanf("%d",&Q[i].k);
		} build(1,0); dfs(1,0,0,0);
		FOR(i,1,q) solve(Q[i]);
	}
}
/*
1
2
2 2 3 3
4 4 5 5

*/