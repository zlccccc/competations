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
const LL maxn=1e6+107;
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

struct node{
	int l,r;
}T[maxn*4];
int A[maxn];//first
node merge(node x,node y){
	node ret; ret.l=x.l; ret.r=y.r;
	ret.l+=max(0,y.l-x.r);
	ret.r+=max(0,x.r-y.l);
	return ret;
}
inline void build(int x,int l,int r){
	if (l==r) {
		if (!(A[l]&1)) T[x].r=1; else T[x].l=1;
		return;
	} int mid=(l+r)/2;
	build(x<<1,l,mid); build(x<<1|1,mid+1,r);
	T[x]=merge(T[x<<1],T[x<<1|1]);
}
inline node query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return T[x];
	int mid=(L+R)/2; node ret; ret.l=ret.r=0;
	if (l<=mid) ret=merge(ret,query(x<<1,l,r,L,mid));
	if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
	// printf("%d: %d-%d: %d %d; ret=%d %d\n",x,L,R,T[x].l,T[x].r,ret.l,ret.r);
	return ret;
}
int S[maxn],top;
int id[maxn],tot;
int main() {
	int i;
	scanf("%d%d%d",&n,&m,&q);
	FOR(i,1,n) scanf("%d",&A[i]);
	build(1,1,n);
	FOR(i,1,n){
		if (!(A[i]&1)) S[++top]=A[i];
		else {
			if (S[top]+1==A[i]) top--;
			else tot++;
		} id[i]=tot;
	}
	while(q--) {
		int l,r;
		scanf("%d%d",&l,&r);
		if (id[l]!=id[r]) puts("No");
		else {
			node ret=query(1,l,r,1,n);
			if (ret.l==0&&ret.r==0) puts("Yes");
			else puts("No");
		}
	}
}
/*
*/
