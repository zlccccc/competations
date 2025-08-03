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

vector<int> edge[maxn];
vector<int> nodes[maxn];
int cnt;
int dfn[maxn],low[maxn],tot;
bool vis[maxn];//instack
int S[maxn],top;
int id[maxn];
void tarjan(int x) {
	low[x]=dfn[x]=++tot;
	S[++top]=x;
	vis[x]=1;
	for (int v:edge[x]) {
		if (!dfn[v]) {
			tarjan(v);
			low[x]=min(low[x],low[v]);
		} else if (vis[v])
			low[x]=min(low[x],dfn[v]);
	}
	if (low[x]==dfn[x]) {
		cnt++;
		while (1) {
			int now=S[top--];
			vis[now]=0; id[now]=cnt;
			nodes[cnt].push_back(now);
			if (now==x) break;
		}
	}
}
int inval[maxn];
int maxval[maxn];
bool used[maxn];
void dfs(int x,int dep){
	used[x]=1; max_(maxval[x],dep);
	for (int v:edge[x]) if (id[x]==id[v]&&!used[v]) {
		dfs(v,dep+1);
	} used[x]=0;
}
int d[maxn];
queue<int> Q;
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
	} FOR(i,1,n) if (!dfn[i]) tarjan(i);
	FOR(i,1,n) inval[i]=1;
	FOR(i,1,n){
		for (int v:edge[i]) if (id[i]!=id[v]) d[id[v]]++;
	} FOR(i,1,cnt) if (d[i]==0) Q.push(i);

	// FOR(i,1,cnt) printf("%d ",d[i]); puts("");
	// FOR(i,1,n) printf("%d ",id[i]); puts("");
	// printf("cnt=%d\n",cnt);

	while (Q.size()){
		int y=Q.front(); Q.pop();
		// printf("y=%d\n",y);
		// for (int x:nodes[y]) printf("%d ",x);puts(" <- nodes");
		for (int x:nodes[y]) dfs(x,inval[x]);
		for (int x:nodes[y]){
			for (int v:edge[x]) if (id[v]!=id[x]){
				d[id[v]]--;
				// printf("%d ",d[id[v]]);
				if (!d[id[v]]) Q.push(id[v]);
				max_(inval[v],maxval[x]+1);
			}
		}
	} int ans=0;
	// FOR(i,1,n) assert(maxval[i]!=0);
	// FOR(i,1,n) printf("%d ",maxval[i]);
	FOR(i,1,n) max_(ans,maxval[i]);
	printf("%d\n",ans);
}
/*
*/
