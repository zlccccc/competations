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
const LL maxn=3e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,ll B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b,ll MOD=M) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%MOD)
		if (b&1) ret=(LL)ret*a%MOD;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

struct node{
	int x,y,len;
	node(int _x=0,int _y=0,int _len=0):x(_x),y(_y),len(_len){};
}e[maxn*2]; int tot;
inline int getid(int x,int y){
	return (x-1)*m+y;
} int Fa[maxn],fa[maxn][20];
inline int getFa(int x){
	if (Fa[x]==x) return x;
	return Fa[x]=getFa(Fa[x]);
} int dep[maxn];
inline int lca(int x,int y){
	int i;
	if (dep[x]<dep[y]) swap(x,y);
	rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
	if (x==y) return x;
	rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
} vector<int> edge[maxn];
void dfs(int x,int father){
	fa[x][0]=father;
	int i; dep[x]=dep[fa[x][0]]+1;
	rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int v:edge[x]) if (v!=father) dfs(v,x);
}
int main() {
	scanf("%d%d",&n,&m);
	int i,j;
	FOR(i,1,n) FOR(j,1,m){
		int val;
		scanf("%s%d",str,&val);
		if (str[0]=='D') e[tot++]=node(getid(i,j),getid(i+1,j),val);
		scanf("%s%d",str,&val);
		if (str[0]=='R') e[tot++]=node(getid(i,j),getid(i,j+1),val);
	} sort(e,e+tot,[](node A,node B){
		return A.len>B.len;
	}); FOR(i,1,n*m) Fa[i]=i;
	REP(i,tot){
		int x=getFa(e[i].x),y=getFa(e[i].y);
		if (x==y) continue; Fa[x]=y;
		edge[e[i].x].push_back(e[i].y);
		edge[e[i].y].push_back(e[i].x);
		// printf("%d-%d: %d\n",e[i].x,e[i].y,e[i].len);
	} dfs(1,0);
	scanf("%d",&q);
	while(q--){
		int x,y,a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		x=getid(a,b); y=getid(c,d);
		// printf("%d %d :  %d %d  %d\n",x,y,dep[x],dep[y],lca(x,y));
		printf("%d\n",dep[x]+dep[y]-2*dep[lca(x,y)]);
	}
}
/*
*/
