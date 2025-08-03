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
const LL maxn=1000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int i;
int a[1024];
int n,k,t;
int read(){
	int ret,i;
	fflush(stdout);
	printf("? ");
	FOR(i,1,n) printf("%d",a[i]);
	puts("");
	cin>>ret;
	return ret;
}
int l,r,mid;
int pre;
int main(){
	scanf("%d",&n);
	FOR(i,1,n) a[i]=0;
	k=read();a[1]=1;k-=read();if (k==-1) k=0;
	FOR(i,1,n) a[i]=k;pre=read();
	l=1;r=n;
	while (l+1<r){
		int mid=(l+r)/2;
		FOR(i,2,mid) a[i]=k^1;
		FOR(i,mid+1,n) a[i]=k;
		if (read()-pre==mid-1) l=mid;
		else r=mid;
	}
	if (k==0) printf("! 1 %d",r);
	else printf("! %d 1",r);
}
/*
0011001100


*/
