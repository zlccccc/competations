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

#define DEBUG1
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
const LL maxn=4e5+7;
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

int bit[1<<15|7],mark[1<<15|7];
int cnt[maxn];
LL f[maxn];
void solve(){
    int m,n,sum;
    int status,i,j;
    scanf("%d%d%d",&sum,&n,&m);
    memset(mark,0,sizeof(mark));
    FOR(i,1,m) cnt[i]=0;mark[0]=1;
    REP(status,(1<<m)) if (mark[status]){
//        rREP(i,10) printf("%d",(status>>i)&1);puts("");
        REP(i,min(n,m-bit[status])){
            int nxtstatus=status|(1<<(bit[status]+i));
            mark[nxtstatus]=1;
        }cnt[bit[status]]++;
    }f[0]=1;
//    puts("");FOR(i,1,m) printf("%d ",cnt[i]);puts("");
    FOR(i,1,sum) {
        f[i]=0;
        FOR(j,1,min(i,m)) f[i]+=f[i-j]*cnt[j];
        f[i]%=233333333;
    }printf("%lld\n",f[sum]);
}
int main() {
    int T,i;
    rep(i,1,(1<<15)) bit[i]=bit[i>>1]+1;
    scanf("%d",&T);
    while (T--) solve();
    return 0;
}
/*
2
5 2 4
5 2 3
*/
