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

void fwt(int *A,int len,int inv) {
	int i,j,k;
    ll div=powMM(2ll,M-2);
	for (i=2; i<=len; i<<=1) {
		for (j=0; j<len; j+=i) {
			for (k=j; k<j+i/2; k++) {
				if (inv==1) {
					int a=A[k],b=A[k+i/2];
					A[k]=(a+b)%M;
					A[k+i/2]=(a-b+M)%M;
				} else {
					int a=A[k],b=A[k+i/2];
					A[k]=(a+b)*div%M;
					A[k+i/2]=(a-b+M)%M*div%M;
				}
			}
		}
	}
}
int ans=n;
int A[5][maxn],B[maxn],C[maxn];
int main() {
	int i,j,k;
	scanf("%d",&n);
	int ans=n; int all=0;
	REP(i,n) scanf("%d",&k),A[0][k]=1,all^=k; A[0][0]=1;
	int len=1<<19;
	if (all) {
		fwt(A[0],len,1); ans--; B[0]=1;
		rep(i,1,5) {
			REP(j,len) A[i][j]=(ll)A[i-1][j]*A[i-1][j]%M;
			// fwt(A[i],len,-1);
			// REP(j,512) printf("%d ",A[i][j]); puts("");
			// fwt(A[i],len,1);
		}
		rREP(i,5) {
			fwt(B,len,1);
			REP(j,len) C[j]=(ll)B[j]*A[i][j]%M;
			fwt(C,len,-1);
			if (C[all]) {fwt(B,len,-1); continue;}
			REP(j,len) B[j]=(C[j]!=0);
			ans-=1<<i;
		}
	} printf("%d\n",ans);
}
/*
8
1 9 2 6 0 8 1 7

8
1 2 4 8 16 32 64 128

9
1 2 4 8 16 32 64 128 256
*/
