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
const LL maxn=1e6+7;
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

LL inv[1000002];//inverse
LL fac[1000002];//Factorial
int l[maxn],r[maxn];
inline ll get2(ll x){
	// printf("get2: %d\n",x);
	return x*(x+1)/2;
}
ll solve(){
	int i,k,ans=0;
	scanf("%d",&n); m=0;
	FOR(i,1,n) scanf("%d%d",&l[i],&r[i]),max_(m,r[i]);
	FOR(k,1,m){//MAX
		ll now=1;
		FOR(i,1,n){
			if (l[i]>k) now=0;
			if (r[i]>=k) mul_(now,inv[r[i]-l[i]+1]*get2(k-l[i]+1)%M);
			else mul_(now,inv[r[i]-l[i]+1]*(M+get2(k-l[i]+1)-get2(k-r[i]))%M);
		} add_(ans,now);
		// printf("%d : %d\n",k,ans);
		now=M-1;
		FOR(i,1,n){
			if (l[i]>k) now=0;
			if (r[i]>=k) mul_(now,inv[r[i]-l[i]+1]*(get2(k-l[i]+1)+M-1)%M);
			else mul_(now,inv[r[i]-l[i]+1]*(M+get2(k-l[i]+1)-get2(k-r[i]))%M);
		} add_(ans,now);
		// printf("%d : %d\n",k,ans);
	} printf("%d\n",ans);
	return 0;
}
int main() {
    int i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
/*
*/
