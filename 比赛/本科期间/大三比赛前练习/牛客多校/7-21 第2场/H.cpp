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
const LL maxn=5e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void multi(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod(T &A,ll B=M) {A%=M;}
template<typename T>inline void maxi(T &A,T B) {(A<B)&&(A=B);}
template<typename T>inline void mini(T &A,T B) {(A>B)&&(A=B);}
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

int A[maxn];
vector<int> edge[maxn];
ll f[maxn][8][2],lef[maxn][8][2],now[8][2],nxt[8][2],actual[8][2];// pos,used,have_down
void dfs(int x,int fa){
	memset(f[x],0,sizeof(f[x]));
	memset(lef[x],0,sizeof(lef[x]));
	for (int v:edge[x]) if (v!=fa) dfs(v,x);
	int i,j;
	f[x][0][1]=A[x]; f[x][1][0]=A[x];
	memset(now,0,sizeof(now));
	memset(nxt,0,sizeof(nxt));
	for (int v:edge[x]) if (v!=fa){
		REP(i,4) REP(j,2) maxi(lef[v][i][j],nxt[i][j]);
		rREP(i,4) rREP(j,4){//left!
			maxi(nxt[i+j][0],f[v][i][0]+now[j][0]);
			maxi(nxt[i+j][1],f[v][i][0]+now[j][0]);
			maxi(nxt[i+j][1],f[v][i][1]+now[j][0]);
			maxi(nxt[i+j][1],f[v][i][0]+now[j][1]);
		}REP(i,4) maxi(nxt[i][1],nxt[i][0]);
		REP(i,4) maxi(nxt[i+1][0],nxt[i][1]);
		REP(i,4) maxi(nxt[i+1][1],nxt[i][1]);
		REP(i,4) REP(j,2) maxi(now[i][j],nxt[i][j]);
	}reverse(edge[x].begin(), edge[x].end());
	memset(now,0,sizeof(now));
	memset(nxt,0,sizeof(nxt));
	for (int v:edge[x]) if (v!=fa){
		memset(actual,0,sizeof(actual));
		rREP(i,4) rREP(j,4){//left!
			maxi(actual[i+j][0],lef[v][i][0]+now[j][0]);
			maxi(actual[i+j][1],lef[v][i][0]+now[j][0]);
			maxi(actual[i+j][1],lef[v][i][1]+now[j][0]);
			maxi(actual[i+j][1],lef[v][i][0]+now[j][1]);
		}REP(i,4) maxi(actual[i][1],actual[i][0]);
		REP(i,4) maxi(actual[i+1][0],actual[i][1]);
		REP(i,4) maxi(actual[i+1][1],actual[i][1]);

		REP(i,4) REP(j,4){
			maxi(f[x][i+j][0],f[v][i][0]+actual[j][0]);//都不用
			maxi(f[x][i+j+1][0],f[v][i][1]+actual[j][1]+A[x]);//link
			maxi(f[x][i+j+1][0],f[v][i][0]+actual[j][1]+A[x]);//link			
			maxi(f[x][i+j+1][0],f[v][i][1]+actual[j][0]+A[x]);//link
			maxi(f[x][i+j][1],f[v][i][1]+actual[j][0]+A[x]);//down
			maxi(f[x][i+j][1],f[v][i][0]+actual[j][1]+A[x]);//down
		}
		rREP(i,4) rREP(j,4){//right!
			maxi(nxt[i+j][0],f[v][i][0]+now[j][0]);
			maxi(nxt[i+j][1],f[v][i][0]+now[j][0]);
			maxi(nxt[i+j][1],f[v][i][1]+now[j][0]);
			maxi(nxt[i+j][1],f[v][i][0]+now[j][1]);
		}REP(i,4) maxi(nxt[i][1],nxt[i][0]);
		REP(i,4) maxi(nxt[i+1][0],nxt[i][1]);
		REP(i,4) maxi(nxt[i+1][1],nxt[i][1]);
		REP(i,4) REP(j,2) maxi(now[i][j],nxt[i][j]);
	}REP(i,4) maxi(f[x][i][1],f[x][i][0]);
	REP(i,4) maxi(f[x][i+1][0],f[x][i][1]);
	REP(i,4) maxi(f[x][i+1][1],f[x][i][1]);
	// printf("%d\n",x);
	// REP(i,4) printf("%lld %lld\n",f[x][i][0],f[x][i][1]);
}
int TaskA() {
	int i;
	// scanf("%d",&n);
	FOR(i,1,n) edge[i].clear();
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs(1,0);
	ll ans=0; maxi(ans,f[1][3][0]);
	REP(i,3) maxi(ans,f[1][i][0]),maxi(ans,f[1][i][1]);
	printf("%lld\n",ans);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_more_n();
}
/*
3
3 2 1
1 2
1 3
6
1 2 3 4 5 6
1 2
2 3
2 5
2 4
2 6
6
1 2 3 4 5 6
1 2
1 3
1 4
1 5
1 6
6
1 1 1 1 1 1
1 2
1 3
1 4
1 5
1 6
13
10 10 10 10 10 1 10 10 10 1 10 10 10
1 2
2 3
3 4
4 5
2 6
6 7
7 8
7 9
6 10
10 11
11 12
11 13
8
1 2 3 4 5 6 7 8
1 2
2 3
3 4
4 5
5 6
6 7
1 8

10
1 1 1 1 1 1 100 100 100 100
1 2
2 3
3 4
4 5
5 6
7 5
8 5
9 6
10 6
*/