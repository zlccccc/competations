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

struct node {
	int l,r,cnt;
} T[maxn*20]; int cnt;
void Update(int &x,int pos,int L,int R) {
	if (!x) x=++cnt; T[x].cnt++;
	if (L==R) return;
	int mid=(L+R)/2;
	if (mid>=pos) Update(T[x].l,pos,L,mid);
	else Update(T[x].r,pos,mid+1,R);
}
int Query(int x,int l,int r,int L,int R) {
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].cnt;
	int mid=(L+R)/2,ret=0;
	if (mid>=l) ret+=Query(T[x].l,l,r,L,mid);
	if (r>mid) ret+=Query(T[x].r,l,r,mid+1,R);
	return ret;
}
int n;
int root[maxn];
inline int lowbit(int x) {return x&-x;}
void update(int x,int y) {
	for (; x<=n; x+=lowbit(x)) Update(root[x],y,1,n);
}
int query(int x,int y) {
	int ret=0;
	for (; x; x-=lowbit(x))
		ret+=Query(root[x],1,y,1,n);
	return ret;
}
int A[maxn],B[maxn],C[maxn];//B,C:rev
int i,k;
LL ans;
int main() {
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n) scanf("%d",&k),B[k]=i;
	FOR(i,1,n) scanf("%d",&k),C[k]=i;
	FOR(i,1,n) {
		// printf("%d %d\n",B[i],C[i]);
		ans+=query(B[A[i]],C[A[i]]);
		update(B[A[i]],C[A[i]]);
	} printf("%I64d\n",ans);
	return 0;
}
/*
4
2 3 1 4
2 1 4 3
2 4 3 1
*/
