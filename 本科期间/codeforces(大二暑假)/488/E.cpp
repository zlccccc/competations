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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=8e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}


struct complex{
    double a,b;
    complex(double _a=.0,double _b=.0):a(_a),b(_b){}
    complex operator+(const complex x)const{return complex(a+x.a,b+x.b);}
    complex operator-(const complex x)const{return complex(a-x.a,b-x.b);}
    complex operator*(const complex x)const{return complex(a*x.a-b*x.b,a*x.b+b*x.a);}
};
void fft(complex *A,int len,int inv){//抄的板子
    int i,j,k;
    for (i=1,j=len/2;i<len-1;i++){
        if (i<j) swap(A[i],A[j]);
        k=len/2;
        while(j>=k){
            j-=k;
            k/=2;
        }if (j<k) j+=k;
    }
    for(i=2;i<=len;i<<=1){
        complex wn(cos(-inv*2*pi/i),sin(-inv*2*pi/i));
        for (j=0;j<len;j+=i){
            complex w(1.0,0.0);
            for (k=j;k<(j+i/2);k++){
                complex a=A[k],b=w*A[k+i/2];
                A[k]=a+b;
                A[k+i/2]=a-b;
                w=w*wn;
            }
        }
    }
    if (inv==-1) REP(i,len) A[i].a/=len;
}
complex x1[maxn],x2[maxn];
int A[maxn];
LL ans[maxn];
int TaskA(){
    int n,x;
    int i,j,k;
    scanf("%d%d",&n,&x);
    FOR(i,1,n) scanf("%d",&A[i]),A[i]=(A[i]<x);
    FOR(i,1,n) A[i]+=A[i-1];
    FOR(i,0,n) x1[A[i]].a++,x2[n-A[i]].a++;
    int len=1;while (len<=n*2) len*=2;
    fft(x1,len,1);fft(x2,len,1);
    REP(i,len) x1[i]=x1[i]*x2[i];
    fft(x1,len,-1);
    REP(i,len) ans[i]=x1[i].a+0.5;
    ans[n]-=n+1;ans[n]/=2;
//    REP(i,len) printf("%I64d ",X1[i]);puts("");
//    LL ans_0=(LL)n*(n+1)/2;
//    FOR(i,n+1,n+n) ans_0-=X1[i];X1[n]=ans_0;
    FOR(i,n,n+n) printf("%I64d ",ans[i]);
    return 0;
}
void initialize(){
}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
