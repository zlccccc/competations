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
const LL maxn=2e5+107;
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
char str[maxn];//倒着的

ll g[27][27];
ll MAX[1<<14|7][17];//status, top;
int bit[1<<14|7];
int main() {
	scanf("%d%d",&n,&m);
	int i,j;
	FOR(i,1,n) FOR(j,1,n) g[i][j]=-1e15;
	FOR(i,1,m) {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		u--; v--;
		g[u][v]=g[v][u]=w;
	}
	int all=1<<n,sta;
	REP(sta,all) bit[sta]=bit[sta>>1]+(sta&1);
	REP(sta,all) REP(i,n) MAX[sta][i]=-1e15;
	REP(i,n) MAX[1<<i][i]=0;
	REP(sta,all) {
		if (bit[sta]<=1) continue;
		REP(i,n) if ((sta>>i)&1) {
			int rem=sta^(1<<i);//no i
			REP(j,n) if (((rem>>j)&1)&&(g[i][j]>0)) {//i->j;
				int S=rem^(1<<j);//no j
				for (int now=S; ; now=S&(now-1)) {
					int s1=now|(1<<i),s2=(S^now)|(1<<j);
					MAX[sta][i]=max(MAX[sta][i],MAX[s1][i]+MAX[s2][j]+bit[s2]*(n-bit[s2])*g[i][j]);
					// pr2(s1,n); pr2(s2,n); printf("to ");pr2(sta,n); puts("");
					if (!now) break;
				}
			}
		}
	}
	printf("%lld\n",MAX[all-1][0]);
}
/*
*/