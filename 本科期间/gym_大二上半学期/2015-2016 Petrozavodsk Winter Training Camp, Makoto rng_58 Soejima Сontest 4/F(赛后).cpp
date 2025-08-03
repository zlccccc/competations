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
const LL maxn=2000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
int n;
int i,j,k;
bool mark[27];
int L[27],R[27];
int c[27],a[27];
int cnt;
int pre,l,r;
int ans;
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d%d",&a[i],&c[i]);
	FOR(i,1,n){
		FOR(j,1,i-1) if (c[i]==c[j]) return 0*puts("0");
		L[++cnt]=a[i]-1;
		while (i<n&&c[i+1]==c[i]) i++;
		R[cnt]=a[i]-1;
	}
	if (cnt==1) return 0*puts("-1"); 
	for (i=1;i<=L[2];i=j+1){
		bool mark=1;j=L[2];
		pre=-1;l=r=0;
		FOR(k,1,cnt){
			l=L[k]/i;r=R[k]/i;
			if (pre>=l||l!=r) mark=0;
			if (l) j=min(j,L[k]/l);
			if (r) j=min(j,R[k]/r);
			pre=r;
		}
//		printf("%d %d\n",i,j);
		if (mark) ans+=j-i+1;
	}
	printf("%d\n",ans);
}
/*
*/
