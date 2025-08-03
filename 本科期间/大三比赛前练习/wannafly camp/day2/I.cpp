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
const LL maxn=1e6+7;
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
inline ll poww(ll a, ll b,ll M) {
	ll ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace FFT {
	const int maxn=1<<20|7;
	struct complex {
		double a,b;
		complex(double _a=.0,double _b=.0):a(_a),b(_b) {}
		complex operator+(const complex x)const {return complex(a+x.a,b+x.b);}
		complex operator-(const complex x)const {return complex(a-x.a,b-x.b);}
		complex operator*(const complex x)const {return complex(a*x.a-b*x.b,a*x.b+b*x.a);}
	};
	complex wn[maxn];
	void initwn(int l) {
		static int len=0; int i;
		if (len==l) return; else len=l;
		REP(i,len) wn[i]=complex(cos(2*pi*i/l),sin(2*pi*i/l));
	}
	void fft(complex *A,int len,int inv) {
		int i,j,k; initwn(len);
		for (i=1,j=len/2; i<len-1; i++) {
			if (i<j) swap(A[i],A[j]);
			k=len/2;
			while (j>=k) j-=k,k/=2;
			if (j<k) j+=k;
		} for (i=2; i<=len; i<<=1) {
			for (j=0; j<len; j+=i) {
				for (k=j; k<(j+i/2); k++) {
					complex a,b; a=A[k];
					b=A[k+i/2]*wn[(ll)(k-j)*len/i];
					A[k]=a+b; A[k+i/2]=a-b;
				}
			}
		} if (inv==-1) REP(i,len) A[i]=complex(A[i].a/len,A[i].b/len);
	}
	inline complex conj(complex &A) {return complex(A.a,-A.b);}
	void mul(int *A,int *B,int *ans,int len,int mod) { //ans=A*B
		static complex x1[maxn],x2[maxn];
		static complex x3[maxn],x4[maxn];
		static const int S=1<<15 ; int i;
		REP(i,len) x1[i]=complex(A[i]/S,A[i]%S);
		REP(i,len) x2[i]=complex(B[i]/S,B[i]%S);
		fft(x1,len,1); fft(x2,len,1);
		REP(i,len) {//这个k1, b1就是前面的, 这就减掉了一半常数
			int j=(len-i)&(len-1);
			complex k1=(conj(x1[i])+x1[j])*complex(0.5,0);//dft k1
			complex b1=(conj(x1[i])-x1[j])*complex(0,0.5);//dft b1
			complex k2=(conj(x2[i])+x2[j])*complex(0.5,0);//dft k2
			complex b2=(conj(x2[i])-x2[j])*complex(0,0.5);//dft b2
			x3[i]=k1*k2+k1*b2*complex(0,1);
			x4[i]=b1*k2+b1*b2*complex(0,1);
		} fft(x3,len,-1); fft(x4,len,-1);
		REP(i,len) {
			ll kk=x3[i].a+0.5,kb=x3[i].b+0.5;
			ll bk=x4[i].a+0.5,bb=x4[i].b+0.5;
			ans[i]=((kk%mod*S%mod+kb+bk)%mod*S%mod+bb)%mod;
		}
	}
	void mul(ll *A,ll *B,ll *ans,int len) { //ans=A*B
		static complex x1[maxn],x2[maxn];
		static complex x3[maxn],x4[maxn];
		static const int S=1<<15 ; int i;
		REP(i,len) x1[i]=complex(A[i]/S,A[i]%S);
		REP(i,len) x2[i]=complex(B[i]/S,B[i]%S);
		fft(x1,len,1); fft(x2,len,1);
		REP(i,len) {//这个k1, b1就是前面的, 这就减掉了一半常数
			int j=(len-i)&(len-1);
			complex k1=(conj(x1[i])+x1[j])*complex(0.5,0);//dft k1
			complex b1=(conj(x1[i])-x1[j])*complex(0,0.5);//dft b1
			complex k2=(conj(x2[i])+x2[j])*complex(0.5,0);//dft k2
			complex b2=(conj(x2[i])-x2[j])*complex(0,0.5);//dft b2
			x3[i]=k1*k2+k1*b2*complex(0,1);
			x4[i]=b1*k2+b1*b2*complex(0,1);
		} fft(x3,len,-1); fft(x4,len,-1);
		REP(i,len) {
			ll kk=x3[i].a+0.5,kb=x3[i].b+0.5;
			ll bk=x4[i].a+0.5,bb=x4[i].b+0.5;
			ans[i]=(kk*S+kb+bk)*S+bb;
		}
	}
	void mul(ll *A,ll *B,ll *ans,int n,int m) {
		int len=1,i;
		while (len<n+m) len<<=1;
		rep(i,n,len) A[i]=0;
		rep(i,m,len) B[i]=0;
		mul(A,B,ans,len);
	}
}
int A[maxn]; ll B[maxn];
int F[maxn],G[maxn];
bool isroot(int x,int p){
	if (!(x%p)||(x%p==1&&p!=2)) return 0;
	for (ll i=2;i*i<=p-1;i++) if ((p-1)%i==0)
		if (poww(x,(p-1)/i,p)==1||poww(x,i,p)==1) return 0;
	return 1;
} ll ans[maxn];
int main() {
	int p,i,j;
	scanf("%d%d",&n,&p);
	FOR(i,1,n) scanf("%d",&A[i]);
	int g;
	rFOR(g,2,p-1) if (isroot(g,p)) break;
	j=1; int cnt0=0;
	FOR(i,0,p-2) F[i]=j,G[j]=i,j=(ll)j*g%p;
	FOR(i,1,n) {
		int now=A[i]%p;
		if (now==0) cnt0++;
		else B[G[now]]++;
	} ans[0]=(ll)cnt0*cnt0+(ll)cnt0*(n-cnt0)*2;
	// printf("g=%d\n",g);
	// FOR(i,0,p-1) printf("%d ",G[i]);puts("");
	// FOR(i,0,p-1) printf("%lld ",B[i]);puts("");
	FFT::mul(B,B,B,2*p,2*p);
	// FOR(i,0,p*2-1) printf("%lld ",B[i]);puts("");
	FOR(i,0,p+p) ans[F[i%(p-1)]]+=B[i];
	// FOR(i,0,p-1) printf("%lld ",ans[i]);puts("");
	FOR(i,1,n) {
		ll Ans=0;
		if (A[i]<=p) Ans=ans[A[i]];
		printf("%lld\n",Ans);
	}
}
/*
7 3
0 2 0 1 2 3 4
*/
