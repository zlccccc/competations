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

struct mat{
	int A[2][2];
	mat() {memset(A,0,sizeof(A));}
}now[maxn*4],inv[maxn*4],amat,bmat;
int pinv[maxn*4];
mat merge(const mat &A,const mat &B) {
	mat ret; int i,j,k;
	REP(i,2) REP(j,2) REP(k,2){
		add_(ret.A[i][j],(ll)A.A[i][k]*B.A[k][j]%M);
	} return ret;
}
char str[maxn];
void printmat(const mat now) {
	printf("(%d,%d)(%d %d)\n",now.A[0][0],now.A[0][1],now.A[1][0],now.A[1][1]);
}
void build(int x,int l,int r) {
	if (l==r) {
		if (str[l]=='A') now[x]=amat,inv[x]=bmat;
		else now[x]=bmat,inv[x]=amat;
		// printf("%d - %d: ",l,r); printmat(now[x]);
		return;
	} int mid=(l+r)/2;
	build(x<<1,l,mid); build(x<<1|1,mid+1,r);
	now[x]=merge(now[x<<1],now[x<<1|1]);
	inv[x]=merge(inv[x<<1],inv[x<<1|1]);
	// printf("%d - %d: ",l,r); printmat(now[x]);
}
void inverse(int x) {
	swap(now[x],inv[x]);
	pinv[x]^=1;
}
void pushdown(int x) {
	if (pinv[x]) {
		inverse(x<<1);
		inverse(x<<1|1);
		pinv[x]=0;
	}
}
mat query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) return now[x];
	pushdown(x);
	int mid=(L+R)/2;
	mat ret; ret.A[0][0]=ret.A[1][1]=1;
	if (l<=mid) ret=merge(query(x<<1,l,r,L,mid),ret);
	if (mid<r) ret=merge(ret,query(x<<1|1,l,r,mid+1,R));
	return ret;
}
void update(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) {inverse(x); return;}
	int mid=(L+R)/2;
	pushdown(x);
	if (l<=mid) update(x<<1,l,r,L,mid);
	if (mid<r) update(x<<1|1,l,r,mid+1,R);
	now[x]=merge(now[x<<1],now[x<<1|1]);
	inv[x]=merge(inv[x<<1],inv[x<<1|1]);
}
int main() {
	int n,q,i;
	amat.A[0][0]=amat.A[1][0]=amat.A[1][1]=1;
	bmat.A[0][0]=bmat.A[0][1]=bmat.A[1][1]=1;
	scanf("%d%d",&n,&q);
	scanf("%s",str+1);
	build(1,1,n);
	FOR(i,1,q) {
		int op,l,r,A,B;
		scanf("%d",&op);
		if (op==1) {
			scanf("%d%d",&l,&r);
			update(1,l,r,1,n);
		} else {
			scanf("%d%d%d%d",&l,&r,&A,&B);
			mat now=query(1,l,r,1,n);
			int ansa=((ll)A*now.A[0][0]+(ll)B*now.A[1][0])%M;
			int ansb=((ll)A*now.A[0][1]+(ll)B*now.A[1][1])%M;
			printf("%d %d\n",ansa,ansb);
		}
	}
}
/*
*/