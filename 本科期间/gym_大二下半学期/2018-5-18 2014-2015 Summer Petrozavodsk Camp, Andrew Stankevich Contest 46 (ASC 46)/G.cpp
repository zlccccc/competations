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
const LL M=242121643;
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

int cnt;
LL pow2[107];
LL C[107][107];
int A[107];
int main() {
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    int n,k;
    int i,j;
    pow2[0]=1;
    FOR(i,1,100) pow2[i]=pow2[i-1]*2%M;
    C[0][0]=1;
    FOR(i,1,100) {
        C[i][0]=1;
        FOR(j,1,100){
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%M;
        }
    }
//    printf("%d\n",C[4][2]);
    while(~scanf("%d%d",&n,&k)&&(n||k)){
        cnt=0;
        FOR(i,1,n){
            scanf("%d",&A[i]);
            if (A[i]==1) cnt++;
        }LL ans=0;
        for (i=0;i<=cnt;i+=2){
            if (i<=k&&k-i<=n-cnt){
                ans+=C[cnt][i]*C[n-cnt][k-i];
                ans%=M;
            }
        }
        ans=C[n][k]-ans;
        ans+=M;ans%=M;
        printf("%I64d\n",ans);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
/*
*/
