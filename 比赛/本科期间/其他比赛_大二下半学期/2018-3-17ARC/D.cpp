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
const LL maxn=4e5+7;
const double eps=0.00000001;
const double pi=acos(-1);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int cnt[maxn];
int pre;
int ans;
    int n,q;
int A[maxn],B[maxn],C[maxn];
int calc(int t){
    LL ret=0,k=n-1,i;
    REP(i,n){
        while (k>=0&&A[i]+B[k]>=t) k--;
        ret+=(n-1-k);
    }
//    printf("%d:%d\n",t,ret);
    return ret&1;
}
int main(){
    int i,j,k;
    scanf("%d",&n);
    REP(i,n) scanf("%d",&A[i]);
    REP(i,n) scanf("%d",&B[i]);
    sort(A,A+n);sort(B,B+n);
    rREP(j,30){
        int k=lower_bound(A,A+n,1<<(j+1))-A;
        REP(i,n) A[i]%=1<<(j+1);
        merge(A,A+k,A+k,A+n,C);
        REP(i,n) A[i]=C[i];

        k=lower_bound(B,B+n,1<<(j+1))-B;
        REP(i,n) B[i]%=1<<(j+1);
        merge(B,B+k,B+k,B+n,C);
        REP(i,n) B[i]=C[i];
//        REP(i,n) printf("%d ",A[i]);puts("");
//        REP(i,n) printf("%d ",B[i]);puts("");
//        REP(i,n) printf("%d ",C[i]);puts("");
        ans|=(calc(1<<j)^calc(2<<j)^calc(3<<j))<<j;
//        printf("%d\n",ans);
    }printf("%d\n",ans);
}
/*
*/
