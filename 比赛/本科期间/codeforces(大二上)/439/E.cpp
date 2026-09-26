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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,q;
struct _node{
	int l,r;
	LL val;
}T[maxn*20];
int cnt;
void Update(int &x,int l,int r,int val,int L,int R){
	if (!x) x=++cnt;
	if (l<=L&&R<=r){T[x].val+=val;return;}
	int mid=(L+R)/2;
	if (mid>=l) Update(T[x].l,l,r,val,L,mid);
	if (r>mid) Update(T[x].r,l,r,val,mid+1,R);
}
int root[maxn<<2];
void update(int x,int l,int r,int yl,int yr,int val,int L,int R){
	if (l<=L&&R<=r) {Update(root[x],yl,yr,val,1,m);return;}
	int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,yl,yr,val,L,mid);
	if (r>mid) update(x<<1|1,l,r,yl,yr,val,mid+1,R);
}
int Query(int &x,int Y,int L,int R){
	if (!x) return 0;
	int ret=T[x].val;
	int mid=(L+R)/2;
	if (mid>=Y) ret+=Query(T[x].l,Y,L,mid);
	else ret+=Query(T[x].r,Y,mid+1,R);
	return ret;
}
int query(int x,int X,int Y,int L,int R){
	int ret=Query(root[x],Y,1,m);
	if (L==R) return ret;
	int mid=(L+R)/2;
	if (mid>=X) ret+=query(x<<1,X,Y,L,mid);
	else ret+=query(x<<1|1,X,Y,mid+1,R);
	return ret;
}
int i,j,k;
struct node{
	int x1,y1,x2,y2;
	bool operator < (const node A) const{
		if (x1!=A.x1) return x1<A.x1;
		if (x2!=A.x2) return x2<A.x2;
		if (y1!=A.y1) return y1<A.y1;
		if (y2!=A.y2) return y2<A.y2;
		return 0;
	}
}now;
inline LL RAND(){return 1ll*rand()<<16|rand()<<16|rand();}
map<node,int> MP;
int main(){
	scanf("%d%d%d",&n,&m,&q);
	srand(time(0));
	FOR(i,1,q){
		scanf("%d",&k);
		if (k==1){
			scanf("%d%d%d%d",&now.x1,&now.y1,&now.x2,&now.y2);
			MP[now]=RAND();
			update(1,now.x1,now.x2,now.y1,now.y2,MP[now],1,n);
		}else if (k==2){
			scanf("%d%d%d%d",&now.x1,&now.y1,&now.x2,&now.y2);
			update(1,now.x1,now.x2,now.y1,now.y2,-MP[now],1,n);
		}else{
			scanf("%d%d%d%d",&now.x1,&now.y1,&now.x2,&now.y2);
//			printf("%d %d\n",query(1,now.x1,now.y1,1,n),query(1,now.x2,now.y2,1,n));
			if (query(1,now.x1,now.y1,1,n)==query(1,now.x2,now.y2,1,n)) puts("Yes");
			else puts("No");
		}
	}
}
/*
*/
