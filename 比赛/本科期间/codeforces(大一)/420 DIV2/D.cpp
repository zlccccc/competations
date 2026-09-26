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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

struct node{
	int n,d;
	node(){};
	node(int a,int b):n(a),d(b){};
	bool operator<(const node &a)const{
		if (d==a.d) return n<a.n;
		return d>a.d;
	}
};
vector<node> edge[maxn];//cell+n+m
int dis[maxn];
void dij(int s){
	int i;
	memset(dis,0x3f,sizeof(dis));
	priority_queue<node> Q;
	dis[s]=0;
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
int n,m,k;
int i,j;
int s,t;
int u,v;
map<pair<int,int>,int> H;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	FOR(i,1,k){
		int x,y;
		scanf("%d%d",&x,&y);
		u=i;
		if (H.count(make_pair(x+1,y))){
			v=H[make_pair(x+1,y)];
			edge[u].push_back(node(v,0));
			edge[v].push_back(node(u,0));
		}
		if (H.count(make_pair(x-1,y))){
			v=H[make_pair(x-1,y)];
			edge[u].push_back(node(v,0));
			edge[v].push_back(node(u,0));
		}
		if (H.count(make_pair(x,y+1))){
			v=H[make_pair(x,y+1)];
			edge[u].push_back(node(v,0));
			edge[v].push_back(node(u,0));
		}
		if (H.count(make_pair(x,y-1))){
			v=H[make_pair(x,y-1)];
			edge[u].push_back(node(v,0));
			edge[v].push_back(node(u,0));
		}
		H[make_pair(x,y)]=i;
		edge[u].push_back(node(x+10002,1));
		edge[u].push_back(node(x+10002+1,1));
		edge[u].push_back(node(x+10002+2,1));
		edge[x+10002].push_back(node(u,0));
		edge[x+10002+1].push_back(node(u,0));
		edge[x+10002+2].push_back(node(u,0));
		edge[u].push_back(node(y+20004,1));
		edge[u].push_back(node(y+20004+1,1));
		edge[u].push_back(node(y+20004+2,1));
		edge[y+20004].push_back(node(u,0));
		edge[y+20004+1].push_back(node(u,0));
		edge[y+20004+2].push_back(node(u,0));
		if (x==1&&y==1) s=i;
		if (x==n&&y==m) t=i;
	}
	if (t==0){
		edge[n+10002+1].push_back(node(0,0));
		edge[m+20004+1].push_back(node(0,0));
	}
	dij(s);
	if (dis[t]!=INF) printf("%d",dis[t]);
	else puts("-1");
}
