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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

void getUpperLeft(int A[1007][1007],int n,int m,ll ans[1007][1007]) {
	static int U[1007][1007],S[1007],top;
	int i,j;
	FOR(i,1,n) {
		ll now=0; int *U_U=U[i];
		U_U[0]=0; top=0;
		FOR(j,1,m) {
			U[i][j]=A[i][j]?0:U[i-1][j]+1;
			while (top&&U_U[S[top]]>=U_U[j]) {
				now-=U_U[S[top]]*(S[top]-S[top-1]); top--;
			} S[++top]=j;
			now+=U_U[S[top]]*(S[top]-S[top-1]);
			ans[i][j]=now;
		}
	}
}
int A[1007][1007];
ll LU[1007][1007],RD[1007][1007];
void solve(int n,int m) {
	int i,j;
	// FOR(i,1,n) {
	// 	FOR(j,1,m) printf("%lld ",LU[i][j]); puts("");
	// }
	// FOR(i,1,n) {
	// 	FOR(j,1,m) printf("%lld ",RD[i][j]); puts("");
	// }
	getUpperLeft(A,n,m,LU);
	FOR(i,1,n)FOR(j,1,m) {
		int x=n-i+1,y=m-j+1;
		if (make_pair(i,j)<make_pair(x,y))
			swap(A[i][j],A[x][y]);
	} getUpperLeft(A,n,m,RD);
	FOR(i,1,n) FOR(j,1,m) {
		int x=n-i+1,y=m-j+1;
		if (make_pair(i,j)<make_pair(x,y)) {
			swap(A[i][j],A[x][y]);
			swap(RD[i][j],RD[x][y]);
		}
	}
	FOR(i,1,n) FOR(j,1,m) {
		add_(LU[i][j],(LU[i-1][j]+LU[i][j-1]-LU[i-1][j-1]+M)%M);
	}
}
int main() {
	int n,m;
	while (~scanf("%d%d",&n,&m)) {
		int i,j;
		FOR(i,1,n) FOR(j,1,m) scanf("%1d",&A[i][j]);
		solve(n,m);
		ll ans=0;
		FOR(i,1,n) FOR(j,1,m) {
			ll base=LU[i-1][m]+LU[n][j-1]-LU[i-1][j-1]+M;
			add_(ans,base*RD[i][j]%M);
			// printf("%d %d : %lld*%lld\n",i,j,base,RD[i][j]);
		}
		FOR(i,1,n) FOR(j,1,m) {
			if (j<m-j+1) swap(A[i][j],A[i][m-j+1]);
		}
		solve(n,m);
		FOR(i,1,n) FOR(j,1,m) {
			ll base=M-LU[i-1][j-1];
			add_(ans,base*RD[i][j]%M);
			// printf("%d %d : %lld*%lld\n",i,j,base,RD[i][j]);
		} ans%=M; ans+=M; ans%=M;
		printf("%lld\n",ans);
	}
}
/*
3 3
.##
##.
...
*/