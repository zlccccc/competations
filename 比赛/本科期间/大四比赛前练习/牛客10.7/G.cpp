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

char str[maxn];
int A[maxn];
int T[maxn*4];
void build(int x,int l,int r) {
	if (l==r) {T[x]=A[l]; return;}
	int mid=(l+r)/2;
	build(x<<1,l,mid); build(x<<1|1,mid+1,r);
	T[x]=min(T[x<<1],T[x<<1|1]);
}
int query(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) return T[x];
	int mid=(L+R)/2,ret=INF;
	if (l<=mid) ret=min(ret,query(x<<1,l,r,L,mid));
	if (mid<r) ret=min(ret,query(x<<1|1,l,r,mid+1,R));
	return ret;
}
int main() {
	int n,q,i;
	while (~scanf("%d%d",&n,&q)) {
		scanf("%s",str+1);
		FOR(i,1,n) {
			if (str[i]=='(') A[i]=1; else A[i]=-1;
			A[i]+=A[i-1];
		} build(1,1,n);
		FOR(i,1,q) {
			int l,r; scanf("%d%d",&l,&r);
			if (l>r) swap(l,r);
			if (A[n]!=0) {puts("No"); continue;}
			else {
				int lval,rval;
				if (str[l]=='(') lval=1; else lval=-1;
				if (str[r]=='(') rval=1; else rval=-1;
				if (l!=1) {
					int qq=query(1,1,l-1,1,n);
					if (qq<0) {puts("No"); continue;}
				}
				int ql=query(1,l,r-1,1,n);
				int qr=query(1,r,n,1,n);
				// printf("%d %d; %d %d\n",ql,qr,ql+rval-lval,qr);
				if (ql+rval-lval<0) {puts("No"); continue;}
				if (qr<0) {puts("No"); continue;}
			} puts("Yes");
		}
	}
}
/*
2 3
)(
1 2
2 1
1 2
*/