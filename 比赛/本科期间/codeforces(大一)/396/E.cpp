#include <cstdio>
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,N) for (I=1;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e6;
const double eps=0.00000001;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline int min(int a,int b) {return a>b?b:a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline double min(double a,double b) {return a>b?b:a;}
inline int max(int a,int b) {return a<b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline double max(double a,double b) {return a<b?b:a;}
inline int abs(int a,int b) {return a>0?a:-a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a,double b) {return a>0?a:-a;}


int n,m;
int a[N];
int u,v;
vector<int> edge[N];
LL num[N][2];
LL ans;
LL sum;
int i,j,k,l;
bool mark;
void dfs(int u,int o){
	int i;
	int k=(a[u]>>l)&1;
	num[u][k]=1; num[u][k^1]=0;
	int nn=edge[u].size();
	REP(i,nn) if (edge[u][i]!=o){
		int v=edge[u][i];
		dfs(v,u);
		sum+=num[v][0]*num[u][1]+num[v][1]*num[u][0];
		num[u][k^0]+=num[v][0];
		num[u][k^1]+=num[v][1];
	}
}
int main()
{
	scanf("%d",&n);
	FOR(i,n) scanf("%d",&a[i]),ans+=a[i];
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	REP(l,23){
		sum=0;
		dfs(1,0);
		ans+=1ll*sum<<l;
	}
	printf("%I64d",ans);
}
/*
3
1 2 3
1 2
2 3

*/
