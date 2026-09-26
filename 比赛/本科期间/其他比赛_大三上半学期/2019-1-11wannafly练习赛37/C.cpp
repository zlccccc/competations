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
const LL maxn=4e7+107;
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
// char str[maxn];

int A[21][21];
int nxt[maxn][2],tot;
int root[21][21];
int ans;
void ins(int &rt,int value){
	int i; if (!rt) rt=++tot;
	int now=rt;
	rREP(i,31){
		int c=(value>>i)&1;
		if (!nxt[now][c]) nxt[now][c]=++tot;
		// printf("ins:%d(%d %d)\n",now,nxt[now][0],nxt[now][1]);
		now=nxt[now][c];
	}
}
void que(int now,int value){
	int i,nowans=0;
	if (!now) return;
	// printf("que: %d %d; nowans=%d\n",now,value,nowans);
	rREP(i,31){
		// printf("now=%d(%d %d) ",now,nxt[now][0],nxt[now][1]);
		int c=(value>>i)&1;
		if (nxt[now][!c]) {
			nowans|=1<<i;
			now=nxt[now][!c];
		} else now=nxt[now][c];
	} ans=max(ans,nowans);
}
void dfs(int x,int y,int value){
	if (x+y==n+1) ins(root[x][y],value);
	if (x+y>=n+1) return;
	if (x<n) dfs(x+1,y,value^A[x+1][y]);
	if (y<n) dfs(x,y+1,value^A[x][y+1]);
}
void redfs(int x,int y,int value){
	// printf("redfs: %d %d %d; n=%d\n",x,y,value,n);
	if (x+y==n+1) que(root[x][y],value^A[x][y]);
	if (x+y<=n+1) return;
	if (x>1) redfs(x-1,y,value^A[x-1][y]);
	if (y>1) redfs(x,y-1,value^A[x][y-1]);
}
int main() {
	int i,j,e;
	scanf("%d%d",&n,&e);
	FOR(i,1,n) FOR(j,1,n) scanf("%d",&A[i][j]);
	dfs(1,1,e^A[1][1]);
	redfs(n,n,A[n][n]);
	printf("%d\n",ans);
}
/*
1 1
2
*/