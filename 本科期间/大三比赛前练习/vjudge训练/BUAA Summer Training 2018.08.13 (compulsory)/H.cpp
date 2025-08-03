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

int p[19]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
ull f[1<<19|7],g[1<<19|7],multi[1<<19|7];
const ull MAX=0xffffffffffffffffull;
int solve(int a,int b){
	int i,k;
	FOR(i,1,70) if (a<=i*i&&i*i<=b) return 0*printf("%d\n",i);
	memset(f,0xff,sizeof(f));
	memset(g,0xff,sizeof(g));
	FOR(i,a,b){
		int now=0,t=i;ull mul=1;
		REP(k,19){
			int mask=0;
			while (t%p[k]==0) {
				if (mask==1) mul*=p[k];
				t/=p[k],mask^=1;
			} now|=mask<<k;
		} if (t!=1) continue;
		REP(k,(1<<19)) if (f[k]!=MAX&&f[k]<MAX/mul/multi[k&now]){
			// printf("%llu %llu\n",g[k^now],f[k]*mul*multi[k&now]);
			min_(g[k^now],f[k]*mul*multi[k&now]);
		} REP(k,(1<<19)) f[k]=g[k];
		min_(f[now],mul);
	} if (f[0]==MAX) return 0*puts("none");
	else printf("%llu\n",(ull)f[0]);
	return 0;
}
int main() {
	int i,j;
	REP(j,1<<19) multi[j]=1;
	REP(i,19) REP(j,1<<19) if ((j>>i)&1){
		if (multi[j]>MAX/p[i]) multi[j]=MAX;
		else multi[j]*=p[i];
	} int a,b;
	while (~scanf("%d%d",&a,&b)) solve(a,b);
}
/*
*/
