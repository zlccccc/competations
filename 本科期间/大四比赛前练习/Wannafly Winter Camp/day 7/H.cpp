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
const LL M=998244353;
const LL maxn=1e6+1007;
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
char str[maxn];//倒着的

namespace NTT {
    const int maxn=1<<19|7;
    const ll MOD=998244353;
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
    void ntt(int *A,int len,int inv) {
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
    void multi(int *a,int *b,int *ans,int len) { //C=A*B
        int i;
        static int A[maxn],B[maxn],C[maxn];
        REP(i,len) A[i]=a[i],B[i]=b[i];
        ntt(A,len,1); ntt(B,len,1);
        REP(i,len) C[i]=mul(A[i],B[i]);
        ntt(C,len,-1);
        REP(i,len) ans[i]=C[i];
    }

	const ll Mod=998244353;
	// 下方的东西和ntt就根本无关, 这个模数是可以改的, 是多项式相关的东西
	// 也就是说, 这个模数完全可以取其他的, 然后高精度的mtt来求, 不过可能会T到死
	int eInv[maxn];
	void initinv(int l) {
		int i; eInv[0]=eInv[1]=1;
		rep(i,2,l) eInv[i]=(Mod-Mod/i)*eInv[Mod%i]%Mod;
	}
	void Ftof(int *A,int *B,int l) {//derivative 求导
		int i;
		FOR(i,1,l) B[i-1]=(ll)A[i]*i%Mod;
	}
	void ftoF(int *A,int *B,int l) {//integral 积分
		int i; // todo:get B[0], getinv
		rFOR(i,1,l) B[i]=(ll)A[i-1]*eInv[i]%Mod;
		B[0]=0;
	}
    void inv(int *A,int *B,int l) { //B=inv(A)
        static int C[maxn];
        B[0]=poww(A[0],MOD-2); B[1]=0;
        for (int len=2; len<=l; len<<=1) {
            int i; fill(B+len,B+len+len,0);
            copy(A,A+len,C); fill(C+len,C+len+len,0);
            ntt(C,len*2,1); ntt(B,len*2,1);
            REP(i,len*2) B[i]=mul(B[i],(MOD+2-mul(C[i],B[i])));
            ntt(B,len*2,-1); fill(B+len,B+len+len,0);
        }
    }
	void ln(int *A,int *B,int l) {
		static int C[maxn];
		inv(A,B,l); Ftof(A,C,l);
		multi(B,C,B,l*2);
		ftoF(B,B,l);
	}
	void exp(int *A,int *B,int l) {
		static int C[maxn],i;
		B[0]=1; B[1]=0;
		for (int len=2; len<=l; len<<=1) {
			fill(B+len,B+len+len,0);
			ln(B,C,len); fill(C+len,C+len+len,0);
			REP(i,len) C[i]=(C[i]-A[i]+Mod)%Mod;
			multi(B,C,C,len*2);
			REP(i,len) B[i]=(B[i]-C[i]+Mod)%Mod;
		}
	}
	//这里是更高一层的东西
	static int A[maxn];
	void getexp(int *a,int *ans,int n) {
		int len=1,i;
		while (len<n) len<<=1;
		REP(i,n) A[i]=a[i]; rep(i,n,len) A[i]=0;
		exp(A,ans,len);
	}
	void solve(int *a,int *ans,int m) {
		static int A[maxn];
		int i,j;
		FOR(i,1,m) {//无穷背包
			int now=(ll)i*a[i]%Mod;
			for (j=i-1; j<=m; j+=i) A[j]=(now+A[j])%Mod;
		} ftoF(A,A,m);
		getexp(A,ans,m+1);
	}
}
int A[maxn],ans[maxn];
int main() {
	NTT::initinv(NTT::maxn);
	scanf("%d",&n); int i;
	FOR(i,3,n) A[i]=1;
	// startTimer();
	NTT::solve(A,ans,n);
	// printTimer();
	// freopen("out.txt","r",stdout);
	printf("%d\n",ans[n]);
	// FOR(i,1,10) printf("%lld,",ans[n]);
	// fclose(stdout);
}
/*
10
0 0 1 1 1 499122178 1 499122178 332748119 499122178
0 0 0 0 0 0 0 0 0 0
19

*/