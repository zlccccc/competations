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

int val[maxn];
int getans(ll k) {
	int t;
	FOR(t,1,100) {
		val[t]=k%(t+1); k/=t+1;
		// printf("k=%lld\n",k);
		if (!k) break;
	} return t;
}
ll C[107][107];
int cnt[maxn],sum[maxn];
void init() {
	int i,j;
	C[0][1]=C[1][1]=1;
	FOR(j,1,100) {
		C[0][j]=1;
		FOR(i,1,j) C[i][j]=C[i-1][j-1]+C[i][j-1];
	}
}
int main() {
	int _,T; scanf("%d",&T);
	init();
	FOR(_,1,T) {
		int i;
		ll now; scanf("%lld",&now);
		int l=getans(now);
		// FOR(i,1,l) printf("%d ",val[i]); puts("");
		FOR(i,1,l) val[i]=l-val[i]+1;
		sort(val+1,val+1+l);
		// FOR(i,1,l) printf("%d ",val[i]); puts("");
		FOR(i,1,l+1) cnt[i]=0;
		FOR(i,1,l) cnt[val[i]]++;
		FOR(i,1,l+1) sum[i]=cnt[i]+sum[i-1];
		// FOR(i,1,l) printf("%d ",cnt[i]); puts("");
		// FOR(i,1,l) printf("%d ",sum[i]); puts("");
		ll ans=0; now=1;
		FOR(i,1,l) now*=C[cnt[i]][i+1-sum[i-1]];
		// printf("now=%lld\n",now);
		ans=now;
		if (sum[l]!=l) {
			now=1; 
			FOR(i,1,l) now*=C[cnt[i]][i-sum[i-1]];
			// printf("now=%lld\n",now);
			ans-=now;
		} ans--;
		printf("%lld\n",ans);
	}
}
/*
3
1
11
123456
*/