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
const LL maxn=5007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

vector<int> edge[maxn];
vector<LL> dp1[maxn],dp2[maxn];
LL now1[maxn],now2[maxn];//1=used,2=may not used
LL a[maxn],b[maxn],m;
int num[maxn],ans;
void dfs(int x){
	num[x]=1;
	dp1[x].resize(2);
	dp2[x].resize(2);
	dp1[x][1]=a[x];dp1[x][0]=0;
	dp2[x][1]=a[x]-b[x];dp2[x][0]=INFF;
	int i,j;
	for (int v:edge[x]){//这里对子树num排序可做到n^2//这个应该也不是n^3不会证 
		dfs(v);
		FOR(i,0,num[x]) now1[i]=dp1[x][i],now2[i]=dp2[x][i];
		dp1[x].resize(num[x]+num[v]+1,INFF);
		dp2[x].resize(num[x]+num[v]+1,INFF);
		FOR(i,0,num[x])
			FOR(j,1,num[v]){
				dp1[x][i+j]=min(dp1[x][i+j],now1[i]+dp1[v][j]);
				dp2[x][i+j]=min(dp2[x][i+j],now2[i]+min(dp1[v][j],dp2[v][j]));
			}
		vector<LL>().swap(dp1[v]);//这样才能成功清空内存，clear是赋值0 
		vector<LL>().swap(dp2[v]);
		num[x]+=num[v];
	}
}
int n;
int i,j,k;
int main(){
	scanf("%d%I64d",&n,&m);
	FOR(i,1,n){
		scanf("%I64d%I64d",&a[i],&b[i]);
		if (i!=1){
			int v;
			scanf("%d",&v);
			edge[v].push_back(i);
		};
	}
	dfs(1);
	ans=0;
//	FOR(i,1,n) printf("%d ",dp1[1][i]);puts("");
//	FOR(i,1,n) printf("%d ",dp2[1][i]);puts("");
	FOR(i,1,n) if (dp1[1][i]<=m||dp2[1][i]<=m) ans=max(ans,i);
	printf("%d",ans);
}
/*
*/
