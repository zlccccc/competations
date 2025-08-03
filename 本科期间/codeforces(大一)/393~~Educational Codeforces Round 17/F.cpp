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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1000+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {int i; rREP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m;
char str[maxn];
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

struct tree{
	vector<int> edge[maxn];
	int subtree[maxn],fa[maxn],n;
	void read(){
		scanf("%d",&n);
		int i,u,v;
		FOR(i,1,n-1){
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
	}
	void dfs_fa(int x,int father){
		fa[x]=father;
		for (int v:edge[x]) if (v!=fa[x]) dfs_fa(v,x);
	}
	void dfs_subtree(int x,int fa){
		subtree[x]=0;
		for (int v:edge[x]) if (v!=fa)
			dfs_subtree(v,x),subtree[x]|=1<<(v-1);
		// pr2(subtree[x],n); printf(" <- %d; n=%d\n",x,n);
	}
}S,T;
int val[1007][1<<12|7];
int dfs(int x,int pos,int status){
	if (pos==(int)S.edge[x].size()) return !status;
	if (S.edge[x][pos]==S.fa[x]) return dfs(x,pos+1,status);
	int y=S.edge[x][pos];
	if (val[y][status]!=-1) return val[y][status];
	int &ret=val[y][status]; ret=0; int i;
	add_(ret,dfs(x,pos+1,status));
	REP(i,T.n) if ((status>>i)&1){
		add_(ret,(ll)dfs(x,pos+1,status^(1<<i))*dfs(y,0,T.subtree[i+1])%M);
	} return ret;
}
int TaskA() {
	S.read(); T.read();
	int i,j,ans=0,inv=0;
	S.dfs_fa(1,0);
	FOR(i,1,T.n){
		T.dfs_subtree(i,0);
		memset(val,0xff,sizeof(val));
		FOR(j,1,S.n) add_(ans,dfs(j,0,T.subtree[i]));
		// printf("%d : ans=%d\n",i,ans);
	} S=T;
	S.dfs_fa(1,0);
	FOR(i,1,T.n){
		T.dfs_subtree(i,0);
		memset(val,0xff,sizeof(val));
		FOR(j,1,S.n) add_(inv,dfs(j,0,T.subtree[i]));
	}
	// printf("%d %d\n",ans,inv);
	printf("%I64d\n",ans*powMM((ll)inv,M-2)%M);
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
*/
