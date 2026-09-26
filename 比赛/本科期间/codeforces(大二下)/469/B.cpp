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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int m,q;
int i,j,k;
int a[maxn];
LL now,suf,n;
inline LL solve(LL n,LL x){
//    printf("solve:%lld %lld\n",n,x);
    if (x&1) return (x+1)/2;
    LL mid=n/2,ret;
    if (n%2==1){
        if (x==n) ret=mid+solve(n-mid,1);
        else ret=mid+solve(n-mid,x/2+1);
    }else ret=mid+solve(mid,x/2);
//    printf("solve:%lld %lld:%lld\n",n,x,ret);
    return ret;
}
int main(){
    scanf("%I64d%d",&n,&q);
//    solve(n,2);
//    FOR(i,1,n) printf("%d ",solve(n,i));puts("");
    while (q--){
        LL x,y;
        scanf("%I64d",&x);
        printf("%I64d\n",solve(n,x));
    }
}
/*
*/
