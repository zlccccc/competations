#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

//l~r不少于k次的连续子序列最大长度 
#define x x_x
#define y y_y
struct node{
	int l,r,sum;
}T[maxn*40];
int cnt,root[maxn];
void update(int l,int r,int &x,int y,int pos,int v){
	T[++cnt]=T[y],T[cnt].sum+=v,x=cnt;
	if (l==r) return;
	int mid=(l+r)/2;
	if (mid>=pos) update(l,mid,T[x].l,T[y].l,pos,v);
	else update(mid+1,r,T[x].r,T[y].r,pos,v);
}
int query(int l,int r,int x,int y,int L,int R){
	if (L<=l&&r<=R) return T[y].sum-T[x].sum;
	int mid=(l+r)/2;
	int sum=0;
	if (mid>=L) sum+=query(l,mid,T[x].l,T[y].l,L,R);
	if (R>mid) sum+=query(mid+1,r,T[x].r,T[y].r,L,R);
	return sum;
}
queue<int> Q[maxn];
int a[maxn];
int n,k,m;
int i,j,l,r,ans;
int main(){
	scanf("%d%d",&n,&k);
	FOR(i,1,n){
		scanf("%d",&a[i]);
		Q[a[i]].push(i);
		if (Q[a[i]].size()<=k)
			update(1,n,root[i],root[i-1],i,1);
		else{
			update(1,n,root[i],root[i-1],Q[a[i]].front(),-1);
			update(1,n,root[i],root[i],i,1);
			Q[a[i]].pop();
		}
	}
	scanf("%d",&m);
	ans=0;
	REP(i,m){
		scanf("%d%d",&l,&r);
		l=(l+ans)%n+1;
		r=(r+ans)%n+1;
		if (l>r) swap(l,r);
		ans=query(1,n,root[l-1],root[r],l,r);
		printf("%d\n",ans);
	}
}
/*
*/
