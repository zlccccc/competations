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
const LL maxn=5e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

const int MAXN=500000;
struct node{
	int l,r,val;
}T[maxn*160];
//维护val //left,right各一个 
int cnt=0;
void update(int &x,int y,int L,int R,int val,int l,int r){
	T[++cnt]=T[y];T[cnt].val=val;x=cnt;
	if (l==r) return;
	int mid=(l+r)/2;
	if (mid>=L) update(T[x].l,T[y].l,L,R,l,mid);
	if (R>mid) update(T[x].r,T[y].r,L,R,mid+1,r);
}
int query(int x,int pos,int l,int r){
	if (x==0) return -1;
	if (l==r) return T[x].val;
	int mid=(l+r)/2;
	if (mid>=pos) return query(T[x].l,pos,l,mid);
	else return query(T[x].r,pos,mid+1,r);
}
int left[maxn],right[maxn];

int main()
{
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&k);
		tot=0;
		FOR(i,1,n) scanf("%d",a[i]);
		memset(left,0,sizeof(left));
		memset(right,0,sizeof(right));
		FOR(i,1,n) update(left[i],left[i-1],1,a[i]i,1,n);
		rFOR(i,1,n) update(right[i],right[i+1],1,a[i],i,1,n);
		FOR(i,1,n){
			now=i;
			le[1]=i;
			FOR(i,2,k) le[i]=query(left[le[i]-1],a[i],1,n);
			ri[1]=i;
			FOR(i,2,k) ri[i]=query(left[ri[i]+1],a[i],1,n);
			FOR(j,1,k){
				
			}
		}
	}
	return 0;
}
/*
*/
