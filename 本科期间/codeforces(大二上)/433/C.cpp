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
	int l,r,sum;
}T[maxn*40];
int cnt;
void update(int &x,int y,int pos,int l,int r){
	x=++cnt;T[x]=T[y];T[x].sum++;
	if (l==r) return;
	int mid=(l+r)/2;
	if (mid>=pos) update(T[x].l,T[y].l,pos,l,mid);
	else update(T[x].r,T[y].r,pos,mid+1,r);
}
LL query(int x,int l,int r,int L,int R){
	if (!x||l<=L&&R<=r) return T[x].sum;
	int mid=(L+R)/2;
	LL ret=0; 
	if (mid>=l) ret+=query(T[x].l,l,r,L,mid);
	if (r>mid) ret+=query(T[x].r,l,r,mid+1,R);
	return ret;
}
int root[maxn];
int n,q;
inline LL count(int x1,int x2,int y1,int y2){
//	x1=max(x1,1);y1=max(y1,1);
//	x2=min(x2,n);y2=min(y2,n);
	if (x2<x1||y2<y1) return 0;
	return query(root[x2],y1,y2,1,n)-query(root[x1-1],y1,y2,1,n);
}
int i;
int val[maxn];
int main(){
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%d",&val[i]);
	FOR(i,1,n) update(root[i],root[i-1],val[i],1,n);
	FOR(i,1,q){
		int x1,x2,y1,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		LL ld=count(1,x1-1,1,y1-1);
		LL l =count(1,x1-1,y1,y2);
		LL lu=count(1,x1-1,y2+1,n);
		LL d =count(x1,x2,1,y1-1);
		LL u =count(x1,x2,y2+1,n);
		LL rd=count(x2+1,n,1,y1-1);
		LL r =count(x2+1,n,y1,y2);
		LL ru=count(x2+1,n,y2+1,n);
		LL ans=ld*(ld-1)/2+l*(l-1)/2+lu*(lu-1)/2+d*(d-1)/2+u*(u-1)/2+rd*(rd-1)/2+r*(r-1)/2+ru*(ru-1)/2;
		ans+=ld*(d+rd+l+lu);
		ans+=d*rd+l*lu;
		ans+=ru*(u+lu+r+rd);
		ans+=u*lu+r*rd;
//		printf("%d %d %d %d %d %d %d %d\n",ld,l,lu,d,u,rd,r,ru);
		printf("%I64d\n",1ll*n*(n-1)/2-ans);
	}
}
/*
4 2
1 3 2 4
4 1 4 4
1 1 2 3
*/
