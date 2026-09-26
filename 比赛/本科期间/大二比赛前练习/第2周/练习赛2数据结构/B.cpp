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
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=5e5+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
//STACK MLE... 
vector<int> TOP[300000*4+7];//pos 
int cnt;
void build(int x,int l,int r){
	TOP[x].push_back(INF);
	if (l==r) return;
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void add(int x,int val,int l,int r,int L,int R){
	if (l<=L&&R<=r) {if (*TOP[x].rbegin()>=val) TOP[x].push_back(val);return;}
	int mid=(L+R)/2;
	if (mid>=l) add(x<<1,val,l,r,L,mid);
	if (r>mid) add(x<<1|1,val,l,r,mid+1,R);
}
void del(int x,int val,int l,int r,int L,int R){
	if (l<=L&&R<=r) {if (*TOP[x].rbegin()==val) TOP[x].pop_back();return;}
	int mid=(L+R)/2;
	if (mid>=l) del(x<<1,val,l,r,L,mid);
	if (r>mid) del(x<<1|1,val,l,r,mid+1,R);
}
int query(int x,int pos,int l,int r){
	if (l==r) return *TOP[x].rbegin();
	int mid=(l+r)/2;
	if (mid>=pos) return min(*TOP[x].rbegin(),query(x<<1,pos,l,mid));
	return min(*TOP[x].rbegin(),query(x<<1|1,pos,mid+1,r));
}
int n,m;
int i;
char a[5];
int S[maxn],SL[maxn],SR[maxn],pos;
int ans[maxn];
int l,r,val;
int main()
{
	freopen("invazia.in","r",stdin);
	freopen("invazia.out","w",stdout);
	scanf("%d%d",&n,&m);
	build(1,1,n);
	pos=0;
	REP(i,m){
		scanf("%s",a);
		if (a[0]=='I'){
			scanf("%d%d%d",&l,&r,&val);
			S[pos]=val;SL[pos]=l;SR[pos]=r;
			pos++;
			add(1,val,l,r,1,n);
		}else if (a[0]=='E') pos--,del(1,S[pos],SL[pos],SR[pos],1,n);
		else if (a[0]=='R'){
			scanf("%d",&l);
			int t=query(1,l,1,n);
			if (t==INF) puts("GUITZZZ!");
			else printf("%d\n",t);
		}
	}
	return 0;
}
/*
*/
