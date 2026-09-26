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

int a[5][11][11][maxn];//ATCG,%j,%=k,l-r
inline int lowbit(int x){
	return x&-x;
}
int presum(int i,int j,int k,int x){
	LL ret=0;
	while (x){
		ret+=a[i][j][k][x];
		x-=lowbit(x);
	}
	return ret;
}
int sum(int i,int j,int k,int l,int r){
	return presum(i,j,k,r)-presum(i,j,k,l-1);
}
char s1[maxn];
void add(int i,int j,int k,int x,int d){
//	printf("%d %d %d %d %d\n",i,j,k,x,d);
	while (x<=1e5){
		a[i][j][k][x]+=d;
		x+=lowbit(x);
	}
}
LL n,m,t; 
LL i,j,k,l,r;
char s2[maxn];
int main(){
	scanf("%s",s1+1);
	n=strlen(s1+1);
	FOR(i,1,10){
		FOR(j,1,n){
			if (s1[j]=='A') add(1,i,j%i,j,1);
			if (s1[j]=='T') add(2,i,j%i,j,1);
			if (s1[j]=='C') add(3,i,j%i,j,1);
			if (s1[j]=='G') add(4,i,j%i,j,1);
		}
	}
	scanf("%d",&m);
	while (m--){
		scanf("%d",&k);
		if (k==1){
			scanf("%d",&j);
			scanf("%s",s2);
			FOR(i,1,10){
				if (s1[j]=='A') add(1,i,j%i,j,-1);
				if (s1[j]=='T') add(2,i,j%i,j,-1);
				if (s1[j]=='C') add(3,i,j%i,j,-1);
				if (s1[j]=='G') add(4,i,j%i,j,-1);
			}
			s1[j]=s2[0];
			FOR(i,1,10){
				if (s1[j]=='A') add(1,i,j%i,j,1);
				if (s1[j]=='T') add(2,i,j%i,j,1);
				if (s1[j]=='C') add(3,i,j%i,j,1);
				if (s1[j]=='G') add(4,i,j%i,j,1);
			}
		}
		if (k==2){
			scanf("%d%d",&l,&r);
			int ans=0;
			scanf("%s",s2+1);
			t=strlen(s2+1);
			i=t;
			FOR(j,1,t){
				if (s2[j]=='A') ans+=sum(1,i,(l+j-1)%i,l,r);
				if (s2[j]=='T') ans+=sum(2,i,(l+j-1)%i,l,r);
				if (s2[j]=='C') ans+=sum(3,i,(l+j-1)%i,l,r);
				if (s2[j]=='G') ans+=sum(4,i,(l+j-1)%i,l,r);
			}
			printf("%d\n",ans);
		}
	}
}
/*
*/
