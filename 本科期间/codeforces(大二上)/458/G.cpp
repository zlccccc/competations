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
const LL maxn=1e6+7;
const double eps=0.00000001;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

void fwt(LL *A,int len,int inv,int type){//xor,and,or
    int i,j,k;
    int div=powMM(2ll,M-2);
    for(i=2;i<=len;i<<=1){
        for(j=0;j<len;j+=i){
            for(k=j;k<j+i/2;k++){
                if (inv==1){
                    LL a=A[k],b=A[k+i/2];
                    if (type==1){
                        A[k]=(a+b)%M;
                        A[k+i/2]=(a-b+M)%M;
                    }else if (type==2){
                        A[k]=(a+b)%M;
                    }else if (type==3){
                        A[k+i/2]=(a+b)%M;
                    }
                }else{
                    LL a=A[k],b=A[k+i/2];
                    if (type==1){
                        A[k]=(a+b)*div%M;
                        A[k+i/2]=(a-b+M)%M*div%M;
                    }else if (type==2){
                        A[k]=(a-b+M)%M;
                    }else if (type==3){
                        A[k+i/2]=(b-a+M)%M;
                    }
                }
            }
        }
    }
}int k;
int n;
LL f[maxn];
LL A[maxn],B[maxn],C[maxn];//S:C
int g[maxn];
int main(){
    int i,j;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&k),f[k]++;
//    //A:brute force
//    REP(i,(1<<17)){
//        int cnt=0;
//        REP(j,17) if ((i>>j)&1) g[1<<cnt]=1<<j,cnt++;
//        rep(j,1,(1<<cnt)) g[j]=g[j^(j&-j)]|g[j&-j];
//        REP(j,(1<<cnt)) (A[i]+=f[g[j]]*f[i^g[j]])%=M;
//    }
    //A:brute force
    REP(i,(1<<17))
        for(j=i;;j=(j-1)&i) {(A[i]+=f[j]*f[i^j])%=M;if (!j) break;}
    //B:
    REP(i,(1<<17)) B[i]=f[i];
    //C:
    REP(i,(1<<17)) C[i]=f[i];
    fwt(C,1<<17,1,1);
    REP(i,(1<<17)) C[i]=(C[i]*C[i])%M;
    fwt(C,1<<17,-1,1);
    f[0]=0;f[1]=1;
    FOR(i,2,(1<<17)) f[i]=(f[i-1]+f[i-2])%M;
    REP(i,(1<<17)){
        (A[i]*=f[i])%=M;
        (B[i]*=f[i])%=M;
        (C[i]*=f[i])%=M;
    }
    fwt(A,1<<17,1,2);
    fwt(B,1<<17,1,2);
    fwt(C,1<<17,1,2);
    REP(i,(1<<17)) (A[i]*=B[i])%=M,(A[i]*=C[i])%=M;
    fwt(A,1<<17,-1,2);
    int ANS=0;
    REP(i,17) (ANS+=A[1<<i])%=M;
    printf("%d\n",ANS);
}
/*
*/
