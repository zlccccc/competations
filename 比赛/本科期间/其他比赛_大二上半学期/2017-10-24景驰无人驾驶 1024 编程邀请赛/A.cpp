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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int n,d;
	node(){}
	node(int a,int b):n(a),d(b){}
	bool operator<(const node&a)const{
		if (d==a.d) return n<a.n;
		return d>a.d;//注意!!! 否则为未优化的bellmanford 
	}
};
vector<node> edge[maxn];
int dis[maxn];
int n,m1;
void dij(int s){
	int i;
	FOR(i,1,100*52) dis[i]=INF;
	dis[s]=0;
	priority_queue<node> Q;
	Q.push(node(s,dis[s]));
	while (!Q.empty()){
		node x=Q.top();Q.pop();
		REP(i,edge[x.n].size()){
			node y=edge[x.n][i];
			if (dis[y.n]>x.d+y.d){
				dis[y.n]=x.d+y.d;
				Q.push(node(y.n,dis[y.n]));
			}
		}
	}
}
void solve(){
	int i,j;
	int m2;int L;
	scanf("%d%d%d%d",&n,&m1,&m2,&L);
	FOR(i,1,100*52) edge[i].clear();
	REP(i,m1){
		int u,v;
		scanf("%d%d",&u,&v);
		FOR(j,0,50){
			edge[u+j*100].push_back(node(v+j*100+100,1));
			edge[v+j*100].push_back(node(u+j*100+100,1));
		}
	}
	REP(i,m2){
		int u,v;int len;
		scanf("%d%d%d",&u,&v,&len);
		FOR(j,0,50){
			edge[u+j*100].push_back(node(v+j*100,len));
			edge[v+j*100].push_back(node(u+j*100,len));
		}
	}
	dij(1);
	int ans=INF;
//	FOR(i,1,(m1+1)*n) printf("%d ",dis[i]);puts("");
//	FOR(i,0,m1) printf("cal:%d %d\n",i,dis[n*i+n]);
	FOR(i,0,50) if (dis[100*i+n]<=L) ans=min(ans,dis[100*i+n]-i);
	if (ans<=L) printf("%d\n",ans);
	else puts("-1");
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
6
4 0 2 6
1 4 5
3 4 4
4 2 2 5
1 2
2 3
1 4 5
3 4 4
4 2 2 4
1 2
2 3
1 4 5
3 4 4
*/
