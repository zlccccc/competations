#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
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
const LL MOD=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%MOD) ret=1ll*ret*a%MOD;return ret;}

#define next nxt
int n,m,s,t;
int i,j,k;
struct node{
	int to,id;
	LL len;
	node(int t=0,LL l=0,int i=0):to(t),len(l),id(i){}
	bool operator<(const node &a)const{
		return len>a.len;
	}
};
vector<node> edge[maxn];
int u[maxn],v[maxn];
LL len1[maxn],len2[maxn],len[maxn];//len1:s->,len2:->t
bool mark[maxn];
LL fa[maxn];
void dij(int s,LL dis[]){
	int i;
	FOR(i,1,n) dis[i]=INFF;
	dis[s]=0;
	priority_queue<node> Q;
	Q.push(node(s,dis[s]));
	while (!Q.empty()){
		node x=Q.top();Q.pop();
		REP(i,edge[x.to].size()){
			node y=edge[x.to][i];
			if (dis[y.to]>x.len+y.len){
				dis[y.to]=x.len+y.len;
				Q.push(node(y.to,dis[y.to],y.id));
			}
		}
	}
}
int low[maxn],dfn[maxn],tot;
bool vis[maxn];
void tarjin(int x,int ii){
	low[x]=dfn[x]=++tot;vis[x]=1;
	int i;
	REP(i,edge[x].size()){
		int v=edge[x][i].to;
		if (!dfn[v]){
			tarjin(v,edge[x][i].id);
			low[x]=min(low[x],low[v]);
			if (low[v]>dfn[x]) mark[edge[x][i].id]=1;
		}
		else if (edge[x][i].id!=ii) low[x]=min(low[x],dfn[v]);
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	REP(i,m) scanf("%d%d%I64d",&u[i],&v[i],&len[i]);
	REP(i,m) edge[u[i]].push_back(node(v[i],len[i],i));
	dij(s,len1);
	FOR(i,1,n) edge[i].clear();
	REP(i,m) edge[v[i]].push_back(node(u[i],len[i],i));
	dij(t,len2);
	FOR(i,1,n) edge[i].clear();
	REP(i,m) if (len1[u[i]]+len2[v[i]]+len[i]==len1[t]){
		edge[u[i]].push_back(node(v[i],0,i));
		edge[v[i]].push_back(node(u[i],0,i));
	}
	tarjin(s,-1);
//	FOR(i,1,n) printf("%d ",dfn[i]);puts("");
//	FOR(i,1,n) printf("%d ",low[i]);puts("");
//	REP(i,m) printf("%d ",mark[i]);puts("");
//	FOR(i,1,n) printf("%I64d ",len1[i]);puts("");
//	FOR(i,1,n) printf("%I64d ",len2[i]);puts("");
	REP(i,m){
		LL uvlen=len1[u[i]]+len2[v[i]];
		if (uvlen+len[i]==len1[t]){
			if (mark[i]) puts("YES");
			else if (len[i]>1) puts("CAN 1");
			else puts("NO");
			continue;
		}
//		printf("%d %d\n",uvlen,len1[t]);
		if (uvlen+1>=len1[t]) {puts("NO");continue;}
		printf("CAN %I64d\n",uvlen+len[i]-len1[t]+1);
	}
}
/*
*/
