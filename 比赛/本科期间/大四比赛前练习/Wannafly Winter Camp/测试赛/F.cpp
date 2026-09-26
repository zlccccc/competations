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
// char str[maxn];

int A[maxn];//first
struct Edge{
	int w,u,v;
}edge[maxn];
vector<int> nodes[maxn];
int fa[maxn],val[maxn];//base
inline int getfa(int x){
	if (fa[x]==x) return x;
	int y=getfa(fa[x]);
	if (fa[x]!=y) val[x]^=val[fa[x]];
	return fa[x]=y;
}
int nxt[maxn*100][2],tot;
void ins(int p,int val){
	int i;
	// printf("ins:%d %d\n",p,val);
	rREP(i,20) {
		int c=(val>>i)&1;
		if (!nxt[p][c]) nxt[p][c]=++tot;
		p=nxt[p][c];
	}
}
int que(int p,int val){
	int ans=0,i;
	// printf("queue:%d %d\n",p,val);
	rREP(i,20) {
		int c=(val>>i)&1;
		if (nxt[p][!c]) {
			ans^=1<<i; p=nxt[p][!c];
		} else p=nxt[p][c];
	} 
	return ans;
}
int main() {
	int i;
	scanf("%d",&n);
	FOR(i,1,n-1) scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
	sort(edge+1,edge+n,[](Edge x,Edge y){return x.w<y.w;});
	FOR(i,1,n) fa[i]=i,nodes[i].push_back(i); tot=n;
	FOR(i,1,n) ins(i,0);
	FOR(i,1,n-1){
		int ans=0;
		int x=getfa(edge[i].u),y=getfa(edge[i].v);
		int w=edge[i].w^val[edge[i].u]^val[edge[i].v];//top_value
		assert(x!=y);//must
		if (nodes[x].size()>nodes[y].size()) swap(x,y);
		for (int v:nodes[x]) {
			getfa(v); ans=max(ans,que(y,w^val[v]));
			// printf("merge: %d->%d : %d; que=%d\n",v,y,w^val[v],que(y,w^val[v]));
			nodes[y].push_back(v);
		} for (int v:nodes[x]) ins(y,w^val[v]);
		fa[x]=y; val[x]=w;
		printf("%d%c",ans," \n"[i==n-1]);
	}
}
/*
*/
