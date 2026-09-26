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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

struct node{
	LL a[16][16];
	node(){
		memset(a,0,sizeof(a));
	}
};
node mul(node a,node b){
	node ret;
	int i,j,k;
	FOR(i,0,15)
		FOR(j,0,15)
			FOR(k,0,15) ret.a[i][j]=(ret.a[i][j]+a.a[i][k]*b.a[k][j])%M;
	return ret;
}
node Pow(node a,LL b){
	node ret;
	int i;
	FOR(i,0,15) ret.a[i][i]=1;
	for(;b;b>>=1){
		if (b&1) ret=mul(ret,a);
		a=mul(a,a);
	}
	return ret;
}
LL n,k;
LL i,j;
LL h[maxn],l[maxn],r[maxn];
node ans;//last
int main(){
	scanf("%d%I64d",&n,&k);
	REP(i,n) scanf("%I64d%I64d%I64d",&l[i],&r[i],&h[i]);
	r[n-1]=k;
	ans.a[0][0]=1;
	REP(i,n){
		node now;
		FOR(j,0,h[i]){
			if (j!=0) now.a[j-1][j]=1;
			now.a[j][j]=1;
			if (j!=h[i]) now.a[j+1][j]=1;//¥”ƒƒ¿Ô¿¥ 
		}
//		REP(j,r[i]-l[i]) {
//			ans=mul(now,ans);
//			printf("%d : ",j+l[i]);
//			FOR(k,0,h[i]+1) printf("%d ",ans.a[k][0]);
//			puts("");
//		}
		ans=mul(Pow(now,r[i]-l[i]),ans);
	}
	printf("%I64d",ans.a[0][0]);
}
