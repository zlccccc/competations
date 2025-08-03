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
const LL maxn=1e4+107;
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
// char str[maxn];


int f[6007][6007];
ll fac[100007];
ll inv[100007];
ll inv2=powMM(2ll,M-2);
const int MAX=6000;
void init(){
	int i,k;
	// int j;
	fac[0]=1; 
	FOR(i,1,MAX) fac[i]=fac[i-1]*i%M;
    inv[0]=inv[1]=1;
    FOR(i,2,MAX) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,MAX) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	FOR(i,1,MAX) f[1][i]=fac[i]*i%M*(i-1)%M*inv2%M*inv2%M;
	FOR(k,2,MAX) {
		ll all=0;
		FOR(i,1,MAX){
			f[k][i]=all*2%M*fac[i-1]%M;
			add_(all,f[k-1][i]*inv[i]%M);
			// FOR(j,1,i-1){
			// 	f[k][i]=(ll)f[k][i]+f[k-1][j]*fac[i-1]%M*inv[j]%M*2%M;
			// }
		}
	}
	// FOR(k,1,10) {FOR(i,1,10) printf("%d ",f[k][i]); puts("");}
}
int main() {
	int _,T;
	init();
	scanf("%d",&T);
	FOR(_,1,T){
		int n,k; scanf("%d%d",&n,&k);
		printf("Case #%d: %d\n",_,f[k][n]);
	}
}
/*
*/