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

class ThreeSameLetters{
public:
    LL f[57][57][7][7];//len,col,same,cnt
    int countStrings(int L, int S){
        int i,j,_j,k,t;
        memset(f,0,sizeof(f));
        REP(i,S) f[1][i][1][0]=1;
        FOR(i,1,L-1) REP(_j,S) REP(j,S) FOR(k,1,2) REP(t,2){
            int _i=i+1,_k,_t=t;
            if (j==_j) _k=k+1;else _k=1;
            if (_k==3) _k=2,_t++;
            f[_i][_j][_k][_t]+=f[i][j][k][t];
            f[_i][_j][_k][_t]%=M;
        }LL ret=0;
        REP(j,S) FOR(k,1,2) (ret+=f[L][j][k][1])%=M;
        return (int)ret;
    }
}test;
int main() {
    printf("%d\n",test.countStrings(3,7));
    printf("%d\n",test.countStrings(4,2));
    printf("%d\n",test.countStrings(2,17));
    printf("%d\n",test.countStrings(10,11));
    return 0;
}
/*
*/
