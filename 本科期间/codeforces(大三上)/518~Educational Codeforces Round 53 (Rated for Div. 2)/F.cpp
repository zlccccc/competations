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
queue<int> Q;
int root;
int dep[maxn],d[maxn],id[maxn];
vector<pair<int,int> > v[maxn]; int l[maxn];
void dfs(int x,int fa) {
	dep[x]=dep[fa]+1;
	for (int v:edge[x]) if (v!=fa&&d[v]) dfs(v,x);
	if (make_pair(dep[x],l[x])>make_pair(dep[root],l[root])) root=x;
}
int main() {
	scanf("%d",&n); int i;
	FOR(i,1,n-1) {
		int u,v; scanf("%d%d",&u,&v);
		d[u]++; d[v]++;
		edge[u].push_back(v);
		edge[v].push_back(u);
	} FOR(i,1,n) if (d[i]==1) Q.push(i);
	FOR(i,1,n) id[i]=i;
	while (Q.size()) {
		int x=Q.front(); Q.pop();
		for (int v:edge[x]) {
			if (d[v]<=2) d[v]--;
			else ::v[v].push_back(make_pair(l[x],id[x]));
			if (d[v]==1) Q.push(v),id[v]=id[x],l[v]=l[x]+1;
			// printf("v=%d\n",v);
		}
	} FOR(i,1,n) if (d[i]==1) d[i]=0;
	// FOR(i,1,n) printf("%d ",d[i]);
	FOR(i,1,n) if (d[i]&&v[i].size()>1) {
		sort(v[i].begin(), v[i].end());
		reverse(v[i].begin(), v[i].end());
		l[i]=v[i][0].first+v[i][1].first;
	}
	
	for (root=1; !d[root]; root++);
	dfs(root,0); dfs(root,0); int U=root;
	dfs(root,0); int V=root;
	// printf("%d %d\n",U,V);
	printf("%d %d\n",v[U][0].second,v[V][0].second);
	printf("%d %d\n",v[U][1].second,v[V][1].second);
}
/*
*/
