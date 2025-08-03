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

struct Tnode{
	int l,r;
	LL val; 
}T[maxn*100];
int tot;
void Update(int &x,int pos,int L,int R){
	if (!x) x=++tot; 
	T[x].val++;
	if (L==R) return;
	int mid=(L+R)/2;
	if (mid>=pos) Update(T[x].l,pos,L,mid);
	else Update(T[x].r,pos,mid+1,R);
}
LL Query(int x,int l,int r,int L,int R){
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].val;
	int mid=(L+R)/2;
	LL ret=0;
	if (mid>=l) ret+=Query(T[x].l,l,r,L,mid);
	if (r>mid) ret+=Query(T[x].r,l,r,mid+1,R);
	return ret;
}
int n;
int root[maxn];
inline int lowbit(int x){
	return x&-x;
}
void update(int posy,int posz){
	while (posy<=n){
		Update(root[posy],posz,1,n);
		posy+=lowbit(posy);
	}
}
LL query(int posy,int posz){
	LL ret=0;
	while (posy){
		ret+=Query(root[posy],1,posz,1,n);
		posy-=lowbit(posy);
	}
	return ret;
}
struct node{
	int x,y,z;
}a[maxn];
bool cmp(node a,node b){
	if (a.x!=b.x) return a.x<b.x;
	if (a.y!=b.y) return a.y>b.y;
	return a.z>b.z;
}
int main(){
	scanf("%d",&n);
	int i;
	REP(i,n) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	sort(a,a+n,cmp);
	LL ans=1ll*n*(n-1)/2;
	REP(i,n){
		ans-=query(a[i].y,a[i].z);
		update(a[i].y,a[i].z);
	}
	printf("%lld\n",ans);
}
/*
*/
