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

int n;
LL sum[maxn];
inline int lowbit(int x){
	return x&-x;
}
void update(int x,int val){
	while (x<=n){
		sum[x]+=val;
		x+=lowbit(x);
	}
}
LL query(int x){
	LL ret=0;
	while (x){
		ret+=sum[x];
		x-=lowbit(x);
	}
	return ret;
}
struct node{
	int x,y,z;
}a[maxn],p[maxn];
bool cmp(node a,node b){
	if (a.x!=b.x) return a.x<b.x;
	if (a.y!=b.y) return a.y>b.y;
	return a.z>b.z;
}
LL ans;
void solve(int l,int r){
	if (l==r) return;
//	printf("%d %d\n",l,r);
	int mid=(l+r)/2;
	solve(l,mid);
	solve(mid+1,r);
	int t1=l,t2=mid+1,t=l,i;
	while (t1<=mid||t2<=r){
		if (t2>r||(t1<=mid&&a[t1].y<a[t2].y)){
			node &now=p[t++]=a[t1++];
			update(now.z,1);
		}else{
			node &now=p[t++]=a[t2++];
			ans-=query(now.z-1);
		}
	}
	FOR(i,l,mid) update(a[i].z,-1);
	FOR(i,l,r) a[i]=p[i];
}
int main(){
	scanf("%d",&n);
	int i;
	FOR(i,1,n) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	sort(a+1,a+n+1,cmp);
	ans=1ll*n*(n-1)/2;
	solve(1,n);
	printf("%lld\n",ans);
}
/*
*/
