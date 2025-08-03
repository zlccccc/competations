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
const LL M=5971847;
const LL maxn=1e7+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}
inline LL powMM(LL a,LL b,LL M){
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
	r[n++]=0;//使rank从1开始(sa[0]=n)
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
bool cmp1(char *s1,char *s2){//s1<s2
	int len=strlen(s1),i;
	REP(i,len){
		if (s1[i]>s2[i]) return 1;
		if (s1[i]<s2[i]) return 0;
	}
	return 0;
}
bool cmp2(char *s1,char *s2){
	int len=strlen(s1),i;
	REP(i,len){
		if (s1[i]>s2[i]) return 1;
		if (s1[i]<s2[i]) return 0;
	}
	return 1;
}
int HASH[M+7];
int n,q;
int i,j;
char a[maxn];
char b[maxn];
char s[maxn];
int r[maxn];
int sa[maxn];
int tot;
int L,R,mid,ll,rr;
LL c[maxn],d[maxn],k;
const LL H=29;
int main()
{
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&q);
		memset(HASH,0,sizeof(HASH));
		tot=0;
		REP(i,n){
			scanf("%s",a);
			int len=strlen(a);
			r[tot++]=27;
			REP(j,len){
				r[tot++]=a[j]-'a';
			}
			r[tot++]=28;
			REP(j,len){
				r[tot++]=a[j]-'a';
			}
			k=0;
			REP(j,len) k=(k*H+a[j])%M;
//			printf("Hash k=%d\n",k);
			HASH[k]++;
		}
		r[tot]=0;
		REP(i,tot) r[i]++;
		da(r,sa,tot,30);
		REP(i,tot) r[i]--;
		REP(i,tot) s[i]=r[i]+'a';
		s[tot]=0;
//		printf("%s\n",s);
//		FOR(i,1,tot) printf("%2d  %2d  %s\n",sa[i],i,s+sa[i]);
		REP(i,q){
			scanf("%s%s",a,b);
			int len1=strlen(a),len2=strlen(b);
//			printf("%s%s  %d %d\n",a,b,len1,len2);
			int cnt=len2;
			k=0;
			REP(j,len1){
				k=(k*H+a[j])%M;
				c[j]=k;
			}
			k=0;
			REP(j,len2){
				k=(k*H+b[j])%M;
				d[j]=k;
			}
			b[cnt++]=28+'a';
			REP(j,len1) b[cnt++]=a[j];
			b[cnt++]='\0';
			L=1;R=tot+1;
			while (L+1<R){
				mid=(L+R)/2;
				if (cmp1(b,s+sa[mid])) L=mid;
				else R=mid;
			}
			ll=L;
			L=1;R=tot+1;
			while (L+1<R){
				mid=(L+R)/2;
				if (cmp2(b,s+sa[mid])) L=mid;
				else R=mid;
			}
			rr=R;
			k=0;
			REP(j,min(len1,len2)){
				k=(k*H+a[len1-j-1])%M;
				LL now=0;
				if (len1-j-2>=0) now=c[len1-j-2]*powMM(H,len2,M)%M;
				now=(now+d[len2-1])%M;
//				printf("%d  %d^%d %d   \n",c[len1-j-2],H,len2,powMM(H,len2));
//				printf("hash k=%d,kk=%d  %d %d   all=%d\n",k,d[j],len1-j-1,j,now);
				if (k==d[j]) rr-=HASH[now];
			}
//			printf("check: %s\n",b);
//			printf("ll=%d , rr=%d\n",ll,rr);
			printf("%d\n",rr-ll-1);
		}
	}
}
/*
*/
