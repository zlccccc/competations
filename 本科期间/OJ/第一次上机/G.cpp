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
const LL INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1000000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const LL MAX=INF*10;
struct node{
	int l,r,val;
}T[maxn*40];
int cnt;
inline void update(int &x,LL pos,LL l,LL r){
	if (!x) x=++cnt,T[x].l=T[x].r=T[x].val=0;T[x].val++;
	if (l==r) return;
	LL mid=(l+r)/2;
	if (mid>=pos) update(T[x].l,pos,l,mid);
	else update(T[x].r,pos,mid+1,r);
}
inline int query(int x,LL l,LL r,LL L,LL R){
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].val;
	int ret=0;
	LL mid=(L+R)/2;
	if (mid>=l) ret+=query(T[x].l,l,r,L,mid);
	if (r>mid) ret+=query(T[x].r,l,r,mid+1,R);
//	printf("%d %lld %lld %lld %lld;ret=%d\n",x,l,r,L,R,ret);
	return ret;
}
int root;
int n,i;
LL a[maxn];
int ans;
int main(){
	while (~scanf("%d",&n)){
		REP(i,n) scanf("%I64d",&a[i]);
		int q;
		scanf("%d",&q);
		while (q--){
			int l,r;
			scanf("%d%d",&l,&r);
			if (l>r) swap(l,r);
			ans=0;
			FOR(i,l,r){
				if (a[i]*2+1<MAX) ans+=query(root,a[i]*2+1,MAX,0,MAX);
				update(root,a[i],0,MAX);
			}
			cnt=0;root=0;
			printf("%d\n",ans);
		}
	}
}
/*
*/
