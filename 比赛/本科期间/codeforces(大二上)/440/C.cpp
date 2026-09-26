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
int a[maxn]; 
int main(){
	int q;
	scanf("%d",&q);
	a[1]=-1;
	a[2]=-1;
	a[3]=-1;
	a[4]=1;
	a[5]=-1;
	a[6]=1;
	a[7]=-1;
	a[8]=2;
	a[9]=1;
	a[10]=2;
	a[11]=-1;
	a[12]=3;
	a[13]=2;
	while (q--){
		scanf("%d",&n);
		if (n<13) printf("%d\n",a[n]);
		else{
			if (n%4==0) printf("%d\n",n/4);
			if (n%4==1) printf("%d\n",(n-9)/4+1);
			if (n%4==2) printf("%d\n",(n-2)/4);
			if (n%4==3) printf("%d\n",(n-9-2)/4+1);
		}
	}
}
/*
*/
