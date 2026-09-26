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

ll poww(ll a,ll b,ll M) {
	ll ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int p[maxn],tot;
bool mark[maxn];
bool isroot(int x,int p) {
	if (!(x%p)||(x%p==1&&p!=2)) return 0;
	for (ll i=2; i*i<=p-1; i++) if ((p-1)%i==0)
			if (poww(x,(p-1)/i,p)==1||poww(x,i,p)==1) return 0;
	return 1;
}
LL guass(LL A[107][107],int n,LL M) {
    LL ret=1; int i,j,k;
    REP(i,n) {
        int id=i;
        if (!A[i][i]) rep(j,i+1,n) if (A[j][i]) id=j;
        if (!A[id][i]) continue;
        if (id!=i) {rep(j,i,n) swap(A[i][j],A[id][j]); ret*=-1;}
        A[i][i]%=M; (A[i][i]<0) &&(A[i][i]+=M);
        LL rev=poww(A[i][i],M-2,M);
        rep(k,i+1,n) if (A[k][i])
            rrep(j,i,n) (A[k][j]-=(LL)A[k][i]*rev%M*A[i][j])%=M;
    } REP(i,n)(ret*=A[i][i])%=M;
    (ret<0) &&(ret+=M);
    return ret;
}
// 矩阵树定理: \sum \prod w[edge_i]
ll A[107][107];
int U[maxn],V[maxn],C[maxn];
int pwone[maxn];
int main() {
	int i,j,k,K,g; ll p;
	scanf("%d%d%d%lld",&n,&m,&K,&p);
	for (g=2; !isroot(g,p); g++);
	int one=poww(g,(p-1)/K,p);
	pwone[0]=1;
	FOR(i,1,100000) pwone[i]=(ll)pwone[i-1]*one%p;
	FOR(i,1,m) {
		scanf("%d%d%d",&U[i],&V[i],&C[i]);
		U[i]--; V[i]--;//one edge
	} int ans=0;
	REP(k,K) {
		REP(i,n) REP(j,n) A[i][j]=0;
		FOR(i,1,m) {
			ll w=pwone[C[i]*k];
			add_(A[U[i]][V[i]],p-w,p);
			add_(A[V[i]][U[i]],p-w,p);
			add_(A[V[i]][V[i]],w,p);
			add_(A[U[i]][U[i]],w,p);
		} add_(ans,guass(A,n-1,p),p);
	} int inv=poww(K,p-2,p);
	printf("%lld\n",(ll)ans*inv%p);
}
/*
*/
