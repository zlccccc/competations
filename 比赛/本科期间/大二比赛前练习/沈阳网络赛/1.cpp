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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

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
int len;
multiset<int> now;
int sa[maxn],r[maxn];
LL calc(LL x){
	LL ret=0;
	int i;
	if (x==1){
		ret=len*(len+1)/2;
		FOR(i,1,len) ret-=height[i];
	}else{
		now.clear();
		FOR(i,1,x-1) now.insert(height[i]);
		FOR(i,x,len){
			int pre=*now.begin();
			now.erase(now.find(height[i-x+1]));
			now.insert(height[i]);
			ret+=max(*now.begin()-pre,0);
		}
	}
//	printf("%d:%d\n",x,ret);
	return ret;
}
int n;
int i;
char a[maxn];
int solve(){
	scanf("%d",&n);
	scanf("%s",a);
	len=strlen(a);
//	puts("ss");
	REP(i,len) r[i]=a[i]-'a'+1;
//	REP(i,len) printf("%d",r[i]);puts("");
	da(r,sa,len,27);
	calheight(r,sa,len);
//	FOR(i,1,len) printf("%d ",sa[i]);puts("");
//	FOR(i,1,len) printf("%d ",height[i]);puts("");
	printf("%lld\n",calc(n)-calc(n+1));
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
10
1
a

1
aa

1
aaa

2
abcabc

3
abcabcabcabc

2
aabbaab

2
aabbaabb

2
aaa

1
aaaa
1
aaab
1
aaaba
1
aaabb
*/
