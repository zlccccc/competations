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
#include <iomanip>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,P;
int i,j,k;
LL a[maxn],b[maxn];
LL ans;LL p;
LL calc(int l,int r,int m,int P,LL p){
    int i;LL ans=INFF;
    FOR(i,l,r){
        LL T=m-abs(P-i);if (P<=i) T--;
        if (T<0) continue;
        ans=min(ans,abs(a[i]-p)+b[i]*T);
//        printf("%d %lld; a,b= %lld %lld; now=%lld; abs=%lld\n",i,T,a[i],b[i],abs(a[i]-p)+b[i]*T,abs(a[i]-p));
    }
//    printf("ans=%lld\n",ans);
    return ans;
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%d%d%lld",&n,&m,&p);
        FOR(i,1,n) scanf("%lld",&a[i]),b[i]=INFF;
        FOR(i,1,n-1){
            b[i]=min(b[i],a[i+1]-a[i]);
            b[i+1]=min(b[i+1],a[i+1]-a[i]);
        }ans=INFF;
        P=lower_bound(a+1,a+1+n,p)-a;
        ans=calc(1,n,m,P,p);
        if (m>1){
            m--;
            if (1<=P&&P<=n) ans=min(ans,abs(a[P]-p)+calc(1,P-1,m,P,a[P]));
            if (1<=P-1&&P-1<=n) ans=min(ans,abs(a[P-1]-p)+calc(P,n,m,P,a[P-1]));
        }
        printf("%lld\n",ans);
    }
}
/*
100
5 0 1
1 2 3 4 5

48370656
*/
