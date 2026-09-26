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
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

inline int poww(int a,int b,int p) {
	// printf("poww: %d %d %d\n",a,b,p);
	int ret=1;
	for (; b; b>>=1,a=(LL)a*a%p)
		if (b&1) ret=(LL)ret*a%p;
	return ret;
}
// 这个比C简单多了...
int p[12],tot;
struct node {
	int mx,c[12],mc,sx;//multi_x; multi_c; [], sumx
	node() {//sc的作用: pushdown少个log
		mc=mx=1; sx=0;
		memset(c,0,sizeof(c));
	}
} T[maxn*4];
int mod;
void pushdown(int x) {
	// if (T[x].mc!=1){
		mul_(T[x<<1].mc,T[x].mc,mod);
		mul_(T[x<<1].sx,T[x].mc,mod);
		mul_(T[x<<1|1].mc,T[x].mc,mod);
		mul_(T[x<<1|1].sx,T[x].mc,mod);
		int i; T[x].mc=1;
		REP(i,tot) {
			T[x<<1].c[i]+=T[x].c[i];
			T[x<<1|1].c[i]+=T[x].c[i];
			T[x].c[i]=0;
		}
	// } if (T[x].mx!=1) {
		mul_(T[x<<1].mx,T[x].mx,mod);
		mul_(T[x<<1].sx,T[x].mx,mod);
		mul_(T[x<<1|1].mx,T[x].mx,mod);
		mul_(T[x<<1|1].sx,T[x].mx,mod);
		T[x].mx=1;
	// }
}
int op,l,r;
int now[12],mx,mc,mul;//好像不是很会一个log
int ans;
void solve(int x,int L,int R) {
	int l=max(L,::l),r=min(R,::r);
	// printf("solve %d %d-%d\n",x,L,R);
	if (l<=L&&R<=r) {
		if (op==1||op==2) {
			int i; mul_(T[x].mx,mx,mod);
			mul_(T[x].mc,mc,mod);
			mul_(T[x].sx,mul,mod);
			REP(i,tot) T[x].c[i]+=now[i];
		} else add_(ans,T[x].sx,mod);
		if (L==R) {//should reset
			int i; T[x].mc=1;
			REP(i,tot) mul_(T[x].mc,poww(p[i],T[x].c[i],mod),mod);
			T[x].sx=(ll)T[x].mx*T[x].mc%mod;
		}
		// printf(" actual %d-%d; l-r=%d-%d: mul*%d*%d sx=%d\n",L,R,l,r,T[x].mx,T[x].mc,T[x].sx);
		return;
	} int mid=(L+R)/2;
	pushdown(x);
	if (l<=mid) solve(x<<1,L,mid);
	if (mid<r) solve(x<<1|1,mid+1,R);
	T[x].sx=(T[x<<1].sx+T[x<<1|1].sx)%mod;
	return;
}
void reset() {
	int i; REP(i,tot) now[i]=0; mul=mx=mc=1;
} 
void setit(int x) {
	int i; mul=x; 
	REP(i,tot) while (x%p[i]==0) now[i]++,x/=p[i];
	mx=x; mc=mul/mx;
}
int main() {
	int q,i,k,_,n; op=1;
	scanf("%d%d",&n,&mod);
	int pwmod=mod;
	for (k=mod,i=2; i*i<=k; i++)
		if (k%i==0) {
			p[tot++]=i; while (k%i==0) k/=i;
		} if (k!=1) p[tot++]=k;
	REP(i,tot) pwmod=pwmod/p[i]*(p[i]-1); pwmod--;
	// REP(i,tot) printf("%d ",p[i]); puts(" <- p");
	FOR(i,1,n) {
		int x;
		scanf("%d",&x);
		reset(); setit(x);
		l=r=i; solve(1,1,n);
	} scanf("%d",&q);
	FOR(_,1,q) {
		int x,i;
		scanf("%d",&op); reset();
		if (op==1) {
			scanf("%d%d%d",&l,&r,&x);
			setit(x);
		} else if (op==2) {
			scanf("%d%d",&l,&x); r=l;
			setit(x);
			REP(i,tot) now[i]=-now[i];
			mx=poww(mx,pwmod,mod);
		} else {
			scanf("%d%d",&l,&r); ans=0;
		} solve(1,1,n);
		if (op==3) printf("%d\n",ans);
	}

}
/*
5 2100
1 2 3 4 5
100
3 2 4
1 1 3 12
1 1 5 10
2 5 50
3 2 4
1 4 4 28
2 4 7
3 1 2
3 3 4
2 3 3
3 1 5

*/