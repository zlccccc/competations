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

#define DEBUG1
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
const LL maxn=5e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void wt2(T x,int k=64) {ll i; rREP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

int SIZE;
struct node {
	int u,v,id,o;
	node() {};
	node(int _u,int _v,int _id=0):u(_u),v(_v),id(_id) {};
} to[maxn],re[maxn],queries[maxn];
int BID[maxn],L[maxn];
bool cmpu(node A,node B) {
	if (A.u!=B.u) return A.u<B.u;
	if (A.v!=B.v) return A.v>B.v;//为了避免漏掉
	return A.id>B.id;
} bool cmpv(node A,node B) {
	if (A.v!=B.v) return A.v<B.v;
	if (A.u!=B.u) return A.u<B.u;
	return A.id<B.id;
} bool cmpQ(node A,node B) {
	if (A.o!=B.o) return A.o<B.o;
	if (A.v!=B.v) return A.v<B.v;
	if (A.u!=B.u) return A.u<B.u;
	return A.id<B.id;
}
int fa[maxn];
inline int getfa(int x) {
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int FA[maxn],SZ[maxn],PID[maxn];
inline int getFA(int x) {
	if (FA[x]==x) return x;
	return FA[x]=getFA(FA[x]);
}
inline void update(int u,int pid) {
	if (PID[u]!=pid) {
		int f=getfa(u);
		if (PID[f]!=pid) {
			FA[f]=f;
			PID[f]=pid;
		} PID[u]=pid; FA[u]=f;
	}
} int tot=0;
int now;
int Ans[maxn];
int TaskA() {
	int n,m,q,i,j,k;
	scanf("%d%*d%d",&n,&m); q=1e5;
	if (q==0) SIZE=m; else SIZE=m/sqrt(q)*2;
	if (!SIZE) SIZE++;
	FOR(i,0,(m+1)/SIZE) L[i]=0;
	FOR(i,1,m+1) {BID[i]=i/SIZE; if (!L[i/SIZE]) L[i/SIZE]=i;}
	FOR(i,1,m) {
		int u,v;
		scanf("%d%d",&u,&v);
		if (u>v) swap(u,v);
		to[i]=node(u,v);
		re[i]=node(u,v);
	} sort(to+1,to+m+1,cmpv);
	sort(re+1,re+m+1,cmpu);
	FOR(i,1,m) {
		to[i].o=BID[lower_bound(re+1,re+1+m,to[i],cmpu)-re];
		re[i].o=BID[i];
	}
	scanf("%d",&q);
	FOR(i,1,q) {
		int u,v;
		scanf("%d%d",&u,&v);
		if (u>v) swap(u,v);
		queries[i]=node(u,v,i);
		queries[i].o=BID[lower_bound(re+1,re+1+m,queries[i],cmpu)-re];
	} sort(queries+1,queries+q+1,cmpQ);
	FOR(i,1,q) {
		if (i==1||queries[i].o!=queries[i-1].o) { //initialize
			FOR(j,1,n) fa[j]=j;
			j=1; now=0;
		}
		for (; j<=m&&to[j].v<=queries[i].v; j++) {
			if (to[j].o>queries[i].o) {//sorted by l
				node &e=to[j];
				int x=getfa(e.u),y=getfa(e.v);
				if (x==y) continue;
				fa[x]=y; now--;
			}
		}
		int ans=now; tot++;
		for (k=L[queries[i].o]; BID[k]==queries[i].o; k++) {
			if (queries[i].u<=re[k].u&&re[k].v<=queries[i].v) {
				node &e=re[k];
				update(e.u,tot); update(e.v,tot);
				int x=getFA(e.u),y=getFA(e.v);
				if (x==y) continue;
				FA[x]=y; ans--;
			}
		}
		Ans[queries[i].id]=ans+queries[i].v-queries[i].u+1;
	}
	FOR(i,1,q) printf("%d\n",Ans[i]);
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
