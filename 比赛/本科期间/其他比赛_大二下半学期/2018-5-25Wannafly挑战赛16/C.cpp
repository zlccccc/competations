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
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e7+7;
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

int inv[maxn],f[maxn];
int main() {
    int i,n;
    inv[0]=inv[1]=1;
    FOR(i,2,10000000) inv[i]=(LL)(M-M/i)*inv[M%i]%M;
    FOR(i,1,10000000){
        f[i]=f[i-1];
        if (i&1) f[i]+=inv[i];
        if (f[i]>M) f[i]-=M;
    }
//    printf("%lld\n",7ll*(inv[6])%M);
//    FOR(i,1,10) printf("%d:%d %d\n",i,inv[i],f[i]);
    scanf("%d",&n);
    while (n--){
        LL l,r;
        scanf("%lld%lld",&l,&r);
        LL ans=0;
//        for (i=1;i<=r;i+=2){
//            if (r/l>=i) ans+=(r*inv[i]%M-l)%M;
//            else break;
//            ans%=M;
//        }
//        printf("ans=%lld\n",ans);(ans*=inv[r-l])%=M;
//        printf("ans=%lld\n",ans);
        ans=(LL)f[r/l]*r%M-(LL)((r/l+1)/2)*l%M;
//        printf("ans=%lld\n",ans);
        (ans*=inv[r-l])%=M;
        ans+=M;ans%=M;
        printf("%lld\n",ans);
    }
    return 0;
}
/*
*/
