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
const LL M=1e9+7;//206158430209;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const LL T=powMM(2ll,M-2);
void FXT(LL x[],int l,int r,int v){//r是不能用的点 
	if (l+1==r) return;
	int m=(l+r)/2,i;
	int ml=(l+m)/2,mr=(m+r)/2;
//	printf("%d-%d-%d-%d-%d\n",l,ml,m,mr,r);
	FXT(x,l,ml,v);FXT(x,ml,m,v);
	FXT(x,m,mr,v);FXT(x,mr,r,v);
	FOR(i,0,ml-l-1){
		LL a=x[l+i],b=x[ml+i],c=x[m+i],d=x[mr+i];
		if (v==1){
			x[l+i]=((b+d)%M+M)%M;
			x[ml+i]=((c+d)%M+M)%M;
			x[m+i]=((d)%M+M)%M;
			x[mr+i]=((a+b+c+d)%M+M)%M;
		}else{
			x[l+i]=((-a-b+c+d)%M+M)%M;
			x[ml+i]=((a-c)%M+M)%M;
			x[m+i]=((b-c)%M+M)%M;
			x[mr+i]=((c)%M+M)%M;
		}
	}
}
LL X[maxn];
LL ans[28];
int main(){
	int n,m;
	scanf("%d",&n);
	int i,j;
	int k;
	REP(i,n) scanf("%d",&k),X[k]++;
	FXT(X,0,1<<18,1);
	FOR(i,0,(1<<18)-1) X[i]=X[i]*X[i]%M;
	FXT(X,0,1<<18,-1);
	REP(i,n*2) printf("%d ",X[i]);
//	FOR(i,0,1<<18){
//		int k=0;
//		for (j=i;j;j>>=2) k+=j&3;
//		ans[k]+=X[i];
//	}
//	FOR(i,0,m*3) printf("%lld\n",ans[i]);
}
/*
20
1 4 2 4 1 3 4 8 5 3 1 4 6 7 3 1 4 4 2 5 7 9 8 2

*/
