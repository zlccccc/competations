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
const LL maxn=4e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k;
LL inv[maxn];
LL fac[maxn];
LL C(int n,int m){
//    printf("C: %d %d; %lld\n",n,m,fac[n]*inv[m]%M*inv[n-m]%M);
    if (n<0||m<0||n<m) return 0;
    return fac[n]*inv[m]%M*inv[n-m]%M;
}LL ans;
int main(){
    int i;
    fac[0]=1;
    FOR(i,1,4000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,4000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,4000000) inv[i]=inv[i]*inv[i-1]%M;
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d%d",&n,&m,&k);
//        ans=fac[m];
//        if (m==1) printf("%d\n",k==1);
        (ans=(C(m+(m-k)-1,m-k)-C(m+(m-k)-1,m-k-1)+M))%=M;
//        (ans*=C(n,m+(m-k))*fac[m+(m-k)]%M)%=M;
//        printf("ans1: %lld\n",ans);
        (ans*=(C(2*n-2*m+k,n-m)-C(2*n-2*m+k,n-m-1)+M))%=M;//emmm²»Í£µÄ
//        (ans*=fac[n])%=M;
        printf("%lld\n",ans);
    }
}
/*
*/
