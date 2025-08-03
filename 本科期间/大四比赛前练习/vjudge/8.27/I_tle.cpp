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

namespace maxflow {
	typedef int type;
	const type INF=0x3f3f3f3f;
	struct node {
		int to; type cap; int next;
		node(int t=0,type c=0,int n=0):to(t),cap(c),next(n) {};
	} edge[maxn*50];
	int head[maxn],tot;
	void addedge(int from,int to,type cap,type rcap=0) {
		edge[tot]=node(to,cap,head[from]); head[from]=tot++;
		edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
	}
	void rollback() {
		int from=edge[tot-1].to,to=edge[tot-2].to;
		head[to]=edge[tot-1].next; head[from]=edge[tot-2].next;
		tot-=2;
	}
	int dep[maxn],cur[maxn];//当前弧优化
	bool bfs(int s,int t,int n) {
		static int Q[maxn],ST,ED;
		memset(dep+1,0,n*sizeof(int));
		ST=0; ED=-1;
		Q[++ED]=s; dep[s]=1;
		while (ST<=ED) {
			int u=Q[ST++];
			for (int i=head[u]; i!=-1; i=edge[i].next) {
				int v=edge[i].to;
				if (!dep[v]&&edge[i].cap) {
					Q[++ED]=v; dep[v]=dep[u]+1;
				}
			}
		} return (dep[t]!=0);
	}
	type dfs(int x,const int &t,type flow=INF) {
		if (x==t||flow==0) return flow;
		type ret=0;
		for (int i=cur[x]; i!=-1; i=edge[i].next) {
			if (dep[x]+1==dep[edge[i].to]&&edge[i].cap) {
				type f=dfs(edge[i].to,t,min(flow,edge[i].cap));
				edge[i].cap-=f; edge[i^1].cap+=f;
				ret+=f; flow-=f; cur[x]=i;
				if (flow==0) break;
			}
		} if (!ret) dep[x]=0;
		return ret;
	}
	type maxflow(int s,int t,int n) {
		type ret=0;
		while (bfs(s,t,n)) {
			type f;
			memcpy(cur+1,head+1,n*sizeof(int));
			while ((f=dfs(s,t))>0) ret+=f;
		} return ret;
	}
	void init(int n) {
		memset(head+1,0xff,n*sizeof(int)); tot=0;
	}
}
int n,m;
inline int getid(int x,int y) {
	return (x-1)*m+y;
}
int ini[107][107],Ans[107][107];
char str[107][107];
// bool mark[107*107];
// void dfs(int x) {
// 	printf("dfs: %d (%d %d)\n",x,(x-1)/m+1,(x-1)%m+1);
// 	Ans[(x-1)/m+1][(x-1)%m+1]^=1; mark[x]=1;
// 	for (int i=maxflow::head[x]; ~i; i=maxflow::edge[i].next) {
// 		if (!maxflow::edge[i].cap) continue;
// 		int v=maxflow::edge[i].to;
// 		if (!mark[v]) dfs(v);
// 	}
// }
int S,T;
// void printNowValue(int n,int m) {
// 	int i,j;
// 	FOR(i,1,n) {
// 		FOR(j,1,m) printf("%d",ini[i][j]); puts("");
// 	} puts("<- ini");
// 	FOR(i,1,n) {
// 		FOR(j,1,m) printf("%c",str[i][j]); puts("");
// 	} puts("<- str");
// 	FOR(i,1,n) FOR(j,1,m) Ans[i][j]=ini[i][j];
// 	FOR(i,1,T) mark[i]=0; dfs(S);
// 	FOR(i,1,n) {
// 		FOR(j,1,m) printf("%c","BW"[Ans[i][j]==0]); puts("");
// 	} puts("<- ans"); system("pause");
// }
int solve(int n,int m,int a,int b) {
	S=n*m+1,T=n*m+2;
	maxflow::init(T);
	int value=0,i,j;
	FOR(i,1,n) FOR(j,1,m) ini[i][j]=0;
	FOR(i,1,n) FOR(j,1,m) {
		if (i+a<=n&&j+b<=m) {
			maxflow::addedge(getid(i,j),getid(i+a,j+b),1,1);
			value++; ini[i+a][j+b]=ini[i][j]^1;
		}
		if (i+a<=n&&1<=j-b) {
			maxflow::addedge(getid(i,j),getid(i+a,j-b),1,1);
			value++; ini[i+a][j-b]=ini[i][j]^1;
		}
		int base=-1;
		if (str[i][j]=='B') base=0;
		if (str[i][j]=='W') base=1;
		if (base!=-1) {
			base^=ini[i][j];
			if (!base) maxflow::addedge(S,getid(i,j),INF);
			else maxflow::addedge(getid(i,j),T,INF);
		}
	}
	value-=maxflow::maxflow(S,T,T);

	// getnowval
	// printf("CHANGE: %d\n",value);
	// printNowValue(n,m);
	// exit(0);
	return value;
}
int main() {
	int _caseT,_; _caseT=1;
	scanf("%d",&_caseT);
	FOR(_,1,_caseT) {
		int i,j,a,b;
		scanf("%d%d%d%d",&n,&m,&a,&b);
		FOR(i,1,n) scanf("%s",str[i]+1);
		int value=solve(n,m,a,b);
		FOR(i,1,n) FOR(j,1,m) {
			if (str[i][j]!='.') continue;
			int base=-1; base=0;//str[i][j]=0
			if (base!=-1) {
				base^=ini[i][j];
				if (!base) maxflow::addedge(S,getid(i,j),INF);
				else maxflow::addedge(getid(i,j),T,INF);
			} int more=maxflow::bfs(S,T,T);
			// printf("(%d,%d):more=%d\n",i,j,more);
			// printNowValue(n,m);
			// return 0*puts("err");}
			if (more) {
				// printf("change: (%d,%d)\n",i,j);
				str[i][j]='W';//back
				maxflow::rollback();
				int base=-1; base=1;//str[i][j]=0
				if (base!=-1) {
					base^=ini[i][j];
					if (!base) maxflow::addedge(S,getid(i,j),INF);
					else maxflow::addedge(getid(i,j),T,INF);
				}
			} else str[i][j]='B';
		}
		printf("%d\n",value);
		FOR(i,1,n) {
			FOR(j,1,m) printf("%c",str[i][j]); puts("");
		}
	}
}
/*
3
2 2 1 1
..
..
2 2 1 1
.W
.B
2 2 1 1
WW
.W

100
3 3 1 1
W..
...
...
100
3 3 1 1
B..
...
...

edges_first:
1->5 : 1 0
5->1 : 1 0
1->11 : 1061109567 0
2->6 : 1 0
6->2 : 1 0
2->4 : 1 0
4->2 : 1 0
10->2 : 1061109567 0
3->5 : 1 0
5->3 : 1 0
10->3 : 1061109567 0
4->8 : 1 0
8->4 : 1 0
5->9 : 1 0
9->5 : 1 0
5->7 : 1 0
7->5 : 1 0
6->8 : 1 0
8->6 : 1 0


1->5 : 1 0
5->1 : 1 0
1->11 : 1061109567 0
2->6 : 1 0
6->2 : 1 0
2->4 : 1 0
4->2 : 1 0
3->5 : 1 0
5->3 : 1 0
4->8 : 1 0
8->4 : 1 0
5->9 : 1 0
9->5 : 1 0
5->7 : 1 0
7->5 : 1 0
6->8 : 1 0
8->6 : 1 0
*/