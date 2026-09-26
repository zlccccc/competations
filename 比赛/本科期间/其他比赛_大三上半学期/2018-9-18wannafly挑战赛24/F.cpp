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
const LL M=1004535809;
const LL maxn=4e5+7;
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

namespace NTT {
	const int maxn=1<<20|7;
	const ll MOD=1004535809;
	const ll g=3;
	int wn[maxn],invwn[maxn];
	ll mul(ll x,ll y) {
		return x*y%MOD;
	}
	ll poww(ll a,ll b) {
		ll ret=1;
		for (; b; b>>=1ll,a=mul(a,a))
			if (b&1) ret=mul(ret,a);
		return ret;
	}
	void initwn(int l) {
		static int len=0;
		if (len==l) return; len=l;
		ll w=poww(g,(MOD-1)/len); int i;
		ll invw=poww(w,MOD-2); wn[0]=invwn[0]=1;
		rep(i,1,len) {
			wn[i]=mul(wn[i-1],w);
			invwn[i]=mul(invw,invwn[i-1]);
		}
	}
	void ntt(ll *A,int len,int inv) {
		int i,j,k; initwn(len);
		for (i=1,j=len/2; i<len-1; i++) {
			if (i<j) swap(A[i],A[j]);
			k=len/2;
			while (j>=k) j-=k,k/=2;
			if (j<k) j+=k;
		} for (i=2; i<=len; i<<=1) {
			for (j=0; j<len; j+=i) {
				for (k=j; k<(j+i/2); k++) {
					ll a,b; a=A[k];
					if (inv==-1) b=mul(A[k+i/2],invwn[(ll)(k-j)*len/i]);
					else b=mul(A[k+i/2],wn[(ll)(k-j)*len/i]);
					A[k]=(a+b); (A[k]>=MOD) &&(A[k]-=MOD);
					A[k+i/2]=(a-b+MOD); (A[k+i/2]>=MOD) &&(A[k+i/2]-=MOD);
				}
			}
		} if (inv==-1) {
			ll vn=poww(len,MOD-2);
			REP(i,len) A[i]=mul(A[i],vn);
		}
	}
	void mul(ll *A,ll *B,ll *C,int len) { //C=A*B
		int i;
		ntt(A,len,1); ntt(B,len,1);
		REP(i,len) C[i]=mul(A[i],B[i]);
		ntt(C,len,-1);
	}
	static ll A[maxn],B[maxn],C[maxn];
	void multiply(vector<ll> &a,vector<ll> &b,vector<ll> &ans) {//C=A*B(actual)
		int len=1,i; int n=a.size(),m=b.size();
		while (len<n+m-1) len<<=1;
		REP(i,n) A[i]=a[i]; rep(i,n,len) A[i]=0;
		REP(i,m) B[i]=b[i]; rep(i,m,len) B[i]=0;
		mul(A,B,C,len);
		REP(i,n+m-1) ans[i]=C[i];
	}
}
vector<ll> P[maxn];
int A[maxn],v[maxn];
void solve(int x,int l,int r){
	if (l==r){
		P[x].push_back(1);
		P[x].push_back(M-v[l]);
		return;
	} else {
		int mid=(l+r)/2;
		solve(x<<1,l,mid);
		solve(x<<1|1,mid+1,r);
		P[x].resize(P[x<<1].size()+P[x<<1|1].size()-1);
		NTT::multiply(P[x<<1],P[x<<1|1],P[x]);
	}
}
int main() {
	int n,k,i,j;
	scanf("%d%d",&n,&k);
	FOR(i,1,k) scanf("%d",&v[i]);
	FOR(i,1,k) scanf("%d",&A[i]);
	if (n<=k) return 0*printf("%d",A[n]);
	solve(1,1,k);
	FOR(i,k+1,n){
		FOR(j,1,k) {
			A[i]=(A[i]-A[i-j]*P[1][j]%M+M)%M;
		}
	} printf("%d",A[n]);
}
/*
*/
