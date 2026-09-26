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
const LL maxn=1e3+7;
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

int fa[maxn];
vector<int> nodes[maxn],edge[maxn];
int dep[maxn],sz[maxn];
int maxdep=0;
void dfs(int x,int fa){
	dep[x]=dep[fa]+1; ::fa[x]=fa;
	max_(maxdep,dep[x]);
	nodes[dep[x]].push_back(x);
	for (int v:edge[x]) if (v!=fa) {
		dfs(v,x); sz[x]+=1+sz[v]+1;//lcol,v
	} if (!sz[x]) sz[x]=1;
}
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int col[maxn],l[maxn];
int solve() {
	scanf("%d%d",&n,&m); int i;
	FOR(i,1,n) fa[i]=i;
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		int x=getfa(u),y=getfa(v);
		if (x==y) return 0*puts("-1");
		fa[x]=y; edge[u].push_back(v);
		edge[v].push_back(u);
	} if (m!=n-1) return 0*puts("-1");
	dfs(1,0);
	int T=sz[1];
	REP(i,T) col[i]=1; l[0]=-1;
	printf("%d %d\n",maxdep,T);
	FOR(i,1,maxdep){
		int front=0;
		for (int v:nodes[i]){
			while (front<l[fa[v]]) printf("%d",col[front++]);
			if (v!=1) printf("%d",col[front++]); l[v]=front;
			while (sz[v]--) printf("%d",col[front++]=i%2);
			if (v!=1) printf("%d",col[front++]);
		} 
		while (front<T) printf("%d",col[front++]); 
		puts("");
	}
	return 0;
}
int main() {
	solve();
	// int T; scanf("%d",&T);
	// while (T--) solve();
}
/*
4 3
1 2
2 3
3 4

4 3
1 2
1 3
1 4

7 6
1 5
1 2
2 3
3 7
3 6
1 4
*/
