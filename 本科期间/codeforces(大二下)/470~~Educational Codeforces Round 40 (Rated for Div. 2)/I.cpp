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
const LL M=1e9+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}


const int MOD=5767169;
const int g=3;
inline int mul(int x,int y) {
    return (LL)x*y%MOD;
}
int poww(int a,int b){
    int ret=1;
    for (;b;b>>=1,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}
int wx[20][maxn];
void initwn(int len,int inv){
    for(int i=2,ix=1;i<=len;i<<=1,ix++){
        wx[ix][0]=1;int wn=poww(g,(MOD-1)/i);
        if (inv==-1) wn=poww(wn,MOD-2);
        for (int k=1;k<i/2;k++)
            wx[ix][k]=mul(wx[ix][k-1],wn);
    }
}
void ntt(int *A,int len,int inv){//抄的板子
    int i,j,k;
    for (i=1,j=len/2;i<len-1;i++){
        if (i<j) swap(A[i],A[j]);
        k=len/2;
        while(j>=k){
            j-=k;
            k/=2;
        }if (j<k) j+=k;
    }
    for(int ix=1,i=2;i<=len;i<<=1,ix++){
        for (j=0;j<len;j+=i){
            for (k=j;k<(j+i/2);k++){
                int a=A[k],b=mul(wx[ix][k-j],A[k+i/2]);
                A[k]=a+b;(A[k]>MOD)&&(A[k]-=MOD);
                A[k+i/2]=a-b;(A[k+i/2]<0)&&(A[k+i/2]+=MOD);
            }
        }
    }
    if (inv==-1){
        int vn=poww(len,MOD-2);
        REP(i,len) A[i]=mul(A[i],vn);
    }
}
int n,m;
char a[maxn],b[maxn];
int A[6][maxn],B[6][maxn];
int C[maxn];
LL S[maxn];
int fa[7];
inline int getfa(int x){
    while (fa[x]!=x) x=fa[x]=fa[fa[x]];
    return x;
}
int main(){
    int i,j,k;
    scanf("%s%s",a,b);
    n=strlen(a);m=strlen(b);
    int len=1;
    while (len<n+m) len<<=1;
    REP(i,n) A[a[i]-'a'][i]=1;
    REP(i,m) B[b[i]-'a'][m-i-1]=1;
    initwn(len,1);
    REP(i,6) ntt(A[i],len,1),ntt(B[i],len,1);
    initwn(len,-1);
    REP(j,6){
        REP(k,6){
            REP(i,len) C[i]=((LL)A[j][i]*B[k][i])%MOD;
//            printf("%d %d\n",j,k);
            ntt(C,len,-1);
            REP(i,len) if (C[i]) S[i]|=1ll<<(j*6+k);
//            REP(i,len) printf("%d ",C[i]);puts("");
        }
    }
    rep(i,m-1,n){
        REP(k,6) fa[k]=k;
        int ans=0;
        REP(k,36) if ((S[i]>>k)&1){
            int x=getfa(k/6),y=getfa(k%6);
            if (x!=y) fa[x]=y,ans++;
        }printf("%d ",ans);
    }puts("");
//    rep(i,m-1,n){
//        REP(k,36) if ((S[i]>>k)&1) printf("%d %d|",k/6,k%6);puts("");
////        REP(k,36) printf("%d",(S[i]>>k)&1);puts("");
//    }
}
/*
aaaaaa
ccccc
*/
