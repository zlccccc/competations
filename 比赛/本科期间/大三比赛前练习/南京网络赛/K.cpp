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
const LL maxn=1e7+7;
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


struct L_B {
	int A[30];
	void clear() {memset(A,0,sizeof(A));}
	void insert(int x) {
		int i;
		rREP(i,20) if ((x>>i)&1) {
			if (!A[i]) A[i]=x; x^=A[i];
		}
	}
	int size() {
		int i,cnt=0;
		REP(i,20) if (A[i]) cnt++;
		return cnt;
	}
} A;
inline int getk(int i,int k,int M){
	int ret=1;
	while (k--) ret=(ll)ret*i%M;
	return ret;
}
ll a,b,c,d,e,k;
int f(int i){
	return (a*getk(i,4,k)+b*getk(i,3,k)+c*getk(i,2,k)+d*getk(i,1,k)+e-1+k)%k+1;
}
int main() {
	ll now;
	scanf("%s%lld",str,&now);
	int len=strlen(str),i;
	scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&d,&e);
	scanf("%lld",&k);
	ll MAX,CNT=0;
	REP(i,len) {
		CNT=CNT*10+str[i]-'0';
		if (CNT>=M-1) CNT=CNT%(M-1)+(M-1);
	} MAX=min(CNT,k);
	FOR(i,1,MAX){
		// printf("%d : %lld\n",i,now);
		A.insert(now);
		now=f(now);
	} ll D=CNT-A.size();
	ll ans=powMM(2ll,CNT)-powMM(2ll,D)+M; ans%=M;
	// printf("%lld %lld A.size=%d\n",CNT,MAX,(int)A.size());
	printf("%lld\n",ans);
}
/*
002 1
1 2 3 4 5
100
100000000000000000000 1
0 0 0 1 1
4095
100000000000000000000 1
1 0 0 1 1
4095
*/
