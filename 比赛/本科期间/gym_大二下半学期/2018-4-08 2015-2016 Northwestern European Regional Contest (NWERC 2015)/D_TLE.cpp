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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

LL MIN[maxn*8];
void update(int x,int l,int r,LL val,int L,int R){
	if (l<=L&&R<=r) {MIN[x]=min(MIN[x],val);return;}
	int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
}
LL query(int x,int p,int L,int R){
	if (L==R) return MIN[x];
	int mid=(L+R)/2;
	LL ret=MIN[x];
	if (p<=mid) ret=min(ret,query(x<<1,p,L,mid));
	else ret=min(ret,query(x<<1|1,p,mid+1,R));
	return ret;
}
int n;
LL p,r;
int main() {
	int i;
	scanf("%d%I64d%I64d",&n,&r,&p);
	FOR(i,1,n*8) MIN[i]=INFF;
	update(1,1,1,0,1,n*2);
	FOR(i,1,n){
		LL f=query(1,i,1,n*2)+r;
		for (int j=i+i;j<=n*2;j+=i){
			f+=p;
			update(1,1,j,f,1,n*2);
			// printf("upd:%d %d %lld\n",1,j,f);339 7 1
		}
	}printf("%I64d\n",query(1,n,1,n*2));
	return 0;
}
/*
1000000 10 1
*/
