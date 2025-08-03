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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct seg_tree{
	int sum[maxn<<2];
	void update(int x,int l,int r,int val,int L,int R){
		
	}
	void query(int x,int l,int r,int L,int R){
		
	}
}T[21],pre;
//dp[i][k]表示i起(包含i),k次split的min_val 
//dp[i][k]=min{dp[pre-1][k-1]+f[pre][i]}//f()表示val
//f[pre][i]计算方法:增加一个点的val //f需要动态维护 
//nxt.push_back()
int cnt[16];
int i,j,k;
int u,v;
int n,m;
int main(){
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n){
		FOR(j,1,k){
			dp[i][j]=T[j-1].query(1,1,i-1,1,n);
			T[j].update(1,i-1,i-1,DP[i][j],1,n);
			T[j].update(1,1,n);
			
		}
	}
}
/*
*/
