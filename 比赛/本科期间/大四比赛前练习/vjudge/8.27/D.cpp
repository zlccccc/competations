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
const LL maxn=4e4+107;
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

namespace FFT {
	const int maxn=1<<18|7;
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
	void mul(int *A,int *B,int *ans,int len) { //ans=A*B
		static complex x1[maxn],x2[maxn]; int i;
		REP(i,len) x1[i]=complex(A[i],B[i]);
		fft(x1,len,1);
		REP(i,len) {//这个k1, b1就是前面的, 这就减掉了一半常数
			int j=(len-i)&(len-1);
			complex a=(conj(x1[i])+x1[j])*complex(0.5,0);//dft a
			complex b=(conj(x1[i])-x1[j])*complex(0,0.5);//dft b
			x2[i]=a*b;
		} fft(x2,len,-1);
		REP(i,len) ans[i]=x2[i].a+0.5;
	}
}
const int SIZE=10000,Base=30000,MulSize=65536;
int R[maxn],L[maxn],val[maxn];
int P[30][maxn],Cnt[30][maxn],All[maxn];
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		int n,s,i,k;
		scanf("%d",&n); s=0;
		FOR(i,1,n) {
			scanf("%d",&val[i]);
			val[i]+=val[i-1];
		} s=val[n];
		FOR(i,0,n/SIZE) L[i]=R[i]=0;
		FOR(i,1,n) {
			if (!L[i/SIZE]) L[i/SIZE]=i;
			R[i/SIZE]=i;
		}
		FOR(i,1,s) P[n/SIZE+1][i]=Cnt[n/SIZE+1][i]=0;
		FOR(k,0,n/SIZE) {//倒着来
			static int A[maxn*2],B[maxn*2],C[maxn*2];
			int MAX=L[k];
			// printf("L=%d\n",L[k]);
			REP(i,MulSize) A[i]=B[i]=0; 
			FOR(i,1,s) Cnt[k][i]=0;
			FOR(i,MAX,n) {
				B[Base-val[i-1]]++; A[val[i]]++;
				Cnt[k][val[i]]++;//right
			} FFT::mul(A,B,C,MulSize);
			// REP(i,MulSize) printf("%d ",A[i]); puts("<- A");
			// REP(i,MulSize) printf("%d ",B[i]); puts("<- B");
			// REP(i,MulSize) printf("%d ",C[i]); puts("<-mul");
			FOR(i,1,s) P[k][i]=C[i+Base];
			// FOR(i,1,s) printf("%d ",P[k][i]); printf("  <--  %d\n",k);
		} //calcute_k
		FOR(i,1,s) All[i]=P[0][i];
		FOR(k,0,n/SIZE) FOR(i,1,s) P[k][i]-=P[k+1][i];
		int ans1=0,ans2=0;
		FOR(k,1,s) if (All[k]) {
			int v=(All[k]+1)/2,_;//count
			FOR(_,0,n/SIZE) {
				if (v<=P[_][k]) break;
				else v-=P[_][k];
			} int *p=Cnt[_],l,r;
			FOR(l,L[_],n) {
				if (val[l-1]+k>s) continue;
				if (v<=p[val[l-1]+k]) break;
				else v-=p[val[l-1]+k]; p[val[l]]--;
				// printf("l=%d: %d; v=%d\n",l,p[val[l-1]+k],v);
			} FOR(i,L[_],l-1) p[val[i]]++;
			// printf("%d: all=%d; left=%d\n",k,All[k],l);
			int _l=0,_r=n;//_r:okay;
			while (_l+1<_r) {
				int mid=(_l+_r)/2;
				if (val[mid]<val[l-1]+k) _l=mid;
				else _r=mid;
			} r=_r+v-1;
			add_(ans1,powMM(233,k)*l%M);
			add_(ans2,powMM(233,k)*r%M);
		}
		printf("%d %d\n",ans1,ans2);
	}
}
/*

2 3 2 2 0 1

3
4
2 1 1 2
4
0 1 0 0
6
2 3 2 3 2 1
-------case1
1: all=2; left=2
2: all=3; left=2
3: all=2; left=1
4: all=2; left=1
6: all=1; left=1
-------case3
1: 6 6
2: 3 3
3: 4 4
5: 2 3
6: 4 6
7: 1 3
8: 2 4
10: 1 4
11: 2 6
12: 1 5
13: 1 6
*/