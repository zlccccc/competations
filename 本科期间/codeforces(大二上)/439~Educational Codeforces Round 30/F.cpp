#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
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
		p=1;x[sa[0]]=0;
		rep(i,1,n) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
int rnk[maxn],pre[maxn],height[maxn];
char a[maxn],b[maxn];
void calheight(int *r,int *sa,int n){
	int i,j,k=0;
	FOR(i,1,n) rnk[sa[i]]=i;
	REP(i,n){
		if (k) k--;
		j=sa[rnk[i]-1];
		while (r[i+k]==r[j+k]) k++;
		height[rnk[i]]=k;
	}
	FOR(i,1,n) if (b[sa[i]]=='1') height[i+1]=min(height[i+1],height[i]);
}
int sa[maxn],r[maxn];
int i,j,k;
int n;
int S[maxn],T[maxn];
int pos;
LL ans;
int main()
{
	scanf("%d",&n);
	scanf("%s%s",a,b);
	ans=n;
	while (ans&&b[ans-1]=='1') ans--;
	reverse(a,a+n);reverse(b,b+n);
	REP(i,n) r[i]=a[i]-'a'+1;
	da(r,sa,n,27);
	calheight(r,sa,n);
//	REP(i,n) printf("%d ",r[i]);puts(""); 
//	FOR(i,1,n) printf("%-40s %d %d,OK:%c\n",a+sa[i],sa[i],height[i],b[sa[i]]);puts("");
	FOR(i,2,n){
		if (b[sa[i]]=='1') continue;
//		printf("%d ",height[i]);
		int addcnt=1;
		while (pos!=0&&S[pos-1]>=height[i]){
			pos--;
			addcnt+=T[pos];
			ans=max(ans,1ll*addcnt*S[pos]);
// 			printf("change: %d %d\n",addcnt,S[pos]);
		}
		S[pos]=height[i],T[pos]=addcnt,pos++;
	}
	int addcnt=0;
	while (pos!=0){
		pos--;
		addcnt+=T[pos];
		ans=max(ans,1ll*(addcnt+1)*S[pos]);
//		printf("change: %d %d\n",addcnt+1,S[pos]);
	}
	printf("%I64d\n",ans);
//	REP(i,n) printf("%d ",rnk[i]);puts("");
//	REP(i,n) printf("%d ",height[rnk[i]]);puts("");
}
/*
*/
