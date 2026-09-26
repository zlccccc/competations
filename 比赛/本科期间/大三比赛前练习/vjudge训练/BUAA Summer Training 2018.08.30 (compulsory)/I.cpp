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
const LL maxn=2e5+7;
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

vector<pair<int,int> > edge[maxn];
int fa[maxn][17],val[maxn][17],dep[maxn];
void dfs(int x,int father,int depth){
	int i;
	dep[x]=depth; fa[x][0]=father;
	rep(i,1,17) fa[x][i]=fa[fa[x][i-1]][i-1];
	rep(i,1,17) val[x][i]=max(val[x][i-1],val[fa[x][i-1]][i-1]);
	// REP(i,20) printf("val[%d][%d]=%d\n",x,i,val[x][i]);
	for (auto now:edge[x]) if (now.first!=father){
		val[now.first][0]=now.second;
		dfs(now.first,x,depth+1);
	}
}
int getans(int x,int y){
	int i; int ret=0;
	if (dep[x]<dep[y]) swap(x,y);;
	rREP(i,17) if (dep[x]-dep[y]>=1<<i) {
		max_(ret,val[x][i]);x=fa[x][i];
	} if (x==y) return ret;
	rREP(i,17) if (fa[x][i]!=fa[y][i]){
		max_(ret,val[x][i]);x=fa[x][i];
		max_(ret,val[y][i]);y=fa[y][i];
	} max_(ret,val[x][0]); max_(ret,val[y][0]);
	return ret;
}
struct node{
	int x,y,w;
}A[maxn];
int Fa[maxn];
inline int getfa(int x){
	if (Fa[x]==x) return x;
	return Fa[x]=getfa(Fa[x]);
}
map<pair<int,int>,int> MP;
int main() {
	int i;FOR(i,1,200000) Fa[i]=i;
	while(~scanf("%d%d",&n,&m)){
		int i;
		FOR(i,1,m) {
			scanf("%d%d%d",&A[i].x,&A[i].y,&A[i].w);
			MP[make_pair(A[i].x,A[i].y)]=A[i].w;
		}
		sort(A+1,A+1+m,[](node x,node y){
			return x.w<y.w;
		});
		int all=0;
		FOR(i,1,m){
			int x=getfa(A[i].x),y=getfa(A[i].y);
			if (x==y) continue; all+=A[i].w; Fa[x]=y;
			// printf(" addedge : %d-%d : %d\n",A[i].x,A[i].y,A[i].w);
			edge[A[i].x].push_back(make_pair(A[i].y,A[i].w));
			edge[A[i].y].push_back(make_pair(A[i].x,A[i].w));
		} dfs(1,0,0);
		// printf("all=%lld\n",all);
		scanf("%d",&q);
		while (q--){
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%d\n",MP[make_pair(x,y)]+all-getans(x,y));
		}
		FOR(i,1,n) edge[i].clear(),Fa[i]=i; MP.clear();
	}
}
/*
*/
