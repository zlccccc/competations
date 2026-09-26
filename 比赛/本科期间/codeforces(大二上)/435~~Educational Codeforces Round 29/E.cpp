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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int l,r,val,add;
}T[maxn*50];
int cnt;
void pushdown(int x){
	if (T[x].add){
		if (!T[x].l) T[x].l=++cnt;
		if (!T[x].r) T[x].r=++cnt;
		T[T[x].l].add+=T[x].add,T[T[x].l].val+=T[x].add;
		T[T[x].r].add+=T[x].add,T[T[x].r].val+=T[x].add;
		T[x].add=0;
	}
}
void pushup(int x){
	T[x].val=INF;
	if (T[x].l) T[x].val=min(T[x].val,T[T[x].l].val);
	if (T[x].r) T[x].val=min(T[x].val,T[T[x].r].val);
}
void update(int &x,int l,int r,int L,int R){
	if (!x) x=++cnt;
	if (l<=L&&R<=r){T[x].add++;T[x].val++;return;}
	int mid=(L+R)/2;
	pushdown(x);
	if (mid>=l) update(T[x].l,l,r,L,mid);
	if (r>mid) update(T[x].r,l,r,mid+1,R);
	pushup(x);
}
int query(int &x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return T[x].val;
	int mid=(L+R)/2,ret=INF;
	pushdown(x);
	if (mid>=l) ret=min(ret,query(T[x].l,l,r,L,mid));
	if (r>mid) ret=min(ret,query(T[x].r,l,r,mid+1,R));
	pushup(x);
	return ret;
}
int root;
int L[maxn],R[maxn];
int main(){
	int i,j,k,n;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d%d",&L[i],&R[i]),update(root,L[i],R[i],0,1e9);
	FOR(i,1,n) if (query(root,L[i],R[i],0,1e9)!=1) return 0*printf("%d",i);
	puts("-1");
}
/*
3
1 2
2 3
3 4

*/
