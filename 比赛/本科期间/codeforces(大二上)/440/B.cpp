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

int n,m,ans;
int a[maxn],l[maxn],r[maxn];
int MIN,MAX;
int i,j,k; 
int main(){
	scanf("%d%d",&n,&k);
	MIN=INF;MAX=-INF;
	FOR(i,1,n){
		scanf("%d",&a[i]);
		l[i]=r[i]=a[i];
		MIN=min(MIN,a[i]);
		MAX=max(MAX,a[i]);
	}
	if (k==1) return 0*printf("%d",MIN);
	if (k>=3) return 0*printf("%d",MAX);
	MIN=-INF;
	FOR(i,2,n) l[i]=min(l[i],l[i-1]);
	rFOR(i,1,n-1) r[i]=min(r[i],r[i+1]);
	FOR(i,1,n-1) MIN=max(MIN,max(l[i],r[i+1]));
	printf("%d\n",MIN);
}
/*
6 2
1 2 3 6 4 5
*/
