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

struct node{
	int l,r,val;
}T[maxn*20];int cnt;
void update(int &x,int l,int r,int id,int L,int R){
	// dbg(x);dbg(l);dbg(r);dbg(id);dbg(L);dbgln(R);
	if (!x) x=++cnt;
	if (l<=L&&R<=r) {
		T[x].val=max(T[x].val,id);
		return;
	}int mid=(L+R)/2;
	if (l<=mid) update(T[x].l,l,r,id,L,mid);
	if (mid<r) update(T[x].r,l,r,id,mid+1,R);
}
int query(int &x,int pos,int L,int R){
	// dbg(x);dbg(id);dbg(L);dbgln(R);
	if (!x) return 0;
	int ret=T[x].val;
	if (L==R) return ret;
	int mid=(L+R)/2;
	if (pos<=mid) ret=max(ret,query(T[x].l,pos,L,mid));
	if (mid<pos) ret=max(ret,query(T[x].r,pos,mid+1,R));
	return ret;
}
int n,m;
int root[maxn];
int ans;
const int MAX=1e5+7;
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int u,v,val;
		scanf("%d%d%d",&u,&v,&val);val++;
		int id;
		id=query(root[u],val,1,MAX)+1;
		// printf("update: %d %d->%d %d\n",v,val+1,MAX,id);
		update(root[v],val+1,MAX,id,1,MAX);
		ans=max(ans,id);
	}printf("%d\n",ans);
	return 0;
}
/*
1 0 0
-1000000
1000000
*/
