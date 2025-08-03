#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=3e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

struct node{
	int n;
	LL d;
	node(int _n=0,LL _d=0):n(_n),d(_d){};
	bool operator<(const node&a)const{
		if (d==a.d) return n<a.n;
		return d>a.d;
	}
};
vector<node> edge[maxn*8];
LL dis[maxn*8],n,m;//²ðµã×ö°É 
void dij(int s){
	int i;
	REP(i,n*4) dis[i]=INFF;
	dis[s]=0;
	priority_queue<node> Q;
	Q.push(node(s,dis[s]));
	while (Q.size()){
		node x=Q.top();Q.pop();
		if (x.d!=dis[x.n]) continue;
		REP(i,edge[x.n].size()){
			node y=edge[x.n][i];
			if (dis[y.n]>x.d+y.d){
				dis[y.n]=x.d+y.d;
				Q.push(node(y.n,dis[y.n]));
			}
		}
	}
}
LL K,T,d12,d23,d34,d41,now;
LL ans;
int i;
int main()
{
	scanf("%d",&T);
	while (T--){
		scanf("%lld%lld%lld%lld%lld",&K,&d12,&d23,&d34,&d41);
		n=2*min(d12,d23);
		REP(i,4*n) vector<node>().swap(edge[i]);
		REP(i,n){
			edge[i].push_back(node(1*n+(d12+d23+d34+d41)%n,d12+d23+d34+d41));
			edge[i].push_back(node(2*n+(d12+d23+d34+d41)%n,d12+d23+d34+d41));
			edge[i].push_back(node(1*n+(i+d12*2)%n,d12*2));//could use 41
			edge[i].push_back(node(2*n+(i+d23*2)%n,d23*2));//could use 34
			edge[i+n*1].push_back(node(n*1+(i+d12*2)%n,d12*2));
			edge[i+n*2].push_back(node(n*2+(i+d23*2)%n,d23*2));
			edge[i+n*1].push_back(node(n*3+(i+d41*2)%n,d41*2));
			edge[i+n*1].push_back(node(n*3+(i+d23*2)%n,d23*2));
			edge[i+n*2].push_back(node(n*3+(i+d34*2)%n,d34*2));
			edge[i+n*2].push_back(node(n*3+(i+d12*2)%n,d12*2));
			edge[i+n*3].push_back(node(n*3+(i+d12*2)%n,d12*2));
			edge[i+n*3].push_back(node(n*3+(i+d23*2)%n,d23*2));
			edge[i+n*3].push_back(node(n*3+(i+d34*2)%n,d34*2));
			edge[i+n*3].push_back(node(n*3+(i+d41*2)%n,d41*2));
		}
		dij(0);
		ans=INFF;
		REP(i,n*4){
			if (dis[i]>=K) ans=min(ans,dis[i]);
			else ans=min(ans,((K-dis[i])/n+((K-dis[i])%n!=0))*n+dis[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
/*
5
4672 616 600 652 732
*/
