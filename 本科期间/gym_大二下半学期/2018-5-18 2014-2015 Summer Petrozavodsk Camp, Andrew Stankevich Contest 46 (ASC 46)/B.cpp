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
typedef long long ll;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=175781251;
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
ll cnt[105][105];
LL an[105];
ll f[105];
ll tot[105][105];
LL pow2[10007];
LL pow3[10007];
LL C[107][107];
int A[107];

int main() {
    freopen("bipartite.in","r",stdin);
    freopen("bipartite.out","w",stdout);
    int n,k;
    int i,j;
    pow2[0]=pow3[0]=1;
    FOR(i,1,10000) pow2[i]=pow2[i-1]*2%M;
    FOR(i,1,10000) pow3[i]=pow3[i-1]*3%M;
    C[0][0]=1;
    FOR(i,1,100) {
        C[i][0]=1;
        FOR(j,1,100){
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%M;
        }
    }
    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)tot[i][j]=pow3[i*j];
    for(i=0;i<=100;i++)
        for(j=0;i+j<=100;j++)
        {
            cnt[i][j]=tot[i][j];
            for(int x=1;x<=i;x++)
                for(int y=0;y<=j;y++)
                {
                    if(x==i&&y==j)continue;
                    cnt[i][j]=(1LL*cnt[i][j] -
                                1LL*tot[i-x][j-y] %M*
                               cnt[x][y]% M* C[i-1][x-1] % M* C[j][y]%M  +M)%M;
                }
        }
    f[0]=1;
    for(int i=1;i<=100;i++)
    {
        for(int x=1;x<=i;x++)
            for(int y=0;y+x<=i;y++)
                f[i]=(f[i]+1LL*f[i-x-y]*C[i-1][x-1]%M*C[i-x][y]%M*cnt[x][y]%M)%M;
    }
    while(scanf("%d",&n)&&n){
        printf("%I64d\n",f[n]);
//        cerr<<f[n];
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
/*
*/
