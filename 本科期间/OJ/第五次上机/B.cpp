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
#include <cassert>
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

int m,k,s;
int dp[maxn];
priority_queue<pair<double,int> > Q;
int main(){
	while (~scanf("%d%d%d",&m,&k,&s)){
		int i,j;
		while (Q.size()) Q.pop();
		dp[0]=0;FOR(i,1,s) dp[i]=-INF;
		FOR(i,1,m){
			int c,l;
			assert(scanf("%d%d",&c,&l)==2);
			Q.push(make_pair(1.0*l/c,c));
		}
		int all=0;
		FOR(i,1,k){
			int w,r;
			assert(scanf("%d%d",&w,&r)==2);
			rFOR(j,0,all) dp[j+w]=max(dp[j+w],dp[j]+r);
			all+=w;if (all>s) all=s;
		}
		double ans=-1;int t;
		rFOR(i,0,s) if (dp[i]>ans) ans=dp[i],t=i;
		t=s-t;
		while (t&&Q.size()){
			auto now=Q.top();Q.pop();
			int del=min(t,now.second);
			t-=del;
			ans+=del*now.first;
		}
		printf("%.1lf\n",ans);
	}
}
/*
*/
