#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
//const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
struct node{
	int ls,rs;
	int l,r;
	LL sum;
}T[maxn*40];
LL a[maxn];
int now,start;
int cnt;
void build(int x,int l,int r){
	if (!x) x=++cnt;
	T[x].l=l;T[x].r=r;
	if (l==r){
		T[x].sum=a[l];
		return;
	}
	int mid=(l+r)/2;
	build(T[x].l,ls,mid);
	build(T[x].r,mid+1,rs);
	T[x].sum=T[T[x].l].sum+T[T[x].r].sum;
}
void change(int &x,int y,int z,int lx,int rx,int ly,int ry){
	
}
LL n,m,T,ans;
int i;
int main()
{
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&a[i]);
	start=build(1,1,n);
	REP(i,m){
		scanf("%d",&k);
		if (k==1){
			scanf("%d%d",&l,&r);
		}
	}
}
/*
*/
