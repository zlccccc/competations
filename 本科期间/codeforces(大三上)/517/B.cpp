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

char str[2007][2007];
int C[2007][2007];
bool yes[2007][2007];
char ans[4007];
int main() {
	int i,j,n,k,cnt;
	scanf("%d%d",&n,&cnt);
	FOR(i,1,n) scanf("%s",str[i]+1);
	yes[1][1]=true;
	FOR(i,1,n) C[i][0]=C[0][i]=cnt+1;
	C[0][1]=0;
	FOR(k,1,n*2-1) {
		char c='z';
		bool coulda=false;
		FOR(i,max(1,k-n+1),min(n,k)) {
			j=k-i+1;
			C[i][j]=min(C[i-1][j],C[i][j-1])+1;
			if (str[i][j]=='a') C[i][j]--;
			if (C[i][j]<=cnt) coulda=true;
			// printf("getans (%d,%d) C=%d\n",i,j,C[i][j]);
			if (yes[i][j]) c=min(c,str[i][j]);
		}
		// printf("k=%d; coulda=%d\n",k,coulda);
		if (coulda) {
			ans[k]='a';
			FOR(i,max(1,k-n+1),min(n,k)) {
				j=k-i+1;
				if (yes[i][j]&&C[i][j]<=cnt)
					yes[i][j+1]=yes[i+1][j]=1;
			}
		} else {
			ans[k]=c;
			FOR(i,max(1,k-n+1),min(n,k)) {
				j=k-i+1;
				if (yes[i][j]&&str[i][j]==c)
					yes[i][j+1]=yes[i+1][j]=1;
			}
		}
	} puts(ans+1);
}
/*
*/