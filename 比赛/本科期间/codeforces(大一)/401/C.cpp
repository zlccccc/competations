#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue> 
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL N=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m;
vector<int>a[N],dp[N];
int q[N];
int qq;
int i,j,k;
int l,r;
int main(){
	cin>>n>>m;
	FOR(i,1,n){
		a[i].push_back(0);
		dp[i].push_back(0);
		FOR(j,1,m){
			cin>>k;
			a[i].push_back(k);
			dp[i].push_back(0);
		}
	}
	FOR(j,1,m){
		k=1;
		dp[1][j]=1;
		FOR(i,2,n){
			if (a[i][j]<a[i-1][j]) k=i;
			dp[i][j]=k; 
		}
	}
	FOR(i,1,n){
		k=i;
		FOR(j,1,m) if (dp[i][j]<k) k=dp[i][j];
		q[i]=k;
	}
//	FOR(i,1,n){
//		FOR(j,1,m) printf("%d ",dp[i][j]);
//		printf("\n");
//	}
//	FOR(i,1,n) printf("%d\n",q[i]);
	cin>>qq;
	REP(i,qq){
		cin>>l>>r;
		if (q[r]<=l) puts("Yes");
		else puts("No");
	}
}
/*
*/
