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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
int i,j,k,t;
int a[2],a1,a0;
int main()
{
	scanf("%d",&n);
	a[0]=a[1]=-INF;
	REP(i,n){
		scanf("%d",&j);
		if (j&1){
			a1=max(a[1],a[0]+j);
			a1=max(a1,j);
			a0=max(a[0],a[1]+j);
			a[1]=a1;a[0]=a0; 
		}
		else{
			a0=max(a[0],a[0]+j);
			a0=max(a0,j);
			a1=max(a[1],a[1]+j);
			a[1]=a1;a[0]=a0; 
		}
//	printf("%d %d\n",a[1],a[0]);
	}
	printf("%d",a[1]);
}
