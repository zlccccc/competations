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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
inline void add(int &A,int B) {A+=B; (A>=M) &&(A-=M);}
inline void mul(ll &A,ll B) {(A*=B)%=M;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m;
char S[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",S)) TaskA();}

int Q[maxn],D[maxn],ST,ED;
int fa[maxn+20];
int dp[maxn][12];
void add_up(int x){
	int i,j; if (!fa[x]) return;
	rFOR(i,1,10) if (dp[fa[x]][i])
		FOR(j,1,10-i)
			add(dp[fa[x]][i+j],(ll)dp[x][j]*dp[fa[x]][i]%M);
}
void del_up(int x){
	int i,j; if (!fa[x]) return;
	FOR(i,1,10) if (dp[fa[x]][i])
		FOR(j,1,10-i)
			add(dp[fa[x]][i+j],M-(ll)dp[x][j]*dp[fa[x]][i]%M);
}
int TaskA() {
	int i; ST=0; ED=-1;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&dp[i][1]);
	FOR(i,2,n) scanf("%d",&fa[i]),D[fa[i]]++;
	FOR(i,1,n) if (!D[i]) Q[++ED]=i;
	while (ST<=ED){
		int x=Q[ST++]; D[fa[x]]--;
		if (!D[fa[x]]) Q[++ED]=fa[x];
		add_up(x);
		// printf("Q;%d\n",x);
	}
	while(m--){
		int op,x,y;
		scanf("%d%d%d",&op,&x,&y);
		if (op==0){
			REP(i,10) Q[i]=x,x=fa[x]; x=Q[0];
			rREP(i,10) del_up(Q[i]);
			y=(ll)y*powMM((ll)dp[x][1],M-2)%M;
			FOR(i,1,10) dp[x][i]=(ll)dp[x][i]*y%M;
			REP(i,10) add_up(Q[i]);
		} else if (op==1){
			REP(i,10) Q[i]=x,x=fa[x]; x=Q[0];
			rREP(i,10) del_up(Q[i]);
			rep(i,1,10) add_up(Q[i]);
			rep(i,1,10) Q[i]=y,y=fa[y]; y=Q[1];
			rrep(i,1,10) del_up(Q[i]);
			fa[x]=y;
			REP(i,10) add_up(Q[i]);
		} else if (op==2){
			REP(i,y) Q[i]=x,x=fa[x]; x=Q[0];
			rREP(i,y) memcpy(dp[n+i+1],dp[Q[i]],sizeof(dp[Q[i]]));
			REP(i,y-1) fa[i+1+n]=i+2+n; fa[n+y]=0;
			rREP(i,y) del_up(n+1+i);
			rep(i,1,y) fa[i+1+n]=i+n; fa[n+1]=0;
			rREP(i,y) add_up(n+1+i);
			printf("%d\n",dp[n+1][y]);
		}
	}
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
3 3
1 2 3
1 1
2 1 2
2 1 3
2 2 3
*/
