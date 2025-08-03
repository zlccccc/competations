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
const int INF=0x3f3f3f3f;

int n,m;
int c[maxn];
inline int lowbit(int x){
	return x&-x;
}
int presum(int x){
	int ret=0;
	while (x){
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}
int sum(int l,int r){
	return presum(r)-presum(l-1);
}
void add(int x,int d){
	while (x<=n+1){
		c[x]+=d;
		x+=lowbit(x);
	}
}
void init(int n){
	int i;
	FOR(i,1,n+1) c[i]=0;
}

struct node{
	int l,r,i;
}Q[maxn];
int ans[maxn];
bool cmp(node a,node b){
	if (a.l==b.l) return a.r<b.r;
	return a.l<b.l;
}
int prepos[maxn];
int l[maxn],r[maxn];
int a[maxn],b[maxn];
vector<int> L[maxn];
void solve(){
	int i,j,k;
	FOR(i,1,n) scanf("%d",&a[i]),b[i]=a[i];
	FOR(i,1,200000) prepos[i]=0;
	FOR(i,1,n) {
		l[i]=1;
		for (k=2;k*k<=a[i];k++) if (a[i]%k==0){
			l[i]=max(l[i],prepos[k]+1);
			while (a[i]%k==0) a[i]/=k;
			prepos[k]=i;
		}
		if (a[i]!=1){
			k=a[i];
			l[i]=max(l[i],prepos[k]+1);
			prepos[k]=i;
		}
	}
	FOR(i,1,200000) prepos[i]=n+1;
	rFOR(i,1,n) {
		r[i]=n;
		for (k=2;k*k<=b[i];k++) if (b[i]%k==0){
			r[i]=min(r[i],prepos[k]-1);
			while (b[i]%k==0) b[i]/=k;
			prepos[k]=i;
		}
		if (b[i]!=1){
			k=b[i];
			r[i]=min(r[i],prepos[k]-1);
			prepos[k]=i;
		}
	}
//	FOR(i,1,n) printf("%d->%d ",l[i],r[i]);puts("");
	FOR(i,1,n) vector<int>().swap(L[i]);
	FOR(i,1,n) L[l[i]].push_back(i);
	REP(i,m) scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].i=i;
	init(n);
	sort(Q,Q+m,cmp);
	int nowl=0;
	REP(i,m){
		while (nowl<Q[i].l){
			if (nowl!=0) add(nowl,-1),add(r[nowl]+1,1);//a[i]--
			nowl++;
			for (int k:L[nowl]){
//				printf("%d+ ",k);
				add(k,1);
//				printf("%d- ",r[i]+1);
				add(r[k]+1,-1);
			}
		}
//		printf("Q:%d->%d\n",Q[i].l,Q[i].r);
		ans[Q[i].i]=sum(Q[i].l,Q[i].r);
	}
	REP(i,m) printf("%d\n",ans[i]);
}
int main(){
	while (~scanf("%d%d",&n,&m)&&(n||m)) solve();
}
/*
*/
