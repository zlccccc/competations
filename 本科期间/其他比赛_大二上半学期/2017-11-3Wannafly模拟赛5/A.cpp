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
const LL M=998244353;
const LL maxn=1.5e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//ans=sum(a[i]*a[j](i<j))所以均分 
int n,m;
int i,j,k,t;
int val;
int main(){
	scanf("%d%d",&n,&m);
	REP(k,n){
		int now=0;
		if (k){
			int t=n%(k+1),nn=n,o=n/(k+1);
			REP(i,k-t){nn-=o;now+=o*nn;}
			REP(i,t){nn-=(o+1);now+=(o+1)*nn;}
//			printf("%d %d %d,o=%d\n",k,now,nn,o);
		}
		if (now>=m) break;
	}
	if (k<n) printf("%d\n",k);
	else puts("-1");
}
/*
100 484372 
1000 499998
*/
