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

int i,j,k,n,q;
double a[maxn];
double sum[maxn<<2],lazy[maxn<<2],mul[maxn<<2];
int L[maxn<<2],R[maxn<<2];
inline void UPD(int x,double val,double p){
	sum[x]=sum[x]*p+val*(R[x]-L[x]+1);
	mul[x]*=p;lazy[x]*=p;lazy[x]+=val;
}
void pushdown(int x){
	UPD(x<<1,lazy[x],mul[x]);
	UPD(x<<1|1,lazy[x],mul[x]);
	lazy[x]=0;mul[x]=1;
}
void pushup(int x){
	sum[x]=sum[x<<1]+sum[x<<1|1];
}
void build(int x,int l,int r){
	L[x]=l;R[x]=r;mul[x]=1;
	if (l==r){
		sum[x]=a[l];
		return;
	}int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void update(int x,int l,int r,double val,double p){
	if (l<=L[x]&&R[x]<=r) {UPD(x,val,p);return;}
	int mid=(L[x]+R[x])/2;
	pushdown(x);
	if (l<=mid) update(x<<1,l,r,val,p);
	if (mid<r) update(x<<1|1,l,r,val,p);
	pushup(x);
}
double query(int x,int l,int r){
	if (l<=L[x]&&R[x]<=r) return sum[x];
	int mid=(L[x]+R[x])/2;
	double ret=0;
	pushdown(x);
	if (l<=mid) ret+=query(x<<1,l,r);
	if (mid<r) ret+=query(x<<1|1,l,r);
	pushup(x);
	return ret;
}
int main(){
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%lf",&a[i]);
	build(1,1,n);
	while (q--){
		int k;
		scanf("%d",&k);
		if (k==1){
			int l1,r1,l2,r2;
			scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
			double x=query(1,l1,r1)/(r1-l1+1);
			double y=query(1,l2,r2)/(r2-l2+1);
			update(1,l1,r1,y/(r1-l1+1),1.0*(r1-l1)/(r1-l1+1));
			update(1,l2,r2,x/(r2-l2+1),1.0*(r2-l2)/(r2-l2+1));
		}else {
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lf\n",query(1,l,r));
		}
	}
}
/*
*/
