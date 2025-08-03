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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int main() {
	int T,_;
	int i,j,k;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,m,K,p,q;
		scanf("%d%d%d%d%d",&n,&m,&K,&p,&q);
		FOR(i,1,n) memset(g[i]+1,0,i*sizeof(int));
		g[1][1]=1;
		FOR(i,1,m-1) {
			//left: f[i+1][1]+=f[i][1]*p; f[i][j]+=f[i][j+1]*p
			//right:f[i][j]+=f[i][j-1]*q; f[i+1][i+1]+=f[i][i]*q
			rFOR(j,1,min(i,n)) { //len,pos
				memcpy(f[j]+1,g[j]+1,j*sizeof(int));
				FOR(k,1,j) mul_(g[j][k],100-p-q);

				if (j!=n) add_(g[j+1][j+1],(ll)f[j][j]*p%M);
				else add_(g[j][1],(ll)f[j][j]*p%M);
				FOR(k,1,j-1) add_(g[j][k+1],(ll)f[j][k]*p%M);

				if (j!=n) add_(g[j+1][1],(ll)f[j][1]*q%M);
				else add_(g[j][j],(ll)f[j][1]*q%M);
				FOR(k,2,j) add_(g[j][k-1],(ll)f[j][k]*q%M);
			}
		} int ans=0;
		FOR(i,1,n) {
			// FOR(j,1,i) printf("%d ",g[i][j]); puts("");
			int now=0;
			FOR(j,1,i) add_(now,g[i][j]);
			add_(ans,(ll)powMM(i,K)*now%M);
		} printf("%d\n",ans);
	}
}
/*
10
5 5 1 25 25
5 5 2 50 50
5 5 3 0 100
3 5 3 0 100
*/