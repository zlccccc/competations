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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,k;
int a[maxn],p[maxn];
bool used,could;
bool cmp(int x,int y){
	if (a[x]!=a[y]) return a[x]<a[y];
	return x<y;
}int okp,chp;
int main(){
	int i;
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%d",&a[i]),p[i]=i;
	sort(p+1,p+n+1,cmp);
//	FOR(i,1,n) printf("%d ",p[i]);
	okp=chp=n+1;
	FOR(i,1,n){
        if (used&&p[i]+k<okp) return 0*puts("NO");
        if (p[i]+k<chp) return 0*puts("NO");
        if (p[i]+k<okp) okp=chp,used=1;
        chp=okp-k;
        okp=min(okp,p[i]);
	}
	puts("YES");
}
/*
5 1
5 5 5 5 5
*/
