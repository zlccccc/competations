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
const LL M=998244353;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int l,r,val;
}T[maxn*40];
int n,m;
int i,j,k;
int a[maxn];
LL ans,now;
const int MAX=1e9+7;
int cnt;
inline void update(int &x,int pos,int l,int r){
	if (!x) x=++cnt;
	T[x].val++;
	if (l==r) return;
	int mid=(l+r)/2; 
	if (pos<=mid) update(T[x].l,pos,l,mid);
	else update(T[x].r,pos,mid+1,r);
}
inline int query(int x,int l,int r,int L,int R){
//	if (L==0&&R==MAX) printf("%d %d\n",l,r);
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].val;
	int ret=0,mid=(L+R)/2;
	if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
	if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
	return ret;
}
int root;
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n){
		LL p=1,t=1;
		FOR(t,1,9){
			if (p*10-1-a[i]>=0){
//				printf("%d : ",t);
				if (p==1) ans+=query(root,0-a[i],p*10-1-a[i],0,MAX)*t;
				else ans+=query(root,p-a[i],p*10-1-a[i],0,MAX)*t;
			}p*=10;
		}
		ans-=now;
		update(root,a[i],0,MAX);
		if (a[i]==0) now++;
		while (a[i]) a[i]/=10,now++;
	}
	printf("%lld\n",ans);
}
/*
11
0 1 2 3 4 5 6 7 8 9 10
*/
