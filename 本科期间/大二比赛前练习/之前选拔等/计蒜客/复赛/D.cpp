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
#define rep(I,pos,N) for (I=pos;I<N;I++)
#define rrep(I,pos,N) for (I=N-1;I>=pos;I--)
#define FOR(I,pos,N) for (I=pos;I<=N;I++)
#define rFOR(I,pos,N) for (I=N;I>=pos;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

struct node{
	LL n,d;
	node(){}
	node(LL nn,LL dd):n(nn),d(dd){}
	bool operator<(const node&a)const{
		if (d==a.d) return n<a.n;
		return d>a.d;//注意!!! 否则为未优化的bellmanford 
	}
};
vector<node> edge[maxn];
LL dis[maxn],n,m;
void dij(LL s){
	LL i;
	FOR(i,1,60000) dis[i]=INFF;
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
LL i,j,k;
LL s,t;
LL u,v,len;
int main(){
	scanf("%lld%lld",&n,&m);
	//n+1~n+m=城市群 
	FOR(i,1,m){
		scanf("%lld",&t);
//		edge[i+20000].push_back(node(i+40000,0));//拆点 
		REP(j,t){
			scanf("%lld",&u);
			edge[u].push_back(node(i+20000,0));
			edge[i+40000].push_back(node(u,0));
		}
	}
	scanf("%lld",&m);
	FOR(i,1,m){
		scanf("%lld%lld%lld",&u,&v,&len);
		edge[u].push_back(node(v,len));
		edge[v].push_back(node(u,len));
	}
	scanf("%lld",&m);
	FOR(i,1,m){
		scanf("%lld%lld%lld",&u,&v,&len);
		edge[u+20000].push_back(node(v+40000,len));
		edge[v+20000].push_back(node(u+40000,len));
	}
	scanf("%lld%lld",&s,&t);
	dij(s);
	if (dis[t]!=INFF) printf("%lld",dis[t]);
	else printf("-1");
}
/*
*/
