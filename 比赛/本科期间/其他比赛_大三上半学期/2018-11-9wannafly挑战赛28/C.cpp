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

vector<int> edge[maxn];
ll A[maxn];
ll f[maxn],g[maxn][maxn];
void dfs(int x,int fa,ll limit){
	int i;
	FOR(i,1,n) g[x][i]=0; f[x]=INF;
	for (int v:edge[x]) if (v!=fa){
		dfs(v,x,limit);
		FOR(i,1,n) {
			if (A[i]-limit<A[x]&&A[x]<=A[i]){
				ll more=f[v]+1;
				if (A[i]-limit<A[v]&&A[v]<=A[i]) more=min(more,g[v][i]);
				g[x][i]+=more;
			} else g[x][i]=INF;
		}
	} FOR(i,1,n) f[x]=min(f[x],g[x][i]);
}
int solve(int val){
	dfs(1,0,val);
	return f[1];
}
int main() {
	int i,k;
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%lld",&A[i]);
	FOR(i,1,n-1){
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} ll l=0,r=INF*2;
	while (l+1<r){
		int mid=(l+r)/2;
		if (solve(mid)<k+1) r=mid;
		else l=mid;
	} printf("%lld\n",l);
}
/*
7 0
8 7 19 2 18 9 9
5 4
3 4
1 5
6 2
6 5
7 4
*/
