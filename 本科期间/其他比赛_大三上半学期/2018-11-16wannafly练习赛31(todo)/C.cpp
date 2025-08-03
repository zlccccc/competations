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
const LL M=998244353 ;
const LL maxn=1<<20|7;
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

int A[27];
char F[maxn][27];
int way[maxn];
int main() {
	int i,k;
	scanf("%d",&n); m=1<<n;
	REP(i,n) scanf("%d",&A[i]),A[i]--;
	REP(i,n) F[0][i]=A[i];
	int sta;
	rep(sta,1,m) {
		REP(i,n) if ((sta>>i)&1){
			int st=0,pre=sta^(1<<i);
			REP(k,n) if (F[pre][k]<i) F[sta][st++]=F[pre][k];
			F[sta][st++]=i;
			REP(k,n) if (F[pre][k]>i) F[sta][st++]=F[pre][k];
			break;
		}//re_solve
		// pr2(sta,n);
		// REP(i,n) printf("%d ",F[sta][i]);puts("");
	} rREP(sta,m){
		int mark=0;
		REP(i,n-1) if (F[sta][i]>F[sta][i+1]) mark=1;
		if (!mark) continue;
		int cnt=0,all=0;
		REP(i,n) if (((sta^(m-1))>>i)&1){
			cnt++; add_(all,way[sta^(1<<i)]);
		} 
		// pr2(sta,n); printf("%d %d\n",all,cnt);
		add_(all,n);
		mul_(all,powMM((ll)cnt,M-2));
		// printf("actual = %d\n",all);
		way[sta]=all;
	} printf("%d\n",way[0]);
}
/*
*/
