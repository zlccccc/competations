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
const LL maxn=2e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

struct node{
	int len,ans;
	node(int L=0,int A=0):len(L),ans(A){}
};
node max(node a,node b){
	if (a.ans==b.ans) return a.len<b.len?a:b;
	return a.ans>b.ans?a:b;
}
node MAX[maxn*4];
void update(int x,int l,int r,int val,int len,int L,int R){
//	printf("UP:%d l,r=%d %d  L,R=%d %d MAX=%d\n",x,l,r,L,R,MAX[x]);
	if (l<=L&&R<=r) {MAX[x]=max(MAX[x],node(len,val));return;}
	int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,val,len,L,mid);
	if (r>mid) update(x<<1|1,l,r,val,len,mid+1,R);
}
node query(int x,int pos,int l,int r){
//	printf("Q:%d pos=%d L,R=%d %d  MAX=%d\n",x,pos,l,r,MAX[x]);
	if (l==r) return MAX[x];
	int mid=(l+r)/2;
	if (mid>=pos) return max(MAX[x],query(x<<1,pos,l,mid));
	return max(MAX[x],query(x<<1|1,pos,mid+1,r));
}
//后缀数组 
int wa[maxn],wb[maxn],wv[maxn],ws1[maxn];
int cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m){
	r[n++]=0;
	int i,j,p,*x=wa,*y=wb,*t;
	REP(i,m) ws1[i]=0;
	REP(i,n) ws1[x[i]=r[i]]++;
	rep(i,1,m) ws1[i]+=ws1[i-1];
	rREP(i,n) sa[--ws1[x[i]]]=i;
	for (j=1,p=1;p<n;j<<=1,m=p){
		p=0;rep(i,n-j,n) y[p++]=i;
		REP(i,n) if (sa[i]>=j) y[p++]=sa[i]-j;
		REP(i,n) wv[i]=x[y[i]];
		REP(i,m) ws1[i]=0;
		REP(i,n) ws1[wv[i]]++;
		rep(i,1,m) ws1[i]+=ws1[i-1];
		rREP(i,n) sa[--ws1[wv[i]]]=y[i];
		t=x,x=y,y=t;
		p=1,x[sa[0]]=0;
		rep(i,1,n) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
int rnk[maxn],height[maxn];
void calheight(int *r,int *sa,int n){
	int i,j,k=0;
	FOR(i,1,n) rnk[sa[i]]=i;
	REP(i,n){
		if (k) k--;
		j=sa[rnk[i]-1];
		while (r[i+k]==r[j+k]) k++;
		height[rnk[i]]=k;
	}
}
//LEN 二分,俩log 
int MINLEN[maxn*4];
void buildLEN(int x,int l,int r){
	if (l==r) {
		MINLEN[x]=height[l];
		return;
	}
	int mid=(l+r)/2;
	buildLEN(x<<1,l,mid);
	buildLEN(x<<1|1,mid+1,r);
	MINLEN[x]=min(MINLEN[x<<1],MINLEN[x<<1|1]);
}
int queryLEN(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return MINLEN[x];
	int mid=(L+R)/2,ret=INF;
	if (mid>=l) ret=min(ret,queryLEN(x<<1,l,r,L,mid));
	if (r>mid) ret=min(ret,queryLEN(x<<1|1,l,r,mid+1,R));
//	printf("Q LEN:%d %d %d %d %d %d\n",x,l,r,L,R,ret);
	return ret;
}
// 能查到的点 
int MINPOS[maxn*4];
void buildPOS(int x,int l,int r){
	MINPOS[x]=INF;
	if (l==r) return;
	int mid=(l+r)/2;
	buildPOS(x<<1,l,mid);
	buildPOS(x<<1|1,mid+1,r);
}
void changePOS(int x,int pos,int val,int l,int r){
	if (l==r){
		MINPOS[x]=val;
		return;
	}
	int mid=(l+r)/2;
	if (mid>=pos) changePOS(x<<1,pos,val,l,mid);
	else changePOS(x<<1|1,pos,val,mid+1,r);
	MINPOS[x]=min(MINPOS[x<<1],MINPOS[x<<1|1]);
}
int queryPOS(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return MINPOS[x];
	int mid=(L+R)/2,ret=INF;
	if (mid>=l) ret=min(ret,queryPOS(x<<1,l,r,L,mid));
	if (r>mid) ret=min(ret,queryPOS(x<<1|1,l,r,mid+1,R));
//	printf("Q LEN:%d %d %d %d %d %d\n",x,l,r,L,R,ret);
	return ret;
}
int n,m;
int i;
char a[maxn];
int L,R,MID,LI,RI;
int r[maxn],sa[maxn],pos[maxn];
int ans;
stack<int> S;
void queryLR(int lenT){
	LI=rnk[i];
	L=1;R=rnk[i]-1;
	while (L<=R){
//		printf("BINERY 1:%d %d\n",L,R);
		MID=(L+R)/2;
		if (queryLEN(1,MID+1,rnk[i],1,n)>=lenT) LI=MID,R=MID-1;//OK
		else L=MID+1;
	}
	RI=rnk[i];
	L=rnk[i]+1;R=n;
	while (L<=R){
//		printf("BINERY 2:%d %d\n",L,R);
		MID=(L+R)/2;
		if (queryLEN(1,rnk[i]+1,MID,1,n)>=lenT) RI=MID,L=MID+1;
		else R=MID-1;
	}
}
int main(){
	scanf("%d",&n);
	scanf("%s",a);
	REP(i,n) r[i]=a[i]-'a'+1; 
	da(r,sa,n,27);
	calheight(r,sa,n);
//	FOR(i,1,n) printf("%-20s i=%d , height=%d\n",a+sa[i],sa[i],height[i]);
	buildLEN(1,1,n);
	buildPOS(1,1,n);
	rREP(i,n){
		int len=1;
		node t=query(1,rnk[i],1,n);
//		printf("Qureying prelen==%d %d\n",t.len,t.ans);
		if (t.len!=0){
			queryLR(t.len);
//			printf("Querypos=%d  ",queryPOS(1,LI,RI,1,n));
			len=t.len+queryPOS(1,LI,RI,1,n)-i;
		}
		changePOS(1,rnk[i],i,1,n);
		queryLR(len);
		ans=max(ans,t.ans+1);
//		printf("len=%2d   ",len);
//		printf("Changeing ::rank=%-3d,%-3d  nowans = %-3d\n",LI,RI,t.ans+1);
		update(1,LI,RI,t.ans+1,len,1,n);
	}
//	FOR(i,1,n) printf("%d ",height[i]);puts("");
//	FOR(i,1,n) printf("%d ",sa[i]);puts("");
	printf("%d\n",ans);
}
/*
*/
