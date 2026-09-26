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
	int l,r,val;
}T[maxn*80];
int cnt;
void update(int &x,int pos,int L,int R){
	if (!x) x=++cnt;
	T[x].val++;
	if (L==R) return;
	int mid=(L+R)/2;
	if (mid>=pos) update(T[x].l,pos,L,mid);
	else update(T[x].r,pos,mid+1,R);
}
int query(int x,int l,int r,int L,int R){
	if (l>r) return 0;
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].val;
	int ret=0,mid=(L+R)/2;
	if (mid>=l) ret+=query(T[x].l,l,r,L,mid);
	if (r>mid) ret+=query(T[x].r,l,r,mid+1,R);
	return ret;
}
int a[maxn];
int ans,now,root;
const int MAX=2000000000;
int main(){
	int n,k;
	int i,j;
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%d",&a[i]),a[i]=max(0,a[i]-i);
	FOR(i,1,n){
		update(root,a[i],0,MAX);
//		printf("U : %d\n",a[i]);
		now=query(root,0,k-i-1,0,MAX);
//		printf("Q : %d\n",k-i-1);
		ans=max(ans,now);
	}
	printf("%d\n",ans);
}
/*
3 10
1 5 3
*/
