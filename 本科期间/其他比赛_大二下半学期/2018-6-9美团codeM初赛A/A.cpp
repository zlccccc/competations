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

string A[9];
int pos[255];
char S[maxn];
int main() {
    A[0]="@!:";
    A[1]="ABC";
    A[2]="DEF";
    A[3]="GHI";
    A[4]="JKL";
    A[5]="MNO";
    A[6]="PQRS";
    A[7]="TUV";
    A[8]="WXYZ";
    int n,m,T;
    int i,j;
    REP(i,9)
        for (auto now:A[i]) pos[now]=i;
    scanf("%d",&T);
    while (T--){
        int ans=0;
        S[0]='@';
        scanf("%s",S+1);
        int len=strlen(S+1);
        FOR(i,1,len){
            int x=pos[S[i-1]],y=pos[S[i]];
            ans+=abs(x%3-y%3)+abs(x/3-y/3);
        }printf("%d\n",ans);
    }
    return 0;
}
/*
*/
