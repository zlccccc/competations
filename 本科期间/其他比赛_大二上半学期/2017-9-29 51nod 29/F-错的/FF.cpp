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
#include <bitset>
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

void FXT(LL x[],int l,int r,int v){//r是不能用的点 
	if (l+1==r) return;
	int m=(l+r)/2,i;
	int ml=(l+m)/2,mr=(m+r)/2;
//	printf("%d-%d-%d-%d-%d\n",l,ml,m,mr,r);
	FXT(x,l,ml,v);FXT(x,ml,m,v);
	FXT(x,m,mr,v);FXT(x,mr,r,v);
	FOR(i,0,ml-l-1){
		int a=x[l+i],b=x[ml+i],c=x[m+i],d=x[mr+i];
		if (v==1){
			x[l+i]=c+d;
			x[ml+i]=a+b+c+d;
			x[m+i]=b+d;
			x[mr+i]=d;
		}else{
			x[l+i]=-a+b-c+d;
			x[ml+i]=c-d;
			x[m+i]=a-d;
			x[mr+i]=d;
		}
	}
}
int X[maxn];
int ans[28];
int main(){
	scanf("%d%d",&n,&m);
	int i,j;
	REP(i,n){
		int now=0;
		REP(j,m) scanf("%d",&k),now=now<<2|k;
		X[now]++;
	}
	FXT(X,0,1<<18,-1);
	FOR(i,0,(1<<18)-1) X[i]=X[i]*X[i];
	FXT(X,0,1<<18,1);
	FOR(i,0,1<<18){
		k=0;
		for (j=i;j;j>>=2) k+=j&3;
		ans[k]+=X[i];
	}
	FOR(i,0,m*3) printf("%lld\n",ans[i]);
}
/*
*/
