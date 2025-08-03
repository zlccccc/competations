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


struct matrix {
	ull A[64];
	matrix() {memset(A,0,sizeof(A));}
} F[107];
matrix mul(matrix &A,matrix &B) {
	matrix C; int i,j,k;
	// REP(i,64) REP(j,64) REP(k,64)//去掉j
	// 	C.A[i]^=(((A.A[i]>>k)&1)&((B.A[k]>>j)&1))<<j;
	REP(k,64) REP(i,64) if ((A.A[i]>>k)&1)//去掉j
		C.A[i]^=B.A[k];
	return C;
}
inline matrix poww(matrix a,ll b){
	matrix ret; int i;
	REP(i,64) ret.A[i]|=1ull<<i;
	for (; b; b>>=1ll,a=mul(a,a))
		if (b&1) ret=mul(ret,a);
	return ret;
}
inline int getid(int x,int y){
	x--; y--; return x*n+y;
}
int A[10][10],B[10][10];
int main() {
	int T;
	scanf("%d",&T);
	while (T--) {
		matrix mul; int i,j,p,q,t;
		scanf("%d%d%d",&n,&m,&t);
		FOR(i,1,n) FOR(j,1,n) scanf("%d",&A[i][j]);
		FOR(i,1,m) FOR(j,1,m) scanf("%d",&B[i][j]);
		m/=2;
		FOR(i,1,n) FOR(j,1,n) {
			FOR(p,max(1,i-m),min(n,i+m)) FOR(q,max(1,j-m),min(n,j+m)){
				mul.A[getid(p,q)]^=(B[p-i+m+1][q-j+m+1]&1ull)<<(getid(i,j));//[p,q][i,j]
			}
		} mul=poww(mul,t);
		int ans=0;
		FOR(i,1,n) FOR(j,1,n){
			int val=0;
			FOR(p,1,n) FOR(q,1,n){
				val^=(A[p][q]&1)&((mul.A[getid(p,q)]>>getid(i,j))&1);//[p,q][i,j]
			} ans+=val;
		} printf("%d\n",ans);
	}
}
/*
*/
