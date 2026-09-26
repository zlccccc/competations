#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}


int n,m;
int a[N];
int i,j,k;
int time;
int sum;
int num;
int u,v;
vector<int> anss;
vector<int> edge[N];



int dfs(int from,int u){
	int i,j,k;
	int ans=0;
	k=edge[u].size();
	REP(i,k) if (edge[u][i]!=from){
		ans+=dfs(u,edge[u][i]);
	}
	if (ans+a[u]==num){
		anss.push_back(u);
		return 0;
	}
//	printf("%d %d\n",u,ans);
	return ans+a[u];
}
int main()
{
	scanf("%d",&n);
	FOR(u,1,n){
		scanf("%d%d",&v,&a[u]);
		edge[u].push_back(v);
		edge[v].push_back(u);
		sum+=a[u];
	}
	if (sum%3!=0){
		printf("-1");
		return 0;
	}
	num=sum/3;
	dfs(0,edge[0][0]);
	if (anss.size()<3) printf("-1");
	else printf("%d %d",anss[0],anss[1]);
}
/*
*/
