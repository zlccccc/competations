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
const LL maxn=1e6+1007;
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
char str[maxn];//倒着的

inline int lowbit(int x){
	return x&-x;
}
ll fib[maxn],low[maxn],ans[maxn];
void check(){
	fib[1]=1; fib[2]=1; int i;
	FOR(i,3,10000) fib[i]=(fib[i-1]+fib[i-2])%(1<<30);
	FOR(i,1,10000) low[i]=lowbit(fib[i])+low[i-1];
	FOR(i,1,10000) ans[i]=ans[i-1]+fib[i];
	// FOR(i,1,100) printf("%d : %lld\n",i,ans[i]-low[i]);
	// FOR(i,1,100) printf("%d : %lld\n",i,low[i]);
	// FOR(i,1,100) printf("%lld,",low[i]);
	FOR(i,1,100) printf("%lld,",ans[i]);puts("");
	// FOR(i,1,10000) if (i%6==0) printf("%d,",lowbit(fib[i])/8); 
}

//f[1]=f[1]+f[2]; f[2]=f[1]; f[3]=f[3]+f[1];
struct mat{
	int A[3][3];
	mat(){memset(A,0,sizeof(A));}
}one;
mat mul(mat A,mat B){
	mat ret; int i,j,k;
	REP(i,3) REP(j,3) REP(k,3)
		add_(ret.A[i][k],(ll)A.A[i][j]*B.A[j][k]%M);
	return ret;
}
ll getfib(ll b){
	mat ret,a=one;
	ret.A[0][0]=ret.A[1][1]=ret.A[2][2]=1;
	for (; b; b>>=1ll,a=mul(a,a))
		if (b&1) ret=mul(ret,a);
	// int i,j;
	// REP(i,3) REP(j,3) printf("%d ",ret.A[i][j]);puts("");
	return (ret.A[0][2]+ret.A[1][2])%M;
}
int main() {
	// check();
	one.A[0][1]=one.A[1][1]=one.A[1][0]=1;
	one.A[0][2]=one.A[2][2]=1;
	int T,_; scanf("%d",&T);
	FOR(_,1,T) {
		ll n;
		scanf("%lld",&n);
		ll ans=getfib(n);
		// printf("first: %lld\n",ans);
		add_(ans,M-n%M);//1
		add_(ans,M-n/3%M);//2
		add_(ans,n/6*2%M);//%6==0
		n/=6;
		// printf("%lld; n=%lld\n",ans,n);
		//计算1<<i的个数
		for (ll x=1;x<=n;x<<=1){
			add_(ans,M-(n/x)*((x-x/2)%M)%M*8%M);
		}
		// printf("%lld; n=%lld\n",ans,n);
		printf("%lld\n",ans);
	}
}
/*
10
0 0 1 1 1 499122178 1 499122178 332748119 499122178
0 0 0 0 0 0 0 0 0 0
19

*/