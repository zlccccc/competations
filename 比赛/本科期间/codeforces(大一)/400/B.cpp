#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
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
const LL N=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

LL n,m;
LL a[N];
LL i,j;
bool mark=0;
int main(){
	scanf("%d",&n);
	FOR(i,2,n+1) a[i]=1;
	FOR(i,2,n+1){
		for (j=i*2;j<=n+1;j+=i){
			a[j]=2;
			mark=1;
		}
	}
	printf("%d\n",mark+1);
	FOR(i,2,n+1) printf("%d ",a[i]);
}
/*
*/
