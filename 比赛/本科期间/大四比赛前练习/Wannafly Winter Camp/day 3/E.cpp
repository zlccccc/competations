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
const LL maxn=2e5+107;
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
char str[maxn];//倒着的

// 可选可不选比一定要选最多大1!
// 所以只需要dp出每个点为根的时候的答案
// 然后每个点加上个1, 再dp一次
// 甚至可以贪心? 
vector<int> edge[maxn];
int initans;
int cnt[maxn],fa[maxn];//cnt: 下方为0的个数
void dfs(int x,int f){
	fa[x]=f;
	for (int v:edge[x]) if (v!=f){
		dfs(v,x);
		if (!cnt[v]) cnt[x]++;
	}
	if (!cnt[x]) initans++;//must choose,底下都没选
	// printf("dfs: %d %d\n",x,cnt[x]);
}
void dfs2(int x){
	//上方因为这个选了,这个不该选
	if (x!=1&&!cnt[x]&&cnt[fa[x]]==1) cnt[x]++;
	if (x!=1&&cnt[fa[x]]==0) cnt[x]++;
	for (int v:edge[x]) if (v!=fa[x]) dfs2(v);
}
int main() {
	scanf("%d%d",&n,&m);
	int i;
	FOR(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs(1,0);
	// FOR(i,1,n) printf("%d ",cnt[i]);puts("");
	dfs2(1);
	// FOR(i,1,n) printf("%d ",cnt[i]);puts("");
	int notc=cnt[1];
	ll ans=initans;//link
	printf("%lld\n",ans);
	FOR(i,1,m){
		int x;
		scanf("%d",&x);
		if (!notc) ans=ans*n%M,notc=1;
		else ans=(ans*n+initans)%M,notc=cnt[x];
		printf("%lld\n",ans);
	}
}
/*
5 100
1 2
2 3
3 4
4 5
1
2

4 100
1 2
2 3
3 4
*/