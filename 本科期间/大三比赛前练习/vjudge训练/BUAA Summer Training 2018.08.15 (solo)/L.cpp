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
const LL maxn=1e5+7;
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

struct node{
	pii max; ll sum;
	int val;//pushdown
}T[maxn<<2];
inline void change(int x,int len,int val){
	T[x].val=val; T[x].sum=(ll)len*val;
}
void pushdown(int x,int len){
	if (T[x].val){
		change(x<<1,len-len/2,T[x].val);
		change(x<<1|1,len/2,T[x].val);
		T[x].val=0;
	}
}
void pushup(int x){
	T[x].sum=T[x<<1].sum+T[x<<1|1].sum;
	T[x].max=max(T[x<<1].max,T[x<<1|1].max);
}
void update(int x,int l,int r,int val,int L,int R){//only need
	if (l>r) return;
	if (l<=L&&R<=r){
        change(x,R-L+1,val);
		// printf("%d - %d: sum=%lld\n",l,r,T[x].sum);
		return;
	} int mid=(L+R)/2;
	pushdown(x,R-L+1);
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
	pushup(x);
}
int A[maxn],H[maxn];
void update(int x,int pos,int L,int R){//only need
//    printf("  update: %d %d %d %d %d\n",x,pos,val,L,R);
	if (L==R){
		max_(T[x].sum,(ll)A[pos]); T[x].max=make_pair(A[pos],pos);
		return;
	} int mid=(L+R)/2;
	pushdown(x,R-L+1);
	if (pos<=mid) update(x<<1,pos,L,mid);
	if (mid<pos) update(x<<1|1,pos,mid+1,R);
	pushup(x);
}
pii query(int x,int l,int r,int L,int R){
	// printf("query: %d %d %d %d %d\n",x,l,r,L,R);
	if (l>r) return make_pair(0,1);
	if (l<=L&&R<=r) return T[x].max;
	pii ret=make_pair(0,0); int mid=(L+R)/2;
	if (l<=mid) {
		pii t=query(x<<1,l,r,L,mid);
		if (t>ret) ret=t;
	} if (mid<r) {
		pii t=query(x<<1|1,l,r,mid+1,R);
		if (t>ret) ret=t;
	} return ret;
}
int queryL(int x,int val,int L,int R){
	if (L==R) return L;
	int mid=(L+R)/2;
	if (T[x<<1].max.first>=val) return queryL(x<<1,val,L,mid);
	else return queryL(x<<1|1,val,mid+1,R);
}
int queryR(int x,int val,int L,int R){
	if (L==R) return R;
	int mid=(L+R)/2;
	if (T[x<<1|1].max.first>=val) return queryR(x<<1|1,val,mid+1,R);
	else return queryR(x<<1,val,L,mid);
}
void build(int x,int L,int R){
    T[x].val=0;
	if (L==R) {
        T[x].max=make_pair(A[L],L); T[x].sum=H[L];
        return;
	} int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	pushup(x);
}
void update(int x){
	pii L=query(1,1,x-1,1,n),R=query(1,x+1,n,1,n);
//	printf("\nupdate (%d): %d %d  %d %d\n",x,L.first,L.second,R.first,R.second);
	if (L.first<A[x]&&R.first<A[x]) {
//        printf("update1: %d %d : %d\n",L.second,x-1,L.first);
//        printf("update1: %d %d : %d\n",x+1,R.second,R.first);
		update(1,L.second+1,x-1,L.first,1,n);
		update(1,x+1,R.second-1,R.first,1,n);
        update(1,x,1,n);
	}else if (L.first<A[x]) {
		int R=queryL(1,A[x],1,n);
//	    printf("update3: %d %d %d\n",x+1,R-1,A[x]);
		update(1,x+1,R-1,A[x],1,n);
        update(1,x,1,n);
	}else if (R.first<A[x]) {
		int L=queryR(1,A[x],1,n);
//	    printf("update2: %d %d %d\n",L+1,x-1,A[x]);
		update(1,L+1,x-1,A[x],1,n);
        update(1,x,1,n);
	}
}
int L[maxn],R[maxn];
int solve() {
	int i; ll all=0;
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%d",&A[i]),all+=A[i];
	A[0]=A[n+1]=0;
	FOR(i,0,n+1) L[i]=R[i]=A[i];
	FOR(i,1,n) max_(L[i],L[i-1]);
	rFOR(i,1,n) max_(R[i],R[i+1]);
	FOR(i,1,n) H[i]=max(min(L[i],R[i]),A[i]);
//	FOR(i,1,n) printf("%d ",H[i]);puts("");
 	build(1,1,n);
// 	FOR(i,1,n) update(i);
 	FOR(i,1,q){
		char op[10];
		scanf("%s",op);
//		printf("sum=%d\n",T[1].sum);
		if (op[0]=='P') printf("%lld\n",T[1].sum-all);//all: wall
		else {
			int x,y;
			scanf("%d%d",&x,&y);
			A[x]+=y; all+=y;
			update(x);
		}
	} return 0;
}
int main() {
	int T; scanf("%d",&T);
	while (T--) solve();
}
/*
*/
