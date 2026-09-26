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
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b,ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// 题意: 给n个区间, 求与0的距离差期望
// 做法: 考虑每一次, 都是个区间分段积分形式
// 所以直接考虑每一段, 2-pointer求2^n项系数即可
int ans=0;
int value[1<<15|7],base[1<<15|7];
int l[17],r[17];
int mbase=1,kbase=1;
inline int lowbit(int x){
	return x&-x;
}
int main() {
	int n,i;
	scanf("%d",&n);
	REP(i,n) {
		scanf("%d%d",&l[i],&r[i]);
		value[0]+=r[i];
		if (r[i]-l[i]) mbase=mbase*powMM(r[i]-l[i],M-2)%M;
	} FOR(i,1,n+1) kbase=kbase*powMM(i,M-2)%M;
	int k=-1;
	REP(i,(1<<n)) {
		if (!i) {
			base[i]=1;
		} else {
			if (lowbit(i)==i) k++;
			base[i]=M-base[i^(1<<k)];
			value[i]=value[i^(1<<k)]-r[k]+l[k];
		}
		//分两段的函数, 分别积分加起来
		// printf("value=%d; k=%d; base=%d\n",value[i],k,base[i]);
		if (value[i]>0) add_(ans,base[i]*powMM(value[i],n+1)%M);
		else add_(ans,M-base[i]*powMM(value[i],n+1)%M);//以0为零点
	}
	// printf("%lld\n",199648872ll*15%M);
	// printf("%lld %lld\n",(ll)ans%M,(ll)mbase*15%M);
	printf("%lld\n",(ll)ans*kbase%M*mbase%M);
}
/*
3
-3 3
-2 2
-1 1
*/