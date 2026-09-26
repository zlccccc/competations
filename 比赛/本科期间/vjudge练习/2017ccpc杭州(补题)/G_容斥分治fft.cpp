#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+7;
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

vector<int> V[maxn];
struct cmp {
    bool operator ()(int A,int B) {
        return V[A].size()>V[B].size();
    }
};
priority_queue<int,vector<int>,cmp> Q;
LL inv[maxn],fac[maxn];
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
const LL g=3;
LL X[maxn],Y[maxn];
void ntt(LL *A,LL len,int inv){
    int i,j,k;
    for (i=1,j=len/2;i<len-1;i++){
        if (i<j) swap(A[i],A[j]);
        k=len/2;
        while (j>=k) j-=k,k/=2;
        if (j<k) j+=k;
    }for (i=2;i<=len;i<<=1){
        LL wn=powMM(g,(M-1)/i);
        if (inv==-1) wn=powMM(wn,M-2);
        for (j=0;j<len;j+=i){
            LL w=1;
            for (k=j;k<(j+i/2);k++){
                LL a=A[k],b=w*A[k+i/2]%M;
                A[k]=(a+b)%M;
                A[k+i/2]=(a-b+M)%M;
                w=w*wn%M;
            }
        }
    }if (inv==-1){
        LL vn=powMM(len,M-2);
        REP(i,len) A[i]=A[i]*vn%M;
    }
}
void merge_fft(vector<int> &A,vector<int> &B) {
    int len=1,n=A.size(),m=B.size(),i;
    while (len<n+m) len<<=1;
    REP(i,n) X[i]=A[i];rep(i,n,len) X[i]=0;
    REP(i,m) Y[i]=B[i];rep(i,m,len) Y[i]=0;
    ntt(X,len,1);ntt(Y,len,1);
    REP(i,len) X[i]=X[i]*Y[i]%M;
    ntt(X,len,-1);
    A.resize(n+m-1);vector<int>().swap(B);
    REP(i,n+m-1) A[i]=X[i];
}
int main() {
    int n,m,T;
    int i,j,k;
    fac[0]=1;
    rep(i,1,maxn) fac[i]=fac[i-1]*i%M;
    inv[0]=inv[1]=1;
    rep(i,2,maxn) inv[i]=(M-M/i)*inv[M%i]%M;
    rep(i,1,maxn) inv[i]=inv[i]*inv[i-1]%M;
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        FOR(i,1,n) vector<int>().swap(V[i]);
        while (Q.size()) Q.pop();
        int all=0;
        FOR(i,1,n) {
            int a,b;
            scanf("%d%d",&a,&b);
            V[i].resize(min(a,b)+1);
            FOR(k,0,min(a,b)) V[i][k]=C(a,k)*C(b,k)%M*fac[k]%M;
            Q.push(i);all+=a;
        }
        while (Q.size()>1) {
            int x=Q.top();Q.pop();
            int y=Q.top();Q.pop();
            merge_fft(V[x],V[y]);
            Q.push(x);
        }
        int x=Q.top();
        Q.pop();
        LL ans=0,seg=1;
//        REP(i,V[x].size()) printf("%d ",V[x][i]);puts("");
        REP(i,V[x].size()) ans+=V[x][i]*seg*fac[all-i]%M,seg=-seg;
        ans%=M;ans+=M;ans%=M;
        printf("%lld\n",ans);
    }
    return 0;
}
/*
4
1
3 3
2
0 2 2 0
4 1 1 1 1 1 1 1 1
6 0 2 1 0 1 2 0 0 2 2 2 0


*/