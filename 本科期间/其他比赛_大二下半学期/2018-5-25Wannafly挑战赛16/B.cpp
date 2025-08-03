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
const LL M=1e9+7;
const LL maxn=1e6+7;
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

LL A[maxn];
int n;
LL get(LL mid){
    LL i,ret=0;
    FOR(i,1,n) ret+=abs(A[i]+mid);
    ret+=abs(mid);
    return ret;
}
int main() {
    int i,m;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%lld",&A[i]);
    FOR(i,1,m) scanf("%lld",&A[i+n]),A[i+n]=-A[i+n];
    n+=m;sort(A+1,A+1+n);
    LL l=-INF,r=INF,ans=INFF;
    while (l<r){
        if (r-l<=10){
            FOR(i,l,r) ans=min(ans,get(i));
            break;
        }LL L=l+(r-l)/3,R=r-(r-l)/3;
        LL ansL=get(L),ansR=get(R);
        if (ansL<ansR) r=R;
        else l=L;
        ans=min(ans,ansL);
        ans=min(ans,ansR);
    }printf("%lld\n",ans);
    return 0;
}
/*
*/
