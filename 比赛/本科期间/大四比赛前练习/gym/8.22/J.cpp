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

namespace mincostflow {
	typedef ll type;
	const type INF=0x3f3f3f3f3f3f3f3fll;
	struct node {
		int to; type cap,cost; int next;
		node(int t=0,type c=0,type _c=0,int n=0):
			to(t),cap(c),cost(_c),next(n) {};
	} edge[maxn*2]; int tot;
	int head[maxn];
	int addedge(int from,int to,type cap,type cost,type rcap=0) {
		// printf("%d->%d : %lld %lld %lld\n",from,to,cap,cost,rcap);
		edge[tot]=node(to,cap,cost,head[from]); head[from]=tot++;
		edge[tot]=node(from,rcap,-cost,head[to]); head[to]=tot++;
		return tot-2;
	}
	type dis[maxn];
	bool mark[maxn];
	void spfa(int s,int t,int n) {
		memset(dis+1,0x3f,n*sizeof(type));
		memset(mark+1,0,n*sizeof(bool));
		static int Q[maxn],ST,ED;
		dis[s]=0; ST=ED=0; Q[ED++]=s;
		while (ST!=ED) {
			int v=Q[ST]; mark[v]=0;
			if ((++ST)==maxn) ST=0;
			for (int i=head[v]; ~i; i=edge[i].next) {
				node &e=edge[i];
				if (e.cap>0&&dis[e.to]>dis[v]+e.cost) {
					dis[e.to]=dis[v]+e.cost;
					if (!mark[e.to]) {
						if (ST==ED||dis[Q[ST]]<=dis[e.to]) {
							Q[ED]=e.to,mark[e.to]=1;
							if ((++ED)==maxn) ED=0;
						} else {
							if ((--ST)<0) ST+=maxn;
							Q[ST]=e.to,mark[e.to]=1;
						}
					}
				}
			}
		}
	} int cur[maxn];
	type dfs(int x,int t,type flow) {
		if (x==t||!flow) return flow;
		type ret=0; mark[x]=1;
		for (int i=cur[x]; ~i; i=edge[i].next) if (!mark[edge[i].to]) {
				if (dis[x]+edge[i].cost==dis[edge[i].to]&&edge[i].cap) {
					int f=dfs(edge[i].to,t,min(flow,edge[i].cap));
					edge[i].cap-=f; edge[i^1].cap+=f;
					ret+=f; flow-=f; cur[x]=i;
					if (flow==0) break;
				}
			}
		mark[x]=0;
		return ret;
	}
	pair<type,type> mincostflow(int s,int t,int n,type flow=INF) {
		type ret=0,ans=0;
		while (flow) {
			spfa(s,t,n); if (dis[t]==INF) break;
			// 这样加当前弧优化会快, 我也不知道为啥
			memcpy(cur+1,head+1,n*sizeof(int));
			type len=dis[t],f;
			if ((f=dfs(s,t,flow))>0)//while也行
				ret+=f,ans+=len*f,flow-=f;
			// printf("%lld %lld %lld\n",ret,len,f);
		} return make_pair(ret,ans);
	}
	void init(int n) {
		memset(head+1,0xff,n*sizeof(int));
		tot=0;
	}
}

int mark[maxn];
int A[maxn];
int n,k,m;
inline int getidx(int x,int y) {
	return (x-1)*m*2+y*2-1;
}
inline int getidy(int x,int y) {
	return (x-1)*m*2+y*2;
}
int pid[107][107];
void dfs(int x,int id,int T) {//getans
	// printf("%d(%d) ",x,(x-1)%(m*2)+1);
	if (x==T) return;
	for (int y=mincostflow::head[x];y!=-1;y=mincostflow::edge[y].next) {
		if (!(y&1)){
			if (mincostflow::edge[y^1].cap) {
				mincostflow::edge[y^1].cap--;
				int nxt=mincostflow::edge[y].to;
				// printf("dfs_down: %d %lld\n",mincostflow::edge[y].to,mincostflow::edge[y^1].cap);
				if (x+1==nxt&&x<=n*m*2) {
					int o=(x-1)/(m*2)+1,p=((x-1)%(m*2)+1+1)/2;
					pid[o][p]=id;
					// printf("(%d %d) ",o,p);
				}
				dfs(nxt,id,T);
				break;
			}
		}
	}
}
int t[107];
int ids[107][107];
int choose[maxn];
int main() {
	int i,j;
	scanf("%d%d%d",&n,&k,&m);
	FOR(i,1,m) scanf("%d",&A[i]);
	int tmp=n*m*2+n+1,S=n*m*2+n+2,T=n*m*2+n+3;
	mincostflow::init(T);
	mincostflow::addedge(S,tmp,k,0);
	mincostflow::addedge(tmp,n*m*2+1,k,0);
	mincostflow::addedge(n*m*2+n,T,k,INF);
	FOR(j,1,m) mincostflow::addedge(tmp,getidx(1,j),1,0);
	ll ans=0;
	FOR(i,1,n) {
		scanf("%d",&t[i]);
		FOR(j,1,m) mark[j]=INF;
		FOR(j,1,t[i]) {
			scanf("%d",&ids[i][j]);
			mark[ids[i][j]]=0;
		} ans-=(ll)(k-t[i])*INF;
		// printf("%d\n",k-t);
		if (i!=1) {
			mincostflow::addedge(n*m*2+i-1,n*m*2+i,k,INF);//infinite
			FOR(j,1,m) mincostflow::addedge(getidy(i-1,j),n*m*2+i,1,0);
			FOR(j,1,m) mincostflow::addedge(getidy(i-1,j),getidx(i,j),1,0);
		}
		FOR(j,1,m) mincostflow::addedge(n*m*2+i,getidx(i,j),1,A[j]);
		FOR(j,1,m) mincostflow::addedge(getidx(i,j),getidy(i,j),1,mark[j]);
	}
	FOR(j,1,m) mincostflow::addedge(getidy(n,j),T,1,0);
	pair<ll,ll> now=mincostflow::mincostflow(S,T,T);
	// printf("ans=%lld %lld; %lld\n",now.first,now.second,now.second%INF);
	// printf("ans=%lld\n",ans);
	printf("%lld\n",now.second+ans);
	// printf("T=%d\n",T);
	FOR(i,1,k) {
		dfs(tmp,i,T);
		// puts("");
	}
	FOR(i,1,n) {
		FOR(j,1,t[i]) printf("%d%c",pid[i][ids[i][j]]," \n"[j==t[i]]);
	}
}
/*
1 4 6
3 5 4 6 10 1
2 1 2

2 4 6
3 5 4 6 10 1
2 1 2
3 3 4 5
3 2 4 6

6 2 3
1 10 100
1 1
2 2 3
2 1 2
2 1 3
1 3
1 1
*/