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

char A[maxn];
void TaskA(){
    LL a,n=0;
    LL inv2=powMM(2ll,M-2);
    scanf("%lld%s",&a,A);
    int len=strlen(A),i;
    REP(i,len) n=(n*10+A[i]-'0')%(M-1);
    if (n==0) n=M-1;
    a=1-2*a*powMM(10000ll,M-2);
    a%=M; a+=M; a%=M;
    printf("%lld\n",((-inv2+M)%M*powMM(a,n)+inv2)%M);

}
void TaskB(){
    LL a,n;
    LL inv2=powMM(2ll,M-2);
    scanf("%lld%lld",&a,&n);
    a=1-2*a*powMM(10000ll,M-2);
    a%=M; a+=M; a%=M;
    printf("%lld\n",((-inv2+M)%M*powMM(a,n)+inv2)%M);
}
int main() {
    int T=1;
//    scanf("%d",&T);
    while (T--) TaskA();
}
/*
2500 3
*/
