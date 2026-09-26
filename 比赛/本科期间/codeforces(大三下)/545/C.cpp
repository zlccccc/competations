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
const LL maxn=1e5+107;
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

//自己不可能向自己连DAG, 否则一定成环
int d;
char str[maxn][52];
vector<int> edge[maxn];//first;
int dfn[maxn][52],low[maxn][52],tot;
bool vis[maxn][52];
int id[maxn][52],cnt;//more
int val[maxn*52];//getans
int havex[maxn];
pii S[maxn*52]; int top;
vector<int> noww;
int mor=0,nowans=0,X,Y,_Y;
void tarjan(int x,int y) {
	low[x][y]=dfn[x][y]=++tot;
	S[++top]=make_pair(x,y); vis[x][y]=1;
	for (int v:edge[x]) {
		int _y=(y+1)%d;
		if (!dfn[v][_y]) {
			tarjan(v,_y);
			low[x][y]=min(low[x][y],low[v][_y]);
		} else if (vis[v][_y])
			low[x][y]=min(low[x][y],dfn[v][_y]);
	} if (low[x][y]==dfn[x][y]) {
		cnt++; noww.clear(); mor=nowans=0;
		while (1) {
			pii now=S[top--];
			X=now.first,Y=now.second,_Y=(Y+1)%d;
			for (int V:edge[X])
				mor=max(mor,val[id[V][_Y]]);//nxt
			//todo:getans_this
			if (str[X][Y]=='1') {
				nowans+=1-havex[X]; havex[X]=1;
				noww.push_back(X);//this
			} vis[X][Y]=0; id[X][Y]=cnt;
			// printf("(%d,%d) ",X,Y);
			if (X==x&&Y==y) break;
		} for (int X:noww) havex[X]=0;
		// printf("=%d+%d\n",nowans,mor);
		val[cnt]=nowans+mor;
	}
	// printf("tarjan:(%d,%d) : %d %d\n",x,y,low[x][y],dfn[x][y]);
}
#define OPENSTACK
int main() {
#ifdef OPENSTACK
	int size = 256 << 20; // 256MB
	char *p = (char*)malloc(size) + size;
#if (defined _WIN64) or (defined __unix)
	__asm__("movq %0, %%rsp\n" :: "r"(p));
#else
	__asm__("movl %0, %%esp\n" :: "r"(p));
#endif
#endif
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
	int n,m;
	int i;
	scanf("%d%d%d",&n,&m,&d);
	FOR(i,1,m) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
	} FOR(i,1,n) scanf("%s",str[i]);
	tarjan(1,0);
	printf("%d\n",val[id[1][0]]);
	exit(0);
}
/*
4 5 50
3 1
1 2
2 4
4 1
2 3
011
110
111
001
*/