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
const LL maxn=4e6+107;
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

int Mod[3]={19280817,998244353,M};
priority_queue<pair<int,pii> > Q;
char pool[maxn],*st=pool;
int lef[maxn][3],rig[maxn][3];
int n,m;
inline int getid(int x,int y) {
	return (x-1)*(m+2)+y-1;
} //不使用
int main() {
	int i,j,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) {
		scanf("%s",st);
		st+=m+2;
	}
	// FOR(i,1,n) {
	// 	FOR(j,1,m) {
	// 		printf("%c",pool[getid(i,j)]);
	// 	} puts("");
	// } puts("<- init_map2");
	FOR(i,1,n) {
		FOR(j,1,m) {
			if (i==1&&j==1) REP(k,3) lef[getid(i,j)][k]=1;
			if (i!=1) {
				if (pool[getid(i,j)]=='.') {
					REP(k,3) add_(lef[getid(i,j)][k],lef[getid(i-1,j)][k],Mod[k]);
				}
			}
			if (j!=1) {
				if (pool[getid(i,j)]=='.') {
					REP(k,3) add_(lef[getid(i,j)][k],lef[getid(i,j-1)][k],Mod[k]);
				}
			}
			// printf("%d ",lef[getid(i,j)]);
		}// puts("");
	}
	// REP(k,3) printf("%d ",lef[getid(n,m)][k]);
	bool ok=0;
	REP(k,3) if (lef[getid(n,m)][k]) ok=1;
	if (!ok) return 0*puts("0");
	rFOR(i,1,n) {
		rFOR(j,1,m) {
			if (i==n&&j==m) REP(k,3) rig[getid(i,j)][k]=1;
			if (i!=1) {
				if (pool[getid(i,j)]=='.') {
					REP(k,3) add_(rig[getid(i-1,j)][k],rig[getid(i,j)][k],Mod[k]);
				}
			}
			if (j!=1) {
				if (pool[getid(i,j)]=='.') {
					REP(k,3) add_(rig[getid(i,j-1)][k],rig[getid(i,j)][k],Mod[k]);
				}
			}
			if (i==1&&j==1) continue;
			if (i==n&&j==m) continue;
			bool ok=1;
			REP(k,3) if ((ll)lef[getid(i,j)][k]*rig[getid(i,j)][k]%Mod[k]!=lef[getid(n,m)][k]) ok=0;
			if (ok) return 0*puts("1");
		}// puts("");
	}
	return 0*puts("2");
}
/*
3 3
.##
##.
...
*/