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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}


const LL MOD=998244353;
const LL g=3;
LL mul(LL x,LL y){
    return x*y%MOD;
//    return ( x * y - ( long long ) ( x / ( long double ) MOD * y + 1e-3 ) * MOD + MOD ) % MOD ;
}
LL poww(LL a,LL b){
    LL ret=1;
    for (;b;b>>=1ll,a=mul(a,a))
        if (b&1) ret=mul(ret,a);
    return ret;
}
void ntt(vector<LL> &A,int len,int inv){//³­µÄ°å×Ó
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
void mul(vector<LL> &A,vector<LL> &B){
    int i,len=1,size=A.size()+B.size()-1;
    while(len<=size) len<<=1;//0->size
    A.resize(len);B.resize(len);
//    for (int v:A) printf("%d ",v);puts("");
//    for (int v:B) printf("%d ",v);puts("");
    ntt(A,len,1);ntt(B,len,1);
    REP(i,len) A[i]=A[i]*B[i]%M;
    ntt(A,len,-1);
    vector<LL>().swap(B);
//    for (int v:A) printf("%d ",v);puts("");
    A.resize(size);
}
vector<LL> O[maxn];
struct cmp{
    bool operator()(const int A,const int B)const{
        if (O[A].size()!=O[B].size()) return O[A].size()>O[B].size();
        return A>B;
    }
};
priority_queue<int,vector<int>,cmp> Q;
LL fac[maxn];//Factorial
LL inv[maxn];//inverse
LL C(int n,int m){
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
int main(){
    int i,j,n;
    fac[0]=1;
    FOR(i,1,100000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,100000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,100000) inv[i]=inv[i]*inv[i-1]%M;
    scanf("%d",&n);
    LL Ans=0;
    FOR(i,1,n){
        int A;scanf("%d",&A);
        O[i].resize(A+1);
        LL now=0,all=0;
        FOR(j,1,A){
            O[i][j]=(C(A-1,j-1)*inv[j])%M;
            all+=C(A-1,j-1);(all>=M)&&(all-=M);
            if (!(j&1)) now+=C(A-1,j-1);(now>=M)&&(now-=M);
        }Q.push(i);now=now*poww(all,M-2)%M;
        Ans=(now*Ans+(1+M-now)*(1+M-Ans))%M;
//        for (int v:O[i]) printf("%d ",v);puts("");
    }while (Q.size()>1){
        int x=Q.top();Q.pop();
        int y=Q.top();Q.pop();
        mul(O[x],O[y]);
        Q.push(x);
    }int x=Q.top();LL ans=0;
    REP(i,O[x].size()){
        if (i&1) (ans+=O[x][i]*fac[i])%=M;
//        printf("ans=%lld\n",ans);
    }
//    for (int v:O[x]) printf("%d ",v);puts("");
    printf("%lld %lld\n",Ans,ans);
    return 0;
}
/*
*/
