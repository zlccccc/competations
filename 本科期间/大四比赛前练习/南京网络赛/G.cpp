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

__int128 C[1000107],G[1000107];
__int128 getPsum(int n) {//p次前缀和
	if (n>=0) printf("%d : %lld\n",n,(ll)C[n]);
	if (n>=0) return C[n];
	else return 0;
}
__int128 getAllsum(int l,int r) {//x->y; sum
	//k=8
	__int128 ret=0;
	if (r<0) ret=0;
	else if (l<=0) ret=G[r];
	else ret=G[r]-G[l-1];
	// if (ret) printf("%d->%d : %lld\n",l,r,(ll)ret);
	return ret;
}
void init() {
	int i,j; C[0]=1;
	REP(j,4) FOR(i,1,1000010) C[i]+=C[i-1];
	FOR(i,0,1000010) G[i]=C[i];
	FOR(i,1,1000010) G[i]+=G[i-1];
}
void check(int l,int r) {
	__int128 ans1=0,ans2=0,i;
	FOR(i,l,r) ans1+=getPsum(i); ans2=getAllsum(l,r);
	printf("%lld %lld\n",(ll)ans1,(ll)ans2);
}
int A[10];
int main() {
	init();
	// check(6,6);
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int i;
		REP(i,8) {
			scanf("%d",&A[i]);
		} int id;
		__int128 ans=(__int128)(A[1]-A[0]+1)*(A[3]-A[2]+1)*(A[5]-A[4]+1)*(A[7]-A[6]+1);
		// printf("%lld\n",(ll) ans);
		REP(id,4) {//id作为max
			REP(i,4) if (i!=id) {
				swap(A[i*2],A[i*2+1]);
				A[i*2]=-A[i*2]; A[i*2+1]=-A[i*2+1];
			} ll nowans=0; int sta;
			// REP(i,8) printf("%d ",A[i]);
			// printf("id=%d; allbase=%d\n",id,allbase);
			REP(sta,16) {//容斥
				int base=1,pos=0;
				REP(i,4) if ((sta>>i)&1) {
					pos+=A[i*2+1]+1; base=-base;
				} else pos+=A[i*2];
				// printf("sta=%d\n",sta);
				// nowans+=base*getPsum(-pos);
				nowans+=base*getAllsum(-pos,-pos+A[id*2+1]+1);
			} ans-=nowans;
			// printf("allbase=%lld\n",allbase);
			// FOR(i,1,3) printf("%d ",getPsum(allbase+1,allbase+i)); puts("");
			// printf("nowans=%lld\n",nowans);
			REP(i,4) if (i!=id) {//roll back
				A[i*2]=-A[i*2]; A[i*2+1]=-A[i*2+1];
				swap(A[i*2],A[i*2+1]);
			}
		} printf("%lld\n",(ll)ans);
	}
}
/*
100
1 3 1 3 1 3 1 3
1 2 1 2 1 2 1 2
1 6 1 6 1 6 1 3
1 4 1 4 1 4 1 4
1 5 1 5 1 5 1 5
1 10 1 10 1 10 1 100
1 5 1 7 1 8 1 2
1 100 1 100 1 100 1 100
1 100000 1 100000 1 100000 1 1000

4
1 5 1 5 1 5 1 5
*/