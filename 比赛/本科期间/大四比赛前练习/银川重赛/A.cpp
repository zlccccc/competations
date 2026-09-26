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

int A[maxn];
int op,val; ll ans;
int all[maxn*4][20][2],lz[maxn][20];
inline void build(int x,int l,int r) {
	int o;
	if (l==r) {
		REP(o,20) all[x][o][(A[l]>>o)&1]=1;
		return;
	} int mid=(l+r)/2;
	build(x<<1,l,mid); build(x<<1|1,mid+1,r);
	REP(o,20) {
		all[x][o][0]=all[x<<1][o][0]+all[x<<1|1][o][0];
		all[x][o][1]=all[x<<1][o][1]+all[x<<1|1][o][1];
		lz[x][o]=0;
	}
}
inline void update(int x,int l,int r,int L,int R) {
	int o;
	if (l<=L&&R<=r) {
		if (op==1) {
			REP(o,20) ans+=(ll)all[x][o][1]<<o;
			// printf("query %d->%d: %lld\n",l,r,ans);
		} else if (op==2) {
			REP(o,20) if ((val>>o)&1) {//0:same;1:reverse;2:all_zero;3:all_one
				swap(all[x][o][0],all[x][o][1]);
				lz[x][o]^=1;
			}
		} else if (op==3) {
			REP(o,20) if ((val>>o)&1) {
				all[x][o][1]=R-L+1; all[x][o][0]=0;
				lz[x][o]=3;
			}
		} else if (op==4) {
			// printf("update: %d->%d\n",l,r);
			REP(o,20) if (!((val>>o)&1)) {
				all[x][o][1]=0; all[x][o][0]=R-L+1;
				lz[x][o]=2;
			}
		} return;
	} int mid=(L+R)/2;
	REP(o,20) {
		if (lz[x][o]==1) {
			swap(all[x<<1][o][0],all[x<<1][o][1]);
			lz[x<<1][o]^=1;
			swap(all[x<<1|1][o][0],all[x<<1|1][o][1]);
			lz[x<<1|1][o]^=1;
		} else if (lz[x][o]==2) {
			// printf("pushdown %d -> %d: o=%d; 2\n",l,r,o);
			all[x<<1][o][1]=0; all[x<<1][o][0]=R-L+1;
			lz[x<<1][o]=2;
			all[x<<1|1][o][1]=0; all[x<<1|1][o][0]=R-L+1;
			lz[x<<1|1][o]=2;
		} else if (lz[x][o]==3) {
			all[x<<1][o][1]=R-L+1; all[x<<1][o][0]=0;
			lz[x<<1][o]=3;
			all[x<<1|1][o][1]=R-L+1; all[x<<1|1][o][0]=0;
			lz[x<<1|1][o]=3;
		}
	}
	if (l<=mid) update(x<<1,l,r,L,mid);
	if (mid<r) update(x<<1|1,l,r,mid+1,R);
	REP(o,20) {
		all[x][o][0]=all[x<<1][o][0]+all[x<<1|1][o][0];
		all[x][o][1]=all[x<<1][o][1]+all[x<<1|1][o][1];
		lz[x][o]=0;
	}
}
int main() {
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	build(1,1,n);
	int q; scanf("%d",&q);
	FOR(i,1,q) {
		int l,r;
		scanf("%d%d%d",&op,&l,&r);
		if (op==1) {
			ans=0;
			update(1,l,r,1,n);
			printf("%lld\n",ans);
		} else {
			scanf("%d",&val);
			update(1,l,r,1,n);
		}
	}
}
/*
5
1 1 1 1 1
7
1 1 5
2 1 2 2
1 1 2
3 1 2 2
1 1 2
4 1 2 2
1 1 2
*/