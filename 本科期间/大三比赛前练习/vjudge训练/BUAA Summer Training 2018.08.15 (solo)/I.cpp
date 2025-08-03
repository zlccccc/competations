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

char C[20]= {'A', 'H', 'I', 'M', 'O', 'T', 'U', 'V', 'W', 'X', 'Y'};
int A[maxn*2];
int s[maxn],p[maxn];
int solve() {
	scanf("%s",str);
	int len=strlen(str),i,j;
	bool mark=0;
	REP(i,len) {
		REP(j,11) if (str[i]==C[j]) break;
		if (j==11) s[i]=i+10000;
		else s[i]=str[i],mark=1;
	} if (!mark) return 0*puts("0");

	A[0]='+'; A[1]='%';
	REP(i,len+1) {
		A[i*2+2]=s[i];
		A[i*2+3]='%';
	} len=len*2+2; A[len+1]=0;
	int id=0,mx=0;
	FOR(i,1,len-1) {
		if (mx>i) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while (A[i+p[i]]==A[i-p[i]]) p[i]++;
		if (p[i]+i>mx) {
			mx=p[i]+i;
			id=i;
		}
	} int ans=0;
	// FOR(i,1,len) printf("%-6d ",A[i]); puts("");
	// FOR(i,1,len) printf("%-6d ",p[i]); puts("");
	FOR(i,1,len-1) if (A[i]<1000) max_(ans,p[i]-1);
	printf("%d\n",ans);
	return 0;
}
int main() {
	int T; scanf("%d",&T);
	while (T--) solve();
}
/*
1000
ASD
AAASAAA
ASAA
*/
