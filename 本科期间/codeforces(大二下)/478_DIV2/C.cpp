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
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+9;
const LL maxn=4e5+7;
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

int n,m;
int now;
LL A[maxn],B[maxn];
LL pre;
int main() {
    int i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%I64d",&A[i]),A[i+n]=A[i];
    FOR(i,1,n*2) A[i]+=A[i-1];
    int now=1;
    FOR(i,1,m){
        LL all;
        scanf("%I64d",&all);
        all+=pre; all=min(all,A[n]);
        int nxt=upper_bound(A+now-1,A+n*2,A[now-1]+all)-A;
        pre=all-(A[nxt-1]-A[now-1]);
        if (nxt!=now) now=nxt;
        if (now>n) now=1,pre=0;
        printf("%d\n",n-now+1);
    }
    return 0;
}
/*
*/
