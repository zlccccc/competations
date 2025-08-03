#include <sstream>
#include <fstream>
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

#define DEBUG
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
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

set<pair<int,int> > S;
int ax[4]={1,0,-1,0};
int ay[4]={0,1,0,-1};
int main() {
    int n,m;
    int nowx=1,nowy=1;
    int i,j,q;
    scanf("%d%d",&n,&m);
    FOR(i,0,n+1){
        S.insert(make_pair(0,i));
        S.insert(make_pair(n+1,i));
        S.insert(make_pair(i,0));
        S.insert(make_pair(i,n+1));
    }j=0;
    REP(i,m){
        S.insert(make_pair(nowx,nowy));
        if (S.count(make_pair(nowx+ax[j],nowy+ay[j]))) j=(j+1)%4;
        nowx=nowx+ax[j],nowy=nowy+ay[j];
    }printf("%d %d\n",nowx,nowy);
    return 0;
}
/*
*/
