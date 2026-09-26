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
#include <cassert>
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
const LL MAX=1e6+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int id[maxn],out[maxn],tot;
LL Dep[maxn],IDEP[maxn];
int ID[maxn];
vector<int> edge[maxn];
void dfs(int x){
	id[x]=++tot;int i;
	REP(i,edge[x].size()){
		dfs(edge[x][i]);
	}out[x]=tot;
}
struct node{
	int l,r;LL val;
	node(){l=r=val=0;}
}*T;
int cnt;
void update(int &x,int y,int pos,LL val,int l,int r){
	T[++cnt]=T[y];x=cnt;
	T[x].val+=val;
	if (l==r) return;
	int mid=(l+r)/2;
	if (pos<=mid) update(T[x].l,T[y].l,pos,val,l,mid);
	else update(T[x].r,T[y].r,pos,val,mid+1,r);
}LL query(int x,int l,int r,int L,int R){
	if (!x) return 0;
	if (l<=L&&R<=r) return T[x].val;
	int mid=(L+R)/2;LL ret=0;
	if (l<=mid) ret+=query(T[x].l,l,r,L,mid);
	if (mid<r) ret+=query(T[x].r,l,r,mid+1,R);
	return ret;
}bool cmp(int x,int y){
	return Dep[x]<Dep[y];
}
int r,ans,q;
int n,i;
int *root1,*root2,now1,now2;
int main(){
	#define OPENSTACK
	#ifdef OPENSTACK
			int size = 256 << 20; // 256MB
			char *p = (char*)malloc(size) + size;
			#if (defined _WIN64) or (defined __unix)
				__asm__("movq %0, %%rsp\n" :: "r"(p));
			#else
				__asm__("movl %0, %%esp\n" :: "r"(p));
			#endif
	#endif
	scanf("%d",&n);
	T=new node[maxn*50];
	root1=new int[MAX];root2=new int[MAX];
	memset(T,0,sizeof(T));
	memset(root1,0,sizeof(root1));
	memset(root2,0,sizeof(root2));
	FOR(i,2,n){
		int f,len;
		scanf("%d%d",&f,&len);
		edge[f].emplace_back(i);
		Dep[i]=Dep[f]+len;
	}dfs(1);
	FOR(i,1,n) ID[i]=i;
	sort(ID+1,ID+n+1,cmp);
	FOR(i,1,n) IDEP[i]=Dep[ID[i]];
	rFOR(i,1,n){
		int v=ID[i];
		update(root1[i],root1[i+1],id[v],Dep[v],1,tot);
		update(root2[i],root2[i+1],id[v],1,1,tot);
	}scanf("%d",&q);
	while (q--){
		int x,k;
		scanf("%d%d",&x,&k);
		int pos=lower_bound(IDEP+1,IDEP+n+1,Dep[x]+k)-IDEP;
		printf("%lld\n",query(root1[pos],id[x],out[x],1,tot)-
				 Dep[x]*query(root2[pos],id[x],out[x],1,tot));
	}exit(0);
}
/*
*/
