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

vector<int> edge[maxn];
bool mark[maxn];
void dfs2(int x,int more) {
	if (mark[x]) return;
	mark[x]=1;
	if (!more) return;
	for (int v:edge[x]) dfs2(v,more-1);
}
int id[maxn];
int dep[maxn],father[maxn],root;
int n;
int check(int mid) {
	int ret=0,i;
	FOR(i,1,n) mark[i]=0;
	// FOR(i,1,n) printf("%d ",id[i]);puts("");
	FOR(i,1,n) if (!mark[id[i]]) {
		ret++; int x=id[i];
		for (int o=0;father[x]&&o<mid;o++) x=father[x];
		// printf("choose : %d(fa[%d],[%d])\n",x,id[i],mid);
		dfs2(x,mid);
	}
	return ret;
}
void dfs(int x,int fa) {
	dep[x]=dep[fa]+1; father[x]=fa;//down
	for (int v:edge[x]) if (v!=fa) dfs(v,x);
}
int main() {
	int k,i;
	scanf("%d%d",&n,&k);
	FOR(i,1,n-1) {
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} FOR(i,1,n) if (edge[i].size()==1) root=i;
	dfs(root,0);
	FOR(i,1,n) id[i]=i;
	sort(id+1,id+1+n,[](int i,int j){
		return dep[i]>dep[j];
	});
	int l=0,r=n+1;
	while (l+1<r){
		int mid=(l+r)/2;
		// printf("l,r=%d %d; mid=%d;\n",l,r,mid);
		if (check(mid)<=k) r=mid;//count
		else l=mid;
	} printf("%d\n",r);
}
/*
6 1
1 2
2 3
2 4
1 5
5 6

7 2
1 2
2 3
3 4
4 5
5 6
6 7
*/