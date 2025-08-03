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
const LL maxn=1e7+107;
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
template<typename T>inline T powMM(T a, T b, ll Mod=M) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%Mod)
		if (b&1) ret=(LL)ret*a%Mod;
	return ret;
}
int n,m,q;
// char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int A[4],tot;
pii com[7];
int used[7][17][17][17][17];
void dfs(int way){
	if (used[way][A[0]][A[1]][A[2]][A[3]]>1) return;
	used[way][A[0]][A[1]][A[2]][A[3]]++;
	// if (way==6&&A[0]==6&&A[1]==6) 
		// printf("%d : %d %d %d %d\n",way,A[0],A[1],A[2],A[3]);
	if (way==6) return;
	A[com[way].first]+=3;
	dfs(way+1);
	A[com[way].first]-=3;
	A[com[way].second]+=3;
	dfs(way+1);
	A[com[way].second]-=3;
	A[com[way].first]+=1;
	A[com[way].second]+=1;
	dfs(way+1);
	A[com[way].first]-=1;
	A[com[way].second]-=1;
}
void init(){
	int i,j;
	REP(i,4) rep(j,i+1,4) com[tot++]=make_pair(i,j);
	dfs(0);
}
int main() {
	// int i; FOR(i,1,100) if (powMM(2,i,7)==1) printf("%d ",i);
	int T,_; T=1; init();
	scanf("%d",&T);
	FOR(_,1,T){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if (max(max(a,b),max(c,d))>10) printf("Case #%d: Wrong Scoreboard\n",_);
		else {
			if (used[6][a][b][c][d]==1) printf("Case #%d: Yes\n",_);
			if (used[6][a][b][c][d]>1) printf("Case #%d: No\n",_);
			if (used[6][a][b][c][d]==0) printf("Case #%d: Wrong Scoreboard\n",_);
		}
	}
}
/*
4 1
5
*/
