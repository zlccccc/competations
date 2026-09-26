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
const LL maxn=1e4+7;
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

struct Edge {
	int to,next;
	Edge(int _to=0,int _next=-1):to(_to),next(_next) {};
} edge[maxn*2];
int head[maxn],etot;
inline void addedge(int u,int v) {
	edge[++etot]=Edge(v,head[u]); head[u]=etot;
}
vector<int> nodes[maxn];
int cnt;
int dfn[maxn],low[maxn],tot;
bool vis[maxn];//instack
int S[maxn],top;
void tarjan(int x,int fa) {
	low[x]=dfn[x]=++tot;
	S[++top]=x;
	vis[x]=1;
	for (int i=head[x]; ~i; i=edge[i].next) {
		int v=edge[i].to;
		if (v==fa) continue;
		if (!dfn[v]) {
			tarjan(v,x);
			low[x]=min(low[x],low[v]);
		} else if (vis[v])
			low[x]=min(low[x],dfn[v]);
	}
	if (low[x]==dfn[x]) {
		cnt++;
		while (1) {
			int now=S[top--];
			vis[now]=0;
			nodes[cnt].push_back(now);
			if (now==x) break;
		}
	}
}
int u[maxn],v[maxn];
int d[maxn],h[maxn];
int fa[maxn],c[maxn];
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int iid[maxn];
int main() {
	int i,j,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,m) scanf("%d%d",&u[i],&v[i]);
	FOR(i,1,n) head[i]=-1,dfn[i]=0;
	FOR(i,1,m) addedge(u[i],v[i]),addedge(v[i],u[i]);
	FOR(i,1,n) if (!dfn[i]) tarjan(i,0);
	int ans=0;
	FOR(i,1,n) fa[i]=i,c[i]=1;
	FOR(i,1,m) {
		int x=getfa(u[i]),y=getfa(v[i]);
		if (x!=y) fa[x]=y,c[y]+=c[x];
	} FOR(i,1,n) if (fa[i]==i) ans+=c[i]*(c[i]-1)/2;
	FOR(i,1,cnt) {
		for (int v:nodes[i]) iid[v]=i;
		ans+=nodes[i].size()*(nodes[i].size()-1)/2;
		nodes[i].clear();
	}
	srand(time(0));
	FOR(k,1,m) if (iid[u[k]]==iid[v[k]]){
		FOR(i,1,n) head[i]=-1,dfn[i]=0; etot=tot=cnt=0;
		FOR(i,1,m) if (i!=k) addedge(u[i],v[i]),addedge(v[i],u[i]);
		FOR(i,1,n) if (!dfn[i]) tarjan(i,0);
		FOR(i,1,cnt){
			int rd=rand()<<15|rand();
			for (int v:nodes[i]) h[v]^=rd;
			nodes[i].clear();
		}
	}
	FOR(i,1,n) FOR(j,i+1,n) if (iid[i]==iid[j]&&h[i]==h[j]) ans++;
	printf("%d\n",ans);
}
/*


8 8
1 2
1 3
2 3
1 6
3 4
4 5
5 6
4 6
*/