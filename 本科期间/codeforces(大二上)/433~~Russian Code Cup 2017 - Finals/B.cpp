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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
set<int> edge[maxn];
int cnt;
int dp[maxn][2];
string a[maxn];
int nxt[maxn][26];
bool mark[maxn];//indegree!=0
void dfs(int x){
	dp[x][1]=1;dp[x][0]=0;
	for (int v:edge[x]){
		dfs(v);
		dp[x][0]+=dp[v][1];//ฒปัก 
		dp[x][1]+=dp[v][0];//ัก (max)
	}
	dp[x][1]=max(dp[x][1],dp[x][0]);
}
void solve(){
	scanf("%d",&n);
	int i;
	FOR(i,1,n){
//		printf("%d %d\n",i,cnt);
		cin>>a[i];
		string str=a[i];
		int i,len=str.length(),now=0;
		REP(i,len){
			if (!nxt[now][str[i]-'a']) nxt[now][str[i]-'a']=++cnt;
			now=nxt[now][str[i]-'a'];
		}
	}
//	printf("%d\n",cnt);
	FOR(i,1,n){
		string &str=a[i];
		int len=str.length(),i,now1=0,now2=0;
		now1=nxt[now1][str[0]-'a'];
		rep(i,1,len){
			now1=nxt[now1][str[i]-'a'];
			now2=nxt[now2][str[i]-'a'];
			if (now1&&now2){
				edge[now2].insert(now1);
				mark[now1]=1;
			}else break;
		}
	}
//	FOR(i,1,cnt)
//		for (int v:edge[i]) printf("%d->%d\n",i,v);
	int ans=0;
	FOR(i,1,cnt) if (!mark[i]){
		dfs(i);
		ans+=dp[i][1];
	}
//	FOR(i,1,cnt) printf("%d %d\n",dp[i][0],dp[i][1]);
	printf("%d\n",ans);
	FOR(i,0,cnt){
		mark[i]=0;
		edge[i].clear();
		memset(nxt[i],0,sizeof(nxt[i]));
	}cnt=0;
}
int main(){
	int T; 
	scanf("%d",&T);
	while (T--) solve();
}
/*
33001
9
aaaaabbbb
a
bbababb
ab
abb
baa
bbbaabbabb
bbaaa
bbbbbaabaa
*/
