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
const LL maxn=507;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
int ans[maxn][maxn];
int cnt;
int i,j,k;
void solve(){ 
	scanf("%d",&n);
	FOR(i,1,n){
		FOR(j,1,n){
			scanf("%d",&ans[i][j]);
		}
	}
	FOR(i,1,(1<<n)-1){
		FOR(j,1,(1<<n)-1){
			int ii,jj;
			FOR(ii,1,n)
				FOR(jj,i,n){
					if (i==j) ans[i][j]=0;
					else if (j&1) ans[i][j]=ans[j][i]=1; 
			}
		}
	}
	cnt=0;
	FOR(i,1,n)
		FOR(j,i+1,n)
			FOR(k,j+1,n) if (ans[i][j]==ans[j][k]&&ans[i][j]==ans[k][i]) cnt++;
	printf("%d\n",cnt);
} 
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
1008
6
0 2 2 1 1 2
2 0 2 2 1 1
2 2 0 2 2 1
1 2 2 0 2 2
1 1 2 2 0 2
2 1 1 2 2 0
9
0 2 2 2 2 1 1 1 1
2 0 2 2 2 2 1 1 1
2 2 0 2 2 2 2 1 1
2 2 2 0 2 2 2 2 1
2 2 2 2 0 2 2 2 2
1 2 2 2 2 0 2 2 2
1 1 2 2 2 2 0 2 2
1 1 1 2 2 2 2 0 2
1 1 1 1 2 2 2 2 0
*/
