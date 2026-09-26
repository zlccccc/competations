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

#define DEBUG1
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
const LL maxn=1e5+107;
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

vector<int> edge[maxn];
int id[2][21],k[2];
int dist[2][21][maxn];
int dis[maxn];
vector<int> ini,nxt;
void solve_bfs() {
	int i=0,j=0;
	while (i<(int)ini.size()||j<(int)nxt.size()) {
		int x=0;
		if (i==(int)ini.size()) x=nxt[j++];
		else if (j==(int)nxt.size()) x=ini[i++];
		else {
			if (dis[ini[i]]<dis[nxt[j]]) x=ini[i++];
			else x=nxt[j++];
		}
		for (int v:edge[x]) {
			if (dis[x]+1<dis[v]) {
				dis[v]=dis[x]+1;
				nxt.push_back(v);
			}
		}
	}
}
vector<int> ids[maxn];
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,m,i;
		scanf("%d%d",&n,&m);
		FOR(i,1,n) edge[i].clear();
		FOR(i,1,m) {
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		} int o;
		REP(o,2) {
			scanf("%d",&k[o]);
			REP(i,k[o]) {
				int t;
				scanf("%d",&id[o][i]);
				ini.clear(); nxt.clear();
				FOR(t,1,n) dis[t]=INF;
				dis[id[o][i]]=0; ini.push_back(id[o][i]);
				solve_bfs();
				FOR(t,1,n) dist[o][i][t]=dis[t];
				// FOR(t,1,n) printf("%d ",dis[t]); printf(" <- %d\n",id[o][i]);
			}
		}
		int x,y;
		ll ans=0;
		REP(x,k[0]) REP(y,k[1]) {
			ini.clear(); nxt.clear();
			int t;
			FOR(t,1,n) {
				dis[t]=dist[0][x][t]+dist[1][y][t];
				ids[dis[t]].push_back(t);
			}
			FOR(t,0,n) {
				for (int k:ids[t]) ini.push_back(k);
				ids[t].clear();
			}
			solve_bfs();
			FOR(t,1,n) ans+=dis[t];
		}
		printf("Case #%d: ",_);
		int g=gcd(ans,n*k[0]*k[1]);
		ans/=g; printf("%lld",ans);
		if (n*k[0]*k[1]!=g) printf("/%d\n",n*k[0]*k[1]/g);
		else puts("");
	}
}
/*
2
1 0
1 1
1 1
*/