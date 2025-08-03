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
const LL maxn=1<<20|7;
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

vector<int> edge[maxn],actual[maxn];
int dfn[maxn],low[maxn],belong[maxn];
bool vis[maxn];
int tot,cnt;
int S[maxn],top;
void dfs(int x) {
	dfn[x]=low[x]=++tot;
	S[++top]=x;
	vis[x]=1;
	for (int v:edge[x]) {
		if (!dfn[v]) {
			dfs(v);
			low[x]=min(low[x],low[v]);
		} else if (vis[v])
			low[x]=min(low[x],dfn[v]);
	}
	if (dfn[x]==low[x]) {
		cnt++;
		while (1) {
			int now=S[top--];
			vis[now]=0;
			belong[now]=cnt;
			if (now==x) break;
		}
	}
}
void init(int n) {
	int i;
	FOR(i,1,n) edge[i].clear(),actual[i].clear();
}
int D[maxn],col[maxn],C[maxn];
int solve(int n) {
	int i;
	tot=cnt=0;
	FOR(i,1,n) dfn[i]=D[i]=C[i]=0;
	FOR(i,1,n) if (!dfn[i]) dfs(i);
	FOR(i,1,n) C[belong[i]]=col[i];
	FOR(i,1,n) if (C[belong[i]]!=col[i]) return 1;//no!
	// FOR(i,1,n) printf("%d ",belong[i]); puts(" <- belong");
	// FOR(i,1,cnt) printf("%d ",C[i]); puts(" <- C");
	FOR(i,1,n) {
		for (int v:edge[i]) if (belong[i]!=belong[v]) {
				actual[belong[v]].push_back(belong[i]);
				D[belong[i]]++;
			}
	} queue<int> Q;
	FOR(i,1,cnt) if (D[i]==0) Q.push(i);
	while (Q.size()) {
		int x=Q.front(); Q.pop();
		// printf("bfs: %d: %d\n",x,C[x]);
		// for (int v:actual[x]) printf(" v=%d(%d) ",v,C[v]); puts("");
		for (int v:actual[x]) if (C[v]&&!C[x]) return 1;//得到错误
		for (int v:actual[x]) if (C[v]) C[x]=0;
		for (int v:actual[x]) {D[v]--; if (!D[v]) Q.push(v);}
	} int ans=0;
	FOR(i,1,cnt) if (C[i]) ans++;
	if (ans>1) return 1;
	return 0;//yes
}
int main() {
	int T; T=1;
	scanf("%d",&T);
	while (T--) {
		int n,m,i;
		scanf("%d%d",&n,&m);
		init(n);
		FOR(i,1,n) scanf("%d",&col[i]);
		FOR(i,1,m) {
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
		} if (solve(n)) puts("yinyinyin");
		else puts("hahaha");
	}
}
/*
*/