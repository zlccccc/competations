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
const LL maxn=5e4+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int k,p;
struct node{
	LL A[2][2];
	node(LL a=1,LL b=0,LL c=0,LL d=1){
		A[0][0]=a;A[0][1]=b;A[1][0]=c;A[1][1]=d;
	}
};
node operator *(node a,node b){
	int i,j,k;
	node ret;
	REP(i,2)
		REP(j,2)
			ret.A[i][j]=(a.A[i][0]*b.A[0][j]%p+a.A[i][1]*b.A[1][j]%p)%p;
	return ret;
}
node POW(node a,LL num){
	node ret;
	while (num){
		if (num&1) ret=ret*a;
		a=a*a;num/=2;
	}
	return ret;
}
int n,m;
int i,j;
LL s[maxn];
node sum[maxn<<2],a[maxn];
void build(int x,int l,int r){
	if (l==r) {sum[x]=a[l]; return;}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	sum[x]=sum[x<<1]*sum[x<<1|1];
}
node query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return sum[x];
	node ret;
	int mid=(L+R)/2;
	if (mid>=l) ret=ret*query(x<<1,l,r,L,mid);
	if (r>mid) ret=ret*query(x<<1|1,l,r,mid+1,R);
	return ret;
}
node ans,all;
void moveto(int now,int should,node &a){
	if (now==should) return;
	a=a*POW(all,(should-now)/n);now+=(should-now)/n*n;
	int k1=now%n+1,k2=(should-1)%n+1;
	if (k1<k2) a=a*query(1,k1,n,1,n)*query(1,1,k2,1,n);
	else a=a*query(1,k1,k2,1,n);
}
pair<LL,LL> b[maxn];
int main(){
	scanf("%d%d",&k,&p);
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&s[i]);s[n+1]=s[1];
	FOR(i,1,n) a[i]=node(0,s[i]%p,1,s[i+1]%p);
	FOR(i,1,n) all=all*a[i];
	scanf("%d",&m);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~test~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	FOR(i,n+1,1000) s[i]=s[i-n];
	REP(i,m){
		int t,tt;
		scanf("%d%d",&t,&tt);
		s[t+1]=tt;
	}
	FOR(i,1,k) printf("%d ",s[i]);puts("");
	LL AA[1000];
	ans=node(0,1,0,0);
	AA[1]=1;AA[0]=0;
	FOR(i,2,k) AA[i]=(s[i]*AA[i-1]%p+s[i-1]*AA[i-2]%p)%p;
//	FOR(i,0,k) printf("%lld ",AA[i]);puts("");
	FOR(i,1,1000) a[i]=node(0,s[i]%p,1,s[i+1]%p);
	FOR(i,1,k){
//		printf("%d ",ans.A[0][0]);
		printf("a=  %d  %d  %d  %d\n",a[i].A[0][0],a[i].A[0][1],a[i].A[1][0],a[i].A[1][1]);
		printf("now=%d ans=%d  %d  %d  %d\n",i-1,ans.A[0][0],ans.A[0][1],ans.A[1][0],ans.A[1][1]);
		ans=ans*a[i];
	}
	printf("%d\n",ans.A[0][0]);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~test~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
	build(1,1,n);
	REP(i,m) {scanf("%d%d",&b[i].first,&b[i].second);b[i].first++;}
	sort(b,b+m);
	int now=0;
	i=0;
	ans=node(0,1,0,0);
	REP(i,m){
		if (b[i].first>k) break;
		moveto(now,b[i].first-1,ans);
		printf("%d  ",now);
		printf("ans=%d  %d  %d  %d\n",ans.A[0][0],ans.A[0][1],ans.A[1][0],ans.A[1][1]);
		if (now!=b[i].first){
			ans=ans*node(0,s[(b[i].first-1)%n+1]%p,1,b[i].second%p);
			now++;
		}
		if (now==k) break;
		if (b[i+1].first==b[i].first)
			ans=ans*node(0,b[i].second%p,1,b[i+1].second%p);
		else ans=ans*node(0,b[i].second%p,1,s[i%n+1]%p);
		now++;
	}
	moveto(now,k,ans);
	printf("%d\n",ans.A[0][0]);
*/
}
/*
10 8
3
1 2 1
2
7 3
5 4


6 1248493
5
5 2 4 1 6
5
9 3
8 4
21 21
10 18
24 10

*/
