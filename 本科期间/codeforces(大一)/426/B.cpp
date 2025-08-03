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
const LL maxn=35007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int mx[maxn*4],lazy[maxn*4];
inline void change(int x,int i){
	mx[x]+=i;
	lazy[x]+=i;
}
inline void pushdown(int x){
	if (lazy[x]){
		change(x<<1,lazy[x]);
		change(x<<1|1,lazy[x]);
		lazy[x]=0;
	}
}
inline void pushup(int x){
	mx[x]=max(mx[x<<1],mx[x<<1|1]);
}
void build(int x,int l,int r){
	mx[x]=lazy[x]=0;
	if (l==r) return;
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void update(int x,int l,int r,int L,int R,int val){
	if (l<=L&&R<=r){
		change(x,val);
		return;
	}
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,L,mid,val);
	if (r>mid) update(x<<1|1,l,r,mid+1,R,val);
	pushup(x);	
}
int query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r){
		return mx[x];
	}
	pushdown(x);
	int mid=(L+R)/2,ret=0;
	if (mid>=l) ret=max(ret,query(x<<1,l,r,L,mid));
	if (r>mid) ret=max(ret,query(x<<1|1,l,r,mid+1,R));
	pushup(x);
	return ret;
}
int n,k;
int i,j,t;
int pos[maxn];
int pre[maxn];
int dp[35007][57];
int a[maxn];
int ans;
int main(){
	scanf("%d%d",&n,&k);
	FOR(i,1,n){
		scanf("%d",&a[i]);
	}
	FOR(i,1,n){
		pre[i]=pos[a[i]];
		pos[a[i]]=i;
	}
	FOR(j,1,k){
		build(1,0,n);
		FOR(i,j,n){
			update(1,pre[i]+1,i,0,n,1);//Õâ¸öµãÇÐ 
			update(1,i,i,0,n,dp[i-1][j-1]);
			dp[i][j]=query(1,1,i,0,n);
		}
	}
	printf("%d\n",dp[n][k]);
}
/*
*/
