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

int n,m;
char A[maxn];
LL H[maxn],F[maxn];//ans
int S[maxn],top;
int main() {
    int i,j,q;
    scanf("%d",&q);
    while (q--){
        scanf("%s",A);
        n=strlen(A);
        F[0]=0;
        REP(i,n){
            if (A[i]=='(') S[++top]=i,H[top]=1,F[top]=0;//H:ans
            else {
                F[top]+=H[top]*(i-S[top]);
                H[top-1]=max(H[top-1],H[top]+1);
                F[top-1]-=F[top];
                top--;
            }
        }
//        REP(i,n) debug("%d ",H[i]);puts("");
//        REP(i,n) debug("%d ",F[i]);puts("");
//        REP(i,n) debug("%d ",S[i]);puts("");
        printf("%lld\n",-F[0]);
    }
    return 0;
}
/*
*/
