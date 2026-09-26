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
const LL maxn=1e5+7;
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

LL f[2007],k[2007];
LL A[maxn];
int main() {
    int T,i,j;
    int n;LL k;
    scanf("%d%lld",&n,&k);
    FOR(i,1,n) scanf("%lld",&A[i]);
    f[1]=1;
    FOR(i,2,n) f[i]=f[i-1]*(k+i-2)%M*powMM((LL)i-1,M-2)%M;
    rFOR(i,1,n){
        rFOR(j,1,i-1) A[i]=(A[i]+f[i-j+1]*A[j])%M;
        if (A[i]<0) A[i]+=M;
    }FOR(i,1,n) printf("%lld%c",A[i]," \n"[i==n]);
    return 0;
}
/*
3 2
1 1 1
*/
