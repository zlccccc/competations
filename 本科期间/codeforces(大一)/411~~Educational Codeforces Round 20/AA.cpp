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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


int n,m;
int i,j,k;
int t;
int a[107][107];
int main(){
	scanf("%d%d",&n,&k);
	if (k>n*n) return 0*puts("-1");
	FOR(i,1,n){
		FOR(j,1,n){
			if (a[i][j]==1) continue;
			if (i!=j&&k==1) continue;
			if (k==0) continue;
			a[i][j]=a[j][i]=1;
			if (i==j) k--;
			else k-=2;
		}
	}
	FOR(i,1,n){
		FOR(j,1,n) printf("%d ",a[i][j]);
		puts("");
	}
}
