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
int in[maxn],out[maxn],dep[maxn],tot;
vector<int> D[maxn];
void dfs(int x,int fa,int dep){
	in[x]=++tot,::dep[x]=dep;
	D[dep].push_back(x); 
	for (int v:edge[x]) if (v!=fa)
		dfs(v,x,dep+1);
	out[x]=tot;
}
vector<pair<pair<int,int>,int> > X[maxn];
ll sum[maxn];
inline int lowbit(int x){return x&-x;}
void add(int x,int val){
	// printf("add : %d %d\n",x,val);
	for (;x<=n;x+=lowbit(x)) sum[x]+=val;
}
void add(int l,int r,int val){
	add(l,val); add(r+1,-val);
}
ll query(int x){
	ll ret=0;
	for (;x;x-=lowbit(x)) ret+=sum[x];
	// printf("query : %d %lld\n",x,ret);
	return ret;
} ll ans[maxn];
int main() {
	int i;
	scanf("%d",&n);
	FOR(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs(1,0,0);
	scanf("%d",&m);
	while (m--){
		int u,d,x;
		scanf("%d%d%d",&u,&d,&x);
		X[dep[u]].push_back(make_pair(make_pair(in[u],out[u]),x));
		if (dep[u]+d+1<=n) X[dep[u]+d+1].push_back(make_pair(make_pair(in[u],out[u]),-x));
	} FOR(i,0,n){
		for (auto now:X[i]) add(now.first.first,now.first.second,now.second);
		for (int x:D[i]) ans[x]=query(in[x]);
	} FOR(i,1,n) printf("%lld ",ans[i]);
}
/*
3 3 0
1 2 1
3 2 1
1 3 3

*/
