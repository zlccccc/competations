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
inline LL powMM(LL a,LL b){
    LL ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        a=a*a%M;
        b>>=1;
    }
    return ret;
}

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
int n,m;
int i,j,k;
char a[maxn];
int s[maxn];
int st[maxn];
int sa[maxn];
int id[maxn];
int val[maxn];
int tot,now,ans;
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		tot=0;
		FOR(i,1,n){
			scanf("%s",a);
			int len=strlen(a);
			st[tot]=len;
			REP(j,len) id[tot]=i,s[tot++]=a[j]-'a'+1;
			s[tot++]='z'-'a'+i+1;
		}
		s[tot]=0;
//		puts("OK1");
		da(s,sa,tot,26+n+1);
//		puts("OK2");
		calheight(s,sa,tot);
//		puts("OK3");
		now=0;
		FOR(i,1,tot){
			val[i]=max(val[i],now);
			now=min(now,height[i+1]);
			if (st[sa[i]]) now=max(now,height[i+1]),val[i]=INF;
		}
		now=0;
		rFOR(i,1,tot){
			val[i]=max(val[i],now);
			now=min(now,height[i]);
			if (st[sa[i]]) now=max(now,height[i]),val[i]=max(val[i],st[sa[i]]);
		}
//		FOR(i,1,tot) printf("%d ",s[i]);puts("");
//		FOR(i,1,tot) printf("%d ",sa[i]);puts("");
//		FOR(i,1,tot) printf("%d ",height[i]);puts("");
//		FOR(i,1,tot) printf("%d ",val[i]);puts("");
		char S[maxn];
		REP(i,tot) S[i]=s[i]+'a'-1;S[tot]=0;
//		printf("%s",S);
//		FOR(i,1,tot) printf("%-30s sa=%3d height=%3d val=%3d\n",S+sa[i],sa[i],height[i],val[i]);
		scanf("%d",&m);
		REP(i,m){
			int x,y,i;
			scanf("%d%d",&x,&y);
			now=0;
			ans=0;
			FOR(i,1,tot){
				if (id[sa[i]]==x&&st[sa[i]]) now=max(now,st[sa[i]]);
				if (id[sa[i]]==y) ans=max(ans,min(now,val[i]));
				now=min(now,height[i+1]);
				if (id[sa[i]]==x) now=max(now,height[i+1]);
			}
			now=0;
			rFOR(i,1,tot){
				if (id[sa[i]]==x&&st[sa[i]]) now=max(now,st[sa[i]]);
				if (id[sa[i]]==y) ans=max(ans,min(now,val[i]));
				now=min(now,height[i]);
				if (id[sa[i]]==x) now=max(now,height[i]);
			}
			printf("%d\n",ans);
		}
		FOR(i,1,tot) val[i]=st[i]=0;
	}
}
/*
*/

