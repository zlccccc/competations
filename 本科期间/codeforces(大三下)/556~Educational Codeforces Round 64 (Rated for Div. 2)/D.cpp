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
const LL maxn=1e6+107;
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


vector<pair<int,int> > edge[maxn];
int sz[maxn]; bool mark[maxn];
int minweight,root;
void dfs1(int x,int fa,int n) {
	int weight=0; sz[x]=1;
	for (auto now:edge[x]) {
		int v=now.first;
		if (v==fa||mark[v]) continue;
		dfs1(v,x,n); sz[x]+=sz[v];
		weight=max(weight,sz[v]);
	} weight=max(weight,n-sz[x]);
	if (weight<minweight) {root=x; minweight=weight;}
}
// getans
//0:0; 1:1; 01:2; 10:3
int C[4];
void dfs2(int x,int fa,int mask) {
	// printf("dfs2 %d : %d\n",x,mask);
	C[mask]++;
	for (auto now:edge[x]) {
		int v=now.first,l=now.second;
		if (v==fa||mark[v]) continue;
		int nxtmask=mask;
		if (mask==0&&l==1) nxtmask=2;
		if (mask==1&&l==0) nxtmask=3;
		if (mask==2&&l==0) continue;
		if (mask==3&&l==1) continue;
		dfs2(v,x,nxtmask);
	}
}
//0:0; 1:1; 01:2; 10:3
ll ans=0;
int D[4];
void getans(int x) {
	int i;
	REP(i,4) C[i]=D[i]=0;
	for (auto now:edge[x]) {
		int v=now.first,l=now.second;
		if (mark[v]) continue;
		dfs2(v,x,l);
		ans+=(ll)C[1]*D[1]*2;//only 1
		ans+=(ll)C[0]*D[0]*2;//only 0
		ans+=(ll)C[0]*D[1]+(ll)D[0]*C[1];//01
		ans+=(ll)C[0]*D[2]+(ll)D[0]*C[2];//001
		ans+=(ll)C[1]*D[3]+(ll)D[1]*C[3];//011
		ans+=C[0]*2+C[1]*2+C[2]+C[3];
		REP(i,4) D[i]+=C[i],C[i]=0;
	}
	// printf("getans %d: %lld\n",x,ans);
}
void dfs3(int x) {
	mark[x]=1; getans(x);
	for (auto now:edge[x]) {
		int v=now.first;
		if (mark[v]) continue;
		minweight=sz[v];
		dfs1(v,0,sz[v]);
		dfs3(root);
	}
}
int main() {
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n-1){
		int u,v,l;
		scanf("%d%d%d",&u,&v,&l);
		edge[u].push_back(make_pair(v,l));
		edge[v].push_back(make_pair(u,l));
	}
	root=1; minweight=n+1;
	dfs1(1,0,n);
	dfs3(1);
	printf("%lld\n",ans);
}
/*
8
1 2 1
2 3 0
3 4 1
4 5 0
5 6 1
6 7 1
7 8 0
*/