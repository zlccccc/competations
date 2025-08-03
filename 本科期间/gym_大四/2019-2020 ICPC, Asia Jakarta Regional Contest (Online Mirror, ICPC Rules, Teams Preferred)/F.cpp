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

vector<int> edge[maxn];
int weight[maxn],sz[maxn];
bool mark[maxn];
void dfs1(int x,int fa,int n) {
	weight[x]=0; sz[x]=1;
	for (int v:edge[x]) {
		if (v==fa||mark[v]) continue;
		dfs1(v,x,n); sz[x]+=sz[v];
		weight[x]=max(weight[x],sz[v]);
	} weight[x]=max(weight[x],n-sz[x]);
}//get_root
int n;
vector<int> roots;
void get_root(int x){
	int i;
	FOR(i,1,n) weight[i]=INF; dfs1(x,0,0);//get_sz[x]
	dfs1(x,0,sz[x]);
	// puts("dfs1:done");
	int minweight=INF; roots.clear();
	FOR(i,1,n) minweight=min(minweight,weight[i]);
	FOR(i,1,n) if (weight[i]==minweight) roots.push_back(i);
	// FOR(i,1,n) printf("%d ",weight[i]); puts("<- weight");
	// // puts("dfs2:done");
	// printf("get_root: %d\n",x);
	// for (auto now:roots) printf("%d " ,now); puts("<- now");
}
string get_str(int x,int fa) {
	vector<string> strings;
	for (int v:edge[x]) {
		if (v==fa||mark[v]) continue;
		strings.push_back("("+get_str(v,x)+")");
	} string ret="";
	sort(strings.begin(), strings.end());
	for (auto now:strings) ret+=now;
	return ret;
}
int main() {
	int i;
	scanf("%d",&n);
	FOR(i,1,n-1) {
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} get_root(1);
	int r=roots[0];
	mark[r]=1;
	if (edge[r].size()<=1) return 0*puts("-1");
	string minimize="";
	int ans=0;
	for (auto x:edge[r]) {
		get_root(x);
		string now="";
		for (auto y:roots) {
			string s=get_str(y,0);
			if (now==""||now>s) now=s;
		} if (minimize=="") minimize=now;
		if (minimize!=now) return 0*puts("-1");
		else ans++;
	} printf("%d\n",ans);
}
/*
13
1 5
1 7
2 4
2 8
2 11
3 12
4 7
4 12
6 11
7 13
9 10
9 12

16
1 2
2 3
2 4
1 13
1 14
3 12
3 9
4 5
13 15
14 16
9 10
10 11
5 6
6 7
7 8

*/