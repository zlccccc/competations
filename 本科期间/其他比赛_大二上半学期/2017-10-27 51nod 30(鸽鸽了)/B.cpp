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
typedef pair<int,int> pii;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
vector<int> Q[maxn];
int fa[maxn],dep[maxn],head[maxn],HEAD[maxn],nxt[maxn];
int dp[maxn][77],len[maxn][77];
LL ans;
void dfs(int x){
	HAED[x]=0;
	int i,j;
	for (int v=head[x];v;v=nxt[v]){
		dfs(v);
		if (i==head[x]){
			HEAD[x]=pre[]
		}
		FOR(i,1,70){
			dp[x][i]=min(dp[x][i],dp[v][i]);//not this
//			dp[x][i]=min(dp[x][i],len[v][i-1]);
		}j=0;
		FOR(i,0,35) FOR(j,0,35)
			dp[x][i+j+1]=min(dp[x][i+j+1],max(len[v][i],len[x][j]));
//		FOR(i,0,70){
//			if (i+j>70) break;
//			while(len[x][j]<len[v][i]&&i+j<=70){
//				dp[x][i+j]=min(dp[x][i+j],max(len[v][i],len[x][j]));
//				j++;
//			}dp[x][i+j]=min(dp[x][i+j],max(len[v][i],len[x][j]));
//		}
		FOR(i,1,70) len[x][i]=min(len[x][i],len[v][i-1]);
	}
}
int main(){
	scanf("%d",&n);
	FOR(i,2,n){
		scanf("%d%*d",&fa[i]);
		nxt[i]=head[fa[i]];
		head[fa[i]]=i;
		dep[i]=dep[fa[i]]+1;
	}dfs(1);
	FOR(i,1,n){
		FOR(j,0,10){
			printf("%d ",dp[i][j]);
		}puts("");
	}
	scanf("%d",&m);
	REP(i,m){
		int l,r;
		scanf("%d%d",&l,&r);l++;r++;
		rFOR(j,0,70) if (dp[l][j]<=r) break;
		ans+=j;
		printf("ans:%d\n",j);
	}
	printf("%d\n",ans);
}
/*
*/
