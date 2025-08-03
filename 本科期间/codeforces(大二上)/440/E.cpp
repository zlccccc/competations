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
const LL maxn=4e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int a[maxn];
vector<int> edge[maxn];
map<int,int> MP1,MP2;
int mark[maxn];
int tot;
int cnt,have;
LL ans,now;
int dfs(int x){
	cnt++;
	mark[x]=1;
	for(int v:edge[x]){
		have++;
		if (!mark[v]) dfs(v);
	}
}
LL fac[maxn],inv[maxn];
LL C(int n,int m){
	return fac[n]*inv[m]%M*inv[n-m]%M; 
}
int main(){
	int i,j;
	fac[0]=1; 
	FOR(i,1,400000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,400000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,400000) inv[i]=inv[i]*inv[i-1]%M;
	scanf("%d",&n);
	REP(i,n){
		int u,v;
		scanf("%d%d",&u,&v);
		if (!MP1.count(u)) MP1[u]=++tot;
		if (!MP2.count(v)) MP2[v]=++tot;
		u=MP1[u];v=MP2[v];
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	ans=1;
	FOR(i,1,tot) if (!mark[i]) {
		dfs(i);have/=2;
		FOR(j,0,min(cnt,have)) now=(now+C(cnt,j))%M;
//		printf("%d:%d %d;%d\n",i,have,cnt,now);
		ans=ans*now%M;cnt=have=now=0;
	}
	printf("%I64d",ans);
}
/*
2
-1 -1
1 2
*/
