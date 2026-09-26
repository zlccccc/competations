#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=5e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

int a[maxn];
struct node{
	int left,right;
}tree[maxn*4*8];
int val[maxn*4*8],lazy[maxn*4*8];
void change(int x,int i){
	val[x]=max(val[x],i);
	lazy[x]=max(lazy[x],i);
}
void pushdown(int x){
	if (lazy[x]){
		change(x<<1,lazy[x]);
		change(x<<1|1,lazy[x]);
		lazy[x]=0;
	}
}
void build(int x,int l,int r){
	tree[x].left=l;tree[x].right=r;
	val[x]=lazy[x]=0;
	if (l==r) return;
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void update(int x,int l,int r,LL val){
	int L=tree[x].left,R=tree[x].right;
	if (l<=L&&R<=r){
		change(x,val);
		return;
	}
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,val);
	if (r>mid) update(x<<1|1,l,r,val);
}
int query(int x,int pos){
	int L=tree[x].left,R=tree[x].right;
	if (L==R) return val[x];
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=pos) return query(x<<1,pos);
	return query(x<<1|1,pos);
}

int n,m;
char s[maxn*2],str[maxn*4];
int len1,len2,p[maxn*8];
int i,j,k;
int del1[maxn*8],del2[maxn*8];
int ans[maxn*8];
int main(){
	scanf("%d",&n);
	scanf("%s",s);
	rep(i,n,n*2) s[i]=s[i-n];
//	printf("%s\n",s);
//	init();
	int i;
	len1=strlen(s);
	str[0]='+';str[1]='%';
	REP(i,len1+1){
		str[i*2+2]=s[i];
		str[i*2+3]='%';
	}
	len2=len1*2+2;
//	manacher();
	int id=0,mx=0;
	FOR(i,1,len2-1){
		if (mx>i) p[i]=min(p[2*id-i],mx-i);
		else p[i]=1;
		while (str[i+p[i]]==str[i-p[i]]) p[i]++;
		if (p[i]+i>mx){
			mx=p[i]+i;
			id=i;
		}
	}
	REP(i,len2) p[i]--;//manacher
	REP(i,len2) {
		if ((p[i]&1)==(n&1)) p[i]=min(p[i],n);
		else p[i]=min(p[i],n-1);
	}
	build(1,1,len2*2);
	REP(i,len2){
		del1[i-p[i]]=max(del1[i-p[i]],p[i]);
		if (i+p[i]-n*2>=0) del2[i+p[i]-n*2]=max(del2[i+p[i]-n*2],p[i]);
		if (i+p[i]-n*2<i-p[i]&&i-p[i]>0){
//			printf("%d->%d    %d,i=%d\n",max(0,i+p[i]-n*2)+1,max(0,i-p[i])+1,p[i],i);
			update(1,max(0,i+p[i]-n*2)+1,max(0,i-p[i])+1,p[i]);
		}
	}
	mx=0;
	REP(i,len2){
		if (str[i]!='%'&&str[i]!='+') mx-=2;
		mx=max(mx,del1[i]);
		ans[i]=max(ans[i],mx);
	}
	mx=0;
	rREP(i,len2*2){
		if (str[i]!='%'&&str[i]!='+') mx-=2;
		mx=max(mx,del2[i]);
		ans[i]=max(ans[i],mx);
	}
//	REP(i,len2) printf("%d ",query(1,i+1));
	REP(i,len2) ans[i]=max(ans[i],query(1,i+1));
//	REP(i,len2) printf("%3d",i);puts("");
//	REP(i,len2) printf("%3c",str[i]);puts("");
//	REP(i,len2) printf("%3d",p[i]);puts("");
//	REP(i,len2) printf("%3d",ans[i]);puts("");
	REP(i,n) printf("%d\n",max(ans[i*2+1],ans[i*2+2]));
}
