#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
inline LL inv(LL x){
	return powMM(x,M-2);
}
vector<int> edge[maxn];
int in[maxn],out[maxn],fa[maxn];
int tot;
void dfs(int x){
	in[x]=++tot;
	for (int v:edge[x]) dfs(v);
	out[x]=tot;
}
LL lazy[maxn*4],MUL[maxn*4],SUM[maxn*4];
void build(int x,int l,int r){
	lazy[x]=MUL[x]=1;SUM[x]=0;
	if (l==r) return;
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void change(int x,LL val){
	MUL[x]=MUL[x]*val%M;
	SUM[x]=SUM[x]*val%M;
	lazy[x]=lazy[x]*val%M;
}
void pushdown(int x){
	if (lazy[x]!=1){
		change(x<<1,lazy[x]);
		change(x<<1|1,lazy[x]);
		lazy[x]=1;
	}
}
void pushup(int x){
	SUM[x]=(SUM[x<<1]+SUM[x<<1|1])%M;
}
void add(int x,int pos,LL val,int L,int R){
//	printf("		ADDing::::%d %d %d %d %d,\n",x,pos,val,L,R);
	if (L==R){
		SUM[x]=val;
		return;
	}
	int mid=(L+R)/2;
	pushdown(x);
	if (mid>=pos) add(x<<1,pos,val,L,mid);
	else add(x<<1|1,pos,val,mid+1,R);
	pushup(x);
//	printf("                SUM[X]=%d\n",SUM[x]);
}
void mul(int x,int l,int r,LL val,int L,int R){
	if (l<=L&&R<=r){
		change(x,val);
		return;
	}
	int mid=(L+R)/2;
	pushdown(x);
	if (mid>=l) mul(x<<1,l,r,val,L,mid);
	if (r>mid) mul(x<<1|1,l,r,val,mid+1,R);
	pushup(x);
}
LL querysum(int x,int l,int r,int L,int R){
//	printf("		query::::%d %d %d %d %d,\n",x,l,r,L,R);
	if (l<=L&&R<=r) return SUM[x];
	int mid=(L+R)/2;
	LL ret=0;
	pushdown(x);
	if (mid>=l) ret=(ret+querysum(x<<1,l,r,L,mid))%M;
	if (r>mid) ret=(ret+querysum(x<<1|1,l,r,mid+1,R))%M;
	pushup(x);
	return ret;
}
LL querymul(int x,int pos,int L,int R){
//	printf("queryMUL::%d %d %d %d\n",x,pos,L,R);
	if (L==R) return MUL[x];
	LL ret;
	int mid=(L+R)/2;
	pushdown(x);
	if (mid>=pos) ret=querymul(x<<1,pos,L,mid);
	else ret=querymul(x<<1|1,pos,mid+1,R);
	pushup(x);
	return ret;
}
int n;
int i;
bool mark[maxn];
int k[maxn],u[maxn],v[maxn];
LL val[maxn];
int size[maxn];
int NUM;
int L;
int main()
{
	scanf("%d%d",&val[0],&n);
	L=1;mark[1]=1;
	FOR(i,1,n){
		while (mark[L]) L++;
		scanf("%d",&k[i]);
		if (k[i]==1){
			scanf("%d%I64d",&u[i],&val[i]);
			v[i]=L;
			edge[u[i]].push_back(v[i]);
			mark[u[i]]=mark[v[i]]=1;
			fa[v[i]]=u[i];
		}else if (k[i]==2){
			scanf("%d",&u[i]);
		}
	}
	dfs(1);
	NUM=n;
	build(1,1,NUM);
	add(1,in[1],val[0],1,NUM);size[1]=1;
	FOR(i,1,n){
		if (k[i]==1){
//			printf("  ADDEDGE:%d -> %d\n",u[i],v[i]);
//			printf("A :   add:%d   %d * %d\n",in[v[i]],val[i],querymul(1,in[v[i]],1,NUM));
			add(1,in[v[i]],val[i]*querymul(1,in[v[i]],1,NUM)%M,1,NUM);
			mul(1,in[u[i]],out[u[i]],(size[u[i]]+1)*inv(size[u[i]])%M,1,NUM);
//			printf("B :   mul %d %d %d %d\n",in[u[i]],out[u[i]],size[u[i]]+1,inv(size[u[i]]));
			size[u[i]]++;size[v[i]]++;
		}else {
//			printf("Q:in/out:%I64d %I64d\n",in[u[i]],out[u[i]]);
			printf("%I64d\n",querysum(1,in[u[i]],out[u[i]],1,NUM)*inv(querymul(1,in[u[i]],1,NUM))%M*size[u[i]]%M);
//			printf("should:%I64d inv:%I64d %I64d\n",querysum(1,in[u[i]],out[u[i]],1,NUM),querymul(1,in[u[i]],1,NUM),size[u[i]]);
		}
	}
	return 0;
}
/*
*/
