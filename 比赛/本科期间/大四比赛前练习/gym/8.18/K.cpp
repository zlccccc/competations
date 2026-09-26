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

int q[1007],x[1007];
int f[2007][207],g[407][257];//count
const int base=107;
int main() {
	freopen("kebab.in","r",stdin);
	freopen("kebab.out","w",stdout);
	int n,t,i,j,k;
	scanf("%d%d",&n,&t);
	FOR(i,1,n) scanf("%d%d",&q[i],&x[i]);
	f[0][t]=1;
	FOR(i,1,n) {
		memset(g,0,sizeof(g));
		FOR(j,0,t) g[base-j][0]=f[i-1][j];
		int MAX=q[i]-x[i];//偷懒
		FOR(j,base-t,q[i]+base) {//time
			FOR(k,0,MAX) { //least_remove
				add_(g[j][k],g[j-1][k]);//g:sum
				if (j>base&&k+1<=MAX) add_(g[j][k+1],g[j-t-1][k]);
				int _t=q[i]+base-j;
				if (_t<=t) add_(f[i][_t],g[j][k]);
				if (_t<t) add_(f[i][_t],-g[j-1][k]+M);
			}
			// FOR(k,0,MAX) printf("%d ",g[j][k]); printf(" <- g %d\n",j-base);
		}
		// FOR(j,0,t) printf("%d ",f[i][j]); puts(" <- f");
	}
	int ans=0;
	FOR(j,0,t) add_(ans,f[n][j]);
	printf("%d\n",ans);
}
/*
3 1
4 3
2 2
2 1

5 0
3 2
4 4
5 1
1 0
0 0
*/