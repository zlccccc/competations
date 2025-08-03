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

//二维前缀和写法
//calculate better
int f[5007][5007];//same_posvious
int pos[107];
void getCount(int n,int A[],int C[]) {
	f[0][0]=1; int i,j; C[0]=1;
	FOR(i,1,100) pos[i]=0;
	FOR(i,1,n) {
		int p=pos[A[i]];
		rFOR(j,1,i) {//position,value
			f[i][j]=C[j-1];
			add_(C[j],f[i][j]);
			if (p) add_(C[j],M-f[p][j]);//不知道这样hit怎样
		} pos[A[i]]=i;
		// FOR(j,1,i) printf("%d ",C[j]); puts("<- C");
	}
}
int A[5007],B[5007];
int CA[5007],CB[5007];
int getbetter(int n,int m) {
	int ret=0,i;
	getCount(n,A,CA); getCount(m,B,CB); CA[0]=CB[0]=0;
	// FOR(i,1,n) printf("%d ",CA[i]); puts("<- countA");
	// FOR(i,1,m) printf("%d ",CB[i]); puts("<- countB");
	FOR(i,1,n) add_(CB[i],CB[i-1]);
	FOR(i,1,n) add_(ret,(ll)CA[i]*CB[i-1]%M);
	return ret;
}
int LA[5007],RA[5007],LB[5007],RB[5007];
void getPos(int n,int m){
	int i;
	FOR(i,1,100) pos[i]=0;
	FOR(i,1,n) {LA[i]=pos[A[i]]; pos[A[i]]=i;}
	FOR(i,1,100) pos[i]=0;
	rFOR(i,1,n) {RA[i]=pos[A[i]]; pos[A[i]]=i;}
	FOR(i,1,100) pos[i]=0;
	FOR(i,1,m) {LB[i]=pos[B[i]]; pos[B[i]]=i;}
	FOR(i,1,100) pos[i]=0;
	rFOR(i,1,m) {RB[i]=pos[B[i]]; pos[B[i]]=i;}
}
//calculate same_length
int g[5007][5007],_g[5007][5007];
int getsame(int n,int m) {
	int i,j;
	getPos(n,m);
	FOR(i,1,n) g[i][m+1]=1;
	FOR(i,1,m) g[n+1][i]=1;
	g[n+1][m+1]=1;
	rFOR(i,1,n) {//same_right
		int px=RA[i];
		rFOR(j,1,m) {//posfix_sum
			int py=RB[j],now=0;//only choose this
			add_(now,g[i+1][j+1]);//f:prefix_sum
			if (px) add_(now,M-g[px+1][j+1]);//+1:sum
			if (py) add_(now,M-g[i+1][py+1]);
			if (px&&py) add_(now,g[px+1][py+1]);
			g[i][j]=f[i][j]=now;
			//sum_it
			add_(g[i][j],g[i+1][j]);
			add_(g[i][j],g[i][j+1]);
			add_(g[i][j],M-g[i+1][j+1]);
		}
	}
	// FOR(i,1,n) {//f:suffix
	// 	FOR(j,1,m) printf("%d ",f[i][j]); puts("  f");
	// }
	// FOR(i,1,n) {//f:suffix
	// 	FOR(j,1,m) printf("%d ",g[i][j]); puts("  g");
	// }
	int ret=0;

	FOR(i,1,n) _g[i][0]=1;
	FOR(i,1,m) _g[0][i]=1;
	_g[0][0]=1;
	FOR(i,1,n) {//same_right
		int px=LA[i];
		FOR(j,1,m) {//posfix_sum
			int py=LB[j],now=0;//only choose this
			add_(now,_g[i-1][j-1]);//f:prefix_sum
			if (px) add_(now,M-_g[px-1][j-1]);//+1:sum
			if (py) add_(now,M-_g[i-1][py-1]);
			if (px&&py) add_(now,_g[px-1][py-1]);

			if (A[i]>B[j]) {
				int base=g[i+1][j+1],mul=now;//choose it
				add_(ret,(ll)mul*base%M);
				// printf("(%d,%d) : %d*%d=%lld(%d %d)\n",i,j,mul,base,(ll)mul*base%M,px,py);
			} 
			if (A[i]==B[j]) {
				f[i][j]=now;
			} else f[i][j]=0;
			_g[i][j]=f[i][j];
			add_(_g[i][j],_g[i-1][j]);
			add_(_g[i][j],_g[i][j-1]);
			add_(_g[i][j],M-_g[i-1][j-1]);
		}
	}
	return ret;
}
int main() {
	int n,m,i; scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,m) scanf("%d",&B[i]);
	int now=0;
	add_(now,getbetter(n,m));
	add_(now,getsame(n,m));
	printf("%d\n",now);
}
/*
3 5
2 1 2
1 2 2 1 2

*/