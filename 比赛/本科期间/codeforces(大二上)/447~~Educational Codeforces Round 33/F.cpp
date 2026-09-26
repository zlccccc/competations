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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int id[maxn],out[maxn],tot,Dep[maxn];
vector<int> have[maxn];
vector<int> edge[maxn];
void dfs(int x,int fa,int dep){
	Dep[x]=dep;have[dep].emplace_back(x);
	id[x]=++tot;
	for (int v:edge[x]) if (v!=fa){
		dfs(v,x,dep+1);
	}out[x]=tot;
}
struct node{
	int l,r,val;
	node(){l=r=0;val=INF;}
}T[maxn*40];
int cnt;
void update(int &x,int y,int pos,int val,int l,int r){
	T[++cnt]=T[y];x=cnt;
	T[x].val=min(T[x].val,val);
	if (l==r) return;
	int mid=(l+r)/2;
	if (pos<=mid) update(T[x].l,T[y].l,pos,val,l,mid);
	else update(T[x].r,T[y].r,pos,val,mid+1,r);
}
int query(int x,int l,int r,int L,int R){
	if (!x) return INF;
	if (l<=L&&R<=r) return T[x].val;
	int mid=(L+R)/2,ret=INF;
	if (l<=mid) ret=min(ret,query(T[x].l,l,r,L,mid));
	if (mid<r) ret=min(ret,query(T[x].r,l,r,mid+1,R));
	return ret;
}
int r,ans,q;
int n,i;
int root[maxn],now;
int a[maxn];
int main(){
	scanf("%d%d",&n,&r);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].emplace_back(v);
		edge[v].emplace_back(u);
	}dfs(r,0,1);
	FOR(i,1,n){
		for (int v:have[i])
			update(now,now,id[v],a[v],1,tot);
		root[i]=now;
	}
	scanf("%d",&q);
	while (q--){
		int x,y;
		scanf("%d%d",&x,&y);
		x=(x+ans)%n+1;y=(y+ans)%n;
		printf("%d\n",ans=query(root[min(n,Dep[x]+y)],id[x],out[x],1,tot));
	}
}
/*
*/
