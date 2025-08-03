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

int n,m;
int A[maxn],B[maxn];
int T;
int solve(){
    int n,i,j;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&B[i]);
    FOR(i,1,50000) if (A[i]==B[1]){
//        FOR(j,1,n) printf("%d %d\n",A[i+j-1],B[j]);
        FOR(j,1,n) if (A[i+j-1]!=B[j]) return 0*puts("no");
        return 0*puts("yes");
    }return 0*puts("no");
}
int main() {
    int i,j;
    A[1]=1;
    FOR(i,1,50000) A[i+1]=A[i]+i+2;
//    printf("%d ",A[50000]);
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}
/*
*/
