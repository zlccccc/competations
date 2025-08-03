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
const LL maxn=1e6+7;
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
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
template<typename T1,typename T2>
inline int mul(T1 A,T2 B,ll MOD=M) {return (ll)A*B%MOD;}
inline int add(int A,int B,int MOD=M) {A+=B; (A>=MOD) &&(A-=MOD); return A;}

//f:must_okay; g:no limit
int f[1007][1007],g[1007][1007];
int pwp[1007];
int A[1007],B[1007],C[1007],H[1007];
void multi(int A[],int B[],int C[],int n){
	int i,j; static int tmp[maxn];
	FOR(i,0,n+n) tmp[i]=0;
	FOR(i,0,n) FOR(j,0,n) add_(tmp[i+j],mul(A[i],B[j]));
	rFOR(i,n,n+n) if (tmp[i]){
		FOR(j,1,n) add_(tmp[i-j],mul(H[j],tmp[i])); tmp[i]=0;
	} FOR(i,0,n) C[i]=tmp[i];
}
int solve(int n,int k,int p) {
	int i,j,t; int q=M+1-p; q%=M;
	pwp[0]=1; FOR(i,1,1000) pwp[i]=mul(pwp[i-1],p);
	FOR(i,1,k+1) memset(f[i],0,sizeof(f[i])),memset(g[i],0,sizeof(g[i]));
	f[k+1][0]=1; f[k+1][1]=0;//yes
	g[k+1][0]=1; g[k+1][1]=0;//at least
	rFOR(t,0,k) {
		int MAX=0;
		if (!t) MAX=k; else MAX=k/t;
		f[t][0]=g[t][0]=1;
		FOR(i,1,MAX) {
			f[t][i]=0;
			FOR(j,1,i) {//position
				add_(f[t][i],mul(mul(g[t+1][j-1],g[t][i-j]),mul(pwp[j-1],q)));
				// printf("add:f[%d][%d],%d*%d*%d\n",t,i,g[t+1][j-1],g[t][i-j],mul(pwp[j-1],q));
			} g[t][i]=add(f[t][i],mul(g[t+1][i],pwp[i]));
		}
	}
	// puts("f:");
	// rFOR(t,0,k) {
	// 	int MAX=0;
	// 	if (!t) MAX=n; else MAX=k/t;
	// 	FOR(i,1,MAX) printf("%d ",f[t][i]); puts("");
	// }
	// puts("g:");
	// rFOR(t,0,k+1) {
	// 	int MAX=0;
	// 	if (!t) MAX=n; else MAX=k/t;
	// 	FOR(i,1,MAX) printf("%d ",g[t][i]); puts("");
	// }
	FOR(i,1,k+1) H[i]=mul(g[1][i-1],mul(pwp[i-1],q));
	FOR(i,0,k+1) A[i]=0,B[i]=0; A[1]=1; B[0]=1;
	for (int x=n;x;x>>=1,multi(A,A,A,k+1)){
		if (x&1) multi(A,B,B,k+1);
		// FOR(i,0,k) printf("%d ",A[i]); puts(" <- A");
		// FOR(i,0,k) printf("%d ",B[i]); puts(" <- B");
	}
	int ans=0;
	FOR(i,0,k) add_(ans,mul(B[i],g[0][i]));
	// printf("ans=%d\n",ans);
	return ans;
}
int main() {
	int k,x,y,p;
	scanf("%d%d%d%d",&n,&k,&x,&y);
	p=(ll)x*powMM((ll)y,M-2)%M;
	int ans=solve(n,k,p); add_(ans,M-solve(n,k-1,p));
	printf("%d\n",ans);
	return 0;
}
/*
10 1 1 2
*/
