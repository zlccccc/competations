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
const LL maxn=1e4+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

//return:flow:actual
namespace maxflow {
	typedef LL type;
	const type INF = 0x3f3f3f3f3f3f3f3f;
	struct node {
		int to; type cap; int next;
		node (int t = 0, type c = 0, int n = 0) : to(t), cap(c), next(n) {};
	} edge[maxn * 50];

	int head[maxn], tot;
	int addedge(int from, int to, type cap, type rcap = 0) {
		// printf("%d -> %d: %d\n",from,to,cap); // TODO
		edge[tot] = node(to, cap, head[from]); head[from] = tot++;
		edge[tot] = node(from, rcap, head[to]); head[to] = tot++;
		return tot-1;//reverse
	}
	int gap[maxn], dep[maxn], cur[maxn];
	void bfs(int s, int t, int n) {
		static int Q[maxn], ST, ED;
		memset(dep + 1, 0xff, n * sizeof(int));
		memset(gap + 1, 0, n * sizeof(int));
		gap[0] = 1; dep[t] = 0;
		ST = 0; ED = -1; Q[++ED] = t;
		while (ST <= ED) {
			int u = Q[ST++];
			for (int i = head[u]; ~i; i = edge[i].next) {
				int v = edge[i].to;
				if (dep[v] != -1) continue;
				Q[++ED] = v; dep[v] = dep[u] + 1;
				gap[dep[v]]++;
			}
		}
	}
	int S[maxn];
	type sap(int s, int t, int n) {
		bfs(s, t, n);
		memcpy(cur + 1, head + 1, n * sizeof(int));
		int top = 0, u = s; type ret = 0;
		while (dep[s] < n) {
			if (u == t) {
				type MIN = INF, inser = 0, i;
				REP(i, top) if (MIN > edge[S[i]].cap)
					MIN = edge[S[i]].cap, inser = i;
				REP(i, top) {
					edge[S[i]].cap -= MIN, edge[S[i] ^ 1].cap += MIN;
				} ret += MIN; top = inser; u = edge[S[top] ^ 1].to;
				continue;
			} bool flag = 0; int v;
			for (int i = cur[u]; ~i; i = edge[i].next) {
				v = edge[i].to;
				if (edge[i].cap && dep[v] + 1 == dep[u]) {
					flag = 1; cur[u] = i; break;
				}
			} if (flag) {
				S[top++] = cur[u]; u = v; continue;
			} int MIN = n;
			for (int i = head[u]; ~i; i = edge[i].next) {
				v = edge[i].to;
				if (edge[i].cap && dep[v] < MIN)
					MIN = min(MIN, dep[v]), cur[u] = i;
			} gap[dep[u]]--;
			if (ret > INF) return ret;
			if (!gap[dep[u]]) return ret;
			dep[u] = MIN + 1; gap[dep[u]]++;
			if (u != s) u = edge[S[--top] ^ 1].to;
		} return ret;
	}
	void init(int n) {
		memset(head + 1, 0xff, n * sizeof(int)); tot = 0;
	}
}

int n,k,T,all=0;
int A[maxn];
vector<int> cir,edge[maxn];
map<int,int> cirnum[maxn];
int vis[maxn],cfa[maxn],circnt[maxn],dep[maxn];
int in[maxn],out[maxn],dtot,ctot;
void dfs(int x,int depth,int cir_id) {
	// printf("dfs: %d\n",x);
	maxflow::addedge(x,T,1); all++;
    vis[x]=1; in[x]=++dtot; cfa[x]=cir_id; dep[x]=depth;
    for (int v:edge[x]) dfs(v,depth+1,cir_id);
    out[x]=dtot;
}
void solve(int x) {
	cir.clear(); ctot++;
	while (A[x]&&!vis[A[x]]) x=A[x],vis[x]=1;
	while (A[x]&&vis[A[x]]==1) {
		vis[A[x]]=2; cir.push_back(x);
		cfa[x]=ctot; x=A[x];
	} int i; circnt[ctot]=cir.size();
	rREP(i,cir.size()-1) dep[cir[i]]=dep[A[cir[i]]]+1;
	// printf("cir\n");
	// for (int v:cir) printf("%d ",v); puts("");
	for (int v:cir) {
		for (int y:edge[v]) if (vis[y]!=2) dfs(y,1,v);
	}
	for (int v:cir) maxflow::addedge(v,x+n+k,1);
	maxflow::addedge(x+n+k,T,cir.size()-1);
	all+=cir.size()-1;
}
vector<int> V;
inline int getid(int x) {
	return lower_bound(V.begin(),V.end(),x)-V.begin()+1;
}
int t[maxn];
vector<int> worker[maxn];

vector<int> mat_edge[maxn],mans[maxn];//k_material
int ans[maxn][2];
int main() {
	int i;
	scanf("%d%d",&n,&k);
	maxflow::init(n+k+n+2);
	// n_roads; k_material; n_circle; S,T;
	int S=n+k+n+1; T=n+k+n+2; 
	FOR(i,1,n) {
		int c; scanf("%d",&A[i]);
		edge[A[i]].push_back(i);
		scanf("%d",&c);
		while (c--) {
			int t; scanf("%d",&t);
			worker[i].push_back(t);
		}
	} FOR(i,1,k) {
		scanf("%d",&t[i]);
		V.push_back(t[i]);
	} V.push_back(INF);
	sort(V.begin(), V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	FOR(i,1,k) mans[getid(t[i])].push_back(i);
	FOR(i,1,k) maxflow::addedge(S,i+n,mans[i].size());//S to material
	FOR(i,1,n) {//matrerial to edges
		for (int v:worker[i]) {
			int id=getid(v); if (V[id-1]!=v) continue;
			// printf("id=%d\n",id);
			mat_edge[id].push_back(maxflow::addedge(id+n,i,1));
		}
	}// edges to T
	FOR(i,1,n) if (!vis[i]) solve(i);//circle
	int ALL=maxflow::sap(S,T,T);
	if (ALL!=n-1) return 0*puts("-1");
	FOR(i,1,k) {
		vector<int> noww;
		for (int now:mat_edge[i]) if (maxflow::edge[now].cap) {
			noww.push_back(maxflow::edge[now^1].to);
			// printf(" %d -> %d flow:%lld\n",i,maxflow::edge[now^1].to,maxflow::edge[now].cap);
		} int o;
		REP(o,(int)noww.size()) {
			ans[mans[i][o]][0]=noww[o];
			ans[mans[i][o]][1]=A[noww[o]];
		}
	}
	FOR(i,1,k) printf("%d %d\n",ans[i][0],ans[i][1]);
}
/*
3 5
2 2 1 2
3 2 2 3
1 2 3 4
1 2 3 4 5
*/
