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
#include <bitset>
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
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int to,cap,next;
	node(int t=0,int c=0,int n=0):to(t),cap(c),next(n){}
}edge[1007*1007];
int head[1007];
int tot;
void addedge(int from,int to,int cap,int rcap=0){
//	printf("%d->%d,%d\n",from,to,cap);
	edge[tot].to=to;edge[tot].next=head[from];edge[tot].cap=cap;head[from]=tot++;
	edge[tot].to=from;edge[tot].next=head[to];edge[tot].cap=rcap;head[to]=tot++;
}
queue<int> Q;
int gap[1007],dep[1007],cur[1007];
void bfs(int s,int t){
	memset(dep,0xff,sizeof(dep));
	memset(gap,0,sizeof(gap));
	gap[0]=1;
	dep[t]=0;
	Q.push(t);
	while (Q.size()){
		int u=Q.front();Q.pop();
		for(int i=head[u];i!=-1;i=edge[i].next){
			int v=edge[i].to;
			if (dep[v]!=-1) continue;
			Q.push(v);
			dep[v]=dep[u]+1;
			gap[dep[v]]++; 
		}
	}
}
int S[1007];
int sap(int s,int t,int n){
	bfs(s,t);
	memcpy(cur,head,sizeof(head));
	int top=0,u=s,ret=0;
	while (dep[s]<n){
		if (u==t){
			int MIN=INF,inser,i;
			REP(i,top) if (MIN>edge[S[i]].cap) MIN=edge[S[i]].cap,inser=i;
			REP(i,top) edge[S[i]].cap-=MIN,edge[S[i]^1].cap+=MIN;
			ret+=MIN;
			top=inser;
			u=edge[S[top]^1].to;
			continue;
		}
		bool flag=0;
		int v;
		for (int i=cur[u];i!=-1;i=edge[i].next){
			v=edge[i].to;
			if (edge[i].cap&&dep[v]+1==dep[u]){
				flag=1;
				cur[u]=i;
				break;
			}
		}
		if (flag){
			S[top++]=cur[u];
			u=v;
			continue;
		}
		int MIN=n;
		for (int i=head[u];i!=-1;i=edge[i].next){
			v=edge[i].to;
			if (edge[i].cap&&dep[v]<MIN) MIN=min(MIN,dep[v]),cur[u]=i;
		}
		gap[dep[u]]--;
		if (!gap[dep[u]]) return ret;
		dep[u]=MIN+1;
		gap[dep[u]]++;
		if (u!=s) u=edge[S[--top]^1].to;
	}
	return ret;
}
int n,m;
int E[1007][1007];
int S_i[1007],i_T[1007];
int u,v,s,t;
int ans;
int main(){
	scanf("%d%d",&n,&m);
	int i,j;
	memset(head,-1,sizeof(head));
	FOR(i,1,n) FOR(j,1,n) E[i][j]=0;
	s=n+1;t=n+2;
	FOR(i,1,m){
		scanf("%d%d",&u,&v);
		E[u][v]=E[v][u]=1;
	}
	FOR(i,1,n) FOR(j,i+1,n){//这里是把图压缩了 
		ans+=j-i;
		addedge(i,j,j-i);
		if (E[i][j]==0) S_i[i]+=j-i;
		else i_T[j]+=j-i;
	}
	FOR(i,1,n) addedge(s,i,S_i[i]);
	FOR(i,1,n) addedge(i,t,i_T[i]);
	printf("%d\n",ans-sap(s,t,n+m+2)); 
}
/*
*/
