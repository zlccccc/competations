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
const LL maxn=5e4+7;
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
int sz[maxn],minweight,root;
bool mark[maxn];
void dfs1(int x,int fa,int n) {
	int weight=0; sz[x]=1;
	for (int v:edge[x]) {
		if (v==fa||mark[v]) continue;
		dfs1(v,x,n);
		sz[x]+=sz[v];
		weight=max(weight,sz[v]);
	} weight=max(weight,n-sz[x]);
	if (weight<minweight) root=x,minweight=weight;
}
int A[maxn],len;
ll V[maxn],T[maxn],an[maxn];
void dfs2(int x,int fa,int val) {
	val|=1<<(A[x]-1); T[val]++;
	for (int v:edge[x]) {
		if (v==fa||mark[v]) continue;
		dfs2(v,x,val);
	}
}
void fwt(ll *A,int len,int inv) {
	int i,j,k;
	for (i=2; i<=len; i<<=1) {
		for (j=0; j<len; j+=i) {
			for (k=j; k<j+i/2; k++) {
				int a=A[k],b=A[k+i/2];
				if (inv==1) A[k+i/2]=a+b;
				else A[k+i/2]=b-a;
			}
		}
	}
}
ll ans;//ans; i&j=i
void dfs3(int x) {
	mark[x]=1; int i;
	REP(i,len) V[i]=0;
	V[1<<(A[x]-1)]=1; if (len==2) ans++;
	// printf("dfs3: %d ans=%d\n",x,ans);
	fwt(V,len,1);
	for (int v:edge[x]) {
		if (mark[v]) continue;
		dfs2(v,x,1<<(A[x]-1)); fwt(T,len,1);
		REP(i,len) an[i]=V[i]*T[i],V[i]+=T[i],T[i]=0;
		fwt(an,len,-1); ans+=an[len-1]*2;
	}
	for (int v:edge[x]){
		if (mark[v]) continue;
		minweight=sz[v];
		dfs1(v,0,sz[v]); dfs3(root); 
	}
}
int main() {
	int k;
	while (~scanf("%d%d",&n,&k)) {
		len=1<<k; int i; ans=0;
		FOR(i,1,n) scanf("%d",&A[i]);
		FOR(i,1,n) edge[i].clear(),mark[i]=0;
		FOR(i,1,n-1) {
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		} minweight=n; dfs1(1,0,n);
		dfs3(root); printf("%lld\n",ans);
	}
}
/*
3 1
1 1 1
1 2
1 3
*/
