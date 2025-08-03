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
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,ll B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b,ll MOD=M) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%MOD)
		if (b&1) ret=(LL)ret*a%MOD;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

const int MAXSIZE=129;
struct matrix {
	ll A[MAXSIZE][MAXSIZE];
	matrix() {
		int i,j;
		REP(i,MAXSIZE) REP(j,MAXSIZE) A[i][j]=-INFF;
	}
};
matrix mul(matrix &A,matrix &B) {
	matrix C; int i,j,k;
	REP(k,MAXSIZE) REP(i,MAXSIZE) {
		if (A.A[i][k]>=0) REP(j,MAXSIZE)//去掉j
			max_(C.A[i][j],A.A[i][k]+B.A[k][j]);
	} return C;
}
inline matrix poww(matrix a,ll b) {
	matrix ret=a; b--; assert(b>=0);
	for (; b; b>>=1ll,a=mul(a,a))
		if (b&1) ret=mul(ret,a);
	return ret;
} int A[maxn];
int main() {
	int n,m,t,T,i,j;
	scanf("%d%d%d%d",&n,&m,&t,&T);
	matrix ini; ll ans=0;
	REP(i,m) {
		int x,y;
		scanf("%d%d",&x,&y);
		ini.A[x][y]=0;
	} FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,0,n) {
		FOR(j,1,n) if (ini.A[i][j]==0) ini.A[i][j]=A[j];
		ini.A[0][i]=A[i];
	} //first_way
	matrix mat_1=poww(ini,t);
	FOR(j,0,n) max_(ans,mat_1.A[0][j]);
	// printf("ans1=%lld\n",ans);
	//second way, 用了血剌
	ini.A[0][0]=-INFF;
	matrix mat_2_1=poww(ini,T);
	matrix o_o;
	// FOR(i,1,n) FOR(j,0,n) {
	// 	printf("%d->%d : %lld\n",i,j,mat_2_1.A[i][j]);
	// }
	FOR(i,0,n) FOR(j,1,n) {
		o_o.A[i][j]=o_o.A[i+n][j+n]=ini.A[i][j];
		o_o.A[i][j+n]=max(-INFF,mat_2_1.A[i][j]*2);
	} o_o.A[0][0]=0;
	matrix mat_2_2=poww(o_o,t-T+1);
	FOR(j,n+1,n+n) max_(ans,mat_2_2.A[0][j]);
	printf("%lld\n",ans);
}
/*
2 1 4 3
1 2
1 2
*/
