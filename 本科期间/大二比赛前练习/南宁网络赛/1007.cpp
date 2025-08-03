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
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const LL eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a) {return a>0?a:-a;}

LL n,m;
LL i,j,k;
struct node{
	LL b,p;
	node(LL _b=0,LL _p=0):b(_b),p(_p){}
}a[maxn];
int cmp(node a,node b){
	if (a.p==b.p) return a.b<b.b;
	return a.p>b.p;
}
LL ANS,ans[maxn];
int main(){
	LL n,m,t;
	scanf("%lld%lld",&n,&m);
	FOR(i,1,n){
		t=0;LL r,b,p;
		scanf("%lld",&r);r=max(r,0ll);
		while (~scanf("%lld",&b)){
			if (b==-1) break;
			scanf("%lld",&p);
			if (1<=b&&b<=m&&p>=r&&p>0) a[t++]=node(b,p);
		}
		if (t==0) continue;
		sort(a,a+t,cmp);
		LL secondp;
		if (t==1) secondp=r*11/10;
		else secondp=(a[1].p*11)/10;
		ans[a[0].b]+=min(secondp,a[0].p);
	}
	LL q,h;
	scanf("%lld",&q);
	FOR(i,1,q){
		scanf("%lld",&h);
		printf("%lld\n",ans[h]);
	}
}
/*
3
5
11 2 12 1 15 -1
5 3 4 -1
23 1 32 2 35 3 40 -1
5
1
1
2
3
4

*/
