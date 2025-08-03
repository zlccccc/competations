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
const LL M=1e9+9;
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

int main() {
    int T;
    scanf("%d",&T);
    while(T--){
        double lat1,lng1,lat2,lng2;
        scanf("%lf%lf%lf%lf",&lat1,&lng1,&lat2,&lng2);
        lat1=lat1/180*pi;
        lng1=lng1/180*pi;
        lat2=lat2/180*pi;
        lng2=lng2/180*pi;
        double d=6371009*sqrt(2-2*(cos(lat1)*cos(lat2)*cos(lng1-lng2)+sin(lat1)*sin(lat2)));
        printf("%.0f\n",2*asin(d/(2*6371009))*6371009-d);
    }
    return 0;
}
/*
1
43.466667 -80.516667 30.058056 31.228889
*/
