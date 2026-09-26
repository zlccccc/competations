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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//emmmmmmm自己想不出来啊... 
int n,m;
int val[maxn];
int posval[31];//posval[i]>>i=1
LL ans,cnt;
int main(){
	int n,m,i,j,k;
	scanf("%d%d",&n,&m);
	while (m--){
		int u,v,len;
		scanf("%d%d%d",&u,&v,&len);
		val[u]^=len;val[v]^=len;
	}
	FOR(i,1,n){
		FOR(k,0,30) if ((val[i]>>k)&1){
			if (!posval[k]) posval[k]=val[i];
			val[i]^=posval[k];
		}
	}
	FOR(k,0,30) if (posval[k]) cnt++;
	FOR(i,0,30){
		FOR(j,0,i-1) posval[i]^=(posval[i]&posval[j]);
		ans+=posval[i];
	}
	ans<<=cnt-1;
	while (ans>=1000000000) ans/=10;
	printf("%lld",ans);
    return 0;
}
/*
*/
