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
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
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

ll mod;
struct matrix{
	ll x[2][2];
	matrix(){memset(x,0,sizeof(x));}
	void init(){x[0][0]=x[1][1]=1;}
}base;
matrix mul(const matrix &x,const matrix &y) {
	matrix ret; int i,j,k;
	REP(i,2) REP(j,2) REP(k,2) {
		add_(ret.x[i][j],(ll)x.x[i][k]*y.x[k][j]%mod,mod);
	} return ret;
}
// inline matrix powMM(matrix a,int b) {
// 	matrix ret; ret.init();
// 	for (; b; b>>=1ll,a=mul(a,a))
// 		if (b&1) ret=mul(ret,a);
// 	return ret;
// }
char str[maxn];
matrix matval[4];//base,2,4,8
int main() {
	ll x0,x1,a,b;
	scanf("%lld%lld%lld%lld",&x0,&x1,&a,&b);
	base.x[1][0]=1;
	base.x[0][1]=b; base.x[1][1]=a;
	scanf("%s",str); scanf("%lld",&mod);
	int len=strlen(str);
	matval[0]=base;
	matrix ans; ans.init();
	int i,o;
	rREP(i,len) {
		rep(o,1,4) matval[o]=mul(matval[o-1],matval[o-1]);
		int now=str[i]-'0';
		// REP(o,4) {
		// 	printf("%d %d\n%d %d (ed)\n",matval[o].x[0][0],matval[o].x[0][1],matval[o].x[1][0],matval[o].x[1][1]);
		// }
		REP(o,4) if ((now>>o)&1) ans=mul(ans,matval[o]);
		matval[0]=mul(matval[1],matval[3]);
	}
	// printf("%d %d\n%d %d (ed)\n",ans.x[0][0],ans.x[0][1],ans.x[1][0],ans.x[1][1]);
	printf("%lld\n",((ll)x0*ans.x[0][0]+(ll)x1*ans.x[1][0])%mod);
}
/*
1 1 1 1
10 10
*/