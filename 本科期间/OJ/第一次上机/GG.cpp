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

const LL MAX=INF*5;
struct node{
	int l,r,val;
}T[maxn*40],Q[maxn];
int cnt;
inline void update(int &x,LL pos,int val,LL l,LL r){
	if (!x) x=++cnt,T[x].l=T[x].r=T[x].val=0;T[x].val+=val;
	if (l==r) return;
	LL mid=(l+r)/2;
	if (mid>=pos) update(T[x].l,pos,val,l,mid);
	else update(T[x].r,pos,val,mid+1,r);
}
inline int query(int x,LL l,LL r,LL L,LL R){
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].val;
	int ret=0;
	LL mid=(L+R)/2;
	if (mid>=l) ret+=query(T[x].l,l,r,L,mid);
	if (r>mid) ret+=query(T[x].r,l,r,mid+1,R);
	return ret;
}
int block[maxn];
int ans[maxn],now;
bool cmp(node a,node b){
	if (block[a.l]==block[b.l]) return a.r<b.r;
	return block[a.l]<block[b.l];
}
int root;
int n,i;
LL a[maxn];
int L,R;
const int SIZE=700;
int main(){
	FOR(i,1,10000) block[i]=i/SIZE;
	while (~scanf("%d",&n)){
		FOR(i,1,n) scanf("%lld",&a[i]);
		int q;
		scanf("%d",&q);
		REP(i,q){
			scanf("%d%d",&Q[i].l,&Q[i].r);Q[i].val=i;
			Q[i].l++;Q[i].r++;
			if (Q[i].l>Q[i].r) swap(Q[i].l,Q[i].r);
		}
		sort(Q,Q+q,cmp);
		L=1;R=0;now=0;
		cnt=root=0;
		REP(i,q){
			while (R<Q[i].r){R++;now+=query(root,a[R]*2+1,MAX,0,MAX);update(root,a[R],1,0,MAX);}
			while (L>Q[i].l){L--;now+=query(root,0,(a[L]-1)/2,0,MAX);update(root,a[L],1,0,MAX);}
			while (R>Q[i].r){update(root,a[R],-1,0,MAX);now-=query(root,a[R]*2+1,MAX,0,MAX);R--;}
			while (L<Q[i].l){update(root,a[L],-1,0,MAX);now-=query(root,0,(a[L]-1)/2,0,MAX);L++;}
			ans[Q[i].val]=now;
		}
		REP(i,q) printf("%d\n",ans[i]);
	}
}
/*
*/
