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
const LL maxn=160000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int n;
	LL d;
	node(){}
	node(int _n,LL _d):n(_n),d(_d){}
	bool operator<(const node&a)const{
		if (d==a.d) return n<a.n;
		return d>a.d; 
	}
};
vector<node> edge[maxn];
LL dis[maxn],n;
void dij(int s){
	int i;
	FOR(i,1,n) dis[i]=INFF;
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
#define MP make_pair
LL T;
int i,j,k;
vector<LL> hashx,hashy;
LL X[maxn],Y[maxn];
char C[maxn];
vector<pair<int,int> > POSX[maxn],POSY[maxn];
set<pair<LL,int> > nxt;//time,dir,i
int main(){
	cin>>n>>T;
	REP(i,n) cin>>X[i]>>Y[i]>>C[i],hashx.emplace_back(X[i]),hashy.emplace_back(Y[i]);
	sort(hashx.begin(),hashx.end());hashx.erase(unique(hashx.begin(),hashx.end()),hashx.end());
	sort(hashy.begin(),hashy.end());hashy.erase(unique(hashy.begin(),hashy.end()),hashy.end());
	REP(i,n){
		POSX[lower_bound(hashx.begin(),hashx.end(),X[i])-hashx.begin()].emplace_back(MP(Y[i],i));
		POSY[lower_bound(hashy.begin(),hashy.end(),Y[i])-hashy.begin()].emplace_back(MP(X[i],i));
	}
	REP(i,hashx.size()){
		sort(POSX[i].begin(),POSX[i].end());
		int pre=-1;
		for (j=0;j<POSX[i].size();j++){
			int v=POSX[i][j].second+1;
			if (pre!=-1){
				int u=POSX[i][pre].second+1,len=POSX[i][j].first-POSX[i][pre].first;
				edge[u].push_back(node(v,len));
//				printf("%d->%d,%d\n",u,v,len);
			}if (C[POSX[i][j].second]=='U') pre=j;
		}reverse(POSX[i].begin(),POSX[i].end());
		pre=-1;
		for (j=0;j<POSX[i].size();j++){
			int v=POSX[i][j].second+1;
			if (pre!=-1){
				int u=POSX[i][pre].second+1,len=POSX[i][pre].first-POSX[i][j].first;
				edge[u].push_back(node(v,len));
//				printf("%d->%d,%d\n",u,v,len);
			}if (C[POSX[i][j].second]=='D') pre=j;
		}
	}//puts("OK1");
	REP(i,hashy.size()){
		sort(POSY[i].begin(),POSY[i].end());
		int pre=-1;
		for (j=0;j<POSY[i].size();j++){
			int v=POSY[i][j].second+1;
			if (pre!=-1){
				int u=POSY[i][pre].second+1,len=POSY[i][j].first-POSY[i][pre].first;
				edge[u].push_back(node(v,len));
//				printf("%d->%d,%d\n",u,v,len);
			}if (C[POSY[i][j].second]=='R') pre=j;
		}reverse(POSY[i].begin(),POSY[i].end());
		pre=-1;
		for (j=0;j<POSY[i].size();j++){
			int v=POSY[i][j].second+1;
			if (pre!=-1){
				int u=POSY[i][pre].second+1,len=POSY[i][pre].first-POSY[i][j].first;
				edge[u].push_back(node(v,len));
//				printf("%d->%d,%d\n",u,v,len);
			}if (C[POSY[i][j].second]=='L') pre=j;
		}
	}
	dij(1);
//	FOR(i,1,n) printf("%lld\n",dis[i]);
	REP(i,n){
		if (dis[i+1]<=T){
			if (C[i]=='U') Y[i]+=T-dis[i+1];
			if (C[i]=='D') Y[i]-=T-dis[i+1];
			if (C[i]=='L') X[i]-=T-dis[i+1];
			if (C[i]=='R') X[i]+=T-dis[i+1];
		}
	}
	REP(i,n) printf("%I64d %I64d\n",X[i],Y[i]);
}
/*
5 1000
1 0 U
0 0 R
1 1 L
0 1 D
1 2 U
*/
