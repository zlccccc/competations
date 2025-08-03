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

int A[10];
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int i,j,k,l;
		REP(i,8) {
			scanf("%d",&A[i]);
		} ll ans=(A[1]-A[0]+1)*(A[3]-A[2]+1)*(A[5]-A[4]+1)*(A[7]-A[6]+1);
		int cnt1,cnt2,cnt3,cnt4;
		cnt1=cnt2=cnt3=cnt4=0;
		FOR(i,A[0],A[1]) {
			FOR(j,A[2],A[3]) {
				FOR(k,A[4],A[5]) {
					FOR(l,A[6],A[7]) {
						if (i-j-k-l>=0) ans--,cnt1++;
						if (j-i-k-l>=0) ans--,cnt2++;
						if (k-i-j-l>=0) ans--,cnt3++;
						if (l-i-j-k>=0) ans--,cnt4++;
					}
				}
			}
		} printf("%d %d %d %d\n",cnt1,cnt2,cnt3,cnt4);
		printf("%lld\n",ans);
	}
}
/*
100
1 2 1 2 1 2 1 2
1 3 1 3 1 3 1 3
1 4 1 4 1 4 1 4
1 5 1 5 1 5 1 5
3 5 1 5 4 5 1 5
*/