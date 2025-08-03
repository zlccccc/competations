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
const LL maxn=5000*2+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,r;LL k,t;
int A[maxn],B[maxn],inv[maxn];
int pre[maxn][2],o;//update->previous
int ans[maxn];
int main(){
    int i,j,k;
    scanf("%d",&n);
    A[0]=A[1]=1;FOR(i,2,n) scanf("%d",&A[i]);
    B[0]=inv[0]=1;FOR(i,1,n) B[i]=(LL)A[i]*B[i-1]%M,inv[i]=powMM((LL)B[i],M-2);
//    FOR(i,1,n) printf("%-10d ",B[i]);puts("");
//    FOR(i,1,n) printf("%-10d ",inv[i]);puts("");
    FOR(i,1,n) pre[i][1]=powMM(2ll,M-2);
    FOR(k,1,2*n-2){//D//zero_WA
        FOR(i,1,n) ans[k]=(ans[k]+(LL)pre[i][o]*A[i]%M*(A[i]-1)%M*B[i-1]%M)%M;
//        FOR(i,1,n) printf("%-10d ",pre[i][o]);puts(" <- pre");
//        FOR(i,1,n) printf("%-10d ",pre[i][o]*A[i]%M*(A[i]-1)%M);puts(" <- pre_changed");
//        FOR(i,1,n) printf("%-10d ",(LL)pre[i][o]*A[i]%M*(A[i]-1)%M*B[i-1]%M);puts(" <- pre_changed2");
//        printf("pre_now(%d)=%d  now_o=%d\n",k,ans[k],o);
        FOR(i,1,n+1) pre[i-1][o]=(LL)pre[i][o]*A[i]%M*A[i]%M;//change
        FOR(i,1,n-k) {
            pre[i][o]=(pre[i][o]+(LL)inv[i]*B[i+k])%M;
            ans[k]=(ans[k]+(LL)inv[i]*B[i+k]%M*B[i])%M;
        }
//        printf("now(%d)=%d\n",k,ans[k]);
//        FOR(i,1,n) printf("%-10d ",pre[i][o]);puts(" <- nxt_pre");
//        printf("now(%d)=%d\n",k,ans[k]);puts("");
        o^=1;
    }
    FOR(i,1,n*2-2) printf("%d ",ans[i]);
}
/*
4
2 2 2
*/
