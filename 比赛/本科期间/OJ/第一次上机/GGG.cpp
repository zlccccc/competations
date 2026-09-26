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
#include <cassert>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const LL INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=10000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,i;
int a[maxn],b[maxn],c[maxn];
int ans;
void msort(int l,int r){
	if (l==r) return;
	int mid=(l+r)/2;
	int i,j,k;
	msort(l,mid);msort(mid+1,r);
	FOR(i,l,r) c[i]=b[i];
	i=l;j=mid+1;
	FOR(k,l,r){
		if (j>r||i<=mid&&(c[i]+1)/2>c[j]) i++;
		else ans+=i-l,j++;
	}
	i=l;j=mid+1;
	FOR(k,l,r){
		if (j>r||i<=mid&&c[i]>c[j]) b[k]=c[i],i++;
		else b[k]=c[j],j++;
	}
}
int main(){
	while (~scanf("%d",&n)){
		REP(i,n) scanf("%d",&a[i]);
		int q;
		scanf("%d",&q);
		REP(i,q){
			int l,r,i;
			scanf("%d%d",&l,&r);
			if (l>r) swap(l,r);
			FOR(i,l,r) b[i]=a[i];
			ans=0;
			msort(l,r);
			printf("%d\n",ans);
		}
	}
}
/*
*/
