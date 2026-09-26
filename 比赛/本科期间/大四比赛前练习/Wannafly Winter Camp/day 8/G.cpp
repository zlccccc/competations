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

int A[2007][2007];
int sum[2007][2007];//left_upper
void getans_zero(){
	int u,v,i,j,ans=0;
	FOR(i,1,n) FOR(j,1,m) if (A[i][j]){
		FOR(u,1,n) FOR(v,1,m) if (A[u][v]){
			int lx=min(i,u),rx=max(i,u);
			int ly=min(j,v),ry=max(j,v);
			ans+=lx*ly*(n-rx+1)*(m-ry+1);
		}
	} printf("%d\n",ans);
}
void getans_check(){
	int u,v,i,j,ans=0;
	FOR(i,1,n) FOR(j,1,m) if (A[i][j]){
		FOR(u,1,n) FOR(v,1,m) if (A[u][v]){
			// if (i<u&&j==v){
				int lx=min(i,u),rx=max(i,u);
				int ly=min(j,v),ry=max(j,v);
				ans+=lx*ly*(n-rx+1)*(m-ry+1);
			// }
		}
	} printf("check: %d\n",ans);
}
int main() {
	int i,j;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) FOR(j,1,m) scanf("%1d",&A[i][j]);
	// getans_check();
	int ans=0;
	FOR(i,1,n) FOR(j,1,m) sum[i][j]=0;
	FOR(i,1,n) FOR(j,1,m) {//LU
		if (A[i][j]){
			add_(ans,(ll)(n-i+1)*(m-j+1)*sum[i-1][j-1]%M);
			add_(sum[i][j],i*j%M);
		} add_(sum[i][j],(sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+M)%M);
	}
	// printf("first : %d\n",ans); ans=0;
	FOR(i,1,n) FOR(j,1,m) sum[i][j]=0;
	FOR(i,1,n) rFOR(j,1,m) {//RU
		if (A[i][j]){
			add_(ans,(ll)(n-i+1)*j*sum[i-1][j+1]%M);
			add_(sum[i][j],i*(m-j+1)%M);
		} add_(sum[i][j],(sum[i-1][j]+sum[i][j+1]-sum[i-1][j+1]+M)%M);
	}
	// printf("second : %d\n",ans); ans=0;
	// first part: okay?
	FOR(i,1,n) FOR(j,1,m) sum[i][j]=0;
	FOR(i,1,n) FOR(j,1,m) {//RU
		if (A[i][j]){
			add_(ans,(ll)i*(n-i+1)*(m-j+1)%M*sum[i][j-1]%M);
			add_(sum[i][j],j);
		} add_(sum[i][j],sum[i][j-1]);
	}
	// printf("third : %d\n",ans); ans=0;
	FOR(i,1,n) FOR(j,1,m) sum[i][j]=0;
	FOR(i,1,n) FOR(j,1,m) {//RU
		if (A[i][j]){
			add_(ans,(ll)(n-i+1)*j*(m-j+1)%M*sum[i-1][j]%M);
			add_(sum[i][j],i);
		} add_(sum[i][j],sum[i-1][j]);
	}
	// printf("last : %d\n",ans); ans=0;
	add_(ans,ans);
	FOR(i,1,n) FOR(j,1,m) {//RU
		if (A[i][j])
			add_(ans,(ll)i*(n-i+1)*j*(m-j+1)%M);
	}
	printf("%d\n",ans);
}
/*
3 3
010
111
010

4 4
0110
1010
1001
0110
*/