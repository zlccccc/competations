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
const LL maxn=4e5+107;
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
char str[maxn];

ll inv[maxn];
LL fac[maxn];//Factorial
int ans[407][407];
int cnt[1007];
int dp[maxn];
vector<int> S;
int main() {
	int i;
	scanf("%s",str);
	n=strlen(str);
	fac[0]=1;
	FOR(i,1,100000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,100000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,100000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	FOR(i,'a','z') S.push_back(i);
	FOR(i,'A','Z') S.push_back(i);
	REP(i,n) cnt[(int)str[i]]++; n/=2;
	dp[0]=1;
	for (int c:S) if (cnt[c])
			rFOR(i,0,n-cnt[c]) add_(dp[i+cnt[c]],dp[i]);
	int base=fac[n]*fac[n]%M;
	for (int c1:S) if (cnt[c1]) base=base*inv[cnt[c1]]%M;
	// printf("base=%d\n",base);
	// FOR(i,0,n) printf("%d ",dp[i]); puts(" <- init");
	for (int c1:S) if (cnt[c1]) {
			vector<int> pos1; int k1=cnt[c1];
			FOR(i,0,n-k1) add_(dp[i+k1],M-dp[i]);//rev1
			for (int c2:S) if (c1!=c2&&cnt[c2]&&cnt[c2]+cnt[c1]<=n) {
					vector<int> pos2; int k2=cnt[c2];
					for (int i=n-k1-k2; i>=0; i-=k2) pos2.push_back(i);
					reverse(pos2.begin(), pos2.end());//rFOR
					// for (int p:pos) printf("%d ",p); puts("");
					for (int p:pos2) add_(dp[p+k2],M-dp[p]);//rev1
					// FOR(i,0,n) printf("%d ",dp[i]);puts("<-deled");
					// for (int p:pos) printf("%d ",p); puts("");
					// printf("%c - %c : %d\n",(char)c1,(char)c2,dp[n-k1-k2]);
					ans[c1][c2]=(ll)dp[n-k1-k2]*2%M;//onleft; onright
					reverse(pos2.begin(), pos2.end());//rFOR
					for (int p:pos2) add_(dp[p+k2],dp[p]);//rev1
				} reverse(pos1.begin(), pos1.end());//rFOR
			rFOR(i,0,n-k1) add_(dp[i+k1],dp[i]);//rev1
		}
	// printf("dp=%d\n",dp[n]);
	scanf("%d",&q);
	while (q--) {
		int u,v,Ans;
		scanf("%d%d",&u,&v); u--; v--;
		if (str[u]==str[v]) Ans=dp[n];
		else Ans=ans[(int)str[u]][(int)str[v]];
		Ans=(ll)Ans*base%M;
		printf("%d\n",Ans);
	}
}
/*
acdefg
10
1 3

*/