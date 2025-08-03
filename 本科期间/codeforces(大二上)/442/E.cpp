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

int S0[maxn<<2],S1[maxn<<2],A[maxn<<2];
int val[maxn];
void pushdown(int x){
	if (A[x]){
		swap(S0[x<<1],S1[x<<1]);A[x<<1]^=1;
		swap(S0[x<<1|1],S1[x<<1|1]);A[x<<1|1]^=1;
		A[x]=0;
	}
}
void pushup(int x){
	S0[x]=S0[x<<1]+S0[x<<1|1];
	S1[x]=S1[x<<1]+S1[x<<1|1];
}
void build(int x,int L,int R){
	if (L==R) {if (val[L]==0) S0[x]++;else S1[x]++;return;}
	int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	pushup(x);
}
void change(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r){swap(S0[x],S1[x]);A[x]^=1;return;}
	int mid=(L+R)/2;
	pushdown(x);
	if (mid>=l) change(x<<1,l,r,L,mid);
	if (r>mid) change(x<<1|1,l,r,mid+1,R);
	pushup(x);
}
int query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r){return S1[x];}
	int mid=(L+R)/2,ret=0;
	pushdown(x);
	if (mid>=l) ret+=query(x<<1,l,r,L,mid);
	if (r>mid) ret+=query(x<<1|1,l,r,mid+1,R);
	pushup(x);
	return ret;
}
int tot;
int in[maxn],out[maxn];
vector<int> edge[maxn];
void dfs(int x){
	in[x]=++tot;
	for (int v:edge[x]) dfs(v);
	out[x]=tot;
}
int n,i,f,k,m;
char a[5];
int main(){
	scanf("%d",&n);
	FOR(i,2,n) scanf("%d",&f),edge[f].emplace_back(i);
	dfs(1);
	FOR(i,1,n) scanf("%d",&k),val[in[i]]=k;
	build(1,1,n);
	scanf("%d",&m);
	while (m--){
		scanf("%s%d",a,&f);
		if (a[0]=='g'){
			printf("%d\n",query(1,in[f],out[f],1,n));
		}else{
			change(1,in[f],out[f],1,n);
		}
	}
}
/*
*/
