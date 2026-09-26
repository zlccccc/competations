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
const LL M=1e6;
const LL N=1e6;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m;
int i,j,k,l;
int u,v; 
bool b[N];
set<int> edge[N];
set<int> dis[N];
queue<int> q;
int ans;
int main()
{
	cin>>n;
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[u].insert(v);
		edge[v].insert(u);
	}
	FOR(i,1,n)
	if (edge[i].size()==1){
		q.push(i);
		dis[i].insert(0);
	}
	while (!q.empty()){
		v=q.front();
		q.pop();
		if (b[v]) continue;
		if (dis[v].size()>2){
			printf("-1");
			return 0;
		}
		if (edge[v].size()!=1||dis[v].size()!=1) continue;
//		printf("%d %d\n",v,dis[v].size());
		u=*edge[v].begin();
		q.push(u);
		edge[v].erase(u);edge[u].erase(v);
		dis[u].insert(*dis[v].begin()+1);
		b[v]=1;
	}
	if (edge[v].size()!=0){
		printf("-1");
		return 0;
	}
	ans=*dis[v].begin()+*dis[v].rbegin();
//	printf("%d ",v);
	while (ans%2==0) ans>>=1;
	printf("%d",ans);
	return 0;
}
/*
*/
