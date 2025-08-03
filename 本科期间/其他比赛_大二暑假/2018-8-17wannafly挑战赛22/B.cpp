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

int D[maxn],Q[maxn],ST,ED;
ui dp[maxn],s_[maxn],d_[maxn],ans;//s:start
vector<pair<int,char> > edge[maxn];
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int u,v;
		char c[3];
		scanf("%d%d%s",&u,&v,c);
		edge[u].push_back(make_pair(v,c[0]));
		D[v]++;
	} ST=0; ED=-1;
	FOR(i,1,n) if (!D[i]) Q[++ED]=i;
	while (ST<=ED){
		int x=Q[ST++];
		// printf("x=%d : %d %d\n",x,dp[x],s_[x]);
		for (auto now:edge[x]){
			D[now.first]--;
			if (!D[now.first]) Q[++ED]=now.first; 
			if ('a'<=now.second&&now.second<='z') dp[now.first]+=dp[x];
			if ('A'<=now.second&&now.second<='Z') dp[now.first]+=s_[x]+1;
			if (now.second=='.') ans+=dp[x],d_[now.first]+=dp[x];
			if (now.second=='_') {
				dp[now.first]+=dp[x]; s_[now.first]+=s_[x]+1;
				d_[now.first]+=d_[x]; ans+=d_[x];
			}
		}
	}printf("%u\n",ans);
}
/*
*/
