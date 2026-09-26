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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
// char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

vector<int> edge[maxn];
ll dp[maxn][3];
int A[maxn],l,r;
//0:not deleted
//1:deleted after father_del(not have edge)
//2:deleted before father_del(have edge)
inline void dfs(int x,int fa){
	int i;
	ll base=0; vector<ll> sonval;
	for (int v:edge[x]) if (v!=fa) {
		dfs(v,x); dp[x][0]+=max(dp[v][0],dp[v][2]);//not choose!
		base+=max(dp[v][0],dp[v][1]);//delete
		if (dp[x][2]!=-INFF) sonval.push_back(dp[v][2]-max(dp[v][0],dp[v][1]));//more
		else sonval.push_back(-INFF);
	} dp[x][1]=dp[x][2]=-INFF;//can not remove
	sort(sonval.begin(), sonval.end());
	// reverse(sonval.begin(), sonval.end());
	base+=A[x]; sonval.push_back(0);//before : dp[v][0];
	rREP(i,(int)sonval.size()) {//delete self
		if (sonval[i]==-INFF) break;//D--
		base+=sonval[i];//i个dp[x][1],after(D=i)
		if (l<=i&&i<=r) max_(dp[x][1],base);
		if (l<=i+1&&i+1<=r) max_(dp[x][2],base);
		// printf("%d : %lld\n",i,base);
	}
	// printf("%d : %lld %lld; %lld; SZ=%d\n",x,dp[x][0],dp[x][1],dp[x][2],(int)sonval.size());
}
int main() {
	int i;
	scanf("%d%d%d",&n,&l,&r);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n-1){
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs(1,0);
	printf("%lld\n",max(dp[1][0],dp[1][1]));
}
/*
5 2 2
1 1 1 1 1
1 2
1 3
1 4
4 5

1 1 1
1 1 1 1 1
1 2
1 3
1 4
4 5
*/
