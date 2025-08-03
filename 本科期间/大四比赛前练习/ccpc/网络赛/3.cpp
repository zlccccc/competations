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
const LL M=1e9+7;
const LL maxn=1e5+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int wa[maxn],wb[maxn],wv[maxn],ws1[maxn];
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
int rnk[maxn],height[maxn];
void calheight(int *r,int *sa,int n){
	int i,j,k=0;
	FOR(i,1,n) rnk[sa[i]]=i;
	REP(i,n){//线性按照从前往后找,充分利用性质 
		if (k) k--;
		j=sa[rnk[i]-1];
		while (r[i+k]==r[j+k]) k++;
		height[rnk[i]]=k;
	}
}
int sa[maxn],r[maxn];
char str[maxn];
struct node{
	int l,r,val;
}T[maxn*32]; int tot;
void update(int &x,int pos,int L,int R) {
	T[++tot]=T[x]; x=tot; T[x].val++;
	if (L==R) return;
	int mid=(L+R)/2;
	if (pos<=mid) update(T[x].l,pos,L,mid);
	else update(T[x].r,pos,mid+1,R);
}
int query(int x,int y,int cnt,int L,int R) {
	if (L==R) return L;
	int mid=(L+R)/2;
	// printf("query: x=%d; y=%d; cnt=%d; val=%d; L,R=%d %d\n",L,R,cnt,T[T[x].l].val-T[T[y].l].val,L,R);
	if (T[T[x].l].val-T[T[y].l].val<cnt) {
		cnt-=T[T[x].l].val-T[T[y].l].val;
		return query(T[x].r,T[y].r,cnt,mid+1,R);
	} else {
		return query(T[x].l,T[y].l,cnt,L,mid);
	}
}
int pre[maxn][20],suf[maxn][20];
int root[maxn];
int main(){
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int n,q,i;
		scanf("%d%d",&n,&q);
		scanf("%s",str);
		REP(i,n) r[i]=str[i]-'a'+1;
		da(r,sa,n,27);
		calheight(r,sa,n);
		// REP(i,n+1) printf("%d ",sa[i]); puts("sa");
		// FOR(i,1,n) printf("%-2d: %s  %d\n",i,str+sa[i],height[i]);
		// REP(i,n) printf("%d ",rnk[i]); puts("rnk");
		tot=0;
		FOR(i,1,n) {
			root[i]=root[i-1];
			update(root[i],sa[i]+1,1,n+1);//start_position
			// printf("update %d: %d\n",i,sa[i]+1);
		}
		// FOR(i,1,n) printf("%d ",sa[i]+1); puts("sa+1,update");
		// puts("okay");
		FOR(i,1,n) {
			pre[i][0]=height[i]; int k;
			rep(k,1,20) {
				if (i-(1<<k)+1<1) pre[i][k]=0;
				else pre[i][k]=min(pre[i][k-1],pre[i-(1<<(k-1))][k-1]);
			}
		}
		rFOR(i,1,n) {
			suf[i][0]=height[i]; int k;
			rep(k,1,20) {
				if (i+(1<<k)-1>n) suf[i][k]=0;
				else suf[i][k]=min(suf[i][k-1],suf[i+(1<<(k-1))][k-1]);
			}
		}
		FOR(i,1,q) {
			int l,r,k;
			scanf("%d%d%d",&l,&r,&k);
			int L=rnk[l-1],R=rnk[l-1]+1,o;
			// printf("l,r=%d %d\n",L,R);
			rREP(o,20) if (pre[L][o]>=r-l+1) L-=1<<o;
			rREP(o,20) if (suf[R][o]>=r-l+1) R+=1<<o; R--;
			// printf("query %d -> %d\n",L,R);
			int ans=query(root[R],root[L-1],k,1,n+1);
			if (ans<=n) printf("%d\n",ans);
			else printf("-1\n");
		}
	}
}
/*
2
12 6
aaabaabaaaab
*/