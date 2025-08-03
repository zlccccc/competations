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
const LL maxn=4e5+107;
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
// char str[maxn];

int A[maxn];
ll val[maxn*4],lazyval[maxn*4],bit[307];//bitset, 标记永久化
ll sum[maxn*4],lazysum[maxn*4];
void change(int x,int len,int mul,ll xo){
	sum[x]=sum[x]*powMM(mul,len)%M;
	lazysum[x]=lazysum[x]*mul%M;
	val[x]=val[x]|xo;
	lazyval[x]|=xo;
}
void pushdown(int x,int L,int mid,int R){
	if (lazyval[x]) {
		change(x<<1,mid-L+1,lazysum[x],lazyval[x]);
		change(x<<1|1,R-mid,lazysum[x],lazyval[x]);
		lazysum[x]=1; lazyval[x]=0;
	}
}
void pushup(int x) {
	sum[x]=sum[x<<1]*sum[x<<1|1]%M;
	val[x]=val[x<<1]|val[x<<1|1];	
}
void build(int x,int l,int r){
	if (l==r) {val[x]=bit[A[l]]; sum[x]=A[l]; return;}
	int mid=(l+r)/2;
	build(x<<1,l,mid); build(x<<1|1,mid+1,r);
	pushup(x); lazysum[x]=1;
}
void update(int x,int l,int r,int v,int L,int R){
	if (l<=L&&R<=r){
		change(x,R-L+1,v,bit[v]); return;
	} int mid=(L+R)/2;
	pushdown(x,L,mid,R);
	if (l<=mid) update(x<<1,l,r,v,L,mid);
	if (mid<r) update(x<<1|1,l,r,v,mid+1,R);
	pushup(x);
}
pll merge(pll A,pll B){
	return make_pair(A.first*B.first%M,A.second|B.second);
}
pair<ll,ll> query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return make_pair(sum[x],val[x]);
	int mid=(L+R)/2;
	pair<ll,ll> ret=make_pair(1,0);
	pushdown(x,L,mid,R);
	if (l<=mid) ret=merge(ret,query(x<<1,l,r,L,mid));
	if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
	pushup(x);
	return ret;
}
int p[1007];//p_val
int chk[1007];
int main() {
	int i,j,C=0;
	FOR(i,2,300) if (!bit[i]){
		for (j=i;j<=300;j+=i) bit[j]|=1ll<<C; 
		chk[C]=powMM((ll)i,M-2)*(i-1)%M; p[C++]=i;
	}
	// REP(i,k) printf("%d ",p[i]); printf("k=%d\n",k);
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%d",&A[i]);
	build(1,1,n);
	while (q--){
		char op[107];
		scanf("%s",op);
		if (op[0]=='T') {
			int l,r; scanf("%d%d",&l,&r);
			pll ans=query(1,l,r,1,n);
			REP(i,62) if ((ans.second>>i)&1) ans.first=ans.first*chk[i]%M;
			printf("%lld\n",ans.first);
		} else {
			int l,r,x; scanf("%d%d%d",&l,&r,&x);
			update(1,l,r,x,1,n);
		}
	}
}
/*
4 4
1 1 1 1
MULTIPLY 1 4 3
TOTIENT 1 4
TOTIENT 3 3
TOTIENT 3 4
MULTIPLY 4 4 3
TOTIENT 4 4
*/