#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1<<20|7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

const LL MOD=998244353;
const LL g=3;
LL mul(LL x,LL y) {
    return x*y%MOD;
}
LL poww(LL a,LL b){
    LL ret=1;
    for (;b;b>>=1ll,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}
void ntt(LL *A,int len,int inv){
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
        LL wn=poww(g,(MOD-1)/i);
        if (inv==-1) wn=poww(wn,MOD-2);
        for (j=0;j<len;j+=i){
            LL w=1;
            for (k=j;k<(j+i/2);k++){
                LL a=A[k],b=mul(w,A[k+i/2]);
                A[k]=(a+b)%MOD;
                A[k+i/2]=(a-b+MOD)%MOD;
                w=mul(w,wn);
            }
        }
    }
    if (inv==-1){
        LL vn=poww(len,MOD-2);
        REP(i,len) A[i]=mul(A[i],vn);
    }
}
char a[maxn];
LL A[maxn],ans;
int main(){
    int i,j,k,n;
    scanf("%s%d",a,&k);
    int len=strlen(a);n=0;
    REP(i,len) n=((LL)n*10+a[i]-'0')%(MOD-1);
    A[0]=A[1]=1;
    ntt(A,k,1);
    REP(i,k) A[i]=poww(A[i],n);
    ntt(A,k,-1);
    REP(i,k) ans=ans^A[i];
    printf("%lld\n",ans);
//    REP(i,k) printf("%d ",A[i]);
    return 0;
}
/*
*/
