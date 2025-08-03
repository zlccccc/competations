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
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; rREP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

const int blockcnt=500;
const int base=503;
int blocksum[507][1007];//后缀和
int l[maxn],r[maxn],all[507];
int dp[maxn],A[maxn],C[maxn];
void rebuild(int block) {
	int _l=l[block],_r=r[block];
	int now=0,i;
	FOR(i,-blockcnt,+blockcnt)
		blocksum[block][i+base]=0;
	rFOR(i,_l,_r) {//down_sum=?
		now+=C[i];
		// printf("i=%d; now=%d\n",i,now);
		add_(blocksum[block][now+base],dp[i-1]);
	} //at most
	FOR(i,-blockcnt,+blockcnt)
		add_(blocksum[block][i+base],blocksum[block][i+base-1]);
	all[block]=now;
}
int pos[maxn],pre[maxn];
int main() {
	int i,n,k,j;
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%d",&A[i]);
	dp[0]=1;
	FOR(i,1,n) {
		if (!l[i/blockcnt]) l[i/blockcnt]=i;
		r[i/blockcnt]=i;
		pre[i]=pos[A[i]]; pos[A[i]]=i;
		if (pre[pre[i]]) {
			C[pre[pre[i]]]++;
			rebuild(pre[pre[i]]/blockcnt);
		} if (pre[i]) {
			C[pre[i]]-=2;
			rebuild(pre[i]/blockcnt);
		} C[i]++;
		// printf("rebuild:\n");
		rebuild(i/blockcnt);
		int now=0;
		rFOR(j,0,i/blockcnt) {
			if (-blockcnt<=k-now) add_(dp[i],blocksum[j][min(blockcnt,k-now)+base]);
			// printf("upper_now=%d; k-now=%d; +=%d\n",now,k-now,blocksum[j][k-now+base]);
			now+=all[j];
		}
		// FOR(j,1,i) printf("%d ",C[j]); puts(" <- C[i]");
		// FOR(j,1,i) printf("%d ",dp[j]); puts(" <- dp[i]");
	} printf("%d\n",dp[n]);
}
/*
3 1
1 1 2
*/