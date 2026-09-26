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
const LL maxn=1e6+107;
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

bool used[maxn];
vector<pii> edge[maxn];
int d[maxn],id[maxn];
vector<pair<int,pii> > P;
void add(int u,int x,int v) {
	// printf("add: %d-%d-%d\n",u,x,v);
	P.push_back(make_pair(u,make_pair(x,v)));
}
int dfs(int x,int fa) {
	// printf("dfs: %d %d\n",x,fa);
	int now=0;
	for (;id[x]<(int)edge[x].size();id[x]++) {
		if (used[edge[x][id[x]].second]) continue;
		int v=edge[x][id[x]].first;
		used[edge[x][id[x]].second]=1;
		v=dfs(v,x); d[v]--; d[x]--;
		if (v) {
			if (now) add(now,x,v),now=0;
			else now=v;
		}
		// printf("  link %d-%d: now=%d\n",x,v,now);
	} if (!now) return x;
	else {if (fa) add(now,x,fa); return 0;}
}
int main(){
	int n,m,i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(make_pair(v,i));
		edge[v].push_back(make_pair(u,i));
		d[u]++; d[v]++;
	} FOR(i,1,n) if (d[i]) dfs(i,0);
	printf("%d\n",(int)P.size());
	for (auto now:P) printf("%d %d %d\n",now.first,now.second.first,now.second.second);
}