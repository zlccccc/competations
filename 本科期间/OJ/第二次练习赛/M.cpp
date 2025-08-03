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
const LL maxn=2e5+7;
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
		return d>a.d;
	}
};
vector<node> edge[maxn];
int dis[maxn],n,m,k;
bool vis[maxn];
int sumnum[maxn];//judge negative ring
bool spfa(int s){
	int i;
	FOR(i,1,n) dis[i]=INF;
	FOR(i,1,n) vis[i]=0;
	FOR(i,1,n) sumnum[i]=0;//judge negative ring
	dis[s]=0;
	deque<int> Q;//slf need
	Q.push_back(s);
//	int sum=0;//lll
	while (!Q.empty()){
		int u=Q.front();Q.pop_front();
//		if (!Q.empty()&&sum/Q.size()<dis[u]) Q.push_back(u);//lll
//		else {vis[u]=0; sum-=dis[u];}//lll
		vis[u]=0;//not lll
		REP(i,edge[u].size()){
			node v=edge[u][i];
			if (dis[u]+v.d<dis[v.n]){
				dis[v.n]=dis[u]+v.d;
				if (!vis[v.n]){
					vis[v.n]=1;
					if (Q.empty()||dis[Q.front()]<dis[v.n]) Q.push_back(v.n);//slf
					else Q.push_front(v.n);//slf
//					Q.push_back(v.n);//not slf
//					sumnum[v.n]++;//judge negative ring
//					if (sumnum[v.n]>=n) return 1;//judge negative ring
//					sum+=dis[v.n];//lll
				}
			}
		}
	}
//	return 0;//judge negative ring
}
int main(){
	while (~scanf("%d%d%d",&n,&m,&k)){
		int i;
		FOR(i,1,n) edge[i].clear();
		REP(i,m){
			int u,v,len;
			scanf("%d%d%d",&u,&v,&len);
			edge[u].emplace_back(node(v,len));
			edge[v].emplace_back(node(u,len));
		}spfa(1);
		FOR(i,1,k){
			int u;
			scanf("%d",&u);
			printf("Case %d:",i);
			if (dis[u]!=INF) printf("%d\n",dis[u]);
			else puts("-1");
		}puts("");
	}
}
/*
*/
