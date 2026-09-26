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
#define mod 998244353
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
long long ans[4],m[4][4],tempans[4],tempm[4][4];
void mul(int n)
{
    while(n)
    {
        if(n&1)
        {
            for(int i=0;i<4;i++)
                tempans[i]=0;
            for(int i=0;i<4;i++)
                for(int j=0;j<4;j++)
                    tempans[i]=(tempans[i]+ans[j]*m[j][i]%mod)%mod;
            for(int i=0;i<4;i++)
                ans[i]=tempans[i];
        }
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                tempm[i][j]=0;
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                for(int k=0;k<4;k++)
                    tempm[i][j]=(tempm[i][j]+m[i][k]*m[k][j]%mod)%mod;
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                m[i][j]=tempm[i][j];
        n>>=1;
    }
}
int main() {
    int n;
    freopen("figure.in","r",stdin);
    freopen("figure.out","w",stdout);
    while(scanf("%d",&n)!=EOF&&n)
    {
        ans[0]=1;
        ans[1]=0;
        ans[2]=0;
        ans[3]=0;
        m[0][0]=1;
        m[0][1]=1;
        m[0][2]=1;
        m[0][3]=0;
        m[1][0]=1;
        m[1][1]=2;
        m[1][2]=2;
        m[1][3]=0;
        m[2][0]=0;
        m[2][1]=0;
        m[2][2]=1;
        m[2][3]=1;
        m[3][0]=0;
        m[3][1]=1;
        m[3][2]=2;
        m[3][3]=1;
        mul(n);
        printf("%I64d\n",ans[0]);
    }
    return 0;
}
/*
*/
