#include <sstream>
#include <fstream>
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
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+27;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}


int wa[maxn*3],wb[maxn*3],wv[maxn*3],ws1[maxn*3];
int cmp(int *r,int a,int b,int l){
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
//sa->pos(后缀排名->pos)
void da(int *r,int *sa,int n,int m){
	r[n++]=0;//使rank从1开始(sa[0]=n)
	int i,j,p,*x=wa,*y=wb,*t;
	REP(i,m) ws1[i]=0;//pre-cmp
	REP(i,n) ws1[x[i]=r[i]]++;//r->x
	rep(i,1,m) ws1[i]+=ws1[i-1];
	rREP(i,n) sa[--ws1[x[i]]]=i;//sort(计数排序)
	for (j=1,p=1;p<n;j<<=1,m=p){//j->2^x
		p=0;rep(i,n-j,n) y[p++]=i;//最后j个是不用加(显然) 
		REP(i,n) if (sa[i]>=j) y[p++]=sa[i]-j;//后缀顺序
		REP(i,n) wv[i]=x[y[i]];//x+y->wv(由于后缀顺序)
		REP(i,m) ws1[i]=0;
		REP(i,n) ws1[wv[i]]++;
		rep(i,1,m) ws1[i]+=ws1[i-1];
		rREP(i,n) sa[--ws1[wv[i]]]=y[i];//sort(计数排序)
		t=x,x=y,y=t;
		p=1;x[sa[0]]=0;
		rep(i,1,n) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}

int len,lenl,lenr;
inline int lowbit(int x){return x&-x;}
int val[maxn];//后方那个不是0
inline void add(int x,int _val){
	x++;
	// printf("add %d: %d\n",x,_val);
	for (;x<=len;x+=lowbit(x)) add_(val[x],_val);
}
inline int query(int x){
	int ret=0; x++;
	// printf("x=%d\n",x);
	for (;x;x-=lowbit(x)) add_(ret,val[x]);
	return ret;
}
inline int query(int l,int r){
	return (query(r)-query(l-1)+M)%M;
}

int c[maxn*3],sa[maxn*3],rnk[maxn*3];

char l[maxn],r[maxn],s[maxn*3];
int dp[maxn];
int main() {
	int i,j,k;
	scanf("%s%s%s",str,l,r);
	len=strlen(str),lenl=strlen(l),lenr=strlen(r);
	int LEN=0;
	REP(i,len) c[LEN++]=str[i]-'0'+1;
	c[LEN++]=1;// no use
	REP(i,lenl) c[LEN++]=l[i]-'0'+1;
	c[LEN++]=0;
	REP(i,lenr) c[LEN++]=r[i]-'0'+1;
	c[LEN++]=12;
	REP(i,LEN) s[i]=c[i]+'0'-1;
	da(c,sa,LEN,13);
	REP(i,LEN) rnk[sa[i]]=i;
	// REP(i,LEN) printf("%d(%d) %s\n",rnk[i],i,s+i);
	int rankl=rnk[len+1];
	int rankr=rnk[len+1+lenl+1];
	// printf("%d %d\n",rankl,rankr);
	add(0,1); dp[0]=1;//start with i
	FOR(i,1,len){
		int L,R;
		if (i-lenl<0) R=-1;
		else if (rnk[i-lenl]>rankl) R=i-lenl;
		else R=i-lenl-1;
		if (i-lenr<0) L=0;
		else if (rnk[i-lenr]<rankr) L=i-lenr;
		else L=i-lenr+1;
		if (L<=R&&R>=0) add_(dp[i],query(L,R));
		if (str[i-1]=='0'&&lenl==1&&l[0]=='0') add_(dp[i],dp[i-1]);
		// printf("%d : (%d,%d)%d  (%d,%d)%d  dp[%d]=%d\n",i,i-lenl,rnk[i-lenl],L,i-lenr,rnk[i-lenr],R,i,dp[i]);
		if (str[i]!='0') add(i,dp[i]);
	}printf("%d\n",dp[len]);
}
/*
111111
1
1
*/
