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
const LL maxn=5007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

LL a[maxn],b[maxn];
int n;
int i,j,k;
bool mark;
LL ans;
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%I64d",&a[i]);
	mark=0;
	while(n){
		n--;
		FOR(i,1,n){
			if (mark) b[i]=((a[i]-a[i+1])+M)%M;
			else b[i]=(a[i+1]+a[i])%M;
			mark^=1; 
		}
		FOR(i,1,n) a[i]=b[i];
	FOR(i,1,n) printf("%I64d ",a[i]);puts("");
	}
	printf("%I64d",(a[1]+M)%M);
}
/*
4
1 10 100 1000
5
1 10 100 1000 10000
6
1 10 100 1000 10000 100000
7
1 10 100 1000 10000 100000 1000000
10
1 10 100 1000 10000 100000 1000000 10000000 100000000 1000000000
*/
