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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int l,r,val;
}T[maxn*40];
int cnt;
//emmmmmm这是个假算法，因为数据弱.... 
inline void update(int &x,int y,int pos,int L,int R){
//	printf("update:%d %d %d\n",pos,L,R);
	x=++cnt;T[x]=T[y];
	T[x].val++;
	if (L==R) return;
	int mid=(L+R)/2;
	if (mid>=pos) update(T[x].l,T[y].l,pos,L,mid);
	else update(T[x].r,T[y].r,pos,mid+1,R);
}
inline int query(int x,int y,int k,int L,int R){
//	printf("query:%d %d %d\n",k,L,R);
	if (T[x].val-T[y].val>k&&L==R) return L;
	int mid=(L+R)/2,ret=-1;
	if (T[T[x].l].val-T[T[y].l].val>k) ret=query(T[x].l,T[y].l,k,L,mid);
	if (ret>0) return ret;
	if (T[T[x].r].val-T[T[y].r].val>k) ret=query(T[x].r,T[y].r,k,mid+1,R);
	return ret;
}
int a[maxn],root[maxn];
int main(){
	int n,q,k;
	int i,j;
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n) update(root[i],root[i-1],a[i],1,n);
	while (q--){
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",query(root[r],root[l-1],(r-l+1)/k,1,n));
	}
}
/*
*/
