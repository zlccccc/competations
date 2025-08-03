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

int solve(){
    int xl,xr,yl,yr,i;
    xl=INF;xr=-INF;yl=INF;yr=-INF;
    REP(i,4){
        int x,y;
        scanf("%d%d",&x,&y);
        xl=min(xl,x);xr=max(xr,x);
        yl=min(yl,y);yr=max(yr,y);
    }int _xl=INF,_xr=-INF,_yl=INF,_yr=-INF;
    REP(i,4){
        int x,y,_x,_y;
        scanf("%d%d",&x,&y);
        _x=x+y;_y=x-y;
        _xl=min(_xl,_x);_xr=max(_xr,_x);
        _yl=min(_yl,_y);_yr=max(_yr,_y);
    }
    int x,y;
    FOR(x,xl,xr){
        FOR(y,yl,yr){
            int _x=x+y,_y=x-y;
            if (_xl<=_x&&_x<=_xr&&_yl<=_y&&_y<=_yr){
                return 0*puts("Yes");
            }
        }
    }return 0*puts("No");
}
int main() {
    int T=1;
//    scanf("%d",&T);
    while (T--) solve();
}
/*
*/
