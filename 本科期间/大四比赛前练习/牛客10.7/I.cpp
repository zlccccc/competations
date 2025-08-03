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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int all[maxn],sub[maxn];
int nowans=0;
int ans[maxn];
void add(int x,int val) {
	nowans-=(sub[x]&&sub[x]!=all[x]);
	sub[x]+=val;
	nowans+=(sub[x]&&sub[x]!=all[x]);
}
int sz[maxn];
pii son[maxn];
vector<pii> edge[maxn];
vector<int> colors[maxn];//sons:color
void dfs1(int x,int fa) {
	sz[x]=1; son[x]=make_pair(0,0); 
	vector<int>().swap(colors[x]);
	for (auto e:edge[x]) {
		int v=e.first;
		if (v!=fa) {
			dfs1(v,x); sz[x]+=sz[v];
			if (sz[v]>sz[son[x].first]) son[x]=e;
		}
	}
}
int c[maxn];
void dfs2(int x,int fa) {
	for (auto e:edge[x]) {
		int v=e.first,id=e.second;
		if (v!=fa&&v!=son[x].first) {
			dfs2(v,x); ans[id]=nowans;
			for (int c:colors[v]) add(c,-1);
		}//removeit
	} if (son[x].first) {
		int v=son[x].first,id=son[x].second;
		dfs2(v,x); ans[id]=nowans;
		colors[x].swap(colors[v]);
	} add(c[x],1); colors[x].push_back(c[x]);
	for (auto e:edge[x]) {
		int v=e.first;
		if (v!=fa&&v!=son[x].first) {
			for (int c:colors[v]) {
				add(c,1); colors[x].push_back(c);
			} vector<int>().swap(colors[v]);
		}//removeit
	}
}
int main() {
	int n;
	while (~scanf("%d",&n)) {
		int i; nowans=0;
		FOR(i,1,n) {
			all[i]=sub[i]=0;
			ans[i]=0;
			vector<int>().swap(colors[i]);
			vector<pii>().swap(edge[i]);
		}
		FOR(i,1,n) {
			scanf("%d",&c[i]);
			all[c[i]]++;
		}
		FOR(i,1,n-1) {
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(make_pair(v,i));
			edge[v].push_back(make_pair(u,i));
		} dfs1(1,0);
		// puts("???");
		dfs2(1,0);
		FOR(i,1,n-1) printf("%d\n",ans[i]);
	}
}
/*
4
1 2 2  1
1 2
1 3
3 4
*/