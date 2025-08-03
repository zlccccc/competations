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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

//1 to i可以|不可以组合成A
//A 从大往小即可
vector<int> edge[maxn];
int fa[maxn];
inline int getfa(int x){
	if (x==fa[x]) return x;
	else return fa[x]=getfa(fa[x]);
}
int father[maxn],depth[maxn];
inline void dfs(int x,int fa,int dep){
	father[x]=fa; depth[x]=dep;
	for (int v:edge[x]) if (v!=fa) dfs(v,x,dep+1);
}
ll now;
int sz[maxn];
void merge(int x,int y){
	x=getfa(x); y=getfa(y);
	assert(x!=y);
	now+=(ll)sz[x]*sz[y];
	fa[x]=y; sz[y]+=sz[x];
}
void linkcircle(int x,int y) {
	while (1) {
		x=getfa(x); y=getfa(y);
		if (x==y) break;
		if (depth[x]<depth[y]) swap(x,y);
		merge(x,father[x]);
	}
}
struct node{
	int x,y;
}e[maxn*2];
int main() {
	int T,_;
	int i;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,m; now=0;
		scanf("%d%d",&n,&m);
		FOR(i,1,n) fa[i]=i,sz[i]=1,edge[i].clear();
		FOR(i,1,m) {
			scanf("%d%d",&e[i].x,&e[i].y);
			int x=getfa(e[i].x),y=getfa(e[i].y);
			if (x!=y) {
				edge[e[i].x].push_back(e[i].y);
				edge[e[i].y].push_back(e[i].x);
				merge(x,y),e[i].x=e[i].y=0;
			}
		} now=0;
		ll ans=0;
		FOR(i,1,n) father[i]=0;
		FOR(i,1,n) if (!father[i]) dfs(i,0,0);
		FOR(i,1,n) fa[i]=i,sz[i]=1;
		FOR(i,1,m) {
			if (e[i].x) linkcircle(e[i].x,e[i].y);
			ans^=now*i;
		} 
		printf("%lld\n",ans);
	}
}
/*
1
4 6
1 2
2 3
3 4
1 3
2 4
1 4
*/