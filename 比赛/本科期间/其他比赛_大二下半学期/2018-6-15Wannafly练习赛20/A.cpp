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
const LL maxn=3e5+7;
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

template<typename T>inline T poww(T a, T b,LL M) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
LL C[2007][2007];
int main() {
    int m,i;
    int T;
    scanf("%d",&T);
    while (T--){
        int M,n,m,k,i,j;
        LL ans=0;
        scanf("%d%d%d%d",&n,&m,&k,&M);
        C[0][0]=1;
        C[0][1]=C[1][1]=1;
        FOR(j,2,2000) {
            C[0][j]=1;
            FOR(i,1,j) C[i][j]=(C[i-1][j-1]+C[i][j-1])%M;
        }
        FOR(i,0,k/2) {
            int j=k-i*2;
            if (n==0&&j!=0) continue;
            if (m==0&&i!=0) continue;
//            printf("%d %d %d\n",i,j,k);
//            printf("%lld(%d %d) * %lld(%d %d)\n",C(n+j-1,j,M),n+j-1,j,C(m+i-1,i,M),m+i-1,i);
            ans+=C[j][max(0,n+j-1)]*C[i][max(0,m+i-1)];
            ans%=M;
        }printf("%lld\n",ans);
    }
}
/*
3
0 10 2 47
0 10 2 3
0 10 2 2
*/
