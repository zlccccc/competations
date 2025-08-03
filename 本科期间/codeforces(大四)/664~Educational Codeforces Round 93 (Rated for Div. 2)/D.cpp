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

map<int,int> MP;
int A[maxn];
int R[maxn],G[maxn],B[maxn];
ll f[207][207][207];
int main() {
	int T,_; T=1;
	// scanf("%d",&T);
	FOR(_,1,T){
		int i,j,k,r,g,b; ll ans=0;
		scanf("%d%d%d",&r,&g,&b);
		FOR(i,1,r) scanf("%d",&R[i]);
		FOR(i,1,g) scanf("%d",&G[i]);
		FOR(i,1,b) scanf("%d",&B[i]);
		sort(R+1,R+1+r); reverse(R+1,R+1+r);
		sort(G+1,G+1+g); reverse(G+1,G+1+g);
		sort(B+1,B+1+b); reverse(B+1,B+1+b);
		FOR(i,0,r) FOR(j,0,g) FOR(k,0,b) {
			if (i&&j) max_(f[i][j][k],f[i-1][j-1][k]+R[i]*G[j]);
			if (i&&k) max_(f[i][j][k],f[i-1][j][k-1]+R[i]*B[k]);
			if (j&&k) max_(f[i][j][k],f[i][j-1][k-1]+G[j]*B[k]);
			max_(ans,f[i][j][k]);
		}
		printf("%lld\n",ans);
	}
}
/*
6 1
1 0 0 1 1 1

6 2
1 0 0 1 1 1
*/