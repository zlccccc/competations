#include <sstream>
#include <fstream>
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

#define DEBUG1
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
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

char A[2007][2007];
int ansx[2007],ansy[2007],cntx[2007],cnty[2007],all;
void TaskA(){
    int n,m,i,j;
    int ans=0;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%s",A[i]+1);
    FOR(i,1,n) FOR(j,1,m)
        cntx[i]+=A[i][j]-'0',cnty[j]+=A[i][j]-'0',all+=A[i][j]-'0';
    all=powMM((LL)all,M-2);
    FOR(i,1,n) FOR(j,1,n) ansx[i]+=cntx[j]*abs(i-j);
    FOR(i,1,m) FOR(j,1,m) ansy[i]+=cnty[j]*abs(i-j);
    FOR(i,1,n) FOR(j,1,m) ans^=(LL)(ansx[i]+ansy[j])*all%M;
    printf("%d\n",ans);
}
int main() {
    int T=1;
//    scanf("%d",&T);
    while (T--) TaskA();
}
/*
*/
