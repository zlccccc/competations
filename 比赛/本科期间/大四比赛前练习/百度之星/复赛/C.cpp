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

int son[maxn][2],A[maxn],sz[maxn];
void dfs1(int x) {
	A[x]=x; sz[x]=1; int o;
	REP(o,2) if (son[x][o]) {
		dfs1(son[x][o]);
		A[x]=min(A[x],A[son[x][o]]);
		sz[x]+=sz[son[x][o]];
	}
}
int id[maxn],tot;
void dfs2(int x) {
	// printf("dfs2: %d; tot=%d\n",x,tot);
	int lson=son[x][0],rson=son[x][1];//mark=2:
	if (A[x]==x) {
		if (!rson) swap(lson,rson);
		else if (lson&&rson) {
			if (sz[lson]>sz[rson]) swap(lson,rson);
			else if (sz[lson]==sz[rson]&&A[lson]>A[rson]) swap(lson,rson);
		}
		// printf("AX=X; %d %d\n",lson,rson);
		if (lson) dfs2(lson);
		id[x]=++tot;
		if (rson) dfs2(rson);
	} else {
		if (!lson||(lson&&rson&&A[lson]>A[rson])) swap(lson,rson);
		// printf("l,r=%d %d\n",lson,rson);
		if (lson) dfs2(lson);
		id[x]=++tot;
		if (rson) dfs2(rson);
	}
}
bool isroot[maxn];
int main() {
	// dfs(17,23);
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int n,root=0,i;
		scanf("%d",&n); tot=0;
		FOR(i,1,n) isroot[i]=1;
		FOR(i,1,n) {
			scanf("%d%d",&son[i][0],&son[i][1]);
			isroot[son[i][0]]=isroot[son[i][1]]=0;
		} FOR(i,1,n) if (isroot[i]) root=i;
		dfs1(root); dfs2(root);
		// FOR(i,1,n) printf("%d ",id[i]); puts("");
		int ans=0;
		FOR(i,1,n) add_(ans,powMM(233,i)*(id[i]^i)%M);
		printf("%d\n",ans);
	}
}