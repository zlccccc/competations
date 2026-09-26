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

int f[507][507],g[507][507];//depth,length; g:all=1
int main() {
	int i,j,k; 
	scanf("%d%d",&n,&m);
	FOR(j,1,n) f[0][j]=1;
	FOR(j,1,n) FOR(k,1,n) g[j][k]=1;
	FOR(i,1,m) {
		if (i==1){
			FOR(j,1,n) f[i][j]=j+1;
		} else {
			FOR(j,1,n){
				add_(f[i][j],1);//000..
				add_(f[i][j],f[i-1][j]);//111...
				// int base=1;
				// rFOR(k,1,j-1) add_(f[i][j],(ll)base*f[k][j]%M),base=M-base;
				// add_(f[i][j],base); if (j==1) add_(f[i][j],-1);
				// add_(f[i][j],(f[i-1][j]+M-1-f[i-2][j])%M);//same; or ==

				FOR(k,1,j-1){
					int now=0;
					add_(now,(ll)f[i-1][k]*f[i-1][j-k]%M);//111...000...
					add_(now,M-(ll)f[i-2][k]*f[i-1][j-k]%M);//top:111...000...
					add_(now,g[j][k]); add_(f[i][j],now);//same
					g[j][k]=now;
					printf("%d %d -: %d * %d +: %d\n",i,j,f[i-2][k],f[i-1][j-k]-1,g[j][k]);
				}
			}
		} FOR(j,1,n) printf("%d ",f[i][j]); puts("");
	}
	printf("%d\n",f[m][n]);
}
/*
*/
