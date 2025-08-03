#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}


priority_queue<LL> Q[5];
LL n,m;
LL k,kk;
LL w[maxn],c[maxn],dp[maxn];
LL i,j,t;
LL tot,ans;
void add(int i){
	if (!Q[i].empty()){
		w[tot]=i;c[tot]=Q[i].top();
		Q[i].pop();tot++;
	}
}
const int maxnum=100;
int main(){
	scanf("%I64d%I64d",&n,&m);
	REP(i,n){
		scanf("%I64d%I64d",&k,&kk);
		Q[k].push(kk);
	}
	while (m>=maxnum){
		t=0;
		FOR(i,1,3)
			if (Q[i].size()>10&&(t==0||Q[i].top()*6ll/i>Q[t].top()*6ll/t)) t=i;
		if (t==0) break;
		m-=t;
		ans+=Q[t].top();
		Q[t].pop();
	}
	tot=0;
	REP(i,600) add(1);
	REP(i,300) add(2);
	REP(i,200) add(3);
	REP(i,tot)
		rFOR(j,w[i],m) dp[j]=max(dp[j],dp[j-w[i]]+c[i]);
	ans+=dp[m];
	printf("%I64d",ans);
}
