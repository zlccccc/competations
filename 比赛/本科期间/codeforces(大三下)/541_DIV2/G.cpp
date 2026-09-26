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
const LL maxn=2.5e5+107;
const LL maxm=1e7+107;
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
int n,m,q;
// char str[maxn];

typedef pair<ll,int> pli;
int A[maxm],tot,L[maxm],R[maxm];
pli S[maxm]; int top;//id_toward
ll cost[maxm],dp[maxm];
int s[maxm];
vector<pii> blocks[maxn];
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) {
		int j,k;
		scanf("%d",&k);
		blocks[i].resize(k);
		REP(j,k) scanf("%d",&blocks[i][j].first);
		REP(j,k) scanf("%d",&blocks[i][j].second);
	} scanf("%d",&q);
	FOR(i,1,q) {
		int id; ll mul;
		scanf("%d%lld",&id,&mul);
		for (auto now:blocks[id]) {
			A[++tot]=now.first;
			cost[tot]=now.second*mul;
		}
	} assert(tot==m);
	// FOR(i,1,m) printf("%-3d ",A[i]); puts("");
	// FOR(i,1,m) printf("%-3lld ",cost[i]); puts("");
	s[0]=0; top=0; //!; 区间min
	FOR(i,1,m) {
		while (top&&s[top]>i-A[i]) top--;
		L[i]=s[top]; s[++top]=i;
	} s[0]=m+1; top=0;
	rFOR(i,1,m) {
		while (top&&s[top]<i+A[i]) top--;
		R[i]=s[top]; s[++top]=i;
	}
	// FOR(i,1,m) printf("%-3d ",L[i]); puts(" <- L");
	// FOR(i,1,m) printf("%-3d ",R[i]); puts(" <- R");
	FOR(i,1,m) {
		while (top&&S[top].second<i) top--;
		dp[i]=dp[L[i]]+cost[i];
		if (top) dp[i]=min(dp[i],S[top].first);
		// printf("i=%d; dp=%lld; R=%d\n",i,dp[i],R[i]-1);
		pli nxt=make_pair(dp[i-1]+cost[i],R[i]-1);//end at
		while (top&&S[top].second==nxt.second&&S[top].first>nxt.first) top--;
		if (!top||nxt.first<S[top].first) S[++top]=nxt;
		// int j;
		// FOR(j,1,top) printf("toword  %d: %lld\n",S[j].second,S[j].first);
	}
	printf("%lld\n",dp[m]);
}
/*
acdefg
10
1 3

*/